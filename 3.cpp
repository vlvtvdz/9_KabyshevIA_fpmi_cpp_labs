#include <iostream>
int main() {
    

    long long a, n, s;;
    std::cout << "Введите k: ";
    if (!(std::cin >> n) || n < 1) {
        std::cerr << "Ошибка: введите другое число!" ;
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
