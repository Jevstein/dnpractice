
#include "zookeeperService.h"
#include "Config.h"
#include "Logger.h"
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <algorithm>


BOOL CZooKeeperService::connected_ = FALSE;
std::set<std::string> CZooKeeperService::invaild_bcs_node_set;
pthread_mutex_t CZooKeeperService::m_invaild_bcs_nodes_Lock = PTHREAD_MUTEX_INITIALIZER;

CZooKeeperService::CZooKeeperService() : ZK_MAX_CONNECTED_TIMES(5), msgSN_(0U), handle_(NULL)
{

}

CZooKeeperService::~CZooKeeperService()
{
	pthread_mutex_destroy(&m_invaild_bcs_nodes_Lock);
}

BOOL CZooKeeperService::zks_init(const std::string& ip, u16 port)
{
    std::stringstream ss;
	ss << ip << ":" << port;
	i32 timeout = 300000;
	zoo_set_debug_level(ZOO_LOG_LEVEL_WARN);

	i32 count = 0;
	do {
        handle_ = zookeeper_init(ss.str().c_str(), watcher, timeout, 0, this, 0);
		count++;
		sleep(1);
	}while((!connected_) && (count < ZK_MAX_CONNECTED_TIMES));

	if (count >= ZK_MAX_CONNECTED_TIMES)
	{
        LOG_WARN("CZooKeeperService : init zoo keeper with host %s failed.", ss.str().c_str());
		return FALSE;
	}

	/* 在ZK服务器上创建节点服务器节点 */
	std::stringstream path;
	path << config_->get_zknssvr_path() << "/" << config_->get_zknssvr_ip() << ":" << config_->get_zknssvr_port();
	char res_path[128] = {0};

	Stat stat;  
    int isExist = -1;  
    //check exist  
    isExist = zoo_exists(handle_, path.str().c_str(), 0, &stat);  
	if (ZOK == isExist)
	{
		LOG_INFO("ns node (%s) already exist, need to recreate it.", path.str().c_str());
		if (removeNode(path.str()))
			LOG_INFO("Reomve zk node (%s) success before starting program!", path.str().c_str());
		else
		{
			LOG_INFO("Reomve zk node (%s) failed before starting program!", path.str().c_str());
			return FALSE;
		}
	}
	
	i32 ret = zoo_create(handle_, path.str().c_str(), NULL, -1, &ZOO_OPEN_ACL_UNSAFE, ZOO_EPHEMERAL, res_path, 128);
	if (ZOK == ret)
	{
        LOG_INFO("CZooKeeperService : create ns node successful with path %s.", path.str().c_str());
	}
	else
	{
        LOG_WARN("CZooKeeperService : create ns node failed with result %d", ret);
		return FALSE;
	}

	return TRUE;
}

void CZooKeeperService::watcher(zhandle_t *zh, int type, int state, const char *path,void *watcherCtx)
{
	if((ZOO_CHILD_EVENT == type) && NULL != strcasestr(path, "bcs"))
	{
		BCSNodeChildrenWatcher(zh, path);
	}
	
    CZooKeeperService* ctx = (CZooKeeperService*)watcherCtx;
    if (state == ZOO_CONNECTED_STATE) 
	{  
	    ctx->connected_ = TRUE;  
	    LOG_INFO("CZooKeeperService : watcher recved ZOO_CONNECTED_STATE notification.");  
	} 
	else if (state == ZOO_AUTH_FAILED_STATE) 
	{
	    ctx->connected_ = FALSE;
	    LOG_INFO("CZooKeeperService : watcher recved ZOO_AUTH_FAILED_STATE notification.");  
	} 
	else if (state == ZOO_EXPIRED_SESSION_STATE) 
	{
	    ctx->connected_ = FALSE;
	    LOG_INFO("CZooKeeperService : watcher recved ZOO_EXPIRED_SESSION_STATE notification.");  
	} 
	else if (state == ZOO_CONNECTING_STATE) 
	{  
	    ctx->connected_ = FALSE;
	    LOG_INFO("CZooKeeperService : watcher recved ZOO_CONNECTING_STATE notification.");	
	}
	else if (state == ZOO_ASSOCIATING_STATE) 
	{  
	    ctx->connected_ = FALSE;
	    LOG_INFO("CZooKeeperService : watcher recved ZOO_ASSOCIATING_STATE notification.");  
	}

	LOG_INFO("CZooKeeperService : called watcher function.");
}

void CZooKeeperService::zks_close()
{
    /* 在ZK服务器上删除节点服务器节点 */
	std::stringstream path;
	path << config_->get_zknssvr_path() << "/" << config_->get_zknssvr_ip() << ":" << config_->get_zknssvr_port();

	removeNode(path.str());
	
	if(NULL != handle_)
	{
		int ret = zookeeper_close(handle_);
		if ( ZOK == ret )
		{
	        LOG_INFO("CZooKeeperService : close zoo keeper success.");
		}
		else
		{
	        LOG_WARN("CZooKeeperService : close zoo keeper failed with result %d", ret);
		}
		handle_ = NULL;
	}
	connected_ = FALSE;
}

