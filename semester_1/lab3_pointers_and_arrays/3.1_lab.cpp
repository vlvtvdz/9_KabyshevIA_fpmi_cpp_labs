#include <iostream>
#include <array>
#include <random>  

int myAbs(int x) {
    return (x < 0) ? -x : x;
}

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

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-100, 100);

        int* mass = new int[a];

        int choice;
        std::cout << "Как заполнить массив? (1 - вручную, 2 - случайными числами): ";
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Введите данные в массив: ";
            for (int i = 0; i < a; ++i) {
                std::cin >> mass[i];
            }
        } else if (choice == 2) {
            for (int i = 0; i < a; ++i) {
                mass[i] = dist(gen); 
            }
        }

        int minIndex = 0, maxIndex = 0;
            for (int i = 1; i < a; i++) {
                if (mass[i] < mass[minIndex]) minIndex = i;
                if (mass[i] > mass[maxIndex]) maxIndex = i;
            }
        int left  = (minIndex < maxIndex) ? minIndex : maxIndex;
        int right = (minIndex > maxIndex) ? minIndex : maxIndex;

        int p = 1;
        if (right - left > 1) { 
            for (int i = left + 1; i < right; i++) {
                p *= mass[i];
            }
        } 
        else {
            p = 0; 
        }

        for (int pass = 0; pass < a - 1; pass++) {
            for (int i = 0; i < a - 1; i++) {
                if (myAbs(mass[i]) > myAbs(mass[i + 1])) {
                    int temp = mass[i];
                    mass[i] = mass[i + 1];
                    mass [i + 1] = temp;
                }
            }
        }

        for (int count = 0; count < n; ++count) {
            int minIndex = 0;
            for (int i = 1; i < a; i++) {
                if (mass[i] < mass[minIndex]) {
                    minIndex = i;
                }
            }
            for (int j = minIndex; j < a - 1; j++) {
                mass[j] = mass[j + 1];
            }
            a--;
            
        }
        for (int i = 0; i < a; ++i) {
                std::cout << "Числа в массиве: " << mass[i] << '\n';
        }

        std::cout << p << " = Произведение всех элементов массива между минимальным и максимальными членами";
        delete[] mass;
    

    return 0;
}