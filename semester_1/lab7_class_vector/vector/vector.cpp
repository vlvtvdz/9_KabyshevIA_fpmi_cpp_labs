#include "vector.h"

#include <algorithm>
#include <iterator>

Vector::Vector() = default;

Vector::Vector(size_t size) : mass_(size), capasity_(size), vectore_(new int[size]) {
    std::fill(vectore_, vectore_ + mass_, 0);
}

Vector::Vector(std::initializer_list<int> list)
    : mass_(list.size()), capasity_(list.size()), vectore_(new int[list.size()]) {
    std::copy(list.begin(), list.end(), vectore_);
}

Vector::Vector(const Vector& other) : mass_(other.mass_), capasity_(other.capasity_), vectore_(new int[capasity_]) {
    std::copy(other.vectore_, other.vectore_ + mass_, vectore_);
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        delete[] vectore_;
        mass_ = other.mass_;
        capasity_ = other.capasity_;
        vectore_ = new int[capasity_];
        std::copy(other.vectore_, other.vectore_ + mass_, vectore_);
    }
    return *this;
}

Vector::~Vector() {
    delete[] vectore_;
}

void Vector::Swap(Vector& other) {
    std::swap(vectore_, other.vectore_);
    std::swap(mass_, other.mass_);
    std::swap(capasity_, other.capasity_);
}

void Vector::Reserve(size_t new_capacity) {
    if (new_capacity > capasity_) {
        int* new_vectore = new int[new_capacity];
        std::copy(vectore_, vectore_ + mass_, new_vectore);
        delete[] vectore_;
        vectore_ = new_vectore;
        capasity_ = new_capacity;
    }
}

void Vector::PushBack(int value) {
    if (mass_ == capasity_) {
        capasity_ = (capasity_ == 0) ? 1 : capasity_ * 2;
        int* new_vectore = new int[capasity_];
        std::copy(vectore_, vectore_ + mass_, new_vectore);
        delete[] vectore_;
        vectore_ = new_vectore;
    }
    vectore_[mass_++] = value;
}

void Vector::PopBack() {
    if (mass_ > 0) {
        --mass_;
    }
}

void Vector::Clear() {
    mass_ = 0;
}

size_t Vector::Size() const {
    return mass_;
}

size_t Vector::Capacity() const {
    return capasity_;
}

int& Vector::operator[](size_t index) {
    return vectore_[index];
}

const int& Vector::operator[](size_t index) const {
    return vectore_[index];
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "[";
    for (size_t i = 0; i < v.mass_; ++i) {
        os << v.vectore_[i];
        if (i + 1 < v.mass_) os << ", ";
    }
    os << "]";
    return os;
}