
#ifndef ALLOCATOR_H
#define ALLOCATOR_H

class Allocator
{
    char *ptr = nullptr;
    size_t offset = 0, max_size = 0;
public:
    void make_allocator(size_t alloc_size){
        if(ptr != nullptr){
            return;
        }
	max_size = alloc_size;
        ptr = new char[max_size];
    }
    char* alloc(size_t size){
        if(offset + size > max_size){
            return nullptr;
        } else {
            char *p = ptr + offset;
            offset += size;
            return p;
        }
    }
    void reset(){
        offset = 0;
    }
    ~Allocator(){
        delete[] ptr;
    }
};

#endif // ALLOCATOR_H
