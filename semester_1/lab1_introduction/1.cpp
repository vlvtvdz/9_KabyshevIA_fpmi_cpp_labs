#include <iostream>
using namespace std;
int main()
{ 
    int a, b, d;
    cout << "Enter a, b, d ";
    cin >>a >>b >>d;
    int x = a;
    if (d == 0) {
        cout << "Шаг прогрессии не может быть равен 0, перезапустите программу";
    }
    while ((d != 0) && (a <= b)) {
      if  (a % 3 == 0) {
        cout << a << " ";
      }
        a += d;
    }
    while ((d != 0) && (b <= a)) {
      if  (b % 3 == 0) {
        cout << b << " ";
      }
        b += d;
    }
    return 0;
}