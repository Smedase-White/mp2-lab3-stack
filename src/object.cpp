#include "objects.h"
#include <string>

Number::Number(int _num)
{
	setType(tNumber);
	num = _num;
}

Number::Number(Object& o)
{
	setType(tNumber);
	num = o.getSomething();
}

int Number::getSomething()
{
	return num;
}

int Number::getSomething(const int num)
{
	return num;
}

int  Number::getSomething(const int num1, const int num2)
{
	return num;
}

ostream& operator<<(ostream& out, const Number& n)
{
	out << n.num << " ";
	return out;
}

string Number::getString()
{
	return std::to_string(getSomething());
}



Operation::Operation(char symb)
{
	setType(tOperation);
	switch (symb)
	{
	case '+': op = new Add<int>(); break;
	case '-': op = new Sub<int>(); break;
	case '*': op = new Mul<int>(); break;
	case '/': op = new Div<int>(); break;
	default: throw logic_error("Invalid operation"); break;
	}
}

Operation::Operation(Object& o)
{
	setType(tOperation);
	switch (o.getSomething(1))
	{
	case '+': op = new Add<int>(); break;
	case '-': op = new Sub<int>(); break;
	case '*': op = new Mul<int>(); break;
	case '/': op = new Div<int>(); break;
	default: throw logic_error("Invalid operation"); break;
	}
}

Operation::~Operation()
{
	delete op;
}

int Operation::getSomething()
{
	return op->getPriority();
}

int Operation::getSomething(const int num)
{
	return op->getSymbol();
}

int Operation::getSomething(const int num1, const int num2)
{
	return op->doOp(num1, num2);
}

ostream& operator<<(ostream& out, const Operation& op)
{
	out << (char)op.op->getSymbol() << " ";
	return out;
}

string Operation::getString()
{
	string s;
	s.insert(0, 1, (char)getSomething(1));
	return s;
}



Bracket::Bracket(bool _is)
{
	setType(tBrackets);
	isOpen = _is;
}

Bracket::Bracket(Object& o)
{
	setType(tBrackets);
	isOpen = o.getSomething();
}

int Bracket::getSomething()
{
	return isOpen;
}

int Bracket::getSomething(const int num)
{
	return isOpen;
}

int Bracket::getSomething(const int num1, const int num2)
{
	return isOpen;
}

ostream& operator<<(ostream& out, const Bracket& b)
{
	if (b.isOpen)
		out << "( ";
	else
		out << ") ";
	return out;
}

string Bracket::getString()
{
	if (isOpen)
		return "(";
	else
		return ")";
}
