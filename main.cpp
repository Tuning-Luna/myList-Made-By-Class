#include <iostream>
#include<cassert>
using std::cout;
using std::endl;
using std::swap;
const int MAX_SIZE = 100;
class Node
{
public:
	int _data;
	//用头结点的数据存储元素个数
	Node* _next;
	Node* _tailNode;

public:
	Node()
	{
		_next = nullptr;
		_data = 0;
		_tailNode = nullptr;
	}

	~Node() {}

	//拷贝构造
	Node(Node* l)
	{
		this->clear();
		Node* p = l;
		Node* q = this;
		this->_data = l->_data;

		while (p->_next != nullptr)
		{
			Node* temp = new Node;
			temp->_data = p->_next->_data;
			q->_next = temp;
			q = q->_next;
			p = p->_next;
			q->_next = nullptr;
		}
		this->_tailNode = q;
	}

	//头插
	void pushFront(int elem)
	{
		assert(this->_data < MAX_SIZE);

		Node* p = new Node;
		p->_data = elem;

		assert(p != nullptr);

		if (this->_data == 0)//空链表
		{
			this->_next = p;
			p->_next = nullptr;
			this->_tailNode = p;
		}
		else
		{
			Node* temp = this;
			assert(temp != nullptr);
			p->_next = temp->_next;
			this->_next = p;
		}
		++this->_data;
	}

	//尾插
	void pushBack(int elem)
	{
		assert(this->_data < MAX_SIZE);

		if (this->_data == 0)//空链表
		{
			this->pushFront(elem);
			return;
		}
		else
		{
			Node* p = new Node;
			assert(p != nullptr);
			p->_data = elem;

			this->_tailNode->_next = p;
			p->_next = nullptr;
			this->_tailNode = p;
		}
		++this->_data;
	}

	//按下标插
	void insert(int pos, int elem)
	{
		if (this->_data == 0)
		{
			this->pushFront(elem);
			return;
		}
		else
		{
			int i = 0;
			Node* p = this;
			while (p != nullptr && pos != i)
			{
				p = p->_next;
				++i;
			}
			if (p == nullptr)
			{
				cout << "插入位置不合法！" << endl;
				assert(0);
			}
			else
			{
				Node* q = new Node;
				assert(q != nullptr);
				q->_data = elem;
				q->_next = p->_next;
				p->_next = q;
				if (this->_tailNode->_next != nullptr)
				{
					this->_tailNode = q;
				}
				++this->_data;
			}

		}
	}

	//头删
	void popFront()
	{
		if (this->empty())
		{
			cout << "已经是空链表，无法删除！" << endl;
			assert(0);
		}
		Node* temp = this->_next;
		this->_next = this->_next->_next;
		delete temp;
		--this->_data;
		if (this->_data == 0)
		{
			this->_next = nullptr;
			this->_tailNode = nullptr;
		}
	}

	//尾删
	void popBack()
	{
		if (this->empty())
		{
			cout << "已经是空链表，无法删除！" << endl;
			assert(0);
		}
		else if (this->_data == 1)
		{
			this->popFront();
			return;
		}
		else
		{
			Node* p = this;
			assert(p != nullptr);

			while (p->_next != this->_tailNode)
			{
				p = p->_next;
			}
			delete this->_tailNode;
			this->_tailNode = p;
			this->_tailNode->_next = nullptr;
			--this->_data;
		}

	}

	//按下标删
	void erase(int pos)
	{
		//给出下标，删除元素
		if (this->empty())
		{
			cout << "链表为空，无法删除！" << endl;
			assert(0);
		}
		else if (pos >= this->_data)
		{
			cout << "删除位置不合法！" << endl;
			assert(0);
		}
		else
		{
			int i = 0;
			Node* p = this;
			assert(p != nullptr);
			while (p != nullptr && i < pos)
			{
				p = p->_next;
				++i;
			}
			if (p == nullptr)
			{
				cout << "删除位置不合法！" << endl;
				assert(0);
			}
			if (p->_next == this->_tailNode)
			{
				this->popBack();
				return;
			}
			else
			{
				Node* temp = p->_next;
				p->_next = temp->_next;
				delete temp;
				--this->_data;
			}
		}
	}

