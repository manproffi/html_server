#ifndef REVERSEPOLISHNOTATION_H
#define REVERSEPOLISHNOTATION_H

#include <functional>
#include <iostream>
#include <stack>
#include <map>
#include <queue>
#include <gtest/gtest_prod.h>
#include <limits>

class ReversePolishNotation
{
public:
	ReversePolishNotation(std::string input);
	void process();
	int calculationRPN();

private:
	void getNumber(const char * str, int & i);
	void addition(int &, int &);
	void subtraction(int &, int &);
	void multiplication(int &, int &);
	void division(int &, int &);
	void remainder(int &, int &); // %
	void checkOverUnderFlow(int64_t);

private:
	std::string m_input_data;
	std::stack<char> stBuf;
	std::stack<int> stOutput;
	std::queue<std::string> quOutput;
	static const std::map<char, int> m_operation_priority;
	std::map<char, std::function<void (int&, int&)>> m_operation;

private:
	FRIEND_TEST(ProcessTest, INputToRPN1);
	FRIEND_TEST(ProcessTest, INputToRPN2);
};

#endif // REVERSEPOLISHNOTATION_H
