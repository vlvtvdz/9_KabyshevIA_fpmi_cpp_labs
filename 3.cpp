#include <iostream>
int main() {
    int a, n, s;

    std::cout << "Введите n: ";
    if (!(std::cin >> n)) {
        std::cerr << "Ошибка: введено не число!" << std::endl;
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
