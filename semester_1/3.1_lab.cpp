#include <iostream>
#include <array>
int main () {

    long long a, n;
        std::cout << "Введите n: ";
        if (!(std::cin >> n) || a - 1 == 0 || !(std::cin >> a)) {
            std::cerr << "Ошибка: введите другое число!" ;
            return 1;
        }

        int* mass = new int[a - 1];

    std::cout << "Введите данные в массив ";
    for (int i = 0; i < a; ++i) {
        std::cin >> mass[i];
    }

    int min = mass[0];
    int max = mass[0];
    int p = 1;
    
    for (int i = 0; i < a; ++i ) {

        if (mass[i] < min) {
            min = mass[i];
        }

        if (mass[i] > max){
            max = mass[i];
        }
    
    }

    for (int i = 0; i < a; ++i && min > mass[i] && max > mass[i]) {
         p *= mass[i];
    }

    std::cout << min << " Минимальный элемент массива ";
    std::cout << max << " Максимальный элемент массива ";
    std::cout << p << " Произведение всех элементов массива между минимальным и максимальными членами";
    delete[] mass;

    return 0;
}