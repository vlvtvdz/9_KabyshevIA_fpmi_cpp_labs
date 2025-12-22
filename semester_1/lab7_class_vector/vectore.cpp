#include <initializer_list>
#include <iostream>
#include <algorithm>
#include <string>
#include <iterator>

class Vector {
private:
    int mass_ = 0;
    int capasity_ = 0;
    int* vectore_ = nullptr;

public: 
    Vector() {
        std::cout << "Вы находитесь в дефолтном конструкторе" << "\n";
    }

    Vector(int mass): mass_(mass), capasity_(mass), vectore_(new int[capasity_]) {
        std::cout << "Вы находитесь в заданном конструкторе" << "\n";
        std::cout << "Enter range of vectore: ";
        int el;
        for (int i = 0; i < mass; ++i) {
            std::cout << "Enter element ";
            std::cin >> el;
            vectore_[i] = el;
        }
    }

    Vector(std::initializer_list<int> list)
        : mass_(list.size()), capasity_(list.size()), vectore_(new int[list.size()]) {
        std::copy(list.begin(), list.end(), vectore_);
    }

    Vector(const Vector& other) : mass_(other.mass_), capasity_(other.capasity_), vectore_(new int[mass_]) {
        std::cout << "Вы находитесь в конструкторе копирования" << "\n";
        std::copy(other.vectore_, other.vectore_ + mass_, vectore_);
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] vectore_;
            mass_ = other.mass_;
            capasity_ = other.capasity_;
            vectore_ = new int[capasity_];
            std::copy(other.vectore_, other.vectore_ + mass_, vectore_);
        }
        return *this;
    }

    ~Vector() {
        std::cout << "Вы находитесь в деструкторе \n";
        delete[] vectore_;
    }

    void Swap(Vector& AnotherVectore_) {
        std::swap(vectore_, AnotherVectore_.vectore_);
        std::swap(mass_, AnotherVectore_.mass_);
        std::swap(capasity_, AnotherVectore_.capasity_);
    }

    void Relocate(int newCapasity) {
        if (newCapasity > capasity_) {
            int* NewVectore_ = new int[newCapasity];
            std::copy(vectore_, vectore_ + mass_, NewVectore_);
            delete[] vectore_;
            vectore_ = NewVectore_;
            capasity_ = newCapasity;
        }
    }

    const int& operator[](int index) const {
        return vectore_[index];
    }

    int& operator[](int index) {
        return vectore_[index];
    }

    void Capasity() const {
        std::cout << "Now capacity is: " << capasity_ << "\n";
    }

    void Clear() {
        mass_ = 0;
    }

    void PushBack(int value) {
        if (mass_ == capasity_) {
            capasity_ = (capasity_ == 0) ? 1 : capasity_ * 2;
            int* NewVectore_ = new int[capasity_];
            std::copy(vectore_, vectore_ + mass_, NewVectore_);
            delete[] vectore_;
            vectore_ = NewVectore_;
        }
        vectore_[mass_++] = value;
    } 

    void PopBack() {
        if (mass_ > 0) {
            --mass_;
        } else {
            std::cerr << "Vectore is empty \n";
        }
    }

    void Size() const {
        std::cout << "Size of vectore is: " << mass_ << "\n";
    } 

    void Print() const {
        std::cout << "[";
        for (int i = 0; i < mass_; ++i) {
            std::cout << vectore_[i];
            if (i + 1 < mass_) std::cout << ", ";
        }
        std::cout << "]\n";
    }

    
    friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
        if (v.mass_ > 0) {
            std::copy(v.vectore_, v.vectore_ + v.mass_ - 1, std::ostream_iterator<int>(os, " "));
            os << v.vectore_[v.mass_ - 1];
        }
        return os;
    }
};

int main() {
    Vector v1{1, 2, 3, 4, 5};
    v1.Print();

    Vector v2(3);
    v2.PushBack(10);
    v2.PushBack(20);
    v2.PushBack(30);
    std::cout << "v2 = " << v2 << "\n";

    v2.PopBack();
    std::cout << "После PopBack: " << v2 << "\n";

    v2.Clear();
    std::cout << "После Clear: " << v2 << "\n";

    v1.Swap(v2);
    std::cout << "После Swap: v1 = " << v1 << ", v2 = " << v2 << "\n";
}