#ifndef LEXEMA_HPP
# define LEXEMA_HPP

# include <iostream>
# include <cstdint>
# include <string>
# include <ctype.h>
# include <map>

# define assertm(cond, str)                                         \
    if (!(cond)) {                                                  \
        std::cerr << "Error (" << __FILE__ << ", " << __func__ << ") : "<< #cond << " (" << str << ")" << std::endl;    \
        exit(-1);                                                   \
    }

# define LEXEMA_MASK_TYPE      0xc0000000
# define LEXEMA_MASK_NUMBER    0x3fffffff
# define LEXEMA_MASK_ID        0x3fffffff
# define LEXEMA_MASK_OPERATION 0x000000ff
# define LEXEMA_SHIFT_TYPE     30


class Lexema {

    uint32_t value;
    static std::map<std::string, uint32_t> names;

    static bool checkIsNumber(const std::string &str);
    static bool checkIsId(const std::string &str);
    static bool checkIsOperation(const std::string &str);
    static int findTypeLexema(const std::string &str);

public:

    enum Type {
        NUMBER = 0,
        ID,
        OPERATION
    };

    Lexema(void);

    uint32_t getType(void);
    void setType(uint32_t type);
    void setInfo(const std::string &str);
    // void setValue(uint32_t argValue);
    uint32_t getInfo(void);
    void reset(void);
    const std::string print(void);

    static int checkLexema(Lexema::Type &type, const std::string &str);
    static Lexema *createLexema(const std::string &str);

};

#endif
