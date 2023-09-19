#include "read_dnf_from_file.hpp"

ReadDNFFromFile::ReadDNFFromFile(const std::string &argFileName) {
    nameFile = argFileName;
}

ReadDNFFromFile::~ReadDNFFromFile(void) { }

const std::string ReadDNFFromFile::getDNFFromFile(void) {
    std::ifstream    file(nameFile);
    std::string      line;

    file >> line;
    return (line);
}


