// Task 1. SimpleCalc
// Made by Roman Samokhvalov, 1536.

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <cmath>

using namespace std;
string s;
string common;

//Any simple operation for two variables.
long long single(char o, int a, int b) {
    if (o == '-')
        return a - b;
    if (o == '+')
        return a + b;
    if (o == '*')
        return a * b;
    if (o == '/')
        if (b == 0) {
            cout << "Error. Division by zero.";
            exit(0);
        } else
            return a / b;
    if (o == '%')
        if (b == 0) {
            cout << "Error. Division by zero.";
            exit(0);
        } else
            return a % b;
}

// The function "calculate" does the following steps:
// 1) gets the string;
// 2) finds brackets and converts substrings inside into a number using the same function inside itself; the number goes back to the string in the certain position;
// 3) parses the elements and divides them by two groups: numbers and operators;
// 4) does the operations, making one result from two operands and deleting the operators from the vector;
// 5) returns the answer or an error.

long long calculate(string temp) {  // 1)
    int number;
    int i, n, convert, start, finish;
    string exchange, inside_brackets, inside_brackets_update, number_string = "";
    vector<int> numbers;
    vector<char> operators;
    char ch[30000];
// 2) Dealing with the brackets. Recursion is used for each pair of them.
    for (i = 0; i < temp.size(); i++) {
        if (temp[i] == ')') {
            temp.erase(i, 1);
            finish = i - 1;
            inside_brackets = "";
            while (temp[i] != '(') {
                i--;
                if (temp[i] != '(') {
                inside_brackets_update = temp[i];
                inside_brackets_update += inside_brackets;
                inside_brackets = inside_brackets_update;
                }
            }
            temp.erase(i, 1);
            start = i;
            convert = calculate(inside_brackets);
            n = sprintf(ch, "%d", convert);
            /* itoa(convert, ch, 10);
            n = 0;
            if ((convert == 0) || (ch[0] == '-'))
                n = 1;
            while (abs(convert) > 0) {
                convert /= 10;
                n++;
            } */
            exchange = "";
            for (int i = 0; i < n; i++)
                exchange += ch[i];
            temp.replace(start, finish - start, exchange);
        }
    }
// 3) Parsing of the string. Operators and numbers are put in different vectors.
    for (i = 0; i < temp.size(); i++) {
        if ((temp[i] == '+') || (temp[i] == '*') || (temp[i] == '/') || (temp[i] == '%'))
            operators.push_back(temp[i]);
        else {
            if (temp[i] == '-') {
                if ((i == 0) || ((i > 0) && ((temp[i - 1] == '-') || (temp[i - 1] == '+') || (temp[i - 1] == '*') || (temp[i - 1] == '/') || (temp[i - 1] == '%')))) {
                    i++;
                    number_string = "-";
                }
                else {
                    operators.push_back('-');
                    number_string = "";
                    continue;
                }
            }
            if ((temp[i] >= '0') && (temp[i] <= '9')) {
                while ((temp[i] >= '0') && (temp[i] <= '9')) {
                    number_string += temp[i];
                    i++;
                }
                i--;
                numbers.push_back(atoi(number_string.c_str()));
                number_string = "";
            } else {
                if (temp[i] != ' ') {
                    cout << "Error. An unacceptable symbol was detected.";
                    exit(0);
                }
            }
        }
    }
// 4) Calculation begins.
//Multiply and division.
    long long result;
    for (i = 0; i < operators.size(); i++)
    {
        if ((operators[i] == '*') || (operators[i] == '/') || (operators[i]== '%')) {
            result = single(operators[i], numbers[i], numbers[i + 1]);
            operators.erase(operators.begin() + i);
            numbers.erase(numbers.begin() + i + 1);
            numbers[i] = result;
            i--;
        }
    }
// Addition and subtraction.
    for (i = 0; i < operators.size(); i++)
    {
        if ((operators[i] == '-') || (operators[i] == '+')) {
            result = single(operators[i], numbers[i], numbers[i + 1]);
            operators.erase(operators.begin() + i);
            numbers.erase(numbers.begin() + i + 1);
            numbers[i] = result;
            i--;
        }
    }
    if (operators.size() == 0)
        return numbers[0];
    else
        return result;
}

// Main function.
int main() {
    cout << "Enter your expression." << "\n";
    getline(cin,s);
    s += " ";
    stringstream st;
    st << s;
    while(st >> s) {
        common += s;
    }
    cout << "The answer is " << calculate(common) << ".";

    return 0;
}
