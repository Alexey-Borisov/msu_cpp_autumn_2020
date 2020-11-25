#include <iostream>
#include "Allocator.h"
#include "Iterator.h"

#ifndef VECTOR_H
#define VECTOR_H

template <class T, class allocator_type = Allocator<T>>
class Vector
{
public:
    Vector(const allocator_type& alloc = allocator_type());
    Vector(size_t size, const allocator_type& alloc = allocator_type());
    Vector(size_t size, const T& init, const allocator_type& alloc = allocator_type());
    Vector(Vector<T>& init);
    ~Vector();

    T& operator[](const size_t idx);
    const T& operator[](const size_t idx) const;

    void push_back(const T& val);
    template <class... Args>
    void emplace_back(Args&&... args);
    void pop_back();
    bool empty() const ;
    void clear();
    void resize(size_t new_size);
    void reserve(size_t new_capacity);

    Iterator<T> begin() const ;
    std::reverse_iterator<Iterator<T>> rbegin() const ;
    Iterator<T> end() const ;
    std::reverse_iterator<Iterator<T>> rend() const ;

    size_t size() const ;
    size_t capacity() const ;

    T* _buffer = nullptr;
    Iterator<T> _begin;
    Iterator<T> _end;
    Iterator<T> _real_end;
    allocator_type _alloc;

};

template <class T, class allocator_type>
Vector<T, allocator_type>::Vector(size_t size, const allocator_type& alloc){
    _alloc = alloc;
    _buffer = _alloc.allocate(size);
    _begin = Iterator<T>(_buffer);
    _end = _begin + size;
    _real_end = _end;
}

template <class T, class allocator_type>
Vector<T, allocator_type>::Vector(size_t size, const T& init, const allocator_type& alloc){
    _alloc = alloc;
    _buffer = _alloc.allocate(size);
    for(size_t i = 0; i < size; ++i){
        _buffer[i] = init;
    }
    _begin = Iterator<T>(_buffer);
    _end = _begin + size;
    _real_end = _end;
}

template <class T, class allocator_type>
Vector<T, allocator_type>::Vector(Vector<T>& init){
    size_t size = init._end - init._begin;
    _alloc = init._alloc;
    _buffer = _alloc.allocate(size);
    std::copy(_begin, _end, Iterator<T>(_buffer));
    /*for(size_t i = 0; i < size; ++i){
        _buffer[i] = init[i];
    }*/
     _begin = Iterator<T>(_buffer);
    _end = _begin + size;
    _real_end = _end;
}

template <class T, class allocator_type>
Vector<T, allocator_type>::~Vector(){
    _alloc.deallocate(_buffer, _real_end - _begin);
}

template <class T, class allocator_type>
T& Vector<T, allocator_type>::operator[](const size_t idx){
    return _buffer[idx];
}

template <class T, class allocator_type>
const T& Vector<T, allocator_type>::operator[](const size_t idx) const{
    return _buffer[idx];
}

template <class T, class allocator_type>
void Vector<T, allocator_type>::push_back(const T& val){
    if(_end == _real_end){
        this->reserve(2 * (_end - _begin));
    }
    *_end = val;
    ++_end;
}

template <class T, class allocator_type>
template <class... Args>
void Vector<T, allocator_type>::emplace_back(Args&&... args){
    if(_end == _real_end){
        this->reserve(2 * (_end - _begin));
    }
    *_end = T(std::forward<Args>(args)...);
    ++_end;
}

template <class T, class allocator_type>
void Vector<T, allocator_type>::pop_back(){
    if(_end == _begin){
        throw -1;
    }
    --_end;
}

template <class T, class allocator_type>
bool Vector<T, allocator_type>::empty() const {
    return _begin == _end;
}

template <class T, class allocator_type>
void Vector<T, allocator_type>::clear(){
    _end = _begin;
}

template <class T, class allocator_type>
void Vector<T, allocator_type>::resize(size_t new_size){
    if(new_size > _end - _begin){
        this->reserve(new_size);
    }
    _end = _begin + new_size;
}

template <class T, class allocator_type>
void Vector<T, allocator_type>::reserve(size_t new_capacity){
    if(new_capacity > _real_end - _begin){
        T* tmp = _buffer;
        size_t size = _end - _begin;
        _buffer = _alloc.allocate(new_capacity);
        for(size_t i = 0; i < size; ++i){
            _buffer[i] = tmp[i];
        }
        _alloc.deallocate(tmp, size);
        _begin = Iterator<T>(_buffer);
        _end = _begin + size;
        _real_end = _begin + new_capacity;
    }
}

template <class T, class allocator_type>
Iterator<T> Vector<T, allocator_type>::begin() const {
    return _begin;
}

template <class T, class allocator_type>
std::reverse_iterator<Iterator<T>> Vector<T, allocator_type>::rbegin() const {
    return std::reverse_iterator<Iterator<T>>(_end);
}

template <class T, class allocator_type>
Iterator<T> Vector<T, allocator_type>::end() const {
    return _end;
}

template <class T, class allocator_type>
std::reverse_iterator<Iterator<T>> Vector<T, allocator_type>::rend() const {
    return std::reverse_iterator<Iterator<T>>(_begin);
}

template <class T, class allocator_type>
size_t Vector<T, allocator_type>::size() const {
    return _end - _begin;
}

template <class T, class allocator_type>
size_t Vector<T, allocator_type>::capacity() const {
    return _real_end - _begin;
}

#endif // VECTOR_H
