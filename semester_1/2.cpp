#include <iostream>
int main ()
{
    int a, n, c, d;
    std::cout << "Введите k: ";
    if (!(std::cin >> n) || n < 2) {
        std::cerr << "Ошибка: введите другое число!" ;
        return 1;
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