#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

int AmountWords(std::string line, std::string& delim);

int main() {
    std::string delim;
    try{
        std::ifstream in("in.txt");
        if (!in.is_open()) {
            std::cerr << "Cannot open file in.txt" << std::endl;
            return 1;
        }

        if (in.eof()) {
            throw std::string("File is empty\n");
        }

        std::cout << "Enter your delimetres: ";
        std::getline(std::cin, delim);
        int maxsize = 0;
        std::string line;
        std::vector<std::string> lines;
        while (std::getline(in, line)) {
            int tmp = AmountWords(line, delim);
            if (tmp > maxsize){
                    lines.clear();
                    maxsize = tmp;
                    lines.push_back(line);
            }   
            else if (tmp == maxsize){
                lines.push_back(line);
                }
        }
        int Size = lines.size();
        for (int i = 0; i < Size; ++i) {
            std::cout << "Lines " << i + 1 << " " << lines[i] << std::endl;
        }
        std::cout << "Max number of consecutive delimiters: " << maxsize << std::endl;
        in.close();
        return 0;
    } catch (std::string msg) { 
        std::cerr << msg;
        return 1;
    }
    
}


int AmountWords(std::string line, std::string& delim) {
    int maxConsecutive = 0;
    size_t pos = 0;
    
    while (pos < line.length()) {
        size_t first = line.find_first_of(delim, pos);
        
        if (first == std::string::npos) {
            break;
        }
        
        size_t last = line.find_first_not_of(delim, first);
        
        if (last == std::string::npos) {
            break;
        }
        
        int distance = last - first;
        maxConsecutive = std::max(maxConsecutive, distance);
        
        pos = last;
    }
    
    return maxConsecutive;
}

