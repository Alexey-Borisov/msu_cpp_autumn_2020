#include <iostream>
#include <sstream>
#include <cassert>
#include <string>
#include "Serializer.h"

struct Data_1
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
};

void DefaultTest(){
    Data_1 x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data_1 y { 0, false, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
}

void NotEnoughElementsTest(){
    std::string str = "123456 true";
    std::stringstream stream;
    stream << str;

    Data_1 y { 0, false, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::CorruptedArchive);
}

struct Data_2
{
    uint64_t a;
    bool b;
    bool c;
    uint64_t d;
    uint64_t e;
    bool f;
    uint64_t g;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c, d, e, f, g);
    }
};

void SaveTest(){
    Data_2 x { 10, true, false, 42, 12, true, 123456};

    std::string answer = "10 true false 42 12 true 123456";
    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);
    assert(answer == stream.str());
}

void LoadTest(){
    std::string str = "10 true false 42 12 true 123456";
    std::stringstream stream;
    stream << str;

    Data_2 x { 0, false, false, 0, 0, false, 0};
    Data_2 answer { 10, true, false, 42, 12, true, 123456};

    Deserializer deserializer(stream);
    const Error err = deserializer.load(x);

    assert(err == Error::NoError);
    assert(x.a == answer.a);
    assert(x.b == answer.b);
    assert(x.c == answer.c);
    assert(x.d == answer.d);
    assert(x.e == answer.e);
    assert(x.f == answer.f);
    assert(x.g == answer.g);
}

void CorruptedArchiveTest(){
    std::string str = "10 true false 42 12 true 1.23456";
    std::stringstream stream;
    stream << str;

    Data_2 x { 0, false, false, 0, 0, false, 0};

    Deserializer deserializer(stream);
    const Error err = deserializer.load(x);

    assert(err == Error::CorruptedArchive);
}

int main(){
    DefaultTest();
    NotEnoughElementsTest();
    SaveTest();
    LoadTest();
    CorruptedArchiveTest();
    std::cout << "All tests passed successfully! :)\n";
}
