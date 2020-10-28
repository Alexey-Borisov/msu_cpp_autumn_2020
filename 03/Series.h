#include <iostream>

#ifndef SERIES_H
#define SERIES_H

class Series
{
private:
    size_t size = 0;
    int *buffer = nullptr;
    Series(){};
    Series(size_t buffer_size, int *buf){
        size = buffer_size;
        buffer = buf;
    }
    Series(size_t buffer_size){
        size = buffer_size;
        buffer = new int[size];
    }
    ~Series(){
        delete[] buffer;
    }
    Series& operator=(const Series& rhs){
        if(this == &rhs){
            return *this;
        }
        if(size != rhs.size){
            throw -1;
        }
        for(size_t i = 0; i < size; ++i){
            buffer[i] = rhs.buffer[i];
        }
        return *this;
    }
    Series& operator*=(const int &x){
        for(size_t i = 0; i < size; ++i){
            buffer[i] *= x;
        }
        return *this;
    }
    bool operator==(const Series &other){
        if(size != other.size){
            return false;
        }
        for(size_t i = 0; i < size; ++i){
            if(buffer[i] != other.buffer[i]){
                return false;
            }
        }
        return true;
    }
    bool operator!=(const Series &other){
        return !(*this == other);
    }
    friend Series operator+(const Series& left, const Series& right);
    friend std::ostream& operator<<(std::ostream& ostream, const Series &series);
    friend std::istream& operator>>(std::istream& istream, const Series &series);
    friend class Matrix;
public:
    int& operator[](size_t idx){
        if(idx > size - 1){
            throw std::out_of_range("Index out of range");
        }
        return buffer[idx];
    }
};

Series operator+(const Series& left, const Series& right){
    if(left.size != right.size){
        throw -1;
    }
    int *arr = new int[left.size];
    for(size_t i = 0; i < left.size; ++i){
        arr[i] = left.buffer[i] + right.buffer[i];
    }
    return Series(left.size, arr);
 }

std::ostream& operator<<(std::ostream& ostream, const Series &series)
{
    for (size_t i = 0; i < series.size; ++i){
        ostream << series.buffer[i] << " ";
    }
    return ostream;
}

std::istream& operator>>(std::istream& istream, const Series &series)
{
    for (size_t i = 0; i < series.size; ++i){
        istream >> series.buffer[i];
    }
    return istream;
}

#endif // SERIES_H
