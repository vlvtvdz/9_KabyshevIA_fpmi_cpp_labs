#include <iostream>
#include <string>
#include <vector>

void AllocateArray(std::vector<int>& arr, int& number, const std::string& text);

void FillArray(std::vector<int>& arr, int& number, const std::string& text1);

void FindIndexes(std::vector<int>& arr, int& number, int& max_index, int& min_index);

void Product (std::vector<int>& arr, int& min_index, int& product, int& max_index);

int main() {
    int number;
    std::vector<int> arr;
    int max_index;
    int min_index;
    int product = 1;

    AllocateArray (arr, number, "Enter number of elements in array: ");
    FillArray (arr, number, "Please, enter elements in array: ");
    FindIndexes(arr, number, max_index, min_index);
    Product (arr, min_index, product, max_index);
    std::cout << "Product between is: " << product;
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

            if (!std::cin) { // если введено не число
                throw std::string("Error! Enter a number! ");
            }
        }
    } 
    catch (const std::string& error) {
        std::cout << error << std::endl;
    }
}

void FindIndexes(std::vector<int>& arr, int& number, 
    int& max_index,
    int& min_index) {
    int Min = arr[number];
    int Max = arr[0];
    
    try {
        for (int i = number; i > 0; --i) {
        
            if (arr[i] < Min && arr[i+1] != Min) {
                Min = arr[i];
                min_index = i;
            }
        }
        
        for (int i = 0; i < number; ++i){

            if (arr[i] > Max && arr[i-1] != Max) {
                Max = arr[i];
                max_index = i;
            }
        }        
        
        
        int result = max_index - min_index;

        if (result > 0) {
            if (result < 1) {
                throw std::string("Error! There is less then 1 element between: ");
            }
        }
        else {
            if (abs(result) < 1) {
                throw std::string("Error! There is less then 1 element between: ");
            }
        }

    } 
    catch (const std::string& error) {
        std::cout << error << std::endl;
    }
    
}

void Product (std::vector<int>& arr, int& min_index, int& product, int& max_index) {

        if (min_index > max_index) {
            for (max_index < min_index; ++max_index;) {
                product *= arr[max_index];
            }
        }

        else {
            for (max_index > min_index; ++min_index;) {
                product *= arr[min_index];
            }
        }

}
    
