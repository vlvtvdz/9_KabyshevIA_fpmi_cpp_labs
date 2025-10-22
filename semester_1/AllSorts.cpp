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

// Сортировка вставками
void InsertionSort(int* arr, int total) {
    for (int i = 1; i < total; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void QuickSort (int** arr) {
    int left = 0;
    int middle = sizeof(arr) / 8 ;
    int right = sizeof(arr) - 1;

    if (left < right) {
        while (left < middle) {
            
        }
    }

}

// Основная функция сортировки матрицы 
void SortMatrixByInsertion(int** matrix, int row, int colum) {
    int total = row * colum;
    int* arr = MatrixToArray(matrix, row, colum);

    InsertionSort(arr, total);

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

    DeleteMemory(matrix, row);
    return 0;
}