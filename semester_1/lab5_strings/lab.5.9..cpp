#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


bool isLowerVowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' ||
           c == 'o' || c == 'u' || c == 'y';
}


void transformString(std::string &s) {
    for (char &c : s) {
        if (isLowerVowel(c)) {
            c = static_cast<char>(std::toupper(c));
        }
        if (c == ' ') {
            c = '+';
        }
    }
}


std::vector<std::string> splitByChar(const std::string &s, char delim) {
    std::vector<std::string> result;
    std::string current;

    for (char c : s) {
        if (c == delim) {
            result.push_back(current);
            current.clear();
        } else {
            current.push_back(c);
        }
    }

    result.push_back(current);
    return result;
}


std::string joinWithChar(const std::vector<std::string> &words, char delim) {
    if (words.empty()) return "";

    std::string res = words[0];
    for (size_t i = 1; i < words.size(); ++i) {
        res.push_back(delim);
        res += words[i];
    }
    return res;
}

int main() {
    std::string s;
    std::cout << "Введите строку: ";
    std::getline(std::cin, s);

    
    transformString(s);

    
    std::vector<std::string> words = splitByChar(s, '+');

    
    std::sort(words.begin(), words.end());

    std::string result = joinWithChar(words, '+');

    std::cout << "Результат: " << result << std::endl;

    return 0;
}