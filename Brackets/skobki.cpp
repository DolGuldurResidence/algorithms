#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool check_brackets(const string& stroka)
{
	stack<char> brackets;

	for (char c : stroka)
	{
		if (c == '(' or c == '{' or c == '[')
		{
			brackets.push(c);
		}
		else if (c == ')' or c == '}' or c == ']')
		{
			if (brackets.empty()) return false;

			char open_bracket = brackets.top();
			brackets.pop();

			if ((c == ')' and open_bracket != '(') or
				(c == '}' and open_bracket != '{') or
				(c == ']' and open_bracket != '['))
			{
				return false;
			}
		}
	}
	
	return brackets.empty();
}


int main() 
{
	setlocale(LC_ALL, "Rus");

	string strochka;
	cout << "Введите строку: ";
	getline(cin, strochka);

	if (check_brackets(strochka))
	{
		cout << "кайфик" << endl;
	}
	else
	{
		cout << "Ты сказал, что ты шаришь в этой теме... " << endl;
	}

	return 0;

}