// #include "lab2.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>


// read table from file
std::vector<int> split_line_by_integer(const std::string &str, char sep) {
    std::vector<int> ans;
    int count_sep = 0;
    int i = 0;

    while (i < str.size()) {
        while (i < str.size() && str[i] == sep) ++i;
        if (i < str.size())
            ans.push_back(atoi(str.c_str() + i));
        while (i < str.size() && str[i] != sep) ++i;
    }
    return (ans);
}

class ReadTable {

    static std::vector<std::vector<int> > table;

    ReadTable(void);
    ReadTable(const ReadTable &);
    ReadTable &operator=(const ReadTable &obj);
    ~ReadTable(void);

public:

    static std::vector<std::vector<int> > read_table(const std::string &table_name) {
        std::string line;
        std::ifstream file(table_name);

        ReadTable::clean_table();
        while (std::getline(file, line)) {
            table.push_back(split_line_by_integer(line, ' '));
        }
        return (table);
    }

    static std::vector<std::vector<int> > &get_table(void) {
        return (table);
    }

    static void clean_table(void) {
        table.clear();
    }
};

std::vector<std::vector<int> > ReadTable::table;

// print table in std::cout
void print_table(const std::vector<std::vector<int> > &table) {
    std::cout << "=============================================" << std::endl;
    std::cout << "Table: " << std::endl;
    for (int i = 0; i < table.size(); ++i) {
        for (int j = 0; j < table[i].size(); ++j) {
            std::cout << table[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "=============================================" << std::endl;
}

// get params about table
int analize_state(const std::vector<std::vector<int> > table) {
    return (table.size() ? table[0].size() : 0);
}

int analize_outstate(const std::vector<std::vector<int> > table) {
    std::set<int> output_state;

    for (int i = 0; i < table.size(); ++i) {
        for (int j = 0; j < table.size(); ++j) {
            output_state.insert(table[i][j]);
        }
    }
    return (output_state.size());
}

int main(int argc, char **argv) {
    int variant;
    std::vector<std::vector<int> > ftable = ReadTable::read_table("test/f.txt");
    std::vector<std::vector<int> > gtable = ReadTable::read_table("test/g.txt");

    print_table(ftable);
    print_table(gtable);

    int count_state = analize_state(ftable);
    int count_outstate = analize_outstate(gtable);
    int count_d_trigger = 0;
    std::vector<uint32_t> mask(count_state); 

    while ((1 << count_d_trigger) < count_state) {
        ++count_d_trigger;
    }
    std::cout << "Count D triggers: " << count_d_trigger << std::endl; 
    if (count_d_trigger > 32) {
        std::cerr << "Error: count d triggers more than 32" << std::endl;
        return (1);
    }

    return (0);
}

