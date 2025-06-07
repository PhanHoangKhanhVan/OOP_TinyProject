#include "Vector.h"
#include <cassert>
#include <iostream>

Vector::Vector() : mSize(0), mData(nullptr) {}

Vector::Vector(int size) : mSize(size), mData(new double[size]()) {}

Vector::Vector(const Vector& other) : mSize(other.mSize), mData(new double[other.mSize]) {
    for (int i = 0; i < mSize; ++i)
        mData[i] = other.mData[i];
}

Vector::~Vector() {
    delete[] mData;
}

int Vector::Size() const {
    return mSize;
}

double& Vector::operator[](int i) {
    assert(i >= 0 && i < mSize);
    return mData[i];
}

double Vector::operator[](int i) const {
    assert(i >= 0 && i < mSize);
    return mData[i];
}

double Vector::operator()(int i) const {
    assert(i > 0 && i <= mSize);
    return mData[i - 1];
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        delete[] mData;
        mSize = other.mSize;
        mData = new double[mSize];
        for (int i = 0; i < mSize; ++i)
            mData[i] = other.mData[i];
    }
    return *this;
}

Vector Vector::operator+(const Vector& other) const {
    assert(mSize == other.mSize);
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result[i] = mData[i] + other.mData[i];
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    assert(mSize == other.mSize);
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result[i] = mData[i] - other.mData[i];
    return result;
}

Vector Vector::operator*(double scalar) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result[i] = mData[i] * scalar;
    return result;
}

void Vector::Print() const {
    for (int i = 0; i < mSize; ++i)
        std::cout << mData[i] << " ";
    std::cout << std::endl;
}