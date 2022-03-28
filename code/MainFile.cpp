#include <iostream>
#include <algorithm> 
#include <string>
#include <cstring>
#include <regex>
using namespace std;

int TwoOperators(string str, int size);
bool op_index(string operation, int size1);
void simplify_fraction(int num, int denom);
void decimalToFraction(double number);
int is_valid(string operation, int size1);
int Find_operator(string str, int size);
int main()
{
	string operation;

	while (operation != "exit")
	{
		//initilization
		int plus = 0, minus = 0, division = 0, multiplication = 0;
		int num1 = 0, num2 = 0, num3 = 0, num4 = 0, w = 0;
		float result = .0;
		int s = 0;
		//string operation;
		//input
		cout << "Please enter a rational number operations (or exit): " << endl;
		std::getline(cin, operation);
		if (operation == "exit")
		{
			cout << "Thank you for using rational number calculator." << endl;
			break;
		}
		auto iter = remove(operation.begin(), operation.end(), ' ');
		operation.erase(iter, operation.end());
		int size1 = operation.length();
		//check if is_valid
		is_valid(operation, size1);
		//-----------------------------------------------
		//main body
		if (s == 1)
		{
			std::cout << "Invalid operation." << std::endl;
		}
		else if (s == 0)
		{
			//how many numbers
			//GetNumbers(operation, size1);
			//--------------------------------------------

			num1 = stoi(operation, nullptr, 10);
			int x1 = Find_operator(operation, size1);
			int length1 = (size1 - x1) - 1;
			TwoOperators(operation, size1);
			if (w == 1)
			{
				x1 += 1;
			}
			string str1 = operation.substr((x1 + 1), length1);
			num2 = stoi(str1, nullptr, 10);
			int x2 = Find_operator(str1, length1);
			if (x2 != -1)
			{
				int length2 = ((length1)-x2) - 1;
				TwoOperators(str1, length1);
				if (w == 1)
				{
					x2 += 1;
				}
				string str2 = str1.substr((x2 + 1), length2);
				num3 = stoi(str2, nullptr, 10);
				int x3 = Find_operator(str2, length2);
				if (x3 != -1)
				{
					int length3 = (length2 - x3) - 1;
					TwoOperators(str2, length2);
					if (w == 1)
					{
						x3 += 1;
					}
					string str3 = str2.substr((x3 + 1), length3);
					num4 = stoi(str3, nullptr, 10);
				}
				else if (x3 == -1)
				{
					num4 = 0;
				}
			}
			else if (x2 == -1)
			{
				num3 = 0;
				num4 = 0;
			}
			for (int i = 0; i < size1; i++)
			{
				if (operation[i] == '+')
				{
					plus += 1;
				}
				else if (operation[i] == '-')
				{
					minus += 1;
				}
				else if (operation[i] == '/')
				{
					division += 1;
				}
				else if (operation[i] == '*')
				{
					multiplication += 1;
				}
			}
			if (num1 != 0 && num2 != 0 && num3 != 0 && num4 != 0)
			{
				if (division == 3)
				{
					result = ((float)num1 / num2) / ((float)num3 / num4);
				}
				else if (plus == 1)
				{
					result = ((float)num1 / num2) + ((float)num3 / num4);
				}
				else if (minus == 1)
				{
					result = ((float)num1 / num2) - ((float)num3 / num4);
				}
				else if (multiplication == 1)
				{
					result = ((float)num1 / num2) * ((float)num3 / num4);
				}
			}
			else if (num1 != 0 && num2 != 0 && num3 == 0 && num4 == 0)
			{
				if (minus == 2)
				{
					num2 = num3;
				}
				if (division == 1)
				{
					result = ((float)num1 / num2);
				}
				else if (plus == 1)
				{
					result = (num1 + num2);
				}
				else if (minus == 1)
				{
					result = (num1 - num2);
				}
				else if (multiplication == 1)
				{
					result = (num1 * num2);
				}
			}
			else if (division == 2)
			{
				result = ((float)num1 / num2) / num3;
			}
			else if (division == 1)
			{
				bool check_case = op_index(operation, size1);
				if (!check_case)
				{
					if (plus == 1)
					{
						result = num1 + ((float)num2 / num3);
					}
					else if (minus == 1)
					{
						result = num1 - ((float)num2 / num3);
					}
					else if (multiplication == 1)
					{
						result = num1 * (float)(num2 / num3);
					}
				}
				else if (check_case)
				{
					if (plus == 1)
					{
						result = ((float)num1 / num2) + num3;
					}
					else if (minus == 1)
					{
						result = ((float)num1 / num2) - num3;
					}
					if (multiplication == 1)
					{
						result = ((float)num1 / num2) * num3;
					}
				}
			}
			decimalToFraction(result);
			cout << endl;
		}
	}
}
int Find_operator(string str, int size)
{
	int x = -1;
	for (int i = 0; i < size; i++)
	{
		if (str[i] == '/')
		{
			x = str.find('/');
			break;
		}
		else if (str[i] == '*')
		{
			x = str.find('*');
			break;
		}
		else if (str[i] == '+')
		{
			x = str.find('+');
			break;
		}
		else if (str[i] == '-')
		{
			x = str.find('-');
			if (x == 0)
			{
				continue;
			}
			else
			{
				break;
			}

		}
	}
	return x;
}

int TwoOperators(string str, int size)
{
	int w = 0;
	for (int i = 0; i < size; i++)
	{
		if ((str[i] == '-') && (i != 0))
		{
			if ((str[i + 1] == '+') || (str[i + 1] == '-') || (str[i + 1] == '*') || (str[i + 1] == '/'))
			{
				w = 1;
			}
		}
	}
	return w;
}


int is_valid(string operation, int size1)
{
	int s = 0;
	for (int i = 0; i < size1; i++)
	{
		if (isalpha(operation[i]))
		{
			s = 1;
			break;
		}
	}
	return s;
}
void decimalToFraction(double number)
{
	if (floor(number) == ceil(number))
	{
		cout << "result = " << number;
	}
	else
	{
		double fractional_part = number - floor(number);

		for (double i = 0.1, j = 10; ; i /= 10, j *= 10)
		{
			if (fractional_part >= i)
			{
				simplify_fraction(number * j, j);
				break;
			}
		}
	}
}

void simplify_fraction(int num, int denom)
{
	for (int i = denom; i >= 2; i--)
	{
		if (num % i == 0 && denom % i == 0)
		{
			num = num / i;
			denom = denom / i;
		}
	}
	cout << "Result = ";
	if (denom == 1)
		cout << num;
	else
		cout << num << "/" << denom;
	cout << endl;
}

bool op_index(string operation, int size1)
{
	bool F = false;
	int z = operation.find('/');
	for (int i = 0; i < size1; i++)
	{
		if (operation[i] == '+')
		{
			int v = operation.find('+');
			if (v > z)
			{
				F = true;
				break;
			}
		}
		else if (operation[i] == '-')
		{
			int v = operation.find('-');
			if (v > z)
			{
				F = true;
				break;
			}
		}
		if (operation[i] == '*')
		{
			int v = operation.find('*');
			if (v > z)
			{
				F = true;
				break;
			}
		}
	}
	return F;
}