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
    Series& operator[](size_t row){
        if(row > n_rows - 1){
            throw std::out_of_range("Index out of range");
        }
        return buffer[row];
    }
    size_t GetRowsNumber(){
        return n_rows;
    }
    size_t GetColumnsNumber(){
        return n_cols;
    }
    Matrix operator+(const Matrix &other){
        if(n_rows != other.n_rows || n_cols != other.n_cols){
            throw -1;
        }
        Matrix res(n_rows, n_cols);
        for(size_t i = 0; i < n_rows; ++i){
            res.buffer[i] = buffer[i] + other.buffer[i];
        }
        return res;
    } 
    Matrix& operator*=(const int &x){
        for(size_t i = 0; i < n_rows; ++i){
            buffer[i] *= x;
        }
        return *this;
    }
    bool operator==(const Matrix &other){
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
    bool operator!=(const Matrix &other){
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

std::istream& operator>>(std::istream& istream, const Matrix &matrix)
{
    for (size_t i = 0; i < matrix.n_rows; ++i){
        istream >> matrix.buffer[i];
    }
    return istream;
}

#endif //MATRIX_H
