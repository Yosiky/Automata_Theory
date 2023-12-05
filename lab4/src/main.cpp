#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include "lexema.hpp"


void printExpression(std::vector<Lexema *> &arr) {
    for (Lexema *i : arr) {
        std::cout << i->print() << ' ';
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

    while (file >> c) {
        while (c != '=' && file >> c) {
            str.push_back(c);
            file >> c;
        }
        expression.push_back(Lexema::createLexema(str));
        assertm(c != '=', "Error: file is finish");
        str.clear();
        str.push_back(c);
        expression.push_back(Lexema::createLexema(str));
        str.clear();
        while (c != ';' && file >> c) {
            if (isdigit(c) || isalpha(c)) {
                str.push_back(c);
            }
            else if (!isspace(c)) {
                expression.push_back(Lexema::createLexema(str));
                str.clear();
                str.push_back(c);
                expression.push_back(Lexema::createLexema(str));
                str.clear();
            }
        }
        str.clear();
        str.push_back(c);
        expression.push_back(Lexema::createLexema(str));
        printExpression(expression);
        processExpression(expression);
        str.clear();
        expression.clear();
    }

}
