#pragma once

#include <iostream>
#include <initializer_list>

class Vector {
private:
    size_t mass_ = 0;
    size_t capasity_ = 0;
    int* vectore_ = nullptr;

public:
    Vector();
    Vector(size_t size);
    Vector(std::initializer_list<int> list);
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);
    ~Vector();

    void Swap(Vector& other);
    void Reserve(size_t new_capacity);
    void PushBack(int value);
    void PopBack();
    void Clear();

    size_t Size() const;
    size_t Capacity() const;
    int& operator[](size_t index);
    const int& operator[](size_t index) const;

    friend std::ostream& operator<<(std::ostream& os, const Vector& v);
};
