#include <iostream>
int main() {
    long long a, b;
    std::cout << "Введите числа a и b: ";
    if (!(std::cin >> a >> b)) {
        std::cout << "Ошибка ввода! Введите два целых числа.\n";
        return 0;
    }
    if (a > b) { long long t = a; a = b; b = t; }
    std::cout << "Простые числа на отрезке [" << a << "; " << b << "]: ";
    for (long long n = a; n <= b; ++n) {
        if (n >= 2) {
            long long j = 2;
            while (j * j <= n && n % j != 0) j++;
            if (j * j > n) std::cout << n << " ";
        }
    }
    std::cout << std::endl;
}