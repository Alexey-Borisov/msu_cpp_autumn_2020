#include <iostream>
#include <fstream>
#include <cassert>
#include "BigInt.h"

void DefaultWorkTest(){
    BigInt a("123456789");
    BigInt b("111222333");
    BigInt answer;
    std::ifstream inf("DefaultWorkTest.txt");
    inf >> answer;
    BigInt res = 5 * a - b * 11;
    assert(res == answer);
}

void TestStringConstructor(){
    BigInt a("12345678987654321");
    BigInt b("-998976855323332");
    BigInt answer_1, answer_2;
    std::ifstream inf("TestStringConstructor.txt");
    inf >> answer_1 >> answer_2;
    assert(a == answer_1 && b == answer_2);
}

void TestOutput(){
    BigInt a("12345678987654321");
    BigInt b("-998976855323332");
    BigInt answer_1, answer_2;
    std::fstream fs("TestOutput.txt");
    fs << a << "\n" << b;
    fs.seekg(0);
    fs >> answer_1 >> answer_2;
    assert(a == answer_1 && b == answer_2);
}

void TestAdd(){
    BigInt a("12345678987654321");
    BigInt b("998976855323332");
    std::ifstream inf("TestAdd.txt");
    BigInt answer_1, answer_2, res_1, res_2;

    res_1 = a + b;
    res_2 = b + a;
    inf >> answer_1 >> answer_2;
    assert(res_1 == answer_1 && res_2 == answer_2);

    a = "12345678987654321";
    b = "-998976855323332";
    res_1 = a + b;
    res_2 = b + a;
    inf >> answer_1 >> answer_2;
    assert(res_1 == answer_1 && res_2 == answer_2);

    a = "-12345678987654321";
    b = "-998976855323332";
    res_1 = a + b;
    res_2 = b + a;
    inf >> answer_1 >> answer_2;
    assert(res_1 == answer_1 && res_2 == answer_2);

    a = "-12345678987654321";
    b = "998976855323332";
    res_1 = a + b;
    res_2 = b + a;
    inf >> answer_1 >> answer_2;
    assert(res_1 == answer_1 && res_2 == answer_2);

    res_1 = a + 123456;
    res_2 = a + -123456;
    inf >> answer_1 >> answer_2;
    assert(res_1 == answer_1 && res_2 == answer_2);

    res_1 = 123456 + a;
    res_2 = -123456 + a;
    inf >> answer_1 >> answer_2;
    assert(res_1 == answer_1 && res_2 == answer_2);

    res_1 = b + 123456;
    res_2 = b + -123456;
    inf >> answer_1 >> answer_2;
    assert(res_1 == answer_1 && res_2 == answer_2);

    res_1 = 123456 + b;
    res_2 = -123456 + b;
    inf >> answer_1 >> answer_2;
    assert(res_1 == answer_1 && res_2 == answer_2);
}

void TestSub(){
    BigInt a("12345678987654321");
    BigInt b("998976855323332");
    std::ifstream inf("TestSub.txt");
    BigInt answer_1, answer_2, res_1, res_2;

    res_1 = a - b;
    res_2 = b - a;
    inf >> answer_1 >> answer_2;
    assert(res_1 == answer_1 && res_2 == answer_2);

    a = "12345678987654321";
    b = "-998976855323332";
    res_1 = a - b;
    res_2 = b - a;
    inf >> answer_1 >> answer_2;
    assert(res_1 == answer_1 && res_2 == answer_2);

    a = "-12345678987654321";
    b = "-998976855323332";
    res_1 = a - b;
    res_2 = b - a;
    inf >> answer_1 >> answer_2;
    assert(res_1 == answer_1 && res_2 == answer_2);

    a = "-12345678987654321";
    b = "998976855323332";
    res_1 = a - b;
    res_2 = b - a;
    inf >> answer_1 >> answer_2;
    assert(res_1 == answer_1 && res_2 == answer_2);

    res_1 = a - 123456;
    res_2 = a - -123456;
    inf >> answer_1 >> answer_2;
    assert(res_1 == answer_1 && res_2 == answer_2);

    res_1 = 123456 - a;
    res_2 = -123456 - a;
    inf >> answer_1 >> answer_2;
    assert(res_1 == answer_1 && res_2 == answer_2);

    res_1 = b - 123456;
    res_2 = b - -123456;
    inf >> answer_1 >> answer_2;
    assert(res_1 == answer_1 && res_2 == answer_2);

    res_1 = 123456 - b;
    res_2 = -123456 - b;
    inf >> answer_1 >> answer_2;
    assert(res_1 == answer_1 && res_2 == answer_2);
}

