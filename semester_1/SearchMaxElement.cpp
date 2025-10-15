#include <iostream>
int SearchMaxElement (int size, const int mass[], int MaxElement) {
    if (size <= 0) return 1;      // защита от пустого массива (или бросайте исключение)
    MaxElement = mass[0];
    for (int i = 1; i < size; ++i) {
        if (mass[i] > MaxElement) {
            MaxElement = mass[i];
        }
    }
    return MaxElement;
}

int main () {
    int size;
    std::cout << "Введите число элементов массива: ";
    std::cin >> size;
    int* mass = new int[size]; // Ввожу динамический массив 
    std::cout << "Введите елементы массива: ";
    for (int i = 0; i < size; ++i) {
        std::cin >> mass[i];
    }
    int MaxIndex = 0;
    int MaxElement = SearchMaxElement(size, mass, MaxElement);
    std::cout << "\n Максимальный элемент: " << MaxElement << std::endl; // Вывожу максимальный элемент
    delete[] mass;
    return 0;
}

