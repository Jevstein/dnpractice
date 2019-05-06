
#ifndef NS_ZOOKEEPER_SERVICE_H_
#define NS_ZOOKEEPER_SERVICE_H_

#include "glo_def.h"

#include <zookeeper/zookeeper.h>
#include <string>
#include <ace/Singleton.h>
#include <set>


class CZooKeeperService
{
    friend class ACE_Singleton<CZooKeeperService, ACE_Recursive_Thread_Mutex>;
public :
	BOOL zks_init(const std::string& ip, u16 port);
	BOOL zks_get_bcs(std::string& ip, u16& port);
    void zks_close();
	u32 get_msg_serial_number();
	~CZooKeeperService();
	static void watcher(zhandle_t *zh, int type, int state, const char *path,void *watcherCtx);
	static void BCSNodeChildrenWatcher(zhandle_t *zh, const char* path);
	void addInvaildBCSNode(std::string& nodeAddr); // ip:port
protected :
	CZooKeeperService();
	BOOL removeNode(const std::string& path);
	
private :
	zhandle_t* handle_;
	static BOOL connected_;
	u32 msgSN_;
	const i32 ZK_MAX_CONNECTED_TIMES;
	static std::set<std::string> invaild_bcs_node_set;
	static pthread_mutex_t m_invaild_bcs_nodes_Lock;
};

typedef ACE_Singleton<CZooKeeperService, ACE_Recursive_Thread_Mutex> g_zks_;
#define zookeeperSvr_ g_zks_::instance()

#endif

