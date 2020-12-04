#include <iostream>
#include <string>
#include "arithmetic.h"

using namespace std;

int main()
{
	try
	{
		string s;
		getline(cin, s);

		Calculator calc(s);
		calc.printExpression();
		calc.nextStep();
		calc.printExpression();
		calc.nextStep();
		calc.printExpression();
	}
	catch (const logic_error a)
	{
		cout << a.what() << endl;
	}
	return 0;
}