#include <iostream>
#include <string>
#include <utility>
#include <cassert>
#include "Vector.h"

void DefaultWorkTest(){
    Vector<int> v(5, 10);
    v.push_back(15);
    v.push_back(20);
    assert(v.size() == 7 && v[4] == 10
           && v[5] == 15 && v[6] == 20);
    v.pop_back();
    assert(v.size() == 6);
}

void TestIndexation(){
    Vector<int> v(4);
    for(size_t i = 0; i < v.size(); ++i){
        v[i] = i;
    }
    for(size_t i = 0; i < v.size(); ++i){
        assert(v[i] == i);
    }
}

void TestPushBack(){
    Vector<std::string> v(1, "Hello");
    v.push_back("Bonjour");
    v.push_back("Hi");
    assert(v.size() == 3 && v[0] == "Hello"
           && v[1] == "Bonjour" && v[2] == "Hi");
}

void TestPopBack(){
    Vector<int> v(5, 3);
    v.pop_back();
    v.pop_back();
    assert(v.size() == 3);
}

void TestEmplaceBack(){
    std::pair<std::string, int> p = {"HAHA", 42};
    Vector<std::pair<std::string, int>> v(10, p);
    v.emplace_back("No plz", 100);
    v.emplace_back("Nooooo", 1000);
    assert(v[10].first == "No plz" && v[10].second == 100
           && v[11].first == "Nooooo" && v[11].second == 1000);

}

void TestEmpty(){
    Vector<int> v(2);
    assert(!v.empty());
    v.pop_back();
    v.pop_back();
    assert(v.empty());
}

void TestSize(){
    Vector<int> v(42);
    assert(v.size() == 42);
    v.pop_back();
    assert(v.size() == 41);
    v.push_back(13);
    assert(v.size() == 42);
    v.push_back(13);
    assert(v.size() == 43);
}

void TestClear(){
    Vector<int> v(42);
    assert(!v.empty());
    v.clear();
    assert(v.empty() && v.size() == 0);
}

void TestIteration(){
    Vector<int> v(42, 0);
    int32_t val = 0;
    for(auto it = v.begin(); it != v.end(); ++it){
        *it = val;
        ++val;
    }
    val = 0;
    for(size_t i = 0; i < v.size(); ++i){
        assert(v[i] == val);
        ++val;
    }
    val = 0;
    for(auto it = v.rbegin(); it != v.rend(); ++it){
        *it = val;
        ++val;
    }
    val = 0;
    for(int32_t i = v.size() - 1; i >= 0; --i){
        assert(v[i] == val);
        ++val;
    }
}

void TestResize(){
    Vector<int> v(42);
    v.resize(100);
    assert(v.size() == 100);
    v.resize(10);
    assert(v.size() == 10);
}

void TestReserve(){
    Vector<int> v(42);
    v.reserve(13);
    assert(v.capacity() == 42);
    v.reserve(100);
    assert(v.capacity() == 100);
}

void TestCapacity(){
    Vector<int> v(42);
    assert(v.capacity() == 42);
    v.push_back(666);
    assert(v.capacity() == 2 * 42);
}



int main(){
    DefaultWorkTest();
    TestIndexation();
    TestPushBack();
    TestPopBack();
    TestEmplaceBack();
    TestEmpty();
    TestSize();
    TestClear();
    TestIteration();
    TestResize();
    TestReserve();
    TestCapacity();
    std::cout << "All tests passed successfully! :)\n";
}
