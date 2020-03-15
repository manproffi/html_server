#include "ReversePolishNotation.h"
#include <cctype>
#include <sstream>

ReversePolishNotation::ReversePolishNotation(std::string input) :
	m_input_data(input)
{
	m_operation =
	{
		{'+', std::bind(&ReversePolishNotation::addition, this, std::placeholders::_1, std::placeholders::_2)},
		{'-', std::bind(&ReversePolishNotation::subtraction, this, std::placeholders::_1, std::placeholders::_2)},
		{'*', std::bind(&ReversePolishNotation::multiplication, this, std::placeholders::_1, std::placeholders::_2)},
		{'/', std::bind(&ReversePolishNotation::division, this, std::placeholders::_1, std::placeholders::_2)},
		{'%', std::bind(&ReversePolishNotation::remainder, this, std::placeholders::_1, std::placeholders::_2)}
	};
}

void ReversePolishNotation::process()
{
	const char *str = m_input_data.c_str();

	for (int i = 0; i < static_cast<int>(m_input_data.size()); ++i)
	{
		if (i == 0 && (str[i] == '+' || str[i] == '-'))
		{
			getNumber(str, i);
		}
		else if (((i - 1 >= 0)
			&& (i + 1) < static_cast<int>(m_input_data.size())
			&& (str[i - 1] < 48)
			&& (str[i] == '+' || str[i] == '-')
			&& isdigit(str[i + 1]))
			|| isdigit(str[i]))
		{
			getNumber(str + i, i);
		}
		else
		{
			int priorityLevel = 0;
			try {
				priorityLevel = m_operation_priority.at(str[i]);
			} catch (const std::out_of_range& oor) {
				std::cout << "Undefined symbol: [" << str[i] << "] " << oor.what() << std::endl;
				throw "Error: Undefined symbol\n";
			}
			if (stBuf.empty() || priorityLevel > m_operation_priority.at(stBuf.top()) || str[i] == '(')
			{
				stBuf.push(str[i]);
			}
			else if (str[i] == ')') //handling close beacket
			{
				while (!stBuf.empty() && stBuf.top() != '(')
				{
					quOutput.push(std::string(1, stBuf.top()));
					stBuf.pop();
				}
				if (stBuf.empty())
					throw "Error: open bracket is missing\n";
				else
					stBuf.pop(); //delete '('
			}
			else // handling characters other than open&close bracket
			{
				while(!stBuf.empty() && priorityLevel <= m_operation_priority.at(stBuf.top()))
				{
					quOutput.push(std::string(1, stBuf.top()));
					stBuf.pop();
				}
				stBuf.push(str[i]);
			}
			
		}
	} //End for
	//move all characters to output stack
	while (!stBuf.empty())
	{
		if (stBuf.top() == '(')
			throw "Error: close bracket is missing\n";
		quOutput.push(std::string(1, stBuf.top()));
		stBuf.pop();
	}

	//print output stack
//	std::cout << "Popping out elements...";
//	while (!quOutput.empty())
//	{
//		std::cout << ' ' << quOutput.top();
//		quOutput.pop();
//	}
//	std::cout << '\n';

//	//print output stack
//	std::cout << "Popping out elements...";
//	while (!stBuf.empty())
//	{
//		std::cout << ' ' << stBuf.top();
//		stBuf.pop();
//	}
//	std::cout << '\n';
}

int ReversePolishNotation::calculationRPN()
{
	//print output stack
//		std::cout << "Popping out elements...";
//		while (!quOutput.empty())
//		{
//			std::cout << ' ' << quOutput.front();
//			quOutput.pop();
//		}
//		std::cout << '\n';

	while (!quOutput.empty())
	{
		if (quOutput.front().size() == 1 && quOutput.front().c_str()[0] < 48)
		{
			if (stOutput.size() < 2)
				throw "Error: not enough elements in stack\n";
			int tmp2 = stOutput.top();
			stOutput.pop();
			int tmp1 = stOutput.top();
			stOutput.pop();
			m_operation[quOutput.front().c_str()[0]](tmp1, tmp2);
		}
		else
		{
			stOutput.push(std::stoi(quOutput.front()));
		}
		quOutput.pop();
	}
	if (stOutput.size() == 1)
		return stOutput.top();
	else {
		throw "Error:: incorrect number of operations\n";
	}

}

void ReversePolishNotation::getNumber(const char *str, int & i)
{
	std::stringstream ss;
	try {
		int tmp = std::stoi(str);
		ss << tmp;
		quOutput.push(ss.str());
		i += (ss.str().size() - 1);
		std::cout << "Num: " << ss.str() << std::endl;
	} catch (const std::out_of_range& ) {
		std::cout << "Error: Invalid number" << std::endl;
		throw "Error: Invalid number\n";
	}
}

void ReversePolishNotation::addition(int & a, int & b)
{
//	std::cout << "addition" << std::endl;
	stOutput.push(a + b);
}

void ReversePolishNotation::subtraction(int & a, int & b)
{
//	std::cout << "subtraction" << std::endl;
	stOutput.push(a - b);
}

void ReversePolishNotation::multiplication(int & a, int & b)
{
//	std::cout << "multiplication" << std::endl;
	stOutput.push(a * b);
}

void ReversePolishNotation::division(int & a, int & b)
{
//	std::cout << "division" << std::endl;
	stOutput.push(a / b);
}

void ReversePolishNotation::remainder(int & a, int & b)
{
//	std::cout << "remainder" << std::endl;
	stOutput.push(a % b);
}

const std::map<char, int> ReversePolishNotation::m_operation_priority =
{
	{'(', 1},
	{')', 1},
	{'+', 2},
	{'-', 2},
	{'*', 3},
	{'/', 3},
	{'%', 3}
};
