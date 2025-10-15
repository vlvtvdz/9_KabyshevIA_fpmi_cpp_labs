#include <iostream>
void AllocateMatrix (int n, int colum) {
    int** matrix = new int* [n];
    for (int row = 0; row < n; ++row) {
        matrix [row] = new int [colum];

    }
}

void DeleteMemory (int** matrix, int n) {
    for (int row = 0; row < n; ++row) {
        delete[] matrix[row];
    }
}

void PrintMatrix (int** matrix, int n, int m) {
    for (int row = 0 ; int i = 0; row < n && m < i; ++row && ++i) {}

}

int main () {

}