
#ifndef ALLOCATOR_H
#define ALLOCATOR_H

template <class T>
class Allocator
{
public:
    Allocator() = default;
    ~Allocator() = default;
    T* allocate(size_t size);
    void deallocate(T* ptr, size_t size);
};

template <class T>
T* Allocator<T>::allocate(size_t size){
    return new T[size];
}

template <class T>
void Allocator<T>::deallocate(T* ptr, size_t size){
    delete[] ptr;
}

#endif // ALLOCATOR_H
