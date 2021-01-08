// PolishCalc.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <conio.h>
#include <iostream>
#include <string>
#include <stack>
#include <queue>
using namespace std;

queue<string> ParseInputs(string _input)
{
	cout << _input << endl;

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

stack<string> MakePolish(string _input)
{
	//   ( 8.0 + 2 * 5 ) / ( 1 + 3 * 2 - 4 )
	queue<string> inputs = ParseInputs(_input);
	stack<string> operators;
	stack<string> result;

	operators.push(inputs.front());
	inputs.pop();

	cout << "results: ";
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
	cout << endl;


	while (!inputs.empty())
	{
		string s = inputs.front();
		switch (s[0])
		{
		case '(':
		{
			operators.push(s);
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
				operators.pop();
				break;
			}
			default:
			{
				result.push(operators.top());
				operators.pop();
				break;
			}
			}
			break;
		}
		case '+':
		{
			if (operators.top()[0] == 'a' || operators.top()[0] == '(')
			{
				operators.push(s);
			}
			else
			{
				result.push(operators.top());
				operators.pop();
			}
			break;
		}
		case '-':
		{
			if (operators.top()[0] == 'a' || operators.top()[0] == '(')
			{
				operators.push(s);
			}
			else
			{
				result.push(operators.top());
				operators.pop();
			}
			break;
		}
		case '/':
		{
			if (operators.top()[0] == '*' || operators.top()[0] == '/')
			{
				result.push(operators.top());
				operators.pop();
			}
			else
			{
				operators.push(s);
			}
			break;
		}
		case '*':
		{
			if (operators.top()[0] == '*' || operators.top()[0] == '/')
			{
				result.push(operators.top());
				operators.pop();
			}
			else
			{
				operators.push(s);
			}
			break;
		}
		case 'a':
		{
			switch (operators.top()[0])
			{
			case 'a':
			{
				cout << "Error 4" << endl;
				break;
			}
			case '(':
			{
				cout << "Error 5" << endl;
				break;
			}
			default:
			{
				result.push(operators.top());
				operators.pop();
				break;
			}
			}
			break;
		}
		default:
		{
			result.push(s);
			break;
		}
		}
		inputs.pop();

		cout << "results: ";
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
		cout << endl;

		

		

	}


	

	return result;
}

double Calc(string _input)
{
	//check


	stack<string> polish = MakePolish(_input);
	//polish
	//calc polish

	return 0;
}

int main()
{
	string input = "(8.0+2*5)/(1+3*2-4)";
	//cin >> input;

	cout << Calc(input) << endl;

	_getch();
}

