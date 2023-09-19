#ifndef IMLICANT_HPP
# define IMLICANT_HPP

class Implicant {

    int num;
    int ind;
    int p;
    bool pw;
    bool inf;


public:

    Implicant(void);
    Implicant(int n);
    ~Implicant(void);
    Implicant(const Implicant &obj);
    Implicant &operator=(const Implicant &obj);

    static Implicant patch(Implicant &firstImpl, Implicant &secondImpl);
    static bool isPatch(const Implicant &firstImpl, const Implicant &secondImpl);
    static bool checkN(int Ni, int Nj);
    static int count_one(int N);
    void init(int argN, int argP, int argPw = 0);

    int get_num(void) const;
    int get_ind(void) const;
    int get_p(void) const;
    bool get_inf(void) const;

    void set_pw(bool argPw);
    bool get_pw(void) const;

    template <class T>
    bool operator==(T b) {
        return (this->num == b.num && this->ind == b.ind && this->p == b.p
                && this->pw == b.pw && this->inf == b.inf);
    }

};

#endif
