#ifndef VECTOR_H
#define VECTOR_H

class Vector {
private:
    int mSize;
    double* mData;

public:
    Vector();                        // Constructor mặc định
    Vector(int size);               // Constructor có kích thước
    Vector(const Vector& other);    // Copy constructor
    ~Vector();                      // Destructor

    int Size() const;

    double& operator[](int i);           // Truy cập 0-based có sửa
    double operator[](int i) const;      // Const version

    double operator()(int i) const;      // Truy cập 1-based

    Vector& operator=(const Vector& other);
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(double scalar) const;

    void Print() const;
};

#endif