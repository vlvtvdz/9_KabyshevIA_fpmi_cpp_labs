#include <iostream>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    int a, b;
    std::cout << "Введите два числа: ";
    std::cin >> a >> b;

    int g = gcd(a, b);

    std::cout << "Общие делители: ";
    for (int i = 1; i <= g; i++) {
        if (g % i == 0) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;

    return 0;
}