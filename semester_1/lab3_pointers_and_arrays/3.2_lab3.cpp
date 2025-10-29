#include <iostream>
#include <random>

// Абсолютное значение
int myAbs(int x) {
    return (x < 0) ? -x : x;
}

// Ввод положительного числа с проверками
int InputPositive(const char* text, int limit) {
    long long num;
    std::cout << text;
    if (!(std::cin >> num)) {
        std::cerr << "Ошибка: введено не число!" << std::endl;
        exit(1);
    }
    if (num <= 0) {
        std::cerr << "Ошибка: число должно быть положительным!" << std::endl;
        exit(2);
    }
    if (num > limit) {
        std::cerr << "Ошибка: число слишком велико!" << std::endl;
        exit(3);
    }
    return static_cast<int>(num);
}

// Заполнение массива вручную или случайно
void FillArray(int* mass, int size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-100, 100);

    int choice;
    std::cout << "Как заполнить массив? (1 - вручную, 2 - случайными числами): ";
    if (!(std::cin >> choice)) {
        std::cerr << "Ошибка: введено не число!" << std::endl;
        exit(4);
    }

    if (choice == 1) {
        std::cout << "Введите элементы массива:\n";
        for (int i = 0; i < size; ++i) {
            if (!(std::cin >> mass[i])) {
                std::cerr << "Ошибка: введено не число!" << std::endl;
                exit(5);
            }
        }
    } else if (choice == 2) {
        for (int i = 0; i < size; ++i)
            mass[i] = dist(gen);
    } else {
        std::cerr << "Ошибка: неверный выбор!" << std::endl;
        exit(6);
    }
}

// Поиск индексов минимального и максимального элементов
void FindMinMaxIndexes(int* mass, int size, int& minIndex, int& maxIndex) {
    minIndex = 0;
    maxIndex = 0;
    for (int i = 1; i < size; ++i) {
        if (mass[i] < mass[minIndex]) minIndex = i;
        if (mass[i] > mass[maxIndex]) maxIndex = i;
    }
}

// Произведение элементов между min и max
int ProductBetweenMinMax(int* mass, int size) {
    int minIndex, maxIndex;
    FindMinMaxIndexes(mass, size, minIndex, maxIndex);
    int left = (minIndex < maxIndex) ? minIndex : maxIndex;
    int right = (minIndex > maxIndex) ? minIndex : maxIndex;

    if (right - left <= 1)
        return 0;

    int p = 1;
    for (int i = left + 1; i < right; ++i)
        p *= mass[i];

    return p;
}

// Сортировка пузырьком по модулю
void SortByAbs(int* mass, int size) {
    for (int pass = 0; pass < size - 1; ++pass) {
        for (int i = 0; i < size - 1; ++i) {
            if (myAbs(mass[i]) > myAbs(mass[i + 1])) {
                int temp = mass[i];
                mass[i] = mass[i + 1];
                mass[i + 1] = temp;
            }
        }
    }
}

// Удаление N наименьших элементов
void RemoveNMinElements(int* mass, int& size, int n) {
    for (int count = 0; count < n && size > 0; ++count) {
        int minIndex = 0;
        for (int i = 1; i < size; ++i)
            if (mass[i] < mass[minIndex]) minIndex = i;
        for (int j = minIndex; j < size - 1; ++j)
            mass[j] = mass[j + 1];
        size--;
    }
}

// Вывод массива
void PrintArray(int* mass, int size) {
    std::cout << "\nЧисла в массиве: ";
    for (int i = 0; i < size; ++i)
        std::cout << mass[i] << ' ';
    std::cout << '\n';
}

int main() {
    int n = InputPositive("Введите количество минимальных элементов которое надо удалить: ", 1000000);
    int a = InputPositive("Введите длинну массива: ", 1000000);

    int* mass = new int[a];

    FillArray(mass, a);
    int p = ProductBetweenMinMax(mass, a);
    SortByAbs(mass, a);
    RemoveNMinElements(mass, a, n);
    PrintArray(mass, a);

    std::cout << "\n" << p << " = Произведение всех элементов массива между минимальным и максимальным членами\n";

    delete[] mass;
    return 0;
}