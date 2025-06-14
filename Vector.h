#ifndef VECTOR_H
#define VECTOR_H

class Vector {
private:
    int mSize;
    double* mData;

public:
    Vector();                       
    Vector(int size);               
    Vector(const Vector& other);  
    ~Vector();                      

    int Size() const;

    double& operator[](int i);         
    double operator[](int i) const;     

    double operator()(int i) const;    

    Vector& operator=(const Vector& other);
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(double scalar) const;

    void Print() const;
};

#endif
