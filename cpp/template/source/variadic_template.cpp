#include <stdio.h>
#include <iostream>

// Variadic template (since the C++11)
// variadic templates are templates that take a variable number of arguments.
// https://en.wikipedia.org/wiki/Variadic_template
//
// Variadic templates in C++
// https://eli.thegreenplace.net/2014/variadic-templates-in-c/
//
// C++11 - New features - Variadic templates
// http://www.cplusplus.com/articles/EhvU7k9E/
//

template<typename T>
T adder(T v) {
  return v;
}

template<typename T, typename... Args>
T adder(const T& firstArg, const Args&... args)
{
  return firstArg + adder(args...);
}

void print()
{

}

template<typename T, typename... Args>
void print(const T& firstArg, const Args&... args)
{
  std::cout << "[" << sizeof...(args) << "] " << firstArg << std::endl;
  print(args...);
}

//==============================================================================
#include <gtest/gtest.h>

TEST(VariadicTemplateTest, sum)
{
  EXPECT_EQ(38, adder(1, 2, 3, 5, 7, 9, 11));
}

TEST(VariadicTemplateTest, print)
{
  // Redirect cout calls to a stringstream
  // https://stackoverflow.com/questions/3803465/how-to-capture-stdout-stderr-with-googletest

  // This can be an ofstream as well or any other ostream
  std::stringstream buffer;

  // Save cout's buffer here
  std::streambuf *sbuf = std::cout.rdbuf();

  // Redirect cout to our stringstream buffer or any other ostream
  std::cout.rdbuf(buffer.rdbuf());

  print("hello", "variadic", "template", 2018, "year");

  // When done redirect cout to its old self
  std::cout.rdbuf(sbuf);

  std::string expectedOutput = "[4] hello\n"\
                               "[3] variadic\n"\
                               "[2] template\n"\
                               "[1] 2018\n"\
                               "[0] year\n";
  EXPECT_EQ(expectedOutput, buffer.str());
}
