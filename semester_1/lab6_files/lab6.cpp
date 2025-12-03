#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct LineInfo {
    int lineNumber;
    std::string text;
    int maxPunctLen;
};

bool isPunctuation(char c, const std::string &punctuation) {
    return punctuation.find(c) != std::string::npos;
}

int main() {
    std::string punctuation;
    std::cout << "Введите знаки препинания: ";
    std::getline(std::cin, punctuation);

    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл input.txt\n";
        return 1;
    }

    std::vector<LineInfo> lines;
    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        lineNumber++;
        int maxLen = 0, currentLen = 0;

        for (char c : line) {
            if (isPunctuation(c, punctuation)) {
                currentLen++;
                maxLen = std::max(maxLen, currentLen);
            } else {
                currentLen = 0;
            }
        }

        lines.push_back({lineNumber, line, maxLen});
    }

    file.close();

    int globalMax = 0;
    for (const auto &l : lines)
        globalMax = std::max(globalMax, l.maxPunctLen);

    std::vector<LineInfo> result;
    for (const auto &l : lines)
        if (l.maxPunctLen == globalMax)
            result.push_back(l);

    std::cout << "\nСтроки с максимальной последовательностью знаков препинания ("
              << globalMax << " символов):\n\n";

    for (size_t i = 0; i < std::min<size_t>(10, result.size()); ++i)
        std::cout << "Строка " << result[i].lineNumber << ": "
                  << result[i].text << "\n";

    return 0;
}