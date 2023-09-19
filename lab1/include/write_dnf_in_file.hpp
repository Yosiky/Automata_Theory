#ifndef WRITE_DNF_IN_FILE_HPP
# define WRITE_DNF_IN_FILE_HPP

# include <iostream>
# include <string>
# include <fstream>
# include "dnf.hpp"

class WriteDNFInFile {

    std::string nameFile;

    WriteDNFInFile(void);
    WriteDNFInFile(const WriteDNFInFile &copyObj);

    WriteDNFInFile &operator=(const WriteDNFInFile &copyObj);

public:

    WriteDNFInFile(const std::string &argFileName);
    ~WriteDNFInFile(void);

    void putDNFFromFile(const DNF &argObj);

};


#endif
