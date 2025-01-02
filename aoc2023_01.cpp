#include <iostream>
#include <string>
#include <ctype.h>
#include <fstream>
#include <array>
#include <chrono>

char first_number(std::string_view s)
{
    for (int i=0; i < s.length(); ++i)
  {
        if (isdigit(s[i]))
        { 
            return s[i];
        }
  }
  std::cout << "No digits found" << "\n";
  return '0';   
}

char last_number(std::string_view s)
{
    for (int i=s.length(); i >= 0; --i)
  {
        if (isdigit(s[i]))
        { 
            return s[i];
        }
  }
  std::cout << "No digits found" << "\n";
  return '0';   
}

int concat(char x, char y)
{
  std::string a{std::string{} + x + y};
  return std::stoi(a);
}

int line_result(std::string line)
{
  return concat(first_number(line), last_number(line));
}

void part_1()
{
  std::ifstream input_1{ "input2023_01.txt "};
  if (!input_1)
  {
    std::cerr << "Uh oh, input could not be opened!\n";
  }
  int result {0};
  std::string line;
  while (std::getline(input_1, line))
  {
    int x {line_result(line)};
    std::cout << line << ' ' << x << "\n";
    result += x;
  }
  std::cout << result << "\n";
}

void replace_words(std::string& str, int first_last)
{
  int first_string_index {str.length()};
  int first_num_index {-1};
  int last_string_index {-1};
  int last_num_index {-1};
  int new_string_index {-1};
  int new_rstring_index {-1};
  constexpr std::array<std::string_view, 10> num {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
  for (int i=0; i < 10; ++i)
  {
    new_string_index = str.find(num[i]);
    new_rstring_index = str.rfind(num[i]);
    if (new_string_index == -1)
    {
      continue;
    }
    if (new_string_index < first_string_index)
    {
      first_string_index = new_string_index;
      first_num_index = i;
    }
    if (new_rstring_index > last_string_index)
    {
      last_string_index = new_rstring_index;
      last_num_index = i;
    }
  }
  if (first_num_index != -1)
  {
    if (first_last == 1)
    {
      str.replace(first_string_index, num[first_num_index].length(), std::to_string(first_num_index));
    }
    else
    {
      str.replace(last_string_index, num[last_num_index].length(), std::to_string(last_num_index));
    }
  }
}

int line_result2(std::string line, std::string liner)
{
  return concat(first_number(line), last_number(liner));
}

void part_2()
{
  std::ifstream input_1{ "input2023_01.txt "};

  if (!input_1)
  {
    std::cerr << "Uh oh, input could not be opened!\n";
  }

  int result {0};
  std::string line;
  std::string liner;
  
  while (std::getline(input_1, line))
  {
    liner = line;
    std::cout << line << " ";
    replace_words(line, 1);
    replace_words(liner, 2);
    int x {line_result2(line, liner)};
    std::cout << x << "\n";
    result += x;
  }
  std::cout << result << "\n";
}

int main()
{
  part_2();
  return 0;
}