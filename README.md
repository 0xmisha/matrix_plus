# s21_matrix+ OOP Library

This repository contains the implementation of the `s21_matrix_oop.h` library, an object-oriented version of the `s21_matrix` library.

## Overview

The `s21_matrix+` library is an advanced implementation of matrix operations using object-oriented programming (OOP) principles. This project builds upon the foundational `s21_matrix` project, incorporating OOP techniques to create a more robust and versatile matrix library.

## Features

### Matrix Operations

The library offers a comprehensive set of matrix operations, including but not limited to:

- Equality Check (`EqMatrix`)
- Addition (`SumMatrix`)
- Subtraction (`SubMatrix`)
- Multiplication by Number (`MulNumber`)
- Matrix Multiplication (`MulMatrix`)
- Transpose (`Transpose`)
- Algebraic Complements Calculation (`CalcComplements`)
- Determinant Calculation (`Determinant`)
- Inverse Matrix Calculation (`InverseMatrix`)

Exception handling is integrated for operations involving matrices of incompatible dimensions or other constraints.

### Constructors & Destructors

- Default Constructor (`S21Matrix()`)
- Parameterized Constructor (`S21Matrix(int rows, int cols)`)
- Copy Constructor (`S21Matrix(const S21Matrix& other)`)
- Move Constructor (`S21Matrix(S21Matrix&& other)`)
- Destructor (`~S21Matrix()`)

### Operator Overloading

Operators are overloaded to provide intuitive matrix operations:

- Addition (`+`)
- Subtraction (`-`)
- Multiplication (`*`)
- Equality Check (`==`)
- Assignment (`=`)
- Addition Assignment (`+=`)
- Subtraction Assignment (`-=`)
- Multiplication Assignment (`*=`)
- Element Access (`(int i, int j)`)

### Accessors & Mutators

Accessors and mutators are provided for manipulating matrix dimensions and data.

## Development Guidelines

- Language: C++ (C++17 Standard)
- Compiler: gcc
- Style: Google C++ Style Guide
- Location: Code stored in `src` folder
- Privacy: `matrix_`, `rows_`, and `cols_` fields are private
- Library Type: Static library
- Testing: Full coverage with GTest
- Build System: Makefile provided (targets: `all`, `clean`, `test`, `s21_matrix_oop.a`)

## Getting Started

Refer to the [matrix operations](#matrix-operations) section for a detailed overview of the available functionalities and their respective exception handling.

For building and testing instructions, see the provided Makefile in the repository.
