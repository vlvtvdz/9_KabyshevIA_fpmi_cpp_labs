#include <iostream>
#include <string>
#include <vector>

void AllocateArray(std::vector<int>& arr, int& number, const std::string& text);

void FillArray(std::vector<int>& arr, int& number, const std::string& text1);

void FindIndexes(std::vector<int>& arr, int& number, int& max_index, int& min_index);

void Product (std::vector<int>& arr, int& min_index, int& product, int& max_index);

void SortOddDescending(std::vector<int>& arr, int& number);

void PrintArray(const std::vector<int>& arr, const std::string& text);

int main() {
    int number;
    std::vector<int> arr;
    int max_index = 0;
    int min_index = 0;
    int product = 1;

    AllocateArray (arr, number, "Enter number of elements in array: ");
    FillArray (arr, number, "Please, enter elements in array: ");
    
    FindIndexes(arr, number, max_index, min_index);
    Product (arr, min_index, product, max_index);
    std::cout << "Product between is: " << product << std::endl;

    std::cout << "\nOriginal array:\n";
    PrintArray(arr, "Array: ");

    SortOddDescending(arr, number);
    std::cout << "\nArray after sorting odd indices (descending):\n";
    PrintArray(arr, "Array: ");

}

void AllocateArray (std::vector<int>& arr, int& number, const std::string& text) {
    std::cout << text;
    std::cin >> number;
    arr.resize(number);
}

void FillArray (std::vector<int>& arr, int& number, const std::string& text1) {
    try {
        for (int i = 0; i < number; ++i) {

            std::cout << text1 << " [" << i + 1 << "]: ";
            std::cin >> arr[i];

            if (!std::cin) {
                throw std::string("Error! Enter a number!");
            }
        }
    } 
    catch (const std::string& error) {
        std::cout << error << std::endl;
    }
}

void FindIndexes(std::vector<int>& arr, int& number, int& max_index, int& min_index) {
    int Min = arr[0];
    int Max = arr[0];
    min_index = 0;
    max_index = 0;

    try {

        for (int i = 1; i < number; ++i) {
           
            if (arr[i] < Min) {
                
                Min = arr[i];
                min_index = i;

            }

        }

        for (int i = 1; i < number; ++i) {

            if (arr[i] > Max) {

                Max = arr[i];
                max_index = i;

            }
            
        }

        int result = max_index - min_index;

        if (abs(result) < 2) {
            throw std::string("Error! There is less than 1 element between!");
        }
    } 
    catch (const std::string& error) {
        std::cout << error << std::endl;
    }
}


void Product (std::vector<int>& arr, int& min_index, int& product, int& max_index) {
    if (min_index > max_index) std::swap(min_index, max_index);

    for (int i = min_index + 1; i < max_index; ++i) {
        product *= arr[i];
    }
}


void SortOddDescending(std::vector<int>& arr, int& number) {
    for (int i = 1; i < number; i += 2) {

        for (int j = i + 2; j < number; j += 2) {

            if (arr[i] < arr[j]) {

                std::swap(arr[i], arr[j]);

            }

        }

    }
    
}


void PrintArray(const std::vector<int>& arr, const std::string& text) {
    std::cout << text;
    for (int el : arr) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}