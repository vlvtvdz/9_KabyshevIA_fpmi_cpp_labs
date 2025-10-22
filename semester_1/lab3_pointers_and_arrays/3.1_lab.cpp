#include <iostream>
#include <random>


int myAbs(int x) {
    return (x < 0) ? -x : x;
}

bool readInt(const char* prompt, long long& out) {
    std::cout << prompt;
    if (!(std::cin >> out)) {
        std::cerr << "Ошибка: введено не число!\n";
        return false;
    }
    return true;
}

void validate(long long value, long long max, const char* name, int errNeg, int errTooBig) {
    if (value <= 0) {
        std::cerr << "Ошибка: " << name << " должно быть положительным числом!\n";
        exit(errNeg);
    }
    if (value > max) {
        std::cerr << "Ошибка: " << name << " слишком велико!\n";
        exit(errTooBig);
    }
}


int* allocateArray(int size) {
    return new int[size];
}

void fillArrayManual(int* arr, int size) {
    std::cout << "Введите данные в массив: ";
    for (int i = 0; i < size; ++i) {
        while (!(std::cin >> arr[i])) {
            std::cin.clear();
            std::cin.ignore(100000, '\n');
            std::cout << "Ошибка ввода! Повторите элемент #" << i << ": ";
        }
    }
}

void fillArrayRandom(int* arr, int size, std::mt19937& gen, std::uniform_int_distribution<>& dist) {
    for (int i = 0; i < size; ++i)
        arr[i] = dist(gen);
}

int askFillMethod() {
    int choice;
    std::cout << "Как заполнить массив? (1 - вручную, 2 - случайными числами): ";
    while (!(std::cin >> choice) || (choice != 1 && choice != 2)) {
        std::cin.clear();
        std::cin.ignore(100000, '\n');
        std::cout << "Введите 1 или 2: ";
    }
    return choice;
}

void findMinMaxIndices(const int* arr, int size, int& minIdx, int& maxIdx) {
    minIdx = 0; maxIdx = 0;
    for (int i = 1; i < size; ++i) {
        if (arr[i] < arr[minIdx]) minIdx = i;
        if (arr[i] > arr[maxIdx]) maxIdx = i;
    }
}

int productBetweenMinMax(const int* arr, int size) {
    int minIdx, maxIdx;
    findMinMaxIndices(arr, size, minIdx, maxIdx);

    int left = (minIdx < maxIdx) ? minIdx : maxIdx;
    int right = (minIdx > maxIdx) ? minIdx : maxIdx;

    if (right - left <= 1) return 0;

    long long product = 1;
    for (int i = left + 1; i < right; ++i)
        product *= arr[i];

    return static_cast<int>(product);
}

void bubbleSortByAbs(int* arr, int size) {
    for (int pass = 0; pass < size - 1; ++pass) {
        for (int i = 0; i < size - 1; ++i) {
            if (myAbs(arr[i]) > myAbs(arr[i + 1])) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
    }
}

int removeNSmallest(int* arr, int size, int n) {
    if (n > size) n = size;

    for (int k = 0; k < n; ++k) {
        int minIdx = 0;
        for (int i = 1; i < size; ++i)
            if (arr[i] < arr[minIdx]) minIdx = i;

        for (int j = minIdx; j < size - 1; ++j)
            arr[j] = arr[j + 1];

        --size;
    }
    return size;
}

void printArray(const int* arr, int size) {
    for (int i = 0; i < size; ++i)
        std::cout << "Числа в массиве: " << arr[i] << '\n';
}


int main() {
    const long long LIMIT = 1000000;
    long long nLL, aLL;

    if (!readInt("Введите n: ", nLL)) return 1;
    validate(nLL, LIMIT, "n", 2, 3);

    if (!readInt("Введите a: ", aLL)) return 4;
    validate(aLL, LIMIT, "a", 5, 6);

    int n = static_cast<int>(nLL);
    int a = static_cast<int>(aLL);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-100, 100);

    int* arr = allocateArray(a);
    int choice = askFillMethod();

    if (choice == 1)
        fillArrayManual(arr, a);
    else
        fillArrayRandom(arr, a, gen, dist);

    int product = productBetweenMinMax(arr, a);

    bubbleSortByAbs(arr, a);
    a = removeNSmallest(arr, a, n);

    printArray(arr, a);
    std::cout << product << " = Произведение всех элементов массива между минимальным и максимальными членами\n";

    delete[] arr;
    return 0;
}