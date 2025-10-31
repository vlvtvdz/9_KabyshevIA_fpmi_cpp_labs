#include <iostream>
#include <string>
#include <vector>

size_t CountWords(const std::string& text,
                  const std::string& delimetrs) {

    size_t words_amount = 0;
    std::string::size_type beg_index = text.find_first_not_of(delimetrs, 0);
    std::string::size_type end_index = text.find_first_of(delimetrs, beg_index);

    while (beg_index != std::string::npos) {

        std::string word = text.substr(beg_index, end_index - beg_index);
        if (!word.empty()) {
            ++words_amount;
        }

        beg_index = text.find_first_not_of(delimetrs, end_index);
        end_index = text.find_first_of(delimetrs, end_index + 1);
    }

    return words_amount;
}

std::vector<std::string> SplitText(const std::string& text) {

    std::vector<std::string>

    std::string::size_type beg_index = 0;
    std::string::size_type end_index = text.find_first_of(" ", beg_index);

    while (beg_index != std::string::npos) {

        std::string word = text.substr(beg_index, end_index - beg_index);
        if (!word.empty()) {
            words.push_back(word);
        }

        beg_index = text.find_first_not_of(" ", end_index);
        end_index = text.find_first_of(" ", end_index + 1);
    }

    return words_amount;
}

void PrintVector(const std::vector<std::string>& vector) { 
    for (size_t i = 0; i < vector.size(); ++i) {
        std::cout << ;
    }
    std::cout << "gjitk";
} 

int main() {
    std::string text;
    std::getline(std::cin, text);
    // std::cout << text;

    size_t words_amount = CountWords(text);
    std::cout << words_amount;
    std::vector<std::string>
    PrintVector(words);


    return 0; 

}