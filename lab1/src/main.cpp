#include "read_dnf_from_file.hpp"
#include "write_dnf_in_file.hpp"
#include "dnf.hpp"

int main(int argc, char **argv) {

    ReadDNFFromFile readFromFile(argv[1]);
    WriteDNFInFile  writeInFile(argv[2]);
    DNF             dnf(readFromFile.getDNFFromFile());

    dnf.minimize();
    writeInFile.putDNFFromFile(dnf);
    return (0);
}
