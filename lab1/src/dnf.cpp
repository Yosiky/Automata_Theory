#include "dnf.hpp"

DNF::DNF(const std::string &argLine) {
    count_implicants = argLine.size();
    line = argLine;
    for (int i = 0; i < argLine.size(); ++i) {
        if (argLine[i] != '0')
            data.push_back(Implicant(i));
    }
}

DNF::~DNF(void) { }

void DNF::print(std::ofstream &out) const {

}

void DNF::printTableVectorImplicants(void) const {
    std::cout << "num\t";
    for (int i = 0; i < data.size(); ++i)
        std::cout << "| " << data[i].get_num() << "\t";
    std::cout << "|" << std::endl << "ind\t";
    for (int i = 0; i < data.size(); ++i)
        std::cout << "| " << data[i].get_ind() << "\t";
    std::cout << "|" << std::endl << "p\t";
    for (int i = 0; i < data.size(); ++i)
        std::cout << "| " << data[i].get_p() << "\t";
    std::cout << "|" << std::endl << "pw\t";
    for (int i = 0; i < data.size(); ++i)
        std::cout << "| " << data[i].get_pw() << "\t";
    std::cout << "|" << std::endl << "inf\t";
    for (int i = 0; i < data.size(); ++i)
        std::cout << "| " << data[i].get_inf() << "\t";
    std::cout << "|" << std::endl;
}

void DNF::printInplecantsTable(void) const {
    std::cout << "Implicants table" << std::endl;
    std::cout << "N\t";
    for (int i = 0; i < count_implicants; ++i) {
        if (line[i] == '1')
            std::cout << "| " << i << "\t";
    }
    std::cout << "|";
    for (int i = 0; i < count_implicants; ++i) {
        if (line[i] == '-')
            std::cout << "| " << i << "\t";
    }
    std::cout << std::endl;
    for (int i = 0; i < data.size(); ++i) {
        std::cout << "(" << data[i].get_num() << ", " << data[i].get_p() << ")\t";
        for (int j = 0; j < count_implicants; ++j) {
            if (line[j] == '1')
                std::cout << "| " << ((j & (~data[i].get_p())) == data[i].get_num()) << "\t";
        }
        std::cout << "|";
        for (int j = 0; j < count_implicants; ++j) {
            if (line[j] == '-')
                std::cout << "| " << ((j & (~data[i].get_p())) == data[i].get_num()) << "\t";
        }
        std::cout << std::endl;
    }
}

void DNF::minimize(void) {
    std::vector<Implicant> copy;
    std::vector<Implicant>::iterator it;
    Implicant value;
    int size = 0;

    while (true) {
        printTableVectorImplicants();
        for (int i = 0; i < data.size() - size; ++i) {
            for (int j = i + 1; j < data.size() - size; ++j) {
                if (Implicant::isPatch(data[i], data[j])) {
                    value = Implicant::patch(data[i], data[j]);
                    it = find(copy.begin(), copy.end(), value);
                    if (it == copy.end())
                        copy.push_back(value);
                    /* printTableVectorImplicants(); */
                }
            }
        }
        std::cout << "Count new implicants: " << copy.size() << std::endl;
        if (!checkPwAllImplicant())
            break ;
        size = 0;
        for (int i = 0; i < data.size(); ++i) {
            if (data[i].get_pw() == 0) {
                it = find(copy.begin(), copy.end(), data[i]);
                if (it == copy.end()) {
                    copy.push_back(data[i]);
                    ++size;
                }
            }
        }
        data = copy;
        copy.clear();
    }
    printTableVectorImplicants();
    printInplecantsTable();
}

bool DNF::checkPwAllImplicant(void) {
    bool ans = false;

    for (int i = 0; i < data.size(); ++i)
        ans |= data[i].get_pw();
    return (ans);
}

std::ofstream &operator<<(std::ofstream &out, const DNF &dnf) {
    dnf.print(out);
    return (out);
}

