#include <iostream>
void TryRead(int& number) {
    if (!(std::cin >> number)) {
        std::cout << "Fail on reading the number." << std::endl;
        exit(0);
    }
}
bool IsNotNegative(int number){
    return abs(number) == number;
    }
int main() {
    int number;
    std::cout << "Enter the number: ";
    TryRead(number);
    bool std_non_negative_check = (number >= 0);
    if (IsNotNegative(number) == std_non_negative_check) {
        std::cout << "Try again...." << std::endl;
    }
    else {
        std::cout << "Shit, you broke my program :(" << std::endl; // надо ввести -2147483648 потому что это нижняя шраница для int
        exit(1);
        }
return 0;
}