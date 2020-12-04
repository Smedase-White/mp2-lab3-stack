#pragma once
#include <iostream>
#include "operations.h"

using namespace std;

enum Types
{
	tNumber,
	tOperation,
	tBrackets
};

class Object
{
private:
	Types type;
public:
	Types getType() { return type; } //���������� ��� �������
	void setType(Types _type) { type = _type; } //������������� ��� �������
	virtual int getSomething() = 0; //���������� �����-�� ��������, ������������ ��������
	virtual int getSomething(const int num) = 0; //���������� ��������� ��������, ������������� ���������, � ������
	virtual int getSomething(const int num1, const int num2) = 0; //���������� ��������� ��������, ������������� ���������, � ����� �������
	virtual string getString() = 0;
};

class Number : public Object
{
private:
	int num;
public:
	Number(int _num);
	Number(Object& o);
	int getSomething();
	int getSomething(const int num);
	int getSomething(const int num1, const int num2);
	friend ostream& operator<<(ostream& out, const Number& n);
	string getString();
};

class Operation : public Object
{
private:
	VOp<int>* op;
public:
	Operation(char symb);
	Operation(Object& o);
	~Operation();
	int getSomething();
	int getSomething(const int num);
	int getSomething(const int num1, const int num2);
	friend ostream& operator<<(ostream& out, const Operation& op);
	string getString();
};

class Bracket : public Object
{
private:
	bool isOpen;
public:
	Bracket(bool _is);
	Bracket(Object& o);
	int getSomething();
	int getSomething(const int num);
	int getSomething(const int num1, const int num2);
	friend ostream& operator<<(ostream& out, const Bracket& b);
	string getString();
};