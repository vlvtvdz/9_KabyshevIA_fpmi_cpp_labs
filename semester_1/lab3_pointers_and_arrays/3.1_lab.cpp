#include <iostream>
#include <random>
#include <string>
#include <cstdlib>


void AllocateArray(double*& arr, int& number, const std::string& text);
void FillArray(double* arr, int& number);
double Abs(double value);
double SumPositive(double* arr, int number);
void FindIndexes(double* arr, int number, int& max_index, int& min_index);
double Product(double* arr, int min_index, int max_index);
void SortOddDescending(double* arr, int number);
void PrintArray(double* arr, int number, const std::string& text);


int main() {
    try {
        int number;
        double* arr = nullptr;
        int max_index = 0, min_index = 0;

        AllocateArray(arr, number, "Enter number of elements in array: ");
        FillArray(arr, number);

        std::cout << "\nOriginal array:\n";
        PrintArray(arr, number, "Array: ");

        // Сумма положительных элементов
        double sum;
        try{
            std::cout << "\nSum of positive elements: " << SumPositive(arr, number)<< "\n";
        }catch (const std::string& error) {
            std::cout << error << "\n";
        }
        
        try {
            // Индексы первого max по модулю и последнего min по модулю
            FindIndexes(arr, number, max_index, min_index);

            // Произведение между ними
            double product = Product(arr, min_index, max_index);
            std::cout << "Product of elements between first |max| and last |min|: " << product << "\n";

        } catch (const std::string& error) {
        std::cout << error << "\n";
        }
        
        // Сортировка нечётных индексов по убыванию
        SortOddDescending(arr, number);
        std::cout << "\nArray after sorting odd indices (descending):\n";
        PrintArray(arr, number, "Array: ");

        delete[] arr;
        arr = nullptr;
    } 
    catch (const std::string& error) {
        std::cout << "Exception caught: " << error << "\n";
    }
    catch (...) {
        std::cout << "Unknown error occurred!\n";
    }

    return 0;
}


void AllocateArray(double*& arr, int& number, const std::string& text) {
   
    std::cout << text;
    std::cin >> number;

    if (!std::cin || number <= 0)
        throw std::string("Error! Invalid array size!");

    arr = new double[number];
    
}


void FillArray(double* arr, int& number) {
    std::cout << "Choose input method:\n1 - Manual input\n2 - Random generation\nYour choice: ";
    int choice;
    std::cin >> choice;


    if (choice == 1) {
        for (int i = 0; i < number; ++i) {
            std::cout << "Enter element [" << i + 1 << "]: ";
            std::cin >> arr[i];
            if (!std::cin)
                throw std::string("Error! Invalid number entered!");
        }
    } else if (choice == 2) {
        double min_val, max_val;
        std::cout << "Enter range for random values (min max): ";
        std::cin >> min_val >> max_val;

        if (!std::cin || min_val > max_val) {
            throw std::string("Error! Invalid range!");
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dist(min_val, max_val);

        for (int i = 0; i < number; ++i)
            arr[i] = dist(gen);

        std::cout << "\nRandomly generated array:\n";
        PrintArray(arr, number, "Array: ");
    } else {
        throw std::string("Invalid choice! Must be 1 or 2.");
    }
    
}


double Abs(double value) {
    return value >= 0 ? value : -value;
}


double SumPositive(double* arr, int number) {
    double sum = 0;
    for (int i = 0; i < number; ++i)
        if (arr[i] > 0)
            sum += arr[i];
    if (sum == 0) {
        throw std::string("There are no positive numbers in array \n");
    }


    return sum;
}


void FindIndexes(double* arr, int number, int& max_index, int& min_index) {
    double max_val = Abs(arr[0]);
    double min_val = Abs(arr[0]);
    max_index = 0;
    min_index = 0;

    for (int i = 1; i < number; ++i) {
        if (Abs(arr[i]) > max_val) {
            max_val = Abs(arr[i]);
            max_index = i;
        }
    }

    for (int i = 0; i < number; ++i) {
        if (Abs(arr[i]) <= min_val) {
            min_val = Abs(arr[i]);
            min_index = i;
        }
    }

    std::cout << "\nFirst max element index: " << max_index
            << " (value = " << arr[max_index] << ")";
    std::cout << "\nLast min element index: " << min_index
            << " (value = " << arr[min_index] << ")\n";

    if (max_index == min_index)
        throw std::string("Max and min absolute values are at the same position! \n");

}


double Product(double* arr, int min_index, int max_index) {
    double product;
    try {
        if (min_index > max_index) {
                int tmp = min_index;
                min_index = max_index;
                max_index = tmp;
            }

        if ((max_index - min_index) < 2)
            throw std::string("There is less than one element between max and min! \n");

        double product = 1.0;
        for (int i = min_index + 1; i < max_index; ++i)
            product *= arr[i];
    } catch (const std::string& error) {
        std::cout << error << "\n";\
    }

    return product;
}


void SortOddDescending(double* arr, int number) {
    try {
        short int Sort_indicator = 0; // Добавил эту переменную для отслеживания сортировки  
        for (int i = 1; i < number; i += 2) {
            for (int j = i + 2; j < number; j += 2) {
                if (arr[i] < arr[j]) {
                    double tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                    Sort_indicator += 1;
                }
            }
        }

        if (Sort_indicator == 0) {
        throw const std::string ("There is nothing to sort! \n"); 
        }

    } catch (const std::string& text) {
        std::cout << text << "\n";
    }  

}


void PrintArray(double* arr, int number, const std::string& text) {
    std::cout << text << " ";
    for (int i = 0; i < number; ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n";
}