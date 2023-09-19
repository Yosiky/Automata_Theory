#ifndef READ_DNF_FROM_FILE_HPP
# define READ_DNF_FROM_FILE_HPP

# include <iostream>
# include <string>
# include <fstream>

class ReadDNFFromFile {

    std::string nameFile;

    ReadDNFFromFile(void);
    ReadDNFFromFile(const ReadDNFFromFile &copyObj);

    ReadDNFFromFile &operator=(const ReadDNFFromFile &copyObj);

public:

    ReadDNFFromFile(const std::string &argFileName);
    ~ReadDNFFromFile(void);

    const std::string getDNFFromFile(void);

};

#endif
