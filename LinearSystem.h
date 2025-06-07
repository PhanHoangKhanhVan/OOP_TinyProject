#ifndef LINEARSYSTEM_H
#define LINEARSYSTEM_H

#include "Matrix.h"
#include "Vector.h"

class LinearSystem {
protected:
    int mSize;
    Matrix* mpA;
    Vector* mpb;

public:
    LinearSystem(Matrix& A, Vector& b);
    virtual ~LinearSystem();

    virtual Vector Solve();
};

class PosSymLinSystem : public LinearSystem {
public:
    PosSymLinSystem(Matrix& A, Vector& b);
    Vector Solve() override;

private:
    bool IsSymmetric(const Matrix& A);
};

#endif