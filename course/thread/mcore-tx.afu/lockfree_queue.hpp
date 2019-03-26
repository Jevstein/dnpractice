/**
 * flqueue.h
 * homepage: http://www.emadar.com/fpc/lockfree.htm
 * pascal code: http://www.emadar.com/fpc/flqueue.pas
 * author: Dariusz Mazur
 * ahfu translate pascal to c++
*/

#ifndef _FL_QUEUE_H_
#define _FL_QUEUE_H_

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>

template<typename NODE>
class flqueue
{
public:
	flqueue(uint32_t queue_size);
	~flqueue();
	bool enqueue(const NODE& in);
	bool dequeue(NODE& out);
	//uint32_t get_item_count();
private:
	flqueue(const flqueue& rsh);
	flqueue& operator=(const flqueue& rsh);
//-----------------------------------------------------------------------------
protected:

private:
	uint32_t m_head;
	uint32_t m_tail;
	uint32_t m_seq;   //入队的位置
	uint32_t m_size;
	NODE* m_data;
};

template<typename NODE>
flqueue<NODE>::flqueue(uint32_t queue_size)
	:m_head(0)
	,m_tail(0)
	,m_seq(0)
	,m_size(queue_size)
	,m_data(NULL)
{
	m_data = new NODE[queue_size];
	memset(m_data, 0, sizeof(NODE)*queue_size);
}

template<typename NODE>
flqueue<NODE>::~flqueue()
{
	if (NULL!=m_data)
	{
		delete[] m_data;
		m_data = NULL;
	}
}

#ifndef MAX_TEST_NUM
#define MAX_TEST_NUM 10000000
#endif

template<typename NODE>
bool flqueue<NODE>::enqueue(const NODE& in)
{
	if (m_head==((m_tail+1)%m_size))  //check queue is full
	{
		return false;
	}
	uint32_t loc = __sync_add_and_fetch(&m_seq, 1);
	uint32_t last_tail = loc - 1;
	m_data[last_tail%m_size] = in;
#ifndef NDEBUG	
	int i = 0;
#endif	
	do
	{
#ifndef NDEBUG	
		++i;
		assert(i<MAX_TEST_NUM);
#endif	
	} while(!__sync_bool_compare_and_swap(&m_tail, last_tail, loc));
        //尝试修改m_tail的时候，其他线程无法修改m_tail;  因为这里不修改，m_tail不增加，其他线程尝试修改一定是失败的
	return true;
}

template<typename NODE>
bool flqueue<NODE>::dequeue(NODE& out)
{
	uint32_t last_head;
#ifndef NDEBUG	
	int i = 0;
#endif	
	do
	{
#ifndef NDEBUG	
		++i;
		assert(i<MAX_TEST_NUM);
#endif	
		last_head = m_head;
		if (m_tail==m_head)  //queue is empty
		{
			return false;
		}
	} while(!__sync_bool_compare_and_swap(&m_head, last_head, last_head+1));
	out = m_data[last_head%m_size];
	return true;
}

#endif
