/**
 * @file matrix.cpp
 * @author Jayden Rice (jrice43@ut.utm.edu)
 * @brief Cpp file for matrix.h
 * @version 0.1
 * @date 2026-02-25
 * 
 * @copyright Copyright (c) 202
 * 
 */



#include <iostream>
#include <iomanip>

#include "matrix.h"

Matrix::Matrix(unsigned int rows, unsigned int cols){
    m = rows;
    n = cols;
    ar = new double*[m];
    for (int i = 0; i < m; ++i) {
        ar[i] = new double[n]{0}; // initialize to zero
    }
}

Matrix::Matrix(const Matrix& rhs){
    m = rhs.m;
    n = rhs.n;
    ar = new double*[m];
    for (int i = 0; i < m; ++i) {
        ar[i] = new double[n];
        for (int j = 0; j < n; ++j) {
            ar[i][j] = rhs.ar[i][j];
        }
    }
}

/**
 * @brief Destroy the Matrix object
 * 
 */
Matrix::~Matrix(){
    for (int i = 0; i < m; ++i) {
        delete[] ar[i];
    }
}

/**
 * @brief Get the number of rows in the matrix.
 * 
 * @return int The number of rows in the matrix.
 */
int Matrix::getRows() const {
    return m;
}

/**
 * @brief Get the number of columns in the matrix.
 * 
 * @return int The number of columns in the matrix.
 */
int Matrix::getCols() const{
    return n;
}

/**
 * @brief Return a reference to the element at the specified row and column.
 *
 * @param row The row of the element.
 * @param col The column of the element.
 * @return double& A reference to the element at the specified row and column. 
 */

 double& Matrix::at(unsigned int row, unsigned int col) {
    return ar[row][col];
}

const double& Matrix::at(unsigned int row, unsigned int col) const {
    return ar[row][col];
}

/**
 * @brief Overloaded assignment operator.
 * 
 * @param rhs The matrix to assign.
 */
 Matrix& Matrix::operator=(const Matrix& rhs){
    if (this == &rhs) {
        return *this; // handle self-assignment
    }

    // Clean up existing resources
    for (int i = 0; i < m; ++i) {
        delete[] ar[i];
    }
    delete[] ar;

    // Copy dimensions
    m = rhs.m;
    n = rhs.n;

    // Allocate new resources
    ar = new double*[m];
    for (int i = 0; i < m; ++i) {
        ar[i] = new double[n];
        for (int j = 0; j < n; ++j) {
            ar[i][j] = rhs.ar[i][j];
        }
    }

    return *this;
}


/**
 * @brief Overloaded operator for the addition of two matrices.
 * 
 * @param m1 The first matrix.
 * @param m2 The second matrix.
 * @return Matrix The sum of the two matrices.
 */
Matrix operator+(const Matrix& m1, const Matrix& m2){
    if (m1.getRows() != m2.getRows() || m1.getCols() != m2.getCols()) {
        throw std::invalid_argument("Matrices must have the same dimensions for addition");
    }

    Matrix result(m1.getRows(), m1.getCols());

    for (unsigned int i = 0; i < m1.getRows(); ++i) {
        for (unsigned int j = 0; j < m1.getCols(); ++j) {
            result.at(i, j) = m1.at(i, j) + m2.at(i, j);
        }
    }

    return result;
}

/**
 * @brief Overloaded operator for the subtraction of two matrices.
 * 
 * @param m1 The first matrix.
 * @param m2 The second matrix.
 * @return Matrix The difference of the two matrices.
 */


 Matrix operator-(const Matrix& m1, const Matrix& m2){
    if (m1.getRows() != m2.getRows() || m1.getCols() != m2.getCols()) {
        throw std::invalid_argument("Matrices must have the same dimensions for subtraction");
    }

    Matrix result(m1.getRows(), m1.getCols());

    for (unsigned int i = 0; i < m1.getRows(); ++i) {
        for (unsigned int j = 0; j < m1.getCols(); ++j) {
            result.at(i, j) = m1.at(i, j) - m2.at(i, j);
        }
    }

    return result;
}

Matrix operator*(const Matrix& m1, const Matrix& m2){
    if (m1.getCols() != m2.getRows()) {
        throw std::invalid_argument("Number of columns of the first matrix must equal the number of rows of the second matrix for multiplication");
    }

    Matrix result(m1.getRows(), m2.getCols());

    for (unsigned int i = 0; i < m1.getRows(); ++i) {
        for (unsigned int j = 0; j < m2.getCols(); ++j) {
            double sum = 0;
            for (unsigned int k = 0; k < m1.getCols(); ++k) {
                sum += m1.at(i, k) * m2.at(k, j);
            }
            result.at(i, j) = sum;
        }
    }

    return result;
}

Matrix operator*(double scalar, const Matrix& m){
    Matrix result(m.getRows(), m.getCols());

    for (unsigned int i = 0; i < m.getRows(); ++i) {
        for (unsigned int j = 0; j < m.getCols(); ++j) {
            result.at(i, j) = scalar * m.at(i, j);
        }
    }

    return result;
}

Matrix operator*(const Matrix& m, double scalar){
    return scalar * m;
}


/**
 * @brief Overloaded operator for the output of a matrix.
 * 
 * @param os The output stream.
 * @param m The matrix.
 * @return std::ostream& The output stream.
 */
std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
    for (unsigned int i = 0; i < m.getRows(); ++i) {
        for (unsigned int j = 0; j < m.getCols(); ++j) {
            os << std::setw(10) << m.at(i,j) << " ";
        }
        os << std::endl;
    }
    return os;
}
/**
 * @brief Overloaded operator for the input of a matrix.
 * 
 * @param is The input stream.
 * @param m The matrix.
 * @return std::istream& The input stream.
 */
std::istream& operator>>(std::istream& is, Matrix& m){
    for (int i = 0; i < m.getRows(); ++i) {
        for (int j = 0; j < m.getCols(); ++j) {
            is >> m.at(i, j);
        }
    }
    return is;
}


