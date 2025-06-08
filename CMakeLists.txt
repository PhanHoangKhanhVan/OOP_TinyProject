cmake_minimum_required(VERSION 3.10)

project(OOP_TinyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(OOP_TinyProject
    main.cpp
    Vector.cpp
    Matrix.cpp
    LinearSystem.cpp
)


add_executable(LinearRegression
    LinearRegression.cpp
    Vector.cpp
    Matrix.cpp
    LinearSystem.cpp
)
