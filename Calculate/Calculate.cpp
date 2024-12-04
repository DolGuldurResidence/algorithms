#include <iostream>
#include <stack>
#include <string>
#include <stdexcept>
#include <cctype>
#include <cmath>

using namespace std;

double apply_operator(double a, double b, char oper)
{
    switch (oper) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (b == 0) {
            throw invalid_argument("Деление на ноль!");
        }
        return a / b;
    default:
        throw invalid_argument("Неизвестный оператор");
    }
}

int priority(char oper)
{
    if (oper == '+' || oper == '-') return 1;
    if (oper == '*' || oper == '/') return 2;
    return 0;
}

double calculate_expression(const string& expression)
{
    stack<double> values;
    stack<char> operators;

    int n = expression.length();
    for (int i = 0; i < n; i++)
    {
        char current = expression[i];

        if (isspace(current)) continue;

        // Если текущий символ - цифра, обрабатываем число
        if (isdigit(current) || current == '.')
        {
            double value = 0;
            bool decimal_point = false;
            double decimal_factor = 1;

            // Собираем число (целая и дробная части)
            while (i < n && (isdigit(expression[i]) || expression[i] == '.'))
            {
                if (expression[i] == '.')
                {
                    decimal_point = true;
                }
                else
                {
                    value = value * 10 + (expression[i] - '0');
                    if (decimal_point) {
                        decimal_factor *= 10;
                    }
                }
                i++;
            }
            values.push(value / decimal_factor); // Если есть дробная часть, корректируем значение
            i--; // Возвращаемся на один шаг назад
        }

        // Если открывающая скобка, просто помещаем её в стек операторов
        else if (current == '(')
        {
            operators.push(current);
        }

        // Если закрывающая скобка, решаем все операции до открывающей скобки
        else if (current == ')')
        {
            while (!operators.empty() && operators.top() != '(')
            {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char oper = operators.top(); operators.pop();
                values.push(apply_operator(a, b, oper));
            }
            if (!operators.empty()) operators.pop(); // Убираем открывающую скобку
        }

        // Если текущий символ - оператор
        else if (current == '+' or current == '-' or current == '*' or current == '/')
        {
            while (!operators.empty() && priority(operators.top()) >= priority(current))
            {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char oper = operators.top(); operators.pop();
                values.push(apply_operator(a, b, oper));
            }
            operators.push(current);
        }
        else
        {
            throw invalid_argument("Неверный символ в выражении");
        }
    }

    // Завершаем все оставшиеся операции
    while (!operators.empty())
    {
        double b = values.top(); values.pop();
        double a = values.top(); values.pop();
        char oper = operators.top(); operators.pop();
        values.push(apply_operator(a, b, oper));
    }

    return values.top();
}

int main()
{
    setlocale(LC_ALL, "Russian");

    string expression;
    cout << "Введите выражение, заканчивающееся знаком равенства '=': ";
    getline(cin, expression);

    if (expression.back() == '=')
    {
        expression.pop_back();
    }
    else
    {
        cout << "Отсутствует знак равенства!" << endl;
        return 1;
    }

    try
    {
        double result = calculate_expression(expression);
        cout << "Результат: " << result << endl;
    }
    catch (const exception& e)
    {
        cout << "Ошибка: " << e.what() << endl;
    }

    return 0;
}