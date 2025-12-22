
#include <cmath>
#include <iostream>
#include <set>

std::set<int> BuildInitialSet(int limit) {
    std::set<int> numbers;
    for (int value = 2; value <= limit; ++value) {
        numbers.insert(value);
    }
    return numbers;
}

std::set<int> SieveOfEratosthenes(int limit) {
    std::set<int> primes = BuildInitialSet(limit);

    const int max_factor = static_cast<int>(std::sqrt(limit));
    for (int factor = 2; factor <= max_factor; ++factor) {
        if (primes.count(factor) == 0) {
            continue;
        }
        for (int multiple = factor * 2; multiple <= limit; multiple += factor) {
            primes.erase(multiple);
        }
    }
    return primes;
}

int main() {
    std::cout << "Enter the upper bound N (>= 2): ";
    int limit = 0;
    if (!(std::cin >> limit)) {
        std::cout << "Failed to read N. Exiting.\n";
        return 0;
    }

    if (limit < 2) {
        std::cout << "There are no prime numbers up to " << limit << ".\n";
        return 0;
    }

    std::set<int> primes = SieveOfEratosthenes(limit);

    std::cout << "Prime numbers not exceeding " << limit << ":\n";
    bool first = true;
    for (int prime : primes) {
        if (!first) {
            std::cout << ' ';
        }
        std::cout << prime;
        first = false;
    }
    std::cout << '\n';

    return 0;
}
