# OOP TinyProject Report

## 1. Introduction

This project demonstrates the application of Object-Oriented Programming (OOP) in C++ to solve problems related to matrices, vectors, linear systems, and linear regression. The project is structured into several classes, each encapsulating specific mathematical concepts and operations.

## 2. Project Structure

- `Matrix.h` / `Matrix.cpp`: Implements a matrix class supporting basic operations (addition, multiplication, transpose, determinant, inverse, pseudo-inverse).
- `Vector.h` / `Vector.cpp`: Implements a vector class with arithmetic operations and utility functions.
- `LinearSystem.h` / `LinearSystem.cpp`: Provides classes to solve linear systems (general and positive symmetric systems).
- `LinearRegression.cpp`: Demonstrates linear regression using the matrix and vector classes, including data loading, shuffling, splitting, and evaluation.
- `main.cpp`: Entry point for testing matrix and vector operations, and solving linear systems interactively.
- `machine.data`: Example dataset for linear regression.

## 3. Main Features

### 3.1 Matrix and Vector Operations
- Creation, copying, and destruction of matrices and vectors.
- Arithmetic operations: addition, multiplication (matrix-matrix, matrix-vector, vector-scalar).
- Transpose, determinant, inverse, and pseudo-inverse of matrices.
- Printing and accessing elements (1-based for matrices, 0-based for vectors).

### 3.2 Solving Linear Systems
- Gaussian elimination for general linear systems (`LinearSystem`).
- Conjugate gradient method for positive symmetric systems (`PosSymLinSystem`).
- Interactive input and output for matrices, vectors, and solutions.

### 3.3 Linear Regression
- Loads dataset from file, parses features and labels.
- Shuffles and splits data into training and testing sets (80/20 split).
- Computes regression coefficients using the pseudo-inverse.
- Evaluates model performance using RMSE (Root Mean Square Error) on both train and test sets.

## 4. Example Usage

- Run `main.cpp` to test matrix and vector operations, compute determinants, inverses, and solve Ax = b interactively.
- Run `LinearRegression.cpp` to perform linear regression on the provided dataset and print RMSE results.

## 5. Conclusion

This project showcases the power of OOP in C++ for mathematical computation, providing reusable and extensible classes for matrix and vector algebra, linear system solving, and machine learning tasks like linear regression.

---
*Date: June 14, 2025*
