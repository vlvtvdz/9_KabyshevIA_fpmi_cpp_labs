#include <iostream>
int main()
{
    int k,a,p1,p2;
    std::cout << "Введите k: ";
    if (!(std::cin >> k)) {
        std::cerr << "Ошибка: введено не число!" << std::endl;
        return 1; 
    }
    while (a<=k) {
        if (k % 2 == 0){
            p1 = 2;
            a = 4;
            p1 *= a;
            a += 2;
        }
        else {
            p2 = 1;
            a = 3;
            p2 *= a;
            a += 2;
        }
    }
    std::cout << "Произведение равно: " <<p1;
    std::cout << "Произведение равно: " <<p2;

}