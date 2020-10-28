#include <iostream>
#include <fstream>
#include <cassert>
#include "Series.h"
#include "Matrix.h"

void TestGetRowsNumber(){
    Matrix m(3, 4);
    std::ifstream inf("test_matrix.txt");
    inf >> m;
    assert(m.GetRowsNumber() == 3);
}

void TestGetColumnsNumber(){
    Matrix m(3, 4);
    std::ifstream inf("test_matrix.txt");
    inf >> m;
    assert(m.GetColumnsNumber() == 4);
}

void TestIndexing(){
    Matrix m(3, 4);
    std::ifstream inf("test_matrix.txt");
    inf >> m;
    assert(m[1][3] == 8);
}

void TestEqual(){
    Matrix m_1(3, 4);
    Matrix m_2(3, 4);
    std::ifstream inf("test_matrix.txt");
    inf >> m_1 >> m_2;
    assert(m_1 == m_2);
}

void TestInequal(){
    Matrix m_1(3, 4);
    Matrix m_2(3, 4);
    std::ifstream inf("test_inequal.txt");
    inf >> m_1 >> m_2;
    assert(m_1 != m_2);
}

void TestAdd(){
    Matrix m_1(3, 4);
    Matrix m_2(3, 4);
    Matrix m_1_copy(3, 4);
    Matrix m_2_copy(3, 4);
    Matrix sum(3, 4);
    Matrix answer(3, 4);
    std::ifstream inf("test_add.txt");
    inf >> m_1 >> m_2 >> answer;
    m_1_copy = m_1;
    m_2_copy = m_2;
    sum = m_1 + m_2;
    assert(sum == answer);
    //Проверяем, что m_1 и m_2 не изменились.
    assert(m_1_copy == m_1 && m_2_copy == m_2);
}

void TestMulWithAssignment(){
    Matrix m_1(3, 4);
    Matrix answer(3, 4);
    int x = 10;
    std::ifstream inf("test_mul.txt");
    inf >> m_1 >> answer;
    m_1 *= x;
    assert(m_1 == answer);
}

void TestOutOfRange(){
    Matrix m_1(3, 4);
    bool catch_flag = false;
    std::ifstream inf("test_matrix.txt");
    inf >> m_1;
    try{
        m_1[3][0];
    }
    catch(std::out_of_range& oor){
        catch_flag = true;
    }
    assert(catch_flag == true);

    catch_flag = false;
    try{
        m_1[2][4];
    }
    catch(std::out_of_range& oor){
        catch_flag = true;
    }
    assert(catch_flag == true);
}

void TestOutput(){
    Matrix res(3, 4);
    std::ifstream inf("test_matrix.txt");
    inf >> res;
    std::fstream fs_1("test_output.txt");
    fs_1 << res;
    Matrix m(3, 4);
    std::fstream fs_2("test_output.txt");
    fs_2 >> m;
    assert(m == res);
}

int main(){
    TestGetRowsNumber();
    TestGetColumnsNumber();
    TestIndexing();
    TestAdd();
    TestMulWithAssignment();
    TestOutOfRange();
    TestOutput();
    std::cout << "All tests passed successfully :)\n";
}
