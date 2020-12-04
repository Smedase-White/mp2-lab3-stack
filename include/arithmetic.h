#pragma once
#include "stack.h"
#include "objects.h"

enum State
{
	ready,
	number,
	afterBracket
};

class Parser
{
private:
	State state;
	int num;
	Object* obj;
public:
	Parser();
	bool creator(char symb);
	State getState();
	Object* getObject();
};

enum Step
{
	wait,
	afterLex,
	afterSynt,
	answer
};

class Calculator
{
private:
	Step step;
	Queue<Object*>* obj;
	void parseString(string s);
public:
	Calculator();
	~Calculator();
	Calculator(string s);
	Calculator(const Calculator& s);
	void addExpression(string s);
	void nextStep();
	int getAnswer();
	int getAnswer(string s);
	Queue<Object*> getExpression() const;
	void printExpression();
	string getString();
};