u32 CZooKeeperService::get_msg_serial_number()
{
	i32 len = sizeof(u32);
	u32 sn = 0;
	i32 ret = zoo_get(handle_, config_->get_zknssvr_path().c_str(), 1, (char*)&sn, &len, NULL);
	if (ZOK != ret)
	{
		LOG_WARN("CZooKeeperService : call zoo_get function failed with return = %d", ret);
		return 0;
	}
	else
	{
		LOG_DEBUG("CZooKeeperService : get msgSN_ = %u", sn);
	}

    (void)__sync_bool_compare_and_swap(&msgSN_, msgSN_, sn);
    (void)__sync_add_and_fetch(&msgSN_, 1);
	sn = msgSN_;
	ret = zoo_set(handle_, config_->get_zknssvr_path().c_str(), (char *)&msgSN_, sizeof(u32), -1);
	if (ZOK != ret)
	{
        LOG_WARN("CZooKeeperService call zoo_set (to set msgSN=%d) failed with return = %d", msgSN_, ret);
	}

	return sn;
}

BOOL CZooKeeperService::zks_get_bcs(std::string& ip, u16& port)
{
    if (NULL == handle_)
	{
	    LOG_WARN("CZooKeeperService : get bcs service failed since zk handle is null.");
        return FALSE;
	}
    std::stringstream path;
	path << config_->get_zkbcssvr_path();
	String_vector bcsnodes;
	i32 ret = zoo_get_children(handle_, path.str().c_str(), 1, &bcsnodes);
	if ( ZOK != ret )
	{
        LOG_WARN("CZooKeeperService : get bcs nodes failed with result %d.", ret);
		return FALSE;
	}
	
	if (bcsnodes.count <= 0)
	{
	    LOG_ERROR("CZooKeeperService : path %s has no any node.", path.str().c_str());
        return FALSE;
	}
	String_vector valid_bcs_nodes = {0, NULL};
	bool newed_flag = false;
	if (0 == invaild_bcs_node_set.size())
	{
		valid_bcs_nodes = bcsnodes;
	}
	else
	{
		valid_bcs_nodes.data = new char*[bcsnodes.count];
		newed_flag = true;
		for(int i = 0; i < bcsnodes.count; ++i)
		{

			if (invaild_bcs_node_set.end() == invaild_bcs_node_set.find(bcsnodes.data[i])) // only not in invaild_bcs_node_set can be add to vaild_bcs_nodes
			{
				++valid_bcs_nodes.count;
				valid_bcs_nodes.data[i] = bcsnodes.data[i];
			}
		}
	}

	if (!valid_bcs_nodes.count)
	{
		LOG_WARN("CZooKeeperService : no valid bcs nodes exist on zookeeper service!");
		return FALSE;
	}
	/* 产生一个0 ~ bcsnodes.count的随机数 */
	srand(time(NULL));
    i32 index = rand()%valid_bcs_nodes.count;

	/* 所有的节点名称信息是ip:port格式存储的 */
    char strip[32] = {0};
	char strport[32] = {0};
	char* colon = strchr(valid_bcs_nodes.data[index], ':');
	if (!colon)
	{
        LOG_WARN("CZooKeeperService : bcs nodes name format is invalid.");
		return FALSE;
	}

	strncpy(strip, valid_bcs_nodes.data[index], colon - valid_bcs_nodes.data[index]);
	strcpy(strport, colon + 1);

	if(newed_flag)
		delete [] valid_bcs_nodes.data;
	
    ip = std::string(strip);
	port = atoi(strport);

	LOG_DEBUG("CZooKeeperService : get bcs ip:port is %s:%d", ip.c_str(), port);
	
    return TRUE;
}

BOOL CZooKeeperService::removeNode(const std::string& path)
{
	if (NULL == handle_)
		return TRUE;
	
	i32 ret = zoo_delete(handle_, path.c_str(), -1);
	if ( ZOK == ret )
	{
        LOG_INFO("CZooKeeperService : remove ns node from zookeeper success with path %s", path.c_str());
		return TRUE;
	}
	else
	{
        LOG_WARN("CZooKeeperService : remove ns node from zookeeper failed with path %s.", path.c_str());
		return FALSE;
	}
}

void CZooKeeperService::addInvaildBCSNode(std::string& node)
{
	pthread_mutex_lock(&m_invaild_bcs_nodes_Lock); 
	invaild_bcs_node_set.insert(node);
	pthread_mutex_unlock(&m_invaild_bcs_nodes_Lock);
	
}

void CZooKeeperService::BCSNodeChildrenWatcher(zhandle_t *zh, const char* path)
{
	LOG_INFO("ZOO_CHILD_EVENT occurred. watched path:%s", path);

	String_vector bcsnodes;
	i32 ret = zoo_get_children(zh, path, 1, &bcsnodes);
	if ( ZOK != ret )
	{
	    LOG_WARN("CZooKeeperService : [watcher] get bcs nodes failed with result %d.", ret);
		return ;
	}

	if (bcsnodes.count <= 0)
	{
	    LOG_ERROR("CZooKeeperService : [watcher]path %s has no any node.", path);
		return ;
	}

	std::set<std::string> valid_bcs_nodes;
	for(int i = 0; i < bcsnodes.count; ++i)
		valid_bcs_nodes.insert(bcsnodes.data[i]);

	std::vector<std::string> set_intersection_res(invaild_bcs_node_set.size());

	std::vector<std::string>::iterator it;
  	it = std::set_intersection(valid_bcs_nodes.begin(), valid_bcs_nodes.end(), invaild_bcs_node_set.begin(), invaild_bcs_node_set.end(), set_intersection_res.begin());
  	set_intersection_res.resize(it - set_intersection_res.begin()); 
	
	pthread_mutex_lock(&m_invaild_bcs_nodes_Lock); 
	invaild_bcs_node_set.clear();
	if (!set_intersection_res.empty())
		invaild_bcs_node_set.insert(set_intersection_res.begin(), set_intersection_res.end());
	pthread_mutex_unlock(&m_invaild_bcs_nodes_Lock);
}
