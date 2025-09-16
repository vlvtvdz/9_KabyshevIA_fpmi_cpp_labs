#include <iostream>
#include <vector>
using namespace std;

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
    cout << "Введите два числа: ";
    cin >> a >> b;

    int g = gcd(a, b);

    cout << "Общие делители: ";
    for (int i = 1; i <= g; i++) {
        if (g % i == 0) {
            cout << i << " ";
        }
    }
    cout << endl;

    return 0;
}