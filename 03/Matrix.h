#include <iostream>
#include "Series.h"

#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
private:
    size_t n_cols = 0;
    size_t n_rows = 0;
    Series *buffer = nullptr;
public:
    Matrix(size_t rows, size_t cols){
        n_rows = rows;
        n_cols = cols;
        buffer = new Series[rows];
        for(size_t i = 0; i < n_rows; ++i){
            buffer[i].size = n_cols;
            buffer[i].buffer = new int[n_cols];
        }
    }
    ~Matrix(){}
    Matrix(const Matrix &other){
        n_rows = other.n_rows;
        n_cols = other.n_cols;
        buffer = new Series[n_rows];
        for(size_t i = 0; i < n_rows; ++i){
            buffer[i].size = n_cols;
            buffer[i].buffer = new int[n_cols];
            buffer[i] = other.buffer[i];
        }
    }
    Matrix& operator=(const Matrix &rhs){
        if(this == &rhs){
            return *this;
        }
        if(n_rows != rhs.n_rows || n_cols != rhs.n_cols){
            throw -1;
        }
        for(size_t i = 0; i < n_rows; ++i){
            buffer[i] = rhs.buffer[i];
        }
        return *this;
    }
    Series& operator[](const size_t row){
        if(row > n_rows - 1){
            throw std::out_of_range("Index out of range");
        }
        return buffer[row];
    }
    const Series& operator[](const size_t row) const{
        if(row > n_rows - 1){
            throw std::out_of_range("Index out of range");
        }
        return buffer[row];
    }
    size_t GetRowsNumber() const{
        return n_rows;
    }
    size_t GetColumnsNumber() const{
        return n_cols;
    }
    Matrix operator+(const Matrix &other) const{
        if(n_rows != other.n_rows || n_cols != other.n_cols){
            throw -1;
        }
        Matrix res(n_rows, n_cols);
        for(size_t i = 0; i < n_rows; ++i){
            res.buffer[i] = buffer[i] + other.buffer[i];
        }
        return Matrix(res);
    }
    Matrix& operator*=(const int &x){
        for(size_t i = 0; i < n_rows; ++i){
            buffer[i] *= x;
        }
        return *this;
    }
    bool operator==(const Matrix &other) const{
        if(n_rows != other.n_rows || n_cols != other.n_cols){
            return false;
        }
        for(size_t i = 0; i < n_rows; ++i){
            if(buffer[i] != other.buffer[i]){
                return false;
            }
        }
        return true;
    }
    bool operator!=(const Matrix &other) const{
        return !(*this == other);
    }
    friend std::ostream& operator<<(std::ostream& ostream, const Matrix &matrix);
    friend std::istream& operator>>(std::istream& istream, const Matrix &matrix);
};

std::ostream& operator<<(std::ostream& ostream, const Matrix &matrix){
    for (size_t i = 0; i < matrix.n_rows; ++i){
        ostream << matrix.buffer[i] << "\n";
    }
    return ostream;
}

std::istream& operator>>(std::istream& istream, const Matrix &matrix){
    for (size_t i = 0; i < matrix.n_rows; ++i){
        istream >> matrix.buffer[i];
    }
    return istream;
}

#endif //MATRIX_H
