
#include <gtest/gtest.h>
#include <iostream>
#include "ReversePolishNotation.h"

TEST(ProcessTest, INputToRPN1)
{
	ReversePolishNotation rpn("1234*23+456+38*(5+10)");
	rpn.process();
	std::string res;
	while (!rpn.quOutput.empty())
	{
		res += rpn.quOutput.front() + " ";
		rpn.quOutput.pop();
	}
	ASSERT_EQ ("1234 23 * 456 + 38 5 10 + * + ", res);
}

TEST(ProcessTest, INputToRPN2)
{
	ReversePolishNotation rpn("465987*23+456/20*(100+10)");
	rpn.process();
	std::string res;
	while (!rpn.quOutput.empty())
	{
		res += rpn.quOutput.front() + " ";
		rpn.quOutput.pop();
	}
	ASSERT_EQ ("465987 23 * 456 20 / 100 10 + * + ", res);
}

TEST(CalculationRPN, Output1)
{
	ReversePolishNotation rpn("1234*23+456+38*(5+10)");
	rpn.process();
	ASSERT_EQ(29408, rpn.calculationRPN());
}

TEST(CalculationRPN, Output2)
{
	ReversePolishNotation rpn("465987*23+1000/20*(100+10)");
	rpn.process();
	ASSERT_EQ(10723201, rpn.calculationRPN());
}

TEST(InputTest, OverflowInt)
{
	ReversePolishNotation rpn("2147483648*23+1000/20*(100+10)");
	ASSERT_THROW(rpn.process(), const char *);
}

TEST(CalculationTest, DivisionBy0)
{
	ReversePolishNotation rpn("200+1000/0");
	rpn.process();
	ASSERT_THROW(rpn.calculationRPN(), const char *);
}

TEST(CalculationTest, RemainderBy0)
{
	ReversePolishNotation rpn("200+1000%0");
	rpn.process();
	ASSERT_THROW(rpn.calculationRPN(), const char *);
}

TEST(CalculationTest, OverMultiplication)
{
	ReversePolishNotation rpn("10-2147483647*2");
	rpn.process();
	ASSERT_THROW(rpn.calculationRPN(), const char *);
}

TEST(CalculationTest, UnderMultiplication)
{
	ReversePolishNotation rpn("3+2147483647*-2147483648");
	rpn.process();
	ASSERT_THROW(rpn.calculationRPN(), const char *);
}

TEST(CalculationTest, OverAddition)
{
	ReversePolishNotation rpn("2147483647+2");
	rpn.process();
	ASSERT_THROW(rpn.calculationRPN(), const char *);
}

TEST(CalculationTest, UnderAddition)
{
	ReversePolishNotation rpn("-2147483647-2");
	rpn.process();
	ASSERT_THROW(rpn.calculationRPN(), const char *);
}

TEST(CalculationTest, OverSubstraction)
{
	ReversePolishNotation rpn("2147483647--10");
	rpn.process();
	ASSERT_THROW(rpn.calculationRPN(), const char *);
}

TEST(CalculationTest, UnderSubtraction)
{
	ReversePolishNotation rpn("-2147483647-10");
	rpn.process();
	ASSERT_THROW(rpn.calculationRPN(), const char *);
}

TEST(ValidationTest, CheckExtraCloseBracket)
{
	ReversePolishNotation rpn("20*2-(40-2))");
	ASSERT_THROW(rpn.process(), const char *);
}

TEST(ValidationTest, CheckMissingOperator)
{
	ReversePolishNotation rpn("20*2(40-2)");
	rpn.process();
	ASSERT_THROW(rpn.calculationRPN(), const char *);
}

TEST(ValidationTest, CheckExtraOpenBracket)
{
	ReversePolishNotation rpn("20*2+((40-2)");
	ASSERT_THROW(rpn.process(), const char *);
}

TEST(CalculationTest, IncorrectNumber)
{
	ReversePolishNotation rpn("2147a483+10");
	ASSERT_THROW(rpn.process(), const char *);
}
