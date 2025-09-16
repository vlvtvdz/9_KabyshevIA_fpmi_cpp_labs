#include <iostream>
int main() {
    int a, n, s;

    long long k, a, p1;
    std::cout << "Введите k: ";
    if (!(std::cin >> k) || k < 0) {
        std::cerr << "Ошибка: введено другое число!" ;
        return 1;
    }

    s = 0;
    a = 1;
    while (a <= n) {
        s += (a * a);
        a += 1;
    }

    std::cout << "Сумма квадратов от 1 до " << n << " равна " << s << std::endl;
    return 0;
}
