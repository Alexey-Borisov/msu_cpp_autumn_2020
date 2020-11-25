
#ifndef ITERATOR_H
#define ITERATOR_H

template <typename T>
class Iterator
    : public std::iterator<std::forward_iterator_tag, T>
{
public:
    Iterator() = default;
    Iterator(T* p);
    Iterator(const Iterator& it);
    ~Iterator() = default;

    Iterator<T>& operator+=(int32_t val);
    Iterator<T>& operator-=(int32_t val);
    Iterator<T> operator+(int32_t val) const;
    Iterator<T> operator-(int32_t val) const;
    Iterator<T> operator++();
    Iterator<T> operator--();
    Iterator<T>& operator=(const Iterator<T>& it);

    T& operator*();
    const T& operator*() const;
    T& operator[](size_t val);
    const T& operator[](size_t val) const;
    ptrdiff_t operator-(const Iterator& other) const ;

    bool operator<(const Iterator<T>& other) const;
    bool operator>(const Iterator<T>& other) const;
    bool operator<=(const Iterator<T>& other) const;
    bool operator>=(const Iterator<T>& other) const;
    bool operator==(const Iterator<T>& other) const;
    bool operator!=(const Iterator<T>& other) const;

    template <class U>
    friend Iterator<U> operator+(int32_t val, Iterator<U>& it);
private:
    T* _ptr = nullptr;
};

template <class T>
Iterator<T>::Iterator(T* p)
    : _ptr(p)
{
}

template <class T>
Iterator<T>::Iterator(const Iterator& it)
    : _ptr(it._ptr)
{
}

template <class T>
Iterator<T>& Iterator<T>::operator+=(int32_t val){
    _ptr += val;
    return *this;
}

template <class T>
Iterator<T>& Iterator<T>::operator-=(int32_t val){
    _ptr -= val;
    return *this;
}

template <class T>
Iterator<T> Iterator<T>::operator+(int32_t val) const {
    Iterator<T> res(*this);
    res += val;
    return res;
}

template <class T>
Iterator<T> Iterator<T>::operator-(int32_t val) const {
    Iterator<T> res(*this);
    res -= val;
    return res;
}

template <class T>
Iterator<T> Iterator<T>::operator++(){
    return ++_ptr;
}

template <class T>
Iterator<T> Iterator<T>::operator--(){
    return --_ptr;
}

template <class T>
Iterator<T>& Iterator<T>::operator=(const Iterator<T>& it){
    _ptr = it._ptr;
    return *this;
}

template <class T>
Iterator<T> operator+(int32_t val, Iterator<T>& it){
    return it + val;
}

template <class T>
T& Iterator<T>::operator*(){
    return *_ptr;
}

template <class T>
const T& Iterator<T>::operator*() const {
    return *_ptr;
}

template <class T>
T& Iterator<T>::operator[](size_t val){
    return _ptr[val];
}

template <class T>
const T& Iterator<T>::operator[](size_t val) const {
    return _ptr[val];
}

template <class T>
ptrdiff_t Iterator<T>::operator-(const Iterator<T>& other) const {
    return _ptr - other._ptr;
}

template <class T>
bool Iterator<T>::operator<(const Iterator<T>& other) const {
    return _ptr < other._ptr;
}

template <class T>
bool Iterator<T>::operator>(const Iterator<T>& other) const {
    return _ptr > other._ptr;
}

template <class T>
bool Iterator<T>::operator<=(const Iterator<T>& other) const {
    return _ptr <= other._ptr;
}

template <class T>
bool Iterator<T>::operator>=(const Iterator<T>& other) const {
    return _ptr >= other._ptr;
}

template <class T>
bool Iterator<T>::operator==(const Iterator<T>& other) const {
    return _ptr == other._ptr;
}

template <class T>
bool Iterator<T>::operator!=(const Iterator<T>& other) const {
    return _ptr != other._ptr;
}

#endif // ITERATOR_H
