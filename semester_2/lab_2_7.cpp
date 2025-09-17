#include <iostream>
using namespace std;

int main() {
    long long n;
    cout << "Введите n: ";
    if (!(cin >> n) || n < 1) {
        cerr << "Ошибка: введите натуральное число!" << endl;
        return 1;
    }

    for (long long a = 1; a <= n; a++) {
        for (long long b = a; b <= n; b++) {
            for (long long c = b; c <= n; c++) {
                if (a * a + b * b == c * c) {
                    cout << "Пифагорова тройка: "
                         << a << " " << b << " " << c << endl;
                }
            }
        }
    }

    return 0;
}