#include <iostream>
#include <random>

void AllocateMatrix(int n, int colum, int**& matrix) {
    matrix = new int*[n];
    for (int row = 0; row < n; ++row) {
        matrix[row] = new int[colum];
    }
}

void DeleteMemory(int** matrix, int n) {
    for (int row = 0; row < n; ++row) {
        delete[] matrix[row];
    }
    delete[] matrix;
}

void FillMatrixManual(int** matrix, int n, int colum) {
    std::cout << "Введите элементы матрицы (" << n << "x" << colum << "):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < colum; ++j) {
            std::cin >> matrix[i][j];
        }
    }
}

void FillMatrixRandom(int** matrix, int n, int colum, int a, int b) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(a, b);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < colum; ++j) {
            matrix[i][j] = dist(gen);
        }
    }
}

void PrintMatrix(int** matrix, int n, int colum) {
    std::cout << "\nМатрица:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < colum; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int CountColumnsWithoutA11(int** matrix, int n, int colum) {
    int a11 = matrix[0][0];
    int count = 0;
    for (int j = 0; j < colum; ++j) {
        bool hasA11 = false;
        for (int i = 0; i < n; ++i) {
            if (matrix[i][j] == a11) {
                hasA11 = true;
                break;
            }
        }
        if (!hasA11) count++;
    }
    return count;
}

int FindRowWithLongestSeries(int** matrix, int n, int colum) {
    int maxRow = 0;
    int maxSeries = 1;

    for (int i = 0; i < n; ++i) {
        int currentSeries = 1;
        for (int j = 1; j < colum; ++j) {
            if (matrix[i][j] == matrix[i][j - 1]) {
                currentSeries++;
                if (currentSeries > maxSeries) {
                    maxSeries = currentSeries;
                    maxRow = i;
                }
            } else {
                currentSeries = 1;
            }
        }
    }
    return maxRow + 1;
}

int main() {
    int n, colum, choice, a, b;
    int** matrix = nullptr;

    std::cout << "Введите количество строк и столбцов: ";
    std::cin >> n >> colum;

    AllocateMatrix(n, colum, matrix);

    std::cout << "Выберите способ заполнения:\n1 — вручную\n2 — случайными числами\nВаш выбор: ";
    std::cin >> choice;

    if (choice == 1) {
        FillMatrixManual(matrix, n, colum);
    } else {
        std::cout << "Введите границы интервала [a, b]: ";
        std::cin >> a >> b;
        FillMatrixRandom(matrix, n, colum, a, b);
    }

    PrintMatrix(matrix, n, colum);

    int countCols = CountColumnsWithoutA11(matrix, n, colum);
    int rowNum = FindRowWithLongestSeries(matrix, n, colum);

    std::cout << "\nКоличество столбцов, не содержащих элемент a11: " << countCols << "\n";
    std::cout << "Номер строки с самой длинной серией одинаковых элементов: " << rowNum << "\n";

    DeleteMemory(matrix, n);
    return 0;
}