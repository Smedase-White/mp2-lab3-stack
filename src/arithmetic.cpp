#include "arithmetic.h"

Parser::Parser()
{
	state = afterBracket;
	num = 0;
}

bool Parser::creator(char symb)
{
	if ((symb >= '0') && (symb <= '9'))
	{
		state = number;
		num = num * 10 + (symb - '0');
		return true;
	}
	else
	{
		if (state == afterBracket)
		{
			switch (symb)
			{
			case '(':
				state = afterBracket;
				obj = new Bracket(true);
				break;
			case ')':
				state = ready;
				obj = new Bracket(false);
				break;
			default:
				state = ready;
				obj = new Number(num);
				return false;
				break;
			}
			return true;
		}
		if (state == number)
		{
			state = ready;
			obj = new Number(num);
			num = 0;
			return false;
		}
		else
		{
			switch (symb)
			{
			case '(':
				state = afterBracket;
				obj = new Bracket(true);
				break;
			case ')':
				obj = new Bracket(false);
				break;
			default:
				obj = new Operation(symb);
				break;
			}
			return true;
		}
	}
}

State Parser::getState()
{
	return state;
}

Object* Parser::getObject()
{
	return obj;
}



Calculator::Calculator()
{
	step = wait;
	obj = new Queue<Object*>;
}

Calculator::~Calculator()
{
	delete obj;
}

void Calculator::parseString(string s)
{
	Parser p;
	for (int i = 0; i < s.size(); i++)
	{
		if (!(s[i] == ' '))
		{
			if (!p.creator(s[i]))
				i--;
			if (p.getState() != number)
			{
				Object* a = p.getObject();
				(*obj).push(a);
			}
		}
	}
	if (p.getState() == number)
	{
		p.creator('.');
		Object* a = p.getObject();
		(*obj).push(a);
	}
}

Calculator::Calculator(string s)
{
	step = afterLex;
	obj = new Queue<Object*>;

	parseString(s);
}

Calculator::Calculator(const Calculator& s)
{
	step = s.step;
	obj = new Queue<Object*>(s.getExpression());
}

void Calculator::addExpression(string s)
{
	Object* a;
	while (!(*obj).isEmpty())
	{
		a = (*obj).pop();
		delete a;
	}
	parseString(s);
	step = afterLex;
}

bool correct(Queue<Object*> q1)
{
	bool b = true;
	Stack<Object*> par;
	Object* a = q1.pop();
	Types t = a->getType();
	if (t == tBrackets)
	{
		b = a->getSomething();
		if (b == 0)
			throw logic_error("Invalid position of the bracket!");
		par.push(a);
	}
	while (!q1.isEmpty())
	{
		a = q1.pop();
		switch (a->getType())
		{
		case tNumber:
			if (t == tBrackets)
			{
				if (b == false)
					throw logic_error("Number after closed bracket!");
			}
			t = tNumber;
			break;
		case tOperation:
			if (t == tOperation)
				throw logic_error("Multiple operations in a row!");
			if ((char)a->getSomething(1) != '-')
				if (t == tBrackets)
					if (b == true)
						throw logic_error("Operation after opened bracket!");
			t = tOperation;
			break;
		case tBrackets:
			b = a->getSomething();
			if (b == 0)
			{
				if (par.isEmpty())
					throw logic_error("Invalid number of bracket!");
				par.pop();
			}
			else
			{
				par.push(a);
			}
			t = tBrackets;
			break;
		}

	}
	if (!par.isEmpty())
		throw logic_error("Invalid number of bracket!");
	return true;
}

