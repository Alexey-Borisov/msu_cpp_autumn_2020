
#ifndef CLASS_H
#define CLASS_H

class Allocator
{
    char *ptr = nullptr;
    size_t offset = 0, max_size;
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

#endif // CLASS_H
