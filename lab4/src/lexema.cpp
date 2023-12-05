#include "lexema.hpp"

std::map<std::string, uint32_t> Lexema::names;

Lexema::Lexema(void) {
    reset();
}

uint32_t Lexema::getType(void) {
    return ((value & LEXEMA_MASK_TYPE) >> LEXEMA_SHIFT_TYPE);
}

void Lexema::setType(uint32_t type) {
    value = (value & (~LEXEMA_MASK_TYPE)) + (type << LEXEMA_SHIFT_TYPE);
}

void Lexema::setInfo(const std::string &str) {
    switch (getType()) {
        case (Lexema::NUMBER):
            value = (NUMBER << LEXEMA_SHIFT_TYPE) + (std::stoi(str) & LEXEMA_MASK_NUMBER);
            break;
        case (Lexema::ID):
            value = (NUMBER << LEXEMA_SHIFT_TYPE) + (names[str] & LEXEMA_MASK_ID);
            break;
        case (Lexema::OPERATION):
            value = (OPERATION << LEXEMA_SHIFT_TYPE) + (str[0] & LEXEMA_MASK_OPERATION);
            break;
        default:
            assertm(true, "Error: type of lexema is not valid");
    }
}

uint32_t Lexema::getInfo(void) {
    switch (getType()) {
        case (Lexema::NUMBER):
            return (value & LEXEMA_MASK_NUMBER);
        case (Lexema::ID):
            return (value & LEXEMA_MASK_ID);
        case (Lexema::OPERATION):
            return (value & LEXEMA_MASK_OPERATION);
        default:
            assertm(true, "Error: type of lexema is not valid");
    }
    return (-1);
}

// void Lexema::setValue(uint32_t argValue) {
    // setType(argValue >> LEXEMA_SHIFT_TYPE);
    // setInfo(argValue);
// }

void Lexema::reset(void) {
    value = (uint32_t)-1;
}

const std::string Lexema::print(void) {
    std::string ans;

    switch (getType()) {
        case (Lexema::NUMBER):
            ans = std::to_string(value & LEXEMA_MASK_NUMBER);
            break;
        case (Lexema::ID):
            ans = std::to_string(value & LEXEMA_MASK_ID);
            break;
        case (Lexema::OPERATION): {
            char sym = value & LEXEMA_MASK_OPERATION;
            ans.push_back(sym);
        }   break;
        default:
            assertm(true, "Error: type of lexema is not valid");
    }
    return (ans);
}

bool Lexema::checkIsNumber(const std::string &str) {
    for (int i = 0; i < str.size(); ++i) {
        if (isdigit(str[i]))
            return (false);
    }
    return (true);
}

bool Lexema::checkIsId(const std::string &str) {
    if (isalpha(str[0]) == 0) 
        return (false);
    for (int i = 1; i < str.size(); ++i) {
        if (isalpha(str[i]) == 0 && isdigit(str[i]) == 0)
            return (false);
    }
    return (true);
}
    
bool Lexema::checkIsOperation(const std::string &str) {
    if (str.size() > 1) {
        return (false);
    }
    // todo: maybe need to add '='
    return (str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/'
            || str[0] == '(' || str[0] == ')' || str[0] == '=' || str[0] == ';');
}

int Lexema::checkLexema(Lexema::Type &type, const std::string &str) {
    switch (type) {
        case (Lexema::NUMBER):
            return (checkIsNumber(str) ? 0 : -1);
        case (Lexema::ID):
            return (checkIsId(str) ? 1 : -1);
        case (Lexema::OPERATION):
            return (checkIsOperation(str) ? 2 : -1);
        default:
            assertm(true, "Error: lexama's type is not valid")
    }
}

int Lexema::findTypeLexema(const std::string &str) {
    int type = (checkIsOperation(str) << OPERATION)
            | (checkIsId(str) << ID)
            | (checkIsNumber(str) << NUMBER);
    int ans = 0;
    
    std::cout << str << std::endl;
    assertm(type != 0, "Error: lexema is not valid");
    while (type > 0) {
        ++ans;
        type >>= 1;
    }
    return (ans);
}

Lexema *Lexema::createLexema(const std::string &str) {
    Lexema *lexema = new Lexema;
    int type = findTypeLexema(str);
    int nameId = names.size();

    lexema->setType(type);
    if (type == ID) {
        if (names.count(str) == 0)
            names[str] = nameId;
    }
    lexema->setInfo(str);
    return (lexema);
}


