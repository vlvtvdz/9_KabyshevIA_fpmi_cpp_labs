#include <iostream>
#include <random>
#include <string>

int myAbs(int x);

int InputPositive(const char* text, int limit);

void FillArray(int* arr, int size);

void PrintArray(int* arr, int size);

void FindMinMaxIndexes(int* arr, int size, int& minIndex, int& maxIndex);

int ProductBetweenMinMax(int* arr, int size);

void RemoveNMinElements(int* arr, int& size, int n);

void SortByAbs(int* arr, int size);

const int MAX_SIZE = 1000; // ограничение для статического массива


int main() {
    try {
        int arr[MAX_SIZE];
        int size = InputPositive("Введите размер массива: ", MAX_SIZE);
        int nRemove = InputPositive("Введите количество минимальных элементов для удаления: ", size);

        FillArray(arr, size);
        PrintArray(arr, size);

        int product = ProductBetweenMinMax(arr, size);
        std::cout << "\nПроизведение элементов между min и max: " << product << "\n";

        RemoveNMinElements(arr, size, nRemove);
        std::cout << "\nМассив после удаления " << nRemove << " минимальных элементов:\n";
        PrintArray(arr, size);

        SortByAbs(arr, size);
        std::cout << "\nМассив после сортировки по возрастанию модулей:\n";
        PrintArray(arr, size);
    }
    catch (const std::string& error) {
        std::cout << error << "\n";
    }
    catch (...) {
        std::cout << "Неизвестная ошибка!\n";
    }

    return 0;
}

int myAbs(int x) {
    return (x < 0) ? -x : x;
}

// ввод положительного числа с проверкой
int InputPositive(const char* text, int limit) {
    int num;
    std::cout << text;

    if (!(std::cin >> num))
        throw std::string("Ошибка: введено не число!");

    if (num <= 0)
        throw std::string("Ошибка: число должно быть положительным!");

    if (num > limit)
        throw std::string("Ошибка: превышен допустимый размер массива!");

    return num;
}

// заполнение массива вручную или случайно
void FillArray(int* arr, int size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-100, 100);

    int choice;
    std::cout << "Как заполнить массив? (1 - вручную, 2 - случайными числами): ";

    if (!(std::cin >> choice))
        throw std::string("Ошибка: введено не число!");

    if (choice == 1) {
        std::cout << "Введите элементы массива:\n";
        for (int i = 0; i < size; ++i) {
            if (!(std::cin >> arr[i]))
                throw std::string("Ошибка: введено не число!");
        }
    } 
    else if (choice == 2) {
        for (int i = 0; i < size; ++i)
            arr[i] = dist(gen);
    } 
    else {
        throw std::string("Ошибка: неверный выбор!");
    }
}

// вывод массива
void PrintArray(int* arr, int size) {
    std::cout << "\nМассив: ";
    for (int i = 0; i < size; ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n";
}

// нахождение индексов минимального и максимального элементов
void FindMinMaxIndexes(int* arr, int size, int& minIndex, int& maxIndex) {
    minIndex = 0;
    maxIndex = 0;

    for (int i = 1; i < size; ++i) {
        if (arr[i] < arr[minIndex])
            minIndex = i;
        if (arr[i] > arr[maxIndex])
            maxIndex = i;
    }

    std::cout << "\nМинимальный элемент: arr[" << minIndex << "] = " << arr[minIndex];
    std::cout << "\nМаксимальный элемент: arr[" << maxIndex << "] = " << arr[maxIndex] << "\n";
}

// произведение элементов между минимальным и максимальным
int ProductBetweenMinMax(int* arr, int size) {
    int minIndex, maxIndex;
    FindMinMaxIndexes(arr, size, minIndex, maxIndex);

    int left = (minIndex < maxIndex) ? minIndex : maxIndex;
    int right = (minIndex > maxIndex) ? minIndex : maxIndex;

    if (right - left <= 1)
        throw std::string("Ошибка: между min и max нет элементов!");

    int product = 1;
    for (int i = left + 1; i < right; ++i)
        product *= arr[i];

    return product;
}

// удаление N наименьших элементов
void RemoveNMinElements(int* arr, int& size, int n) {
    if (n >= size)
        throw std::string("Ошибка: нельзя удалить больше элементов, чем есть в массиве!");

    for (int count = 0; count < n; ++count) {
        int minIndex = 0;
        for (int i = 1; i < size; ++i)
            if (arr[i] < arr[minIndex])
                minIndex = i;

        for (int j = minIndex; j < size - 1; ++j)
            arr[j] = arr[j + 1];
        size--;
    }
}

// сортировка по возрастанию модулей элементов
void SortByAbs(int* arr, int size) {
    for (int pass = 0; pass < size - 1; ++pass) {
        for (int i = 0; i < size - 1; ++i) {
            if (myAbs(arr[i]) > myAbs(arr[i + 1])) {
                int tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
            }
        }
    }
}