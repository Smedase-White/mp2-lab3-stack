#pragma once
template <class TC>
class VOp
{
	int priority;
	char symbol;
public:
	virtual TC doOp(TC first, TC second) = 0;
	void setPriority(int p)
	{
		priority = p;
	}
	int getPriority()
	{
		return priority;
	}
	void setSymbol(char s)
	{
		symbol = s;
	}
	int getSymbol()
	{
		return symbol;
	}
};

template <class TC>
class Add : public VOp<TC>
{
public:
	Add()
	{
		VOp<TC>::setPriority(2);
		VOp<TC>::setSymbol('+');
	}
	TC doOp(const TC first, const TC second)
	{
		return first + second;
	}
};

template <class TC>
class Sub : public VOp<TC>
{
public:
	Sub()
	{
		VOp<TC>::setPriority(2);
		VOp<TC>::setSymbol('-');
	}
	TC doOp(const TC first, const TC second)
	{
		return first - second;
	}
};

template <class TC>
class Mul : public VOp<TC>
{
public:
	Mul()
	{
		VOp<TC>::setPriority(3);
		VOp<TC>::setSymbol('*');
	}
	TC doOp(const TC first, const TC second)
	{
		return first * second;
	}
};

template <class TC>
class Div : public VOp<TC>
{
public:
	Div()
	{
		VOp<TC>::setPriority(3);
		VOp<TC>::setSymbol('/');
	}
	TC doOp(const TC first, const TC second)
	{
		return first / second;
	}
};