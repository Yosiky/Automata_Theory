#ifndef DNF_HPP
# define DNF_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "implicant.hpp"

class DNF {

    std::vector<Implicant> data;
    std::string line;
    int count_implicants;

    DNF(const DNF &obj);
    DNF &operator=(const DNF &obj);
    bool checkPwAllImplicant(void);
public:

    DNF(const std::string &argLine);
    ~DNF(void);

    void print(std::ofstream &in) const;
    void printTableVectorImplicants(void) const;
    void printInplecantsTable(void) const;
    void minimize(void);

};

std::ofstream &operator<<(std::ofstream &in, const DNF &dnf);


#endif
