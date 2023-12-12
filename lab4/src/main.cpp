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
        std::make_pair(')', -1),
        std::make_pair('+', 1),
        std::make_pair('-', 1),
        std::make_pair('*', 2),
        std::make_pair('/', 2),
        std::make_pair('@', -2) };
    std::stack<std::pair<int, Lexema *> > shop;
    static std::vector<int> variables(100);
    std::vector<Lexema *> poliz;

    shop.push(std::make_pair(-2, Lexema::createLexema("@")));
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
                if (c == ')' || c == ';') {
                    if (c == ')') {
                        shop.pop();
                    }
                    else if (c == ';') {
                        shop.pop();
                        // poliz.push_back(shopElem.second);
                        break ;
                    }
                    else 
                        assertm(true, "Error: char is not valid");
                }
                else 
                    shop.push(std::make_pair(priorityShop[c], arr[i]));
                std::cout << "stack.top(): " << (shop.top().first) << std::endl;
            }   break;
            default: 
                assertm(true, "Error: type's lexema is not valid")
        }
    }
    arr = poliz;
}

int main(int argc, char **argv) {
    assertm(argc > 1, "Error: no input program");
    std::ifstream file(argv[1]);
    std::string str;
    char c;
    int state = 0;

    std::vector<Lexema *> expression;
    std::stack<std::pair<int32_t, Lexema *> > store;

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
        printExpression(expression);
        str.clear();
        expression.clear();
    }

}
