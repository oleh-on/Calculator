#include "Calculator.h"

std::stack<double> operands;
std::stack<Operator> operators;
std::vector<double> previous;

void reorganize_operands(std::stack<double>& operands, std::stack<Operator>& operators)
{
    double tmp = 0;
    if (operators.top().name == '+') {
        tmp = operands.top();
        operands.pop();
        operands.top() += tmp;
    }
    else if (operators.top().name == '-') {
        tmp = operands.top();
        operands.pop();
        operands.top() -= tmp;
    }
    else if (operators.top().name == '/') {
        tmp = operands.top();
        operands.pop();
        operands.top() /= tmp;
    }
    else if (operators.top().name == '*') {
        tmp = operands.top();
        operands.pop();
        operands.top() *= tmp;
    }
    operators.pop();
}

Operator check_operator(const char operat)
{
    if (operat == '+') {
        return Operator('+', 1);
    }
    else if (operat == '-') {
        return Operator('-', 1);
    }
    else if (operat == '/') {
        return Operator('/', 2);
    }
    else if (operat == '*') {
        return Operator('*', 2);
    }
}

double calculate(const std::string& command)
{
    for (unsigned int i = 0; i < command.length(); ++i)
    {
        if (isdigit(command[i]))
        {
            double x = 0;
            while (isdigit(command[i]))
            {
                x = x * 10 + (command[i] - '0');
                ++i;
            }
            --i;
            operands.push(x);
        }
        else if (command[i] == '.')
        {
            std::size_t offset = 0;
            operands.top() += std::stod(&command[i], &offset);
            i += offset-1;
        }
        else if (command[i] == '$')
        {
            double x = command[i + 1] - '0';
            operands.push(previous[x]);
            i++;
        }
        else if(command[i] == '+' || command[i] == '-' || command[i] == '/' || command[i] == '*')
        {
            Operator op = check_operator(command[i]);

            if (operators.empty())
                operators.push(op);
            else {
                while (!operators.empty() && op.precedence <= operators.top().precedence) {
                    reorganize_operands(operands, operators);
                }
                operators.push(op);
            }
        }
    }

    while (!operators.empty())
    {
        reorganize_operands(operands, operators);
    }
    previous.push_back(operands.top());
    return operands.top();
}