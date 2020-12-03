#include "ThreadPool.h"
#include <iostream>
#include <cmath>
#include <cassert>

// Функция проверки на простоту
int32_t is_prime(int32_t num){
    if(num <= 1){
        return 0;
    }
    long double root = sqrt(num);
    int32_t limit = round(root) + 1;
    for(int32_t i = 2; i < limit; ++i){
        if(num % i == 0){
            return 0;
        }
    }
    return 1;
}

//Поиск n-ого простого числа
//Использовал чтобы потоки работали не очень маленькое время.
int32_t n_prime(int32_t n){
    int32_t prime_num = 0;
    int32_t cur_prime = 0, cur_num = 2;
    while(prime_num != n && cur_num != 0){
        if(is_prime(cur_num)){
            cur_prime = cur_num;
            ++prime_num;
        }
        ++cur_num;
    }
    return cur_prime;
}

void DefaultWorkTest(){
    ThreadPool pool(3);
    auto thread_1 = pool.exec(n_prime, 30000);
    auto thread_2 = pool.exec(n_prime, 20000);
    auto thread_3 = pool.exec(n_prime, 10000);
    auto res_1 = thread_1.get();
    auto res_2 = thread_2.get();
    auto res_3 = thread_3.get();
    assert(res_1 == n_prime(30000) &&
            res_2 == n_prime(20000) &&
            res_3 == n_prime(10000));
}

void LotsOfTasksTest(){
    ThreadPool pool(2);
    auto thread_1 = pool.exec(n_prime, 60000);
    auto thread_2 = pool.exec(n_prime, 50000);
    auto thread_3 = pool.exec(n_prime, 40000);
    auto thread_4 = pool.exec(n_prime, 30000);
    auto thread_5 = pool.exec(n_prime, 20000);
    auto thread_6 = pool.exec(n_prime, 10000);
    auto res_1 = thread_1.get();
    auto res_2 = thread_2.get();
    auto res_3 = thread_3.get();
    auto res_4 = thread_4.get();
    auto res_5 = thread_5.get();
    auto res_6 = thread_6.get();
    assert(res_1 == n_prime(60000) &&
            res_2 == n_prime(50000) &&
            res_3 == n_prime(40000) &&
            res_4 == n_prime(30000) &&
            res_5 == n_prime(20000) &&
            res_6 == n_prime(10000));
}

void WithoutGetTest(){
    ThreadPool pool(100);
    for(size_t i = 0; i < 100; ++i){
        auto thread = pool.exec([i]{return n_prime((i + 1) * 100); });
    }
}

int main(){
    DefaultWorkTest();
    LotsOfTasksTest();
    WithoutGetTest();
    std::cout << "All tests passed successfully :)" << std::endl;
}
