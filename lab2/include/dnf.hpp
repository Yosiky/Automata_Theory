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
    int count_ones;

    DNF &operator=(const DNF &obj);
    bool check_pw_all_implicant(void) const;
    bool check_overlap_condition(int num, const Implicant &impl) const;

public:

    DNF(const std::string &argLine);
    ~DNF(void);
    DNF(const DNF &obj);

    void print() const;
    void printTableVectorImplicants(void) const;
    void printInplecantsTable(void) const;
    void minimize(bool off=1);

};

std::ofstream &operator<<(std::ofstream &in, const DNF &dnf);


#endif
