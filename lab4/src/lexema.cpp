#include "lexema.hpp"

std::map<uint32_t, std::string> Lexema::names;
std::set<std::string> Lexema::s;

Lexema::Lexema(void) {
    reset();
}

uint32_t Lexema::getType(void) {
    return ((value & LEXEMA_MASK_TYPE) >> LEXEMA_SHIFT_TYPE);
}

void Lexema::setType(uint32_t type) {
    value = (value & (~LEXEMA_MASK_TYPE)) + (type << LEXEMA_SHIFT_TYPE);
}

void Lexema::setInfo(const std::string &str, uint32_t argValue) {
    switch (getType()) {
        case (Lexema::NUMBER):
            value = (NUMBER << LEXEMA_SHIFT_TYPE) + (std::stoi(str) & LEXEMA_MASK_NUMBER);
            break;
        case (Lexema::ID):
            value = (NUMBER << LEXEMA_SHIFT_TYPE) + (argValue & LEXEMA_MASK_ID);
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

void Lexema::print(std::ostream &out) {
    // out << "\tPrint lexema: " << std::endl;
    // out << "\t\tType: " << getType() << std::endl;
    // out << "\t\tValue: ";
    switch (getType()) {
        case (Lexema::NUMBER):
            out << (value & LEXEMA_MASK_NUMBER);
            break;
        case (Lexema::ID):
            out << (value & LEXEMA_MASK_ID);
            break;
        case (Lexema::OPERATION): {
            out << (char)(value & LEXEMA_MASK_OPERATION);
        }   break;
        default:
            assertm(true, "Error: type of lexema is not valid");
    }
    // out << std::endl;
}

bool Lexema::checkIsNumber(const std::string &str) {
    for (int i = 0; i < str.size(); ++i) {
        if (!isdigit(str[i]))
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
            || str[0] == '(' || str[0] == ')' || str[0] == '=' || str[0] == ';' || str[0] == '@');
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
    int ans = -1;
    
    assertm(type != 0, "Error: lexema is not valid");
    while (type > 0) {
        ++ans;
        type >>= 1;
    }
    // --type;
    return (ans);
}

Lexema *Lexema::createLexema(const std::string &str) {
    Lexema *lexema = new Lexema;
    int type = findTypeLexema(str);
    uint32_t nameId = s.size();

    lexema->setType(type);
    if (type == ID) {
        if (s.count(str) == 0) {
            names[nameId] = str;
            s.insert(str);
        }
    }
    lexema->setInfo(str, nameId);
    return (lexema);
}

const std::string &Lexema::getName(int id) {
    if (names.count(id))
        return (names[id]);
    return ("");
}

int Lexema::countVariables(void) {
    return (names.size());
}