void Calculator::nextStep()
{
	switch (step)
	{
	case wait:
		return;
		break;
	case afterLex:
	{
		correct((*obj));
		Queue<Object*> temp;
		Stack<Object*> stack;
		Object* a;
		Object* b;
		while (!(*obj).isEmpty())
		{
			a = (*obj).pop();
			switch (a->getType())
			{
			case tNumber:
				temp.push(a);
				break;
			case tOperation:
				if (stack.isEmpty())
				{
					stack.push(a);
				}
				else
				{
					b = stack.pop();
					int pr1 = a->getSomething(), pr2 = b->getSomething();
					if (stack.isEmpty())
					{
						if (pr2 >= pr1)
						{
							if (b->getType() == tOperation)
								temp.push(b);
							else
								delete b;
						}
						else
						{
							stack.push(b);
						}
					}
					else
					{
						while ((pr2 >= pr1) && (!stack.isEmpty()))
						{
							if (b->getType() == tOperation)
								temp.push(b);
							else
								delete b;
							b = stack.pop();
							pr2 = b->getSomething();
						}
						if (pr2 < pr1)
							stack.push(b);
						else
							temp.push(b);
					}
					stack.push(a);
				}
				break;
			case tBrackets:
				if (a->getSomething() == 1)
					stack.push(a);
				else
				{
					b = stack.pop();
					while ((b->getType() == tOperation) && (!stack.isEmpty()))
					{
						temp.push(b);
						b = stack.pop();
					}
					if (b->getType() == tOperation)
						temp.push(b);
					else
						delete b;
				}
				break;
			}
		}
		while (!stack.isEmpty())
		{
			a = stack.pop();
			temp.push(a);
		}
		(*obj) = temp;
		step = afterSynt;
		break;
	}
	case afterSynt:
	{
		Stack<Object*> stack;
		Object* a;
		Object* b;
		int n1, n2;
		while (!(*obj).isEmpty())
		{
			a = (*obj).pop();
			switch (a->getType())
			{
			case tNumber:
				stack.push(a);
				break;
			case tOperation:
				b = stack.pop();
				n1 = b->getSomething();
				delete b;
				b = stack.pop();
				n2 = b->getSomething();
				delete b;
				b = new Number(a->getSomething(n2, n1));
				stack.push(b);
				delete a;
				break;
			}
		}
		step = answer;
		b = stack.pop();
		obj->push(b);
		break;
	}
	case answer:
		return;
		break;
	default:
		break;
	}
}

int Calculator::getAnswer()
{
	if (step == wait) return 0;
	while (step != answer)
		nextStep();
	Object* a = (*obj).pop();
	(*obj).push(a);
	return a->getSomething();
}

int Calculator::getAnswer(string s)
{
	Object* a;
	while (!(*obj).isEmpty())
	{
		a = (*obj).pop();
		delete a;
	}
	parseString(s);
	step = afterLex;
	while (step != answer)
		nextStep();
	a = (*obj).pop();
	(*obj).push(a);
	return a->getSomething();
}

Queue<Object*> Calculator::getExpression() const
{
	Queue<Object*> copy(*obj);
	Queue<Object*> temp;
	Object* a;
	Object* b;
	while (!(copy.isEmpty()))
	{
		a = copy.pop();
		switch (a->getType())
		{
		case tNumber:
			b = new Number(a->getSomething());
			break;
		case tOperation:
			b = new Operation(a->getSomething(0));
			break;
		case tBrackets:
			b = new Bracket(a->getSomething());
			break;
		default:
			break;
		}
		temp.push(b);
	}
	return temp;
}

void Calculator::printExpression()
{
	Queue<Object*> copy(*obj);
	Object* ob;
	while (!(copy.isEmpty()))
	{
		ob = copy.pop();
		switch (ob->getType())
		{
		case tNumber:
			cout << (Number)(*ob);
			break;
		case tOperation:
			cout << (Operation)(*ob);
			break;
		case tBrackets:
			cout << (Bracket)(*ob);
			break;
		default:
			break;
		}
	}
	cout << endl;
}

string Calculator::getString()
{
	string s;
	Queue<Object*> copy(*obj);
	while (!copy.isEmpty())
		s += copy.pop()->getString();
	return s;
}