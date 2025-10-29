#include <iostream>

// Выделение памяти под матрицу
void AllocateMatrix(int n, int colum, int**& matrix) {
    matrix = new int*[n];
    for (int row = 0; row < n; ++row)
        matrix[row] = new int[colum];
}

// Освобождение памяти
void DeleteMemory(int** matrix, int n) {
    for (int row = 0; row < n; ++row)
        delete[] matrix[row];
    delete[] matrix;
}

// Ввод матрицы
void EnterMatrix(int** matrix, int row, int colum) {
    std::cout << "Введите элементы матрицы (" << row << "x" << colum << "):\n";
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < colum; ++j)
            std::cin >> matrix[i][j];
}

// Вывод матрицы
void PrintMatrix(int** matrix, int row, int colum) {
    std::cout << "\nМатрица:\n";
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < colum; ++j)
            std::cout << matrix[i][j] << " ";
        std::cout << "\n";
    }
}

// Перенос матрицы в одномерный массив
int* MatrixToArray(int** matrix, int row, int colum) {
    int total = row * colum;
    int* arr = new int[total];
    int k = 0;
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < colum; ++j)
            arr[k++] = matrix[i][j];
    return arr;
}

// Обратный перенос одномерного массива в матрицу
void ArrayToMatrix(int** matrix, int* arr, int row, int colum) {
    int k = 0;
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < colum; ++j)
            matrix[i][j] = arr[k++];
}

// Сортировка вставками
void InsertionSort(int* arr, int total) {
    for (int i = 1; i < total; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Модификация сортировки вставками — бинарные вставки
int BinarySearch(int* arr, int item, int low, int high) {
    while (low <= high) {
        int mid = (low + high) / 2;
        if (item == arr[mid]) return mid + 1;
        else if (item > arr[mid]) low = mid + 1;
        else high = mid - 1;
    }
    return low;
}

void BinaryInsertionSort(int* arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        int loc = BinarySearch(arr, key, 0, j);
        while (j >= loc) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Быстрая сортировка (Хоара)
void QuickSort(int* arr, int left, int right) {
    int i = left, j = right;
    int pivot = arr[(left + right) / 2];
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            int t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
            i++; j--;
        }
    }
    if (left < j) QuickSort(arr, left, j);
    if (i < right) QuickSort(arr, i, right);
}

// Сортировка выбором
void SelectionSort(int* arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j)
            if (arr[j] < arr[minIndex]) minIndex = j;
        int t = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = t;
    }
}

// Модификация сортировки выбором — двусторонний выбор
void DoubleSelectionSort(int* arr, int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        int minIdx = left, maxIdx = right;
        for (int i = left; i <= right; ++i) {
            if (arr[i] < arr[minIdx]) minIdx = i;
            if (arr[i] > arr[maxIdx]) maxIdx = i;
        }
        int temp = arr[left];
        arr[left] = arr[minIdx];
        arr[minIdx] = temp;

        if (maxIdx == left) maxIdx = minIdx;

        temp = arr[right];
        arr[right] = arr[maxIdx];
        arr[maxIdx] = temp;

        left++;
        right--;
    }
}

// Пузырьковая сортировка
void BubbleSort(int* arr, int n) {
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (arr[j] > arr[j + 1]) {
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
}

// Модификация пузырьковой сортировки — с флагом оптимизации
void BubbleSortOptimized(int* arr, int n) {
    bool swapped;
    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// Сортировка подсчётом
void CountingSort(int* arr, int n) {
    int min = arr[0], max = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
    int range = max - min + 1;
    int* count = new int[range];
    for (int i = 0; i < range; ++i) count[i] = 0;
    for (int i = 0; i < n; ++i) count[arr[i] - min]++;
    int index = 0;
    for (int i = 0; i < range; ++i)
        while (count[i]-- > 0) arr[index++] = i + min;
    delete[] count;
}

// Сортировка слиянием
void Merge(int* arr, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int* L = new int[n1];
    int* R = new int[n2];
    for (int i = 0; i < n1; ++i) L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    delete[] L;
    delete[] R;
}

void MergeSort(int* arr, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        MergeSort(arr, l, m);
        MergeSort(arr, m + 1, r);
        Merge(arr, l, m, r);
    }
}

// Основная программа
int main() {
    int row, colum;
    std::cout << "Введите количество строк и столбцов: ";
    std::cin >> row >> colum;

    int** matrix;
    AllocateMatrix(row, colum, matrix);
    EnterMatrix(matrix, row, colum);

    int total = row * colum;
    int* arr = MatrixToArray(matrix, row, colum);

    std::cout << "\nВыберите сортировку:\n";
    std::cout << "1. Вставками\n2. Бинарными вставками\n3. Быстрая\n4. Выбором\n5. Двусторонний выбор\n6. Пузырьковая\n7. Оптимизированная пузырьковая\n8. Подсчётом\n9. Слиянием\n> ";
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1: InsertionSort(arr, total); break;
        case 2: BinaryInsertionSort(arr, total); break;
        case 3: QuickSort(arr, 0, total - 1); break;
        case 4: SelectionSort(arr, total); break;
        case 5: DoubleSelectionSort(arr, total); break;
        case 6: BubbleSort(arr, total); break;
        case 7: BubbleSortOptimized(arr, total); break;
        case 8: CountingSort(arr, total); break;
        case 9: MergeSort(arr, 0, total - 1); break;
        default: std::cout << "Неверный выбор!"; return 0;
    }

    ArrayToMatrix(matrix, arr, row, colum);
    std::cout << "\nОтсортированная матрица:\n";
    PrintMatrix(matrix, row, colum);

    delete[] arr;
    DeleteMemory(matrix, row);
    return 0;
}