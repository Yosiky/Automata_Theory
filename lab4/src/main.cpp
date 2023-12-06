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

void processExpression(std::vector<Lexema *> &arr) {

}

int main(int argc, char **argv) {
    assertm(argc > 1, "Error: no input program");
    std::ifstream file(argv[1]);
    std::string str;
    char c;
    int state = 0;

    std::vector<Lexema *> expression;
    std::vector<int32_t> memory;
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
        processExpression(expression);
        str.clear();
        expression.clear();
    }

}
