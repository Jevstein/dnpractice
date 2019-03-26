/**
 * single_pc_ring_buffer.h
 *
 * single producer and consumer ring buffer
*/

#ifndef _SINGLE_PC_RING_BUFFER_H_
#define _SINGLE_PC_RING_BUFFER_H_

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>

template<typename NODE>
class single_pc_ring_buffer
{
public:
	single_pc_ring_buffer(uint32_t queue_size);
	~single_pc_ring_buffer();
	bool enqueue(const NODE& in);
	bool dequeue(NODE& out);
	//uint32_t get_item_count();
private:
	single_pc_ring_buffer(const single_pc_ring_buffer& rsh);
	single_pc_ring_buffer& operator=(const single_pc_ring_buffer& rsh);

private:
	uint32_t m_head;
	// char _pad_1[64];
	uint32_t m_tail;
	// char _pad_2[64];
	uint32_t m_size;
	NODE* m_data;
};

//-----------------------------------------------------------------------------

template<typename NODE>
single_pc_ring_buffer<NODE>::single_pc_ring_buffer(uint32_t queue_size)
	:m_head(0)
	,m_tail(0)
	,m_size(queue_size)
	,m_data(NULL)
{
	m_data = new NODE[queue_size];
	memset(m_data, 0, sizeof(NODE)*queue_size);
}

template<typename NODE>
single_pc_ring_buffer<NODE>::~single_pc_ring_buffer()
{
	if (NULL!=m_data)
	{
		delete[] m_data;
		m_data = NULL;
	}
}

template<typename NODE>
bool single_pc_ring_buffer<NODE>::enqueue(const NODE& in)
{
	uint32_t next = (m_tail+1) % m_size;
	if (next==m_head)
	{
		return false;
	}
	m_data[m_tail] = in;
	m_tail = next;
	return true;
}

template<typename NODE>
bool single_pc_ring_buffer<NODE>::dequeue(NODE& out)
{
	if (m_head==m_tail)
	{
		return false;
	}
	out = m_data[m_head];
	m_head = (m_head + 1) % m_size;
	return true;
}

#endif
