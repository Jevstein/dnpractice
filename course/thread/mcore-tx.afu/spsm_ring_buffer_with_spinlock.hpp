/**
 * single_pc_ring_buffer_l_with_spinlock.h
 * 
 * single producer and consumer ring buffer, with spinlock
*/

#ifndef _single_pc_ring_buffer_l_H_
#define _single_pc_ring_buffer_l_H_

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>

//#ifndef MAX_TEST_NUM
//#define MAX_TEST_NUM 100000
//#endif

template<typename NODE>
class single_pc_ring_buffer_l
{
public:
	single_pc_ring_buffer_l(uint32_t queue_size);
	~single_pc_ring_buffer_l();
	bool enqueue(const NODE& in);
	bool dequeue(NODE& out);
	//uint32_t get_item_count();
private:
	single_pc_ring_buffer_l(const single_pc_ring_buffer_l& rsh);
	single_pc_ring_buffer_l& operator=(const single_pc_ring_buffer_l& rsh);
protected:

private:
	uint32_t m_head;
	// char _pad_1[64];
	uint32_t m_tail;
	// char _pad_2[64];
	uint32_t m_size;
	NODE* m_data;
	pthread_spinlock_t m_enqueue;
	pthread_spinlock_t m_dequeue;
};

//-----------------------------------------------------------------------------

template<typename NODE>
single_pc_ring_buffer_l<NODE>::single_pc_ring_buffer_l(uint32_t queue_size)
	:m_head(0)
	,m_tail(0)
	,m_size(queue_size)
	,m_data(NULL)
{
	m_data = new NODE[queue_size];
	memset(m_data, 0, sizeof(NODE)*queue_size);
	pthread_spin_init(&m_enqueue, 0);
	pthread_spin_init(&m_dequeue, 0);
}

template<typename NODE>
single_pc_ring_buffer_l<NODE>::~single_pc_ring_buffer_l()
{
	if (NULL!=m_data)
	{
		delete[] m_data;
		m_data = NULL;
	}
	pthread_spin_destroy(&m_enqueue);
	pthread_spin_destroy(&m_dequeue);
}

template<typename NODE>
bool single_pc_ring_buffer_l<NODE>::enqueue(const NODE& in)
{
	pthread_spin_lock(&m_enqueue);
	uint32_t next = (m_tail+1)%m_size;
	if (next==m_head)
	{
		pthread_spin_unlock(&m_enqueue);
		return false;
	}
	m_data[m_tail] = in;
	m_tail = next;
	pthread_spin_unlock(&m_enqueue);
	return true;
}

template<typename NODE>
bool single_pc_ring_buffer_l<NODE>::dequeue(NODE& out)
{
	pthread_spin_lock(&m_dequeue);
	if (m_head==m_tail)
	{
		pthread_spin_unlock(&m_dequeue);
		return false;
	}
	out = m_data[m_head];
	m_head = (m_head + 1) % m_size;
	pthread_spin_unlock(&m_dequeue);
	return true;
}

#endif
