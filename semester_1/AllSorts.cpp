#include <iostream>

// Выделение памяти под матрицу
void AllocateMatrix(int n, int colum, int**& matrix) {
    matrix = new int*[n];
    for (int row = 0; row < n; ++row) {
        matrix[row] = new int[colum];
    }
}

// Освобождение памяти
void DeleteMemory(int** matrix, int n) {
    for (int row = 0; row < n; ++row) {
        delete[] matrix[row];
    }
    delete[] matrix;
}

// Ввод матрицы
void EnterMatrix(int** matrix, int row, int colum) {
    std::cout << "Введите элементы матрицы (" << row << "x" << colum << "):\n";
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < colum; ++j) {
            std::cin >> matrix[i][j];
        }
    }
}

// Вывод матрицы
void PrintMatrix(int** matrix, int row, int colum) {
    std::cout << "\nМатрица:\n";
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < colum; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

// Функция переноса матрицы в одномерный массив 
int* MatrixToArray(int** matrix, int row, int colum) {
    int total = row * colum;
    int* arr = new int[total];
    int k = 0;

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < colum; ++j) {
            arr[k++] = matrix[i][j];
        }
    }

    return arr;
}

// Функция обратного переноса массива в матрицу
void ArrayToMatrix(int** matrix, int* arr, int row, int colum) {
    int k = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < colum; ++j) {
            matrix[i][j] = arr[k++];
        }
    }
}

bool compareAscending(int x, int y) {
    return x < y;
}

bool compareDecending(int x, int y) {
    return x > y;
}

// Сортировка вставками
void InsertionSort(int* arr, int total) { // InsertionSort(int* arr, int total, bool (*comp)(int, int))
    for (int i = 1; i < total; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) { // arr[j] > key -> comp(arr[j], key)
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// Функция быстрой сортировки (рекурсивная)
void quicksort(int* arr, int left, int right) {
    int i = 0;
    int j = right;
    int middle = arr[(left + right) / 2]; // опорный элемент

    while (i <= j) {
        while (arr[i] < middle) i++;
        while (arr[j] > middle) j--;

        if (i <= j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    if (left < j) quicksort(arr, left, j);
    if (i < right) quicksort(arr, i, right);
}

// Основная функция сортировки матрицы 
void SortMatrixByInsertion(int** matrix, int row, int colum) {
    int total = row * colum;
    int* arr = MatrixToArray(matrix, row, colum);

    InsertionSort(arr, total);

    ArrayToMatrix(matrix, arr, row, colum);
    delete[] arr;
}

void QuickSortMatrix(int** matrix, int row, int colum) {
    int total = row * colum;
    int* arr = MatrixToArray(matrix, row, colum);

    quicksort(arr, 0, total - 1);

    ArrayToMatrix(matrix, arr, row, colum);
    delete[] arr;
}

// MAIN 
int main() {
    int row, colum;
    int** matrix = nullptr;

    std::cout << "Введите количество строк и столбцов: ";
    std::cin >> row >> colum;

    AllocateMatrix(row, colum, matrix);
    EnterMatrix(matrix, row, colum);

    std::cout << "\nИсходная матрица:";
    PrintMatrix(matrix, row, colum);

    SortMatrixByInsertion(matrix, row, colum);

    std::cout << "\nМатрица после сортировки вставками:";
    PrintMatrix(matrix, row, colum);

    quicksort()

    DeleteMemory(matrix, row);
    return 0;
}