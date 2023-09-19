#include "write_dnf_in_file.hpp"

WriteDNFInFile::WriteDNFInFile(const std::string &argFileName) {
    nameFile = argFileName;
}

WriteDNFInFile::~WriteDNFInFile(void) { }

void WriteDNFInFile::putDNFFromFile(const DNF &argObj) {
    std::ofstream file(nameFile);

    file << argObj;
}


