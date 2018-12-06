/*
 *  priority_test.c 
 *  priority_test
 *
 *  Created by Jevstein on 2018/12/6 16:23.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 *  https://www.cnblogs.com/imapla/p/4234258.html
 */

#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <assert.h>

static int api_get_thread_policy(pthread_attr_t *attr)
{
	int policy;
	int rs = pthread_attr_getschedpolicy(attr, &policy);
	assert(rs == 0);

	switch (policy)
	{
	case SCHED_FIFO:
		printf("policy = SCHED_FIFO\n");
		break;
	case SCHED_RR:
		printf("policy = SCHED_RR");
		break;
	case SCHED_OTHER:
		printf("policy = SCHED_OTHER\n");
		break;
	default:
		printf("policy = UNKNOWN\n");
		break;
	}
	return policy;
}

static void api_show_thread_priority(pthread_attr_t *attr, int policy)
{
	int priority = sched_get_priority_max(policy);
	assert(priority != -1);
	printf("max_priority = %d\n", priority);
	priority = sched_get_priority_min(policy);
	assert(priority != -1);
	printf("min_priority = %d\n", priority);
}

static int api_get_thread_priority(pthread_attr_t *attr)
{
	struct sched_param param;
	int rs = pthread_attr_getschedparam(attr, &param);
	assert(rs == 0);
	printf("priority = %d\n", param.__sched_priority);
	return param.__sched_priority;
}

static void api_set_thread_policy(pthread_attr_t *attr, int policy)
{
	int rs = pthread_attr_setschedpolicy(attr, policy);
	assert(rs == 0);
	api_get_thread_policy(attr);
}

int main(void)
{
	pthread_attr_t attr;       // �߳�����
	struct sched_param sched;  // ���Ȳ���
	int rs;

	/*
	* ���߳����Գ�ʼ��
	* ��ʼ������Ժ�pthread_attr_t �ṹ�������Ľṹ��
	* ���ǲ���ϵͳʵ��֧�ֵ������߳����Ե�Ĭ��ֵ
	*/
	rs = pthread_attr_init(&attr);
	assert(rs == 0);     // ��� rs ������ 0������ abort() �˳�

	/* ��õ�ǰ���Ȳ��� */
	int policy = api_get_thread_policy(&attr);

	/* ��ʾ��ǰ���Ȳ��Ե��߳����ȼ���Χ */
	printf("Show current configuration of priority\n");
	api_show_thread_priority(&attr, policy);

	/* ��ȡ SCHED_FIFO �����µ��߳����ȼ���Χ */
	printf("show SCHED_FIFO of priority\n");
	api_show_thread_priority(&attr, SCHED_FIFO);

	/* ��ȡ SCHED_RR �����µ��߳����ȼ���Χ */
	printf("show SCHED_RR of priority\n");
	api_show_thread_priority(&attr, SCHED_RR);

	/* ��ʾ��ǰ�̵߳����ȼ� */
	printf("show priority of current thread\n");
	int priority = api_get_thread_priority(&attr);

	/* �ֶ����õ��Ȳ��� */
	printf("Set thread policy\n");

	printf("set SCHED_FIFO policy\n");
	api_set_thread_policy(&attr, SCHED_FIFO);

	printf("set SCHED_RR policy\n");
	api_set_thread_policy(&attr, SCHED_RR);

	/* ��ԭ֮ǰ�Ĳ��� */
	printf("Restore current policy\n");
	api_set_thread_policy(&attr, policy);

	/*
	* ����ʼ�� pthread_attr_t �ṹ
	* ��� pthread_attr_init ��ʵ�ֶ����Զ�����ڴ�ռ��Ƕ�̬����ģ�
	* phread_attr_destory �ͻ��ͷŸ��ڴ�ռ�
	*/
	rs = pthread_attr_destroy(&attr);
	assert(rs == 0);

	return 0;
}


//compile:
// $ g++ -o ../../../bin/thread_priority thread_priority.c -lpthread