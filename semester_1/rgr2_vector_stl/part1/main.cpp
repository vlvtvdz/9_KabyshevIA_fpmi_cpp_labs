
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

struct Interval {
    size_t left = 0;
    size_t right = 0;
};

std::vector<int> ReadNumbers() {
    std::vector<int> values;
    std::cout << "Enter integers separated by spaces (empty line to finish):\n";
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            break;
        }
        std::istringstream iss(line);
        int value = 0;
        while (iss >> value) {
            values.push_back(value);
        }
    }
    return values;
}

int ReadIntWithPrompt(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) {
            throw std::runtime_error("Input stream closed unexpectedly.");
        }
        std::istringstream iss(line);
        int value = 0;
        if (iss >> value) {
            return value;
        }
        std::cout << "Please enter a valid integer value.\n";
    }
}

Interval ReadInterval(size_t max_size) {
    while (true) {
        std::cout << "Enter interval boundaries inside [0, " << (max_size - 1)
                  << "] as \"start end\": ";
        std::string line;
        if (!std::getline(std::cin, line)) {
            throw std::runtime_error("Input stream closed unexpectedly.");
        }
        std::istringstream iss(line);
        long long left = 0;
        long long right = 0;
        if (iss >> left >> right && left >= 0 && right >= 0 &&
            left < static_cast<long long>(max_size) &&
            right < static_cast<long long>(max_size)) {
            Interval interval{static_cast<size_t>(left), static_cast<size_t>(right)};
            if (interval.left > interval.right) {
                size_t temp = interval.left;
                interval.left = interval.right;
                interval.right = temp;
            }
            return interval;
        }
        std::cout << "Invalid interval. Please try again.\n";
    }
}

void PrintVector(const std::vector<int>& data, const std::string& label) {
    std::cout << label;
    if (data.empty()) {
        std::cout << " (empty)\n";
        return;
    }
    for (size_t i = 0; i < data.size(); ++i) {
        if (i != 0) {
            std::cout << ' ';
        }
        std::cout << data[i];
    }
    std::cout << '\n';
}

void RemoveAbsoluteDuplicates(std::vector<int>& data) {
    std::vector<int> seen_abs;
    std::vector<int> filtered;
    filtered.reserve(data.size());
    for (int value : data) {
        int abs_value = std::abs(value);
        if (std::find(seen_abs.begin(), seen_abs.end(), abs_value) == seen_abs.end()) {
            seen_abs.push_back(abs_value);
            filtered.push_back(value);
        }
    }
    data = std::move(filtered);
}

int main() {
    try {
        std::vector<int> numbers = ReadNumbers();

        if (numbers.empty()) {
            std::cout << "No numbers were provided. Exiting.\n";
            return 0;
        }

        PrintVector(numbers, "Input numbers:");

        long long sum = std::accumulate(numbers.begin(), numbers.end(), 0LL);
        std::cout << "Sum of numbers: " << sum << '\n';
        std::cout << "Total amount of numbers: " << numbers.size() << '\n';

        int target_value = ReadIntWithPrompt("Enter value to count occurrences: ");
        size_t equal_count =
            static_cast<size_t>(std::count(numbers.begin(), numbers.end(), target_value));
        std::cout << "Numbers equal to " << target_value << ": " << equal_count << '\n';

        int threshold = ReadIntWithPrompt("Enter threshold n (count numbers greater than n): ");
        size_t greater_count =
            static_cast<size_t>(std::count_if(numbers.begin(), numbers.end(),
                                              [threshold](int value) { return value > threshold; }));
        std::cout << "Numbers greater than " << threshold << ": " << greater_count << '\n';

        long long average = sum / static_cast<long long>(numbers.size());
        std::cout << "Integer part of the average value: " << average << '\n';
        for (int& value : numbers) {
            if (value == 0) {
                value = static_cast<int>(average);
            }
        }
        PrintVector(numbers, "After replacing zeros with the average:");

        Interval interval = ReadInterval(numbers.size());
        auto first = numbers.begin() +
                     static_cast<std::vector<int>::difference_type>(interval.left);
        auto last = numbers.begin() +
                    static_cast<std::vector<int>::difference_type>(interval.right) + 1;
        long long interval_sum = std::accumulate(first, last, 0LL);
        for (int& value : numbers) {
            value += static_cast<int>(interval_sum);
        }
        PrintVector(numbers, "After adding the interval sum to each element:");

        auto minmax = std::minmax_element(numbers.begin(), numbers.end());
        int diff = *minmax.second - *minmax.first;
        for (int& value : numbers) {
            if (std::abs(value) % 2 == 0) {
                value = diff;
            }
        }
        PrintVector(numbers,
                    "After replacing values with even absolute value by (max - min):");

        RemoveAbsoluteDuplicates(numbers);
        PrintVector(numbers,
                    "After removing duplicates by absolute value (keeping the first):");

    } catch (const std::exception& err) {
        std::cerr << "Error: " << err.what() << '\n';
        return 1;
    }

    return 0;
}