void TestMul(){
    BigInt a("12345678987654321");
    BigInt b("998976855323332");
    std::ifstream inf("TestMul.txt");
    BigInt answer_1, answer_2, res_1, res_2;

    res_1 = a * b;
    res_2 = b * a;
    inf >> answer_1 >> answer_2;
    assert(res_1 == answer_1 && res_2 == answer_2);

    a = "12345678987654321";
    b = "-998976855323332";
    res_1 = a * b;
    res_2 = b * a;
    inf >> answer_1 >> answer_2;
    assert(res_1 == answer_1 && res_2 == answer_2);

    a = "-12345678987654321";
    b = "-998976855323332";
    res_1 = a * b;
    res_2 = b * a;
    inf >> answer_1 >> answer_2;
    assert(res_1 == answer_1 && res_2 == answer_2);

    a = "-12345678987654321";
    b = "998976855323332";
    res_1 = a * b;
    res_2 = b * a;
    inf >> answer_1 >> answer_2;
    assert(res_1 == answer_1 && res_2 == answer_2);

    res_1 = a * 123456;
    res_2 = a * -123456;
    inf >> answer_1 >> answer_2;
    assert(res_1 == answer_1 && res_2 == answer_2);

    res_1 = 123456 * a;
    res_2 = -123456 * a;
    inf >> answer_1 >> answer_2;
    assert(res_1 == answer_1 && res_2 == answer_2);

    res_1 = b * 123456;
    res_2 = b * -123456;
    inf >> answer_1 >> answer_2;
    assert(res_1 == answer_1 && res_2 == answer_2);

    res_1 = 123456 * b;
    res_2 = -123456 * b;
    inf >> answer_1 >> answer_2;
    assert(res_1 == answer_1 && res_2 == answer_2);
}

void TestMinus(){
    BigInt a("12345678987654321");
    BigInt b("-998976855323332");
    std::ifstream inf("TestMinus.txt");
    BigInt answer_1, answer_2;
    inf >> answer_1 >> answer_2;
    assert(-a == answer_1 && -b == answer_2);
}

void TestCompare(){
    BigInt a("12345678987654321");
    BigInt b("12345678987654321");
    assert(a == b && b == a && !(-b == a) && !(a == -b)
           && !(-a == b) && !(b == -a) && -b == -a && -a == -b);
    assert(!(a != b) && !(b != a) && -b != a && a != -b
           && -a != b && b != -a && !(-b != -a) && !(-a != -b));

    a = "12345678987654321";
    b = "998976855323332";
    assert(a != b && b != a && !(a == b) && !(b == a));
    assert(b < a && !(b >= a) && -b < a && !(-b >= a) && -a < b
            && !(-a >= b) && -a < -b && !(-a >= -b));
    assert(a > b && !(a <= b) && a > -b && !(a <= -b) && b > -a
            && !(b <= -a) && -b > -a && !(-b <= -a));
    assert(b <= a && !(b > a) && -b <= a && !(-b > a)
            && -a <= b && !(-a > b) && -a <= -b && !(-a > -b));
    assert(a >= b && !(a < b) && a >= -b && !(a < -b)
            && b >= -a && !(b < -a) && -b >= -a && !(-b < -a));

    a = "12345678987654321";
    b = "12345678987654321";
    assert(b <= a && !(b > a) && -b <= a && !(-b > a) && -a <= b
            && !(-a > b) && -a <= -b && !(-a > -b));
    assert(a >= b && !(a < b) && a >= -b && !(a < -b) && b >= -a
            && !(b < -a) && -b >= -a && !(-b < -a));
}

void TestCopyConstructorAndOperator(){
    BigInt a("12345678987654321");
    BigInt b(a);
    BigInt c;
    c = a;
    assert(b == a && c == a);
    a = a + 1;
    assert(b != a && c != a);
}

void TestMoveConstructorAndOperator(){
    BigInt a("12345678987654321");
    BigInt b(std::move(a));
    BigInt c;
    c = std::move(a);
    assert(b == a && c == a);
}

int main(){
    DefaultWorkTest();
    TestStringConstructor();
    TestOutput();
    TestAdd();
    TestSub();
    TestMul();
    TestMinus();
    TestCompare();
    TestCopyConstructorAndOperator();
    TestMoveConstructorAndOperator();
    std::cout << "All tests passed successfully :)";
}