	//输入元素，查找下标
	int find(int elem)
	{
		//输入元素，返回下标.
		//如果有多个相同，则返回第一个
		//如果没找到，返回-1
		Node* p = this;
		int i = 0;
		while (p->_next != nullptr)
		{
			if (p->_next->_data == elem)
				return i;
			++i;
			p = p->_next;
		}
		return (-1);
	}

	//重载赋值运算符
	Node* operator=(Node*& l)
	{
		this->clear();
		Node* p = l;
		Node* q = this;
		this->_data = l->_data;

		while (p->_next != nullptr)
		{
			Node* temp = new Node;
			temp->_data = p->_next->_data;
			q->_next = temp;
			q = q->_next;
			p = p->_next;
			q->_next = nullptr;
		}
		this->_tailNode = q;
		return this;
	}

	//交换两个容器
	void swapList(Node* l)
	{
		swap(this->_data, l->_data);
		Node* temp = l->_next;
		l->_next = this->_next;
		this->_next = temp;
		swap(this->_tailNode, l->_tailNode);
	}

	//指定大小
	void resize(int num, int elem = 0)
	{
		//num小于长度，删除多余
		//num大于长度，用elem（缺省0）填充到尾部
		if (num < this->_data)
		{
			int i = this->_data - num;
			while (i--)
				this->popBack();
		}
		else
		{
			int i = num - this->_data;
			while (i--)
				this->pushBack(elem);
		}
	}

	//输入元素，移除目标元素结点
	void remove(int elem)
	{
		//移除所有和elem相同的元素
		Node* p = this;
		while (p->_next != nullptr)
		{
			if (p->_next->_data == elem)
			{
				Node* temp = p->_next;
				p->_next = temp->_next;
				delete temp;
				--this->_data;
			}
			else
			{
				p = p->_next;
			}
		}
	}

	//反转
	void reverse()
	{
		if (this->_data == 0 || this->_data == 1)
			return;

		Node* prev = nullptr;
		Node* current = this->_next;
		Node* next = nullptr;

		this->_tailNode = current;//更新尾结点

		while (current != nullptr)
		{
			next = current->_next;
			current->_next = prev;
			prev = current;
			current = next;
		}
		this->_next = prev;//更新头结点
	}

	//排序（默认从小到大）
	void sort()
	{
		//默认从小到大排序
		if (this->_data == 0 || this->_data == 1)
			return;
		Node* p = this->_next;
		Node* q = nullptr;
		while (p != nullptr)
		{
			q = p->_next;
			while (q != nullptr)
			{
				if (p->_data > q->_data)
					swap(p->_data, q->_data);
				q = q->_next;
			}
			p = p->_next;
		}
	}

	//打印元素及其个数
	void printList()const
	{
		if (this->empty())
		{
			cout << "空链表" << endl;
			return;
		}
		Node* p = this->_next;
		cout << "元素个数：" << this->_data << endl;
		int cnt = 0;
		while (p != nullptr)
		{
			cout << p->_data << "\t";
			p = p->_next;
			++cnt;
			if (cnt % 5 == 0)
				cout << endl;
		}
		cout << endl;
	}

	//返回第一个元素
	int front()const
	{
		return this->_next->_data;
	}

	//返回最后一个元素
	int back()const
	{
		return this->_tailNode->_data;
	}

	//是否为空
	bool empty()const
	{
		return (this->_data == 0);
	}

	//返回目前大小
	int size()const
	{
		return this->_data;
	}

	//销毁
	void clear()
	{
		Node* p = this;
		Node* temp = nullptr;
		while (p->_next != nullptr)
		{
			temp = p;
			p = p->_next;
			delete temp;
		}
		this->_next = nullptr;
		this->_tailNode = nullptr;
		this->_data = 0;
	}
};

typedef Node* List;
//Node* == List
//Node* 强调是一个节点
//List 强调是链表

void test(List& L)
{
	//test here
	//***********begin************
	



	//***********end************
	L->clear();//clear
}
int main()
{
	List L = new Node;//建立一个链表
	test(L);
	return 0;
}