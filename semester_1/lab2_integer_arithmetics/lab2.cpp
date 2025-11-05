#include <iostream>
int main() {
    long long a, b;
    const char* error;
    try {
        std::cout << "Введите числа a и b: ";

        if (!(std::cin >> a >> b)) {
            std::cout << "Ошибка ввода! Введите два целых числа.\n";
            return 1;
        }

        if (a == b) {
            throw error = "Error, there is no numbers between A and B! \n";
        }

        if (a < 0 || b < 0) {
            throw error = "Error, you could enter only positive! \n";
        }

         if (a - b == 1 || b - a == 1 ) {
            throw error = "Error, there are no numbers! \n";
        }
    
        if (a > b) {
            long long t = a;
            a = b;
            b = t; 
        }
        std::cout << "Простые числа на отрезке [" << a << "; " << b << "]: ";
        for (long long n = a; n <= b; ++n) {
            if (n >= 2) {
                long long j = 2;
                while (j * j <= n && n % j != 0)
                j++;
                if (j * j > n) 
                std::cout << n << " ";
            }
        }
        std::cout << std::endl;
    } catch (const char*) {
        std::cout << error;
    }
}


// std::vector<std::vector<int>> matrix (n, vectore<int>(m))