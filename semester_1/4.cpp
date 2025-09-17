#include <iostream>

int main() {
    long long k, a, p1;
    std::cout << "Введите k: ";
    if (!(std::cin >> k) || k < 1) {
        std::cerr << "Ошибка: введите другое число!" ;
        return 1;
    }
    if (k % 2 == 0) {
        a = 2;
        p1 = a;
        while (a <= k){
            p1 *= a;
            a += 2; 
        }     
        std::cout << "Двойной факториал равен: " << p1; 
    }
    else {
        a = 1;
        p1 = a;
        while (a <= k){
            p1 *= a;
            a += 2;
        }    
        std::cout << "Двойной факториал равен: " << p1;
    }
}
