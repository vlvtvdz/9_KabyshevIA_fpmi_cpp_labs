#include <iostream>
int main () {
    long long a, n, s;;
    std::cout << "Введите n: ";
    if (!(std::cin >> n) || n < 1) {
        std::cerr << "Ошибка: введите другое число!" ;
        return 1;
    }
    s = 0;
    a = 1;
    if (a % 2 != 0) {
        while (a <= n * 2){
            s += a;
            a +=2;
        }
        
    }
    std::cout << "Сумма нечетных чисел: "<< s;
    return 0;
}