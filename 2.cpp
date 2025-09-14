#include <iostream>
using namespace std;
int main ()
{
    int a, n, c, d;
    cout << "Введите конечный член промежутка ";
    cin >>n;
    while (n <= 2) {
        cout << "Введите число больше 1 ";
        cin >>n;
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
        cout << c << " Сумма четных ";
        cout << d << " Произведение нечетных ";
    }
    return 0;
}