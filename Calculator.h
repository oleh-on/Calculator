#pragma once
#include <stack>
#include <vector>
#include <string>

struct Operator
{
    Operator() {}
    Operator(const char n, int p) : name(n), precedence(p) {}
    const char name = ' ';
    int precedence = 0;
};

extern std::stack<double> operands;
extern std::stack<Operator> operators;
extern std::vector<double> previous;

double calculate(const std::string& command);

void reorganize_operands(std::stack<double>& operands, std::stack<Operator>& operators);

Operator check_operator(const char operat);