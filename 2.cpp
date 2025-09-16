#include <iostream>
int main ()
{
    int a, n, c, d;
    long long k, a, p1;
    std::cout << "Введите k: ";
    if (!(std::cin >> k) || k < 0) {
        std::cerr << "Ошибка: введено другое число!" ;
        return 1;
    }
    while (n <= 2) {
        std::cout << "Введите число больше 1 ";
        std::cin >>n;
    }
    if (n > 2){
        a = 1; 
        c = 0;
        d = 1;
        while ( a <= n ) {
            if (a % 2 == 0) {
            c += a;
            }
            else { 
                d *= a;
            }
            a += 1;
         }
        std::cout << c << " Сумма четных ";
        std::cout << d << " Произведение нечетных ";
    }
    return 0;
}