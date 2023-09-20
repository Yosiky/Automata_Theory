#include "dnf.hpp"

DNF::DNF(const std::string &argLine) {
    // конструктор для создания ДНФ из строки

    count_implicants = argLine.size();
    line = argLine;
    for (int i = 0; i < argLine.size(); ++i) {
        if (argLine[i] != '0')
            data.push_back(Implicant(i));
    }
}

DNF::~DNF(void) { }

static int intlog2(int v) {
    // функция для поиска степени числа
    // P.S.: работает только если v действительно степень числа

    int ans = 0;

    while (v >>= 1) {
        ++ans;
    }
    return ans;
}

void DNF::print() const {
    // метод выводит ответ в std::cout

    int count = intlog2(count_implicants); // сколько переменных используется

    std::cout << "Count variable: " << count << std::endl;
    for (int i = 0; i < count; ++i) // выводит название переменных
        std::cout << (char)('A' + i);
    std::cout << std::endl;
    for (int i = 0; i < data.size(); ++i) { // обход по импликантам
        for (int j = count - 1; j >= 0; --j) { // обход по переменным
            if (data[i].get_p() & (1 << j))
                std::cout << "-"; // если сокращалась ранее выводим '-'
            else // в противном случае выводим 1 или 0
                std::cout << ((data[i].get_num() & (1 << j)) > 0 ? 1 : 0);
        }
        std::cout << std::endl;
    }
}

void DNF::printTableVectorImplicants(void) const {
    // метод печтает хранящиеся импликанты

    std::cout << "num\t";
    for (int i = 0; i < data.size(); ++i)
        std::cout << "| " << data[i].get_num() << "\t";
    std::cout << "|" << std::endl << "ind\t";
    for (int i = 0; i < data.size(); ++i)
        std::cout << "| " << data[i].get_ind() << "\t";
    std::cout << "|" << std::endl << "p\t";
    for (int i = 0; i < data.size(); ++i)
        std::cout << "| " << data[i].get_p() << "\t";
    std::cout << "|" << std::endl << "pw\t";
    for (int i = 0; i < data.size(); ++i)
        std::cout << "| " << data[i].get_pw() << "\t";
    std::cout << "|" << std::endl << "inf\t";
    for (int i = 0; i < data.size(); ++i)
        std::cout << "| " << data[i].get_inf() << "\t";
    std::cout << "|" << std::endl;
}

void DNF::printInplecantsTable(void) const {
    // метод печатает импликантную таблицу

    std::cout << "Implicants table" << std::endl;
    std::cout << "N\t";
    for (int i = 0; i < count_implicants; ++i) {
        if (line[i] == '1') // если переменная в изначальной строке равна 1
            std::cout << "| " << i << "\t";
    }
    std::cout << "|";
    for (int i = 0; i < count_implicants; ++i) {
        if (line[i] == '-') // если переменная в изначальной строке равна '-'
            std::cout << "| " << i << "\t";
    }
    std::cout << std::endl;
    for (int i = 0; i < data.size(); ++i) {
        std::cout << "(" << data[i].get_num() \
            << ", " << data[i].get_p() << ")\t";
        for (int j = 0; j < count_implicants; ++j) {
            if (line[j] == '1') // тоже самое что и в строке 75
                std::cout << "| " \
                    << (check_overlap_condition(j, data[i]) ? '+' : ' ') \
                    << "\t";
        }
        std::cout << "|";
        for (int j = 0; j < count_implicants; ++j) {
            if (line[j] == '-') // тоже самое что и в строке 80
                std::cout << "| " \
                    << (check_overlap_condition(j, data[i]) ? '+' : ' ') << "\t";
        }
        std::cout << std::endl;
    }
}

