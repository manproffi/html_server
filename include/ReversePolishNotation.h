#ifndef REVERSEPOLISHNOTATION_H
#define REVERSEPOLISHNOTATION_H

#include <functional>
#include <iostream>
#include <stack>
#include <map>
#include <queue>

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

private:
	std::string m_input_data;
	std::stack<char> stBuf;
	std::stack<int> stOutput;
	std::queue<std::string> quOutput;
	static const std::map<char, int> m_operation_priority;
	std::map<char, std::function<void (int&, int&)>> m_operation;
};

#endif // REVERSEPOLISHNOTATION_H
