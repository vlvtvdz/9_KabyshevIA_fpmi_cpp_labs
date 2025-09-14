#include <iostream>
using namespace std;

int main() {
    long long a, b, d;
    cout << "Введите a, b, d: ";
    cin >> a >> b >> d;

    long long L = min(a, b);
    long long R = max(a, b);

    // Первый член прогрессии
    long long x = a;

    if (d == 0) {
        // Прогрессия постоянная
        if (x % 3 == 0 && x >= L && x <= R) {
            cout << x << " ";
        }
        return 0;
    }

    // Перебираем члены прогрессии
    while (true) {
        if (x >= L && x <= R) {
            if (x % 3 == 0) {
                cout << x << " ";
            }
        }

        // Условие выхода
        if (d > 0 && x > R) break;
        if (d < 0 && x < L) break;

        x += d;
    }

    return 0;
}