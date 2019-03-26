/**
 * 锁无关栈
*/
struct NodeType
{
	DataType data;
	struct NodeType* next;
};

NodeType* top = NULL;  //栈顶指针

void Push(DataType data)
{
	NodeType* node = new NodeType;
	node->data = data;
	node->next = NULL;
	while (1)
	{
		NodeType* temp = top;  //读取这个变量的值后，其他线程可能连续pop top, push something, push top，导致ABA问题
                //如果只有一个线程push，则不会有问题
               //加入一个sequence变量，每次原子累加，然后使用CAS2来交换TOP指针
		node->next = temp;
		if (CAS(&top, temp, node))
		{
			return;
		}
	}
}

bool Pop(DataType& data)
{
	while (1)
	{
		NodeType* temp = top;
		if (NULL==temp)
		{
			return false;
		}
		if (top!=temp)
		{
			continue;
		}
		NodeTupe* next = t->next;
		if (CAS(&top, temp, next))
		{
			data = temp->data;
			delete temp;  //不能直接删除，别的线程可能在访问这个节点
			return true;
		}
	}
}
//-----------------------------------------------------------------------------
#define MAX_COUNT 100
#define MAX_NODE 50
struct HPRecType
{
	NodeType* HP[MAX_COUNT];
	struct HPRecType* next;
};
HPRecType head_hp_rec;
list<NodeType*> rlist;
int rcount = 0;

void RetireNode(NodeType* node)
{
	rlish.push(node);
	rcount++;
	if (rcount>=MAX_NODE)
	{
		Scan(head_hp_rec);
	}
}

void Scan(HPRecType& head)
{
	
}