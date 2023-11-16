#include "implicant.hpp"

Implicant::Implicant(void) {
    num = 0;
    ind = 0;
    p = 0;
    pw = 0;
    inf = 0;
}

Implicant::Implicant(int n) {
    num = n;
    ind = count_one(n);
    p = 0;
    pw = 0;
    inf = 0; // todo ?
}

Implicant::~Implicant(void) { }

Implicant::Implicant(const Implicant &obj) {
    *this = obj;
}

Implicant &Implicant::operator=(const Implicant &obj) {
    num = obj.num;
    ind = obj.ind;
    p = obj.p;
    pw = obj.pw;
    inf = obj.inf;
    return (*this);
}


Implicant Implicant::patch(Implicant &firstImpl, Implicant &secondImpl) {
    Implicant ans;

    firstImpl.set_pw(true);
    secondImpl.set_pw(true);
    ans.init(firstImpl.num, firstImpl.p + (secondImpl.num - firstImpl.num));
    return (ans);
}

bool Implicant::isPatch(const Implicant &firstImpl, const Implicant &secondImpl) {
    return (checkN(firstImpl.num, secondImpl.num)
        && (firstImpl.p == secondImpl.p)
        && (secondImpl.ind - firstImpl.ind == 1)
        && (count_one(secondImpl.num - firstImpl.num) == 1));
}

bool Implicant::checkN(int Ni, int Nj) {
    return (Ni < Nj);
}

int Implicant::count_one(int N) {
    int ans = 0;

    while (N > 0) {
        if (N & 1)
            ++ans;
        N >>=1;
    }
    return (ans);
}

void Implicant::init(int argN, int argP, int argPw) {
    num = argN;
    ind = count_one(num);
    p = argP;
    pw = argPw;
    inf = 0;
}

int Implicant::get_num(void) const {
    return (num);
}

int Implicant::get_ind(void) const {
    return (ind);
}

int Implicant::get_p(void) const {
    return(p);
}

bool Implicant::get_inf(void) const {
    return (inf);
}

void Implicant::set_pw(bool argPw) {
    pw = argPw;
}

bool Implicant::get_pw(void) const {
    return (pw);
}

bool Implicant::operator==(const Implicant &b) {
    return (this->num == b.num && this->ind == b.ind && this->p == b.p
            && this->pw == b.pw && this->inf == b.inf);
}


