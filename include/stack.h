#pragma once
const int MAX_STACK_SIZE = 1000;
const int MAX_QUEUE_SIZE = 1000;

template <class TC>
class VDynMem
{
public:
	virtual void push(const TC el) = 0;
	virtual TC pop() = 0;
	virtual bool isEmpty() const = 0;
	virtual bool isFull() const = 0;
};

template <class TC>
class Stack : public VDynMem<TC>
{
private:
	TC* mem;
	int Size;
	int hE;
public:
	Stack(int _size = MAX_STACK_SIZE) : Size(_size)
	{
		if ((_size <= 0) || (_size > MAX_STACK_SIZE)) throw std::logic_error("Invalid size stack.");
		mem = new TC[_size];
		hE = -1;
	}
	~Stack()
	{
		delete[]mem;
	}
	Stack(const Stack& s) : Size(s.Size)
	{
		hE = s.hE;
		mem = new TC[Size];
		for (int i = 0; i <= hE; i++)
			mem[i] = s.mem[i];
	}
	bool Stack::operator==(const Stack& s) const
	{
		if (Size != s.Size) return false;
		for (int i = 0; i < Size; i++)
			if (mem[i] != s.mem[i])
				return false;
		return true;
	}
	bool Stack::operator!=(const Stack& s) const
	{
		return !(this->operator==(s));
	}
	Stack& operator=(const Stack& s)
	{
		if (this == &s)
			return *this;
		if (Size != s.Size)
		{
			delete[]mem;
			mem = new TC[s.Size];
			Size = s.Size;
		}
		hE = s.hE;
		for (int i = 0; i <= hE; i++)
			mem[i] = s.mem[i];
		return *this;
	}
	void push(const TC el)
	{
		if (isFull()) throw std::logic_error("Stack is full.");
		hE++;
		mem[hE] = el;
	}
	TC pop()
	{
		if (isEmpty()) throw std::logic_error("Stack is empty.");
		hE--;
		return mem[hE + 1];
	}
	bool isEmpty() const
	{
		return hE == -1;
	}
	bool isFull() const
	{
		return hE == Size - 1;
	}
};

template <class TC>
class Queue : public VDynMem<TC>
{
private:
	TC* mem;
	int Size;
	int lE;
	int hE;
	void incL() { lE = (lE + 1) % Size; }
	void incH() { hE = (hE + 1) % Size; }
public:
	Queue(int _size = MAX_QUEUE_SIZE) : Size(_size)
	{
		if ((_size <= 1) || (_size > MAX_QUEUE_SIZE)) throw std::logic_error("Invalid size queue.");
		mem = new TC[_size];
		hE = _size - 1;
		lE = 0;
	}
	~Queue()
	{
		delete[]mem;
	}
	Queue(const Queue& q) : Size(q.Size)
	{
		lE = q.lE;
		hE = q.hE;
		mem = new TC[Size];
		for (int i = lE; i != (hE + 1) % Size; i = (i + 1) % Size)
			mem[i] = q.mem[i];
	}
	bool Queue::operator==(const Queue& q) const
	{
		if (Size != q.Size) return false;
		for (int i = 0; i < Size; i++)
			if (mem[i] != q.mem[i])
				return false;
		return true;
	}
	bool Queue::operator!=(const Queue& q) const
	{
		return !(this->operator==(q));
	}
	Queue& operator=(const Queue& q)
	{
		if (this == &q)
			return *this;
		if (Size != q.Size)
		{
			delete[]mem;
			mem = new TC[q.Size];
			Size = q.Size;
		}
		lE = q.lE;
		hE = q.hE;
		for (int i = lE; i != (hE + 1) % Size; i = (i + 1) % Size)
			mem[i] = q.mem[i];
		return *this;
	}
	void push(const TC el)
	{
		if (isFull()) throw std::logic_error("Queue is full.");
		incH();
		mem[hE] = el;
	}
	TC pop()
	{
		if (isEmpty()) throw std::logic_error("Queue is empty.");
		TC temp = mem[lE];
		incL();
		return temp;
	}
	bool isEmpty() const
	{
		return (hE + 1) % Size == lE;
	}
	bool isFull() const
	{
		return (hE + 2) % Size == lE;
	}
};