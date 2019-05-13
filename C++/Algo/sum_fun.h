/*
Write a program that outputs all possibilities to put + or -or nothing 
between the numbers 1, 2, ..., 9 (in this order) such that the result 
is always 100. For example : 1 + 2 + 34 – 5 + 67 – 8 + 9 = 100.
*/
#pragma once
#include <iostream>
#include <string>

using namespace std;

void func(string str, int subtotal, char oper, int operand2, int next_num)
{
	int total;

	switch (oper)
	{
	case '+': total = subtotal + operand2; break;
	case '-': total = subtotal - operand2; break;
	}

	if (next_num == 10)
	{
		if (total == 100)
		{
			cout << (str + oper + to_string(operand2)) << endl;
		}
		return;
	}

	func(str + oper + to_string(operand2), total, '+', next_num, next_num + 1);
	func(str + oper + to_string(operand2), total, '-', next_num, next_num + 1);
	func(str, subtotal, oper, (operand2 * 10) + next_num, next_num + 1);
}

int main_func()
{
	func("0", 0, '+', 1, 2);
	return 0;
}
