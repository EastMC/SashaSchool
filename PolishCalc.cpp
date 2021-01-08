// PolishCalc.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <conio.h>
#include <iostream>
#include <string>
#include <stack>
#include <queue>
using namespace std;

queue<string> inputs;
stack<string> operators;
queue<string> result;

void ShowPolishQueue()
{
	queue<string> buf = result;
	int size = buf.size();
	for (int i = 0; i < size; i++)
	{
		cout << buf.front() << " ";
		buf.pop();
	}
	cout << endl;
}

queue<string> ParseInputs(string _input)
{
	//cout << _input << endl;
	queue<string> result;
	result.push("a");
	int numberStart = -1;
	for (int i = 0; i < _input.length(); i++)
	{
		if (_input[i] == '(' ||
			_input[i] == ')' ||
			_input[i] == '+' ||
			_input[i] == '-' ||
			_input[i] == '/' ||
			_input[i] == '*')
		{
			if (numberStart >= 0)
			{
				result.push(_input.substr(numberStart, i - numberStart));
				numberStart = -1;
			}
			result.push(_input.substr(i, 1));
		}
		else //не оператор (в случае синусов-косинусов тоже сюда)
		{
			if (numberStart >= 0)
			{
				//идем дальше по числу, ничего не делая
			}
			else
			{
				numberStart = i;
			}
		}
	}
	result.push("a");
	return result;
}



void f1()
{
	operators.push(inputs.front());
	inputs.pop();
}

void f2()
{
	result.push(operators.top());
	operators.pop();
}

void f3()
{
	operators.pop();
	inputs.pop();
}

void fnumber()
{
	result.push(inputs.front());
	inputs.pop();
}

queue<string> MakePolish(string _input)
{
	//   ( 8.0 + 2 * 5 ) / ( 1 + 3 * 2 - 4 )
	inputs = ParseInputs(_input);

	f1();

	while (!inputs.empty())
	{		
		string s = inputs.front();
		switch (s[0])
		{
			case '(':
			{
				f1();
				break;
			}
			case ')':
			{
				switch (operators.top()[0])
				{
				case 'a':
				{
					cout << "Error 5" << endl;
					break;
				}
				case '(':
				{
					f3();
					break;
				}
				default:
				{
					f2();
					break;
				}
				}
				break;
			}
			case '+':
			{
				if (operators.top()[0] == 'a' || operators.top()[0] == '(')
				{
					f1();
				}
				else
				{
					f2();
				}
				break;
			}
			case '-':
			{
				if (operators.top()[0] == 'a' || operators.top()[0] == '(')
				{
					f1();
				}
				else
				{
					f2();
				}
				break;
			}
			case '/':
			{
				if (operators.top()[0] == '*' || operators.top()[0] == '/')
				{
					f2();
				}
				else
				{
					f1();
				}
				break;
			}
			case '*':
			{
				if (operators.top()[0] == '*' || operators.top()[0] == '/')
				{
					f2();
				}
				else
				{
					f1();
				}
				break;
			}
			case 'a':
			{
				switch (operators.top()[0])
				{
				case 'a':
				{
					return result;
					break;
				}
				case '(':
				{
					cout << "Error 5" << endl;
					break;
				}
				default:
				{
					f2();
					break;
				}
				}
				break;
			}
			default:
			{
				fnumber();
				break;
			}
		}

		/*cout << "results: ";
		stack<string> buf = result;
		int size = buf.size();
		for (int i = 0; i < size; i++)
		{
			cout << buf.top() << " ";
			buf.pop();
		}
		cout << endl;

		cout << "operators: ";
		stack<string> buf2 = operators;
		int size2 = buf2.size();
		for (int i = 0; i < size2; i++)
		{
			cout << buf2.top() << " ";
			buf2.pop();
		}
		cout << endl;

		cout << "inputs: ";
		queue<string> buf1 = inputs;
		int size1 = buf1.size();
		for (int i = 0; i < size1; i++)
		{
			cout << buf1.front() << " ";
			buf1.pop();
		}
		cout << endl;*/

	}

	return result;
}

double CalcPolish()
{
	double output = 0;
	stack<double> args;

	while (!result.empty())
	{
		//ShowPolishQueue();

		string s = result.front();

		/*cout << "args: ";
		stack<double> buf2 = args;
		int size2 = buf2.size();
		for (int i = 0; i < size2; i++)
		{
			cout << buf2.top() << " ";
			buf2.pop();
		}
		cout << endl;*/


		if (s[0] == '+' ||
			s[0] == '-' ||
			s[0] == '/' ||
			s[0] == '*')
		{
			double right = args.top();
			args.pop();
			double left = args.top();
			args.pop();
			
			switch (s[0])
			{
				case '+':
				{
					args.push(left + right);
					break;
				}
				case '-':
				{
					args.push(left - right);
					break;
				}
				case '*':
				{
					args.push(left * right);
					break;
				}
				case '/':
				{
					args.push(left / right);
					break;
				}			
			}
			result.pop();
		}
		else
		{
			args.push(stod(s));
			result.pop();
		}
	}

	return args.top();
}

bool CheckInput(string _input)
{
	return true;
}


void MakeRandomInputs()
{

}


double Calc(string _input)
{
	if (CheckInput(_input))
	{
		queue<string> polish = MakePolish(_input);
		return CalcPolish();
	}
	else
	{
		cout << "Некорректное выражение.";
		return 0;
	}
}

int main()
{
	//string input = "(8.0+2*5)/(1+3*2-4)";
	string input;

	while (true)
	{
		cout << "Enter the expression: ";
		cin >> input;
		cout << Calc(input) << endl;
	}
	_getch();
}

