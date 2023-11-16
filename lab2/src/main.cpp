// #include "lab2.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include "dnf.hpp"
#include "implicant.hpp"


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

void pirnt_table_with_mask(const std::vector<std::vector<int> > &table, const std::vector<uint32_t> &mask) {
    std::cout << "=============================================" << std::endl;
    std::cout << "Table: " << std::endl;
    for (int i = 0; i < table.size(); ++i) {
        for (int j = 0; j < table[i].size(); ++j) {
            if (table[i][j])
                std::cout << mask[table[i][j] - 1] << ' ';
            else
                std::cout << "-" << ' ';
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

void create_code_gray(std::vector<uint32_t> &mask, int count_state, int count_d_trigger) {
    mask.resize(1 << count_d_trigger);
    if (mask.size() < 2) {
        std::cerr << "Error: invalid count state" << std::endl;
        exit(1);
    }
    int p = 1;

    mask[0] = 0;
    mask[1] = 1;
    for (int i = 2; i <= count_d_trigger; ++i) {
        int value = 1 << i;
        for (int j = value - 1; j >= value / 2; --j) {
            mask[j] = mask[value - j - 1] | (1 << p);
        }
        ++p;
    }
    mask.resize(count_state);
}

template <class T>
void print_vector(const std::vector<T> &arr, char endl=' ') {
    std::cout << "=========================================" << std::endl;
    std::cout << "Print vector:" << std::endl;
    for (const T &i : arr)
        std::cout << i << endl;
    std::cout << std::endl;
    std::cout << "=========================================" << std::endl;
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
    int count_input = 0;
    std::vector<uint32_t> mask; 

    while ((1 << count_d_trigger) < count_state) {
        ++count_d_trigger;
    }
    while ((1 << count_input) < ftable.size()) {
        ++count_input;
    }
    std::cout << "Count D triggers: " << count_d_trigger << std::endl; 
    std::cout << "Count input signals: " << count_input << std::endl; 
    if (count_d_trigger > 32) {
        std::cerr << "Error: count d triggers more than 32" << std::endl;
        return (1);
    }
    create_code_gray(mask, count_state, count_d_trigger);
    print_vector(mask);

    std::vector<std::string> cdnf;
    std::string line(1 << (count_input + count_d_trigger), '-');
    std::cout << "Start line: " << line << std::endl;

    for (int line_it = 0; line_it < count_d_trigger; ++line_it) {
        std::cout << "Trigger : " << line_it << std::endl;
        int mask_value = 1 << line_it;
        int value;

        cdnf.push_back(line);
        for (int i = 0; i < ftable.size(); ++i) {
            value = i << count_d_trigger;
            for (int j = 0; j < ftable[i].size(); ++j) {
                if (ftable[i][j]) {
                    if (mask[ftable[i][j] - 1] & mask_value) {
                        cdnf[line_it][value + mask[ftable[i][j] - 1]] = '1';
                    } else {
                        cdnf[line_it][value + mask[ftable[i][j] - 1]] = '0';
                   }
                }
            }
        }
    }

    print_vector(cdnf, '\n');
    pirnt_table_with_mask(ftable, mask);
    std::vector<DNF> mdnf;
    
    for (int i = 0; i < cdnf.size(); ++i) {
        mdnf.push_back(cdnf[i]);
        mdnf[i].minimize();
    }

    return (0);
}

