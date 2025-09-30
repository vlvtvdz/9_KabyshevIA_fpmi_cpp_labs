#include <iostream>
#include <array>
int main () {

    long long a, n, v;
        std::cout << "Введите n: ";
        if (!(std::cin >> n)) {                    
            std::cerr << "Ошибка: введено не число!" << std::endl;
            return 1;
        }
        if (n <= 0) {                              
            std::cerr << "Ошибка: n должно быть положительным числом!" << std::endl;
            return 2;
        }
        if (n > 1000000) {                         
            std::cerr << "Ошибка: n слишком велико!" << std::endl;
            return 3;
        }

        std::cout << "Введите a: ";
        if (!(std::cin >> a)) {                   
            std::cerr << "Ошибка: введено не число!" << std::endl;
            return 4;
        }
        if (a <= 0) {                              
            std::cerr << "Ошибка: a должно быть положительным числом!" << std::endl;
            return 5;
        }
        if (a > 1000000) {                         
            std::cerr << "Ошибка: a слишком велико!" << std::endl;
            return 6;
        }

    std::cout << "Выьерите какой вы хотите массив динамический (1) или статический (2)";
    if (!(std::cin >> v)) {                  
        std::cerr << "Ошибка: v должно быть числом!" << std::endl;
        return 1;
    }
    if (v != 1 && v != 2) {                  
        std::cerr << "Ошибка: v может быть только 1 или 2!" << std::endl;
        return 1;
    }
    int* mass = new int[a];

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

    for (int i = 0; i < a; ++i) {
        if (mass[i] != min && mass[i] != max) {
            p *= mass[i];
        }
    }

    std::cout << p << " Произведение всех элементов массива между минимальным и максимальными членами";
    delete[] mass;

    return 0;
}