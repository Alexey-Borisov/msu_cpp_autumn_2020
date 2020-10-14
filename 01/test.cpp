#include <cassert>
#include <iostream>
#include "Allocator.h"

void default_work_test(){
    Allocator my_allocator;
    my_allocator.make_allocator(100);
    int *arr_1 = (int *)my_allocator.alloc(20 * sizeof(int));
    char *arr_2 = (char *)my_allocator.alloc(20 * sizeof(char));
    for(int i = 0; i < 20; ++i){
        arr_1[i] = i;
    }
    for(int i = 0; i < 20; ++i){
        arr_2[i] = 2 * i;
    }
    for(int i = 0; i < 20; ++i){
        assert(arr_1[i] == i);
    }
    for(int i = 0; i < 20; ++i){
        assert(arr_2[i] == 2 * i);
    }
}

void overflow_test(){
    Allocator my_allocator;
    my_allocator.make_allocator(10 * sizeof(int));
    int *arr_1 = (int *)my_allocator.alloc(8 * sizeof(int));
    char *arr_2 = (char *)my_allocator.alloc(5 * sizeof(char));
    int *arr_3 = (int *)my_allocator.alloc(sizeof(int));
    assert(arr_1 != nullptr && arr_2 != nullptr && arr_3 == nullptr);
}

void alloc_before_make_test(){
    Allocator my_allocator;
    int *arr_1 = (int *)my_allocator.alloc(sizeof(int));
    assert(arr_1 == nullptr);
}

void reset_test(){
    Allocator my_allocator;
    my_allocator.make_allocator(10 * sizeof(int));
    int *arr_1 = (int *)my_allocator.alloc(8 * sizeof(int));
    char *arr_2 = (char *)my_allocator.alloc(7 * sizeof(char));
    int *arr_3 = (int *)my_allocator.alloc(sizeof(int));
    assert(arr_1 != nullptr && arr_2 != nullptr && arr_3 == nullptr);
    my_allocator.reset();
    int *arr_4 = (int *)my_allocator.alloc(10 * sizeof(int));
    assert(arr_4 != nullptr);
}

void some_allocators_test(){
    Allocator alloc_arr[20];
    int *ptr_arr[20];
    for(int i = 0; i < 20; ++i){
        ptr_arr[i] = nullptr;
    }
    for(int i = 0; i < 20; ++i){
        alloc_arr[i].make_allocator(100 * sizeof(int));
        ptr_arr[i] = (int *)alloc_arr[i].alloc(100 * sizeof(int));
        assert(ptr_arr[i] != nullptr);
    }
}




int main(){
    default_work_test();
    overflow_test();
    reset_test();
    alloc_before_make_test();
    some_allocators_test();
    std::cout << "All tests passed successfully :)" << std::endl;
    return 0;
}
