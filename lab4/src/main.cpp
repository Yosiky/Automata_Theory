#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>
#include "lexema.hpp"


void printExpression(std::vector<Lexema *> &arr) {
    std::cout << "Print expression" << std::endl;
    std::cout << "Count lexems: " << arr.size() << std::endl;
    for (Lexema *i : arr) {
        // std::cout << "TYPE: " << i->getType() << " " << i->getInfo() << " ";
        i->print(std::cout);
        std::cout << " ";
    }
    std::cout << std::endl;
}

void createPOLIZ(std::vector<Lexema *> &arr) {
    static std::map<char, int> priorityLenta = {
        std::make_pair('(', 3),
        std::make_pair(')', 0),
        std::make_pair('+', 1),
        std::make_pair('-', 1),
        std::make_pair('*', 2),
        std::make_pair('/', 2),
        std::make_pair(';', -1) };
    static std::map<char, int> priorityShop = {
        std::make_pair('(', -1),
        std::make_pair('+', 1),
        std::make_pair('-', 1),
        std::make_pair('*', 2),
        std::make_pair('/', 2),
        std::make_pair('@', -2) };
    std::stack<std::pair<int, Lexema *> > shop;
    static std::vector<int> variables(100);
    std::vector<Lexema *> poliz;

    shop.push(std::make_pair(-2, Lexema::createLexema("@")));
    poliz.push_back(arr[0]);
    for (int i = 2; i < arr.size(); ++i) {
        switch (arr[i]->getType()) {
            case (Lexema::NUMBER):
            case (Lexema::ID):
                poliz.push_back(arr[i]);
                break;
            case (Lexema::OPERATION): {
                char c = arr[i]->getInfo();
                auto shopElem = shop.top();

                while (priorityLenta[c] <= shopElem.first) {
                    shop.pop();
                    poliz.push_back(shopElem.second);
                    shopElem = shop.top();
                }
                if (c == ')') {
                    shop.pop();
                }
                else if (c == ';') {
                    break ;
                } else 
                    shop.push(std::make_pair(priorityShop[c], arr[i]));
            }   break;
            default: 
                assertm(true, "Error: type's lexema is not valid")
        }
    }
    arr = poliz;
}

void processPOLIZ(std::vector<Lexema *> &arr, std::vector<int> &memory) {
    std::stack<int> shop;

    for (int i = 1; i < arr.size(); ++i) {
        switch (arr[i]->getType()) {
            case (Lexema::NUMBER): 
                shop.push(arr[i]->getInfo());
                break;
            case (Lexema::ID):
                shop.push(memory[arr[i]->getInfo()]);
                break;
            case (Lexema::OPERATION): {
                int a, b;

                assertm(shop.size(), "Error: shop is empty");
                b = shop.top();
                shop.pop();
                assertm(shop.size(), "Error: shop is empty");
                a = shop.top();
                shop.pop();
                switch (arr[i]->getInfo()) {
                    case '+': a = a + b; break;
                    case '-': a = a - b; break;
                    case '*': a = a * b; break;
                    case '/': a = a / b; break;
                    default: assertm(true, "Error: invalid operation");
                }
                shop.push(a);
            } break;
            default:
                assertm(true, "Error: type's lexema is not valid");
        }
    }
    assertm(arr[0]->getType() == Lexema::ID, "Error: type's lexema is not ID");
    memory[arr[0]->getInfo()] = shop.top();
    std::cout << Lexema::getName(arr[0]->getInfo()) << " = " << memory[arr[0]->getInfo()] << std::endl;
}


int main(int argc, char **argv) {
    assertm(argc > 1, "Error: no input program");
    std::ifstream file(argv[1]);
    std::string str;
    char c;
    int state = 0;

    std::vector<Lexema *> expression;
    std::vector<int> memory;

    while (file >> c) {
        while (c != ';') {
            if (isdigit(c) || isalpha(c)) {
                str.push_back(c);
            }
            else if (!isspace(c)) {
                if (str.size() != 0) {
                    expression.push_back(Lexema::createLexema(str));
                    str.clear();
                }
                str.push_back(c);
                expression.push_back(Lexema::createLexema(str));
                str.clear();
            }
            file >> c;
        }
        if (str.size() != 0) {
            expression.push_back(Lexema::createLexema(str));
            str.clear();
        }
        str.push_back(c);
        expression.push_back(Lexema::createLexema(str));
        printExpression(expression);
        createPOLIZ(expression);
        memory.resize(Lexema::countVariables());
        printExpression(expression);
        processPOLIZ(expression, memory);
        std::cout << "======================================" << std::endl;
        str.clear();
        expression.clear();
    }
    return (0);
}