void DNF::minimize(void) {
    // метод для минимизации ДНФ

    std::vector<Implicant> copy; // массив, где хранятся вычисляемые имплеканты
    std::vector<Implicant>::iterator it;
    Implicant value;
    int size = 0; // сколько имплекант, которые не склеивались

    while (true) { // склейка имплекант
        printTableVectorImplicants();
        for (int i = 0; i < data.size() - size; ++i) {
            for (int j = i + 1; j < data.size() - size; ++j) {
                if (Implicant::isPatch(data[i], data[j])) {
                    // если импликанты data[i] и data[j] можно склеить
                    value = Implicant::patch(data[i], data[j]);
                    it = find(copy.begin(), copy.end(), value);
                    if (it == copy.end()) // проверяем есть ли такая имплеканта
                        copy.push_back(value);
                }
            }
        }
        std::cout << "Count new implicants: " << copy.size() << std::endl;
        if (!check_pw_all_implicant()) // если не было склеек выходим из цикла
            break ;
        size = 0;
        for (int i = 0; i < data.size(); ++i) {
            // добавляем импликанты, которые не склеивались ранее на всех этапах
            if (data[i].get_pw() == 0) {
                it = find(copy.begin(), copy.end(), data[i]);
                if (it == copy.end()) {
                    copy.push_back(data[i]);
                    ++size;
                }
            }
        }
        data = copy;
        copy.clear();
    }
    printTableVectorImplicants();
    printInplecantsTable();
    print();

    std::vector<int> visit(data.size(), false); // используемые имплеканты
    std::vector<bool> plus(count_implicants); // ответы
    std::vector<Implicant> min_variant(data); // минимальный вариант
    int perenos = 1; // перенос
    bool flag;

    copy.resize(data.size() - size, 0);
    for (int i = 0; i < (1 << data.size()); ++i) {
        // проход от 0 до (2^n) - 1, где n - кол-во имплекант
        for (int j = 0; j < plus.size(); ++j)
            plus[j] = 0;
        for (int j = 0; j < visit.size(); ++j) {
            // определяем какие импликанты будут использоваться
            if (visit[j] + perenos == 2) {
                visit[j] = 0;
                perenos = 1;
            }
            else if (visit[j] + perenos == 1) {
                visit[j] = 1;
                perenos = 0;
            }
            else {
                visit[j] = 0;
                perenos = 0;
            }
        }
        perenos = 1;
        for (int j = 0; j < data.size(); ++j) {
            // проверяем где ставить '+', а где '-'
            if (visit[j]) {
                for (int k = 0; k < count_implicants; ++k) {
                    if (line[k] == '1')
                        plus[k] = plus[k] || check_overlap_condition(k, data[j]);
                }
            }
        }
        flag = 1; // переменная для проверки что все ответы 1
        for (int j = 0; j < plus.size(); ++j) {
            // проверяем, что все важные значения принимают значение 1
            if (line[j] == '1') {
                flag &= plus[j];
            }
        }
        if (flag && Implicant::count_one(i + 1) < min_variant.size()) {
            // проверяем, что все столбцы в таблице
            // имплекант в данном наборе равны 1
            // если да и кол-во имплекант меньше, то сохраняем новый набор
            min_variant.clear();
            for (int j = 0; j < visit.size(); ++j) {
                if (visit[j])
                    min_variant.push_back(data[j]);
            }
        }
    }
    data = min_variant; // сохраняем результат
}

bool DNF::check_pw_all_implicant(void) const {
    // метод, проверяющий была ли хотя бы одна склейка

    bool ans = false;

    for (int i = 0; i < data.size(); ++i)
        ans |= data[i].get_pw();
    return (ans);
}

bool DNF::check_overlap_condition(int num, const Implicant &impl) const {
    // метод для проверки условия
    // N & ~(Pт) == Nт

    return ((num & (~impl.get_p())) == impl.get_num());
}

std::ofstream &operator<<(std::ofstream &out, const DNF &dnf) {
    // вывод результата в файл, но это не работает, поэтому вывод происходит в
    // std::cout

    dnf.print();
    return (out);
}

