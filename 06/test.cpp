#include <iostream>
#include <cassert>
#include "format.h"

void DefaultWorkTest(){
    std::string text = format("{1} + {1} = {0}", 2, "one");
    assert(text == "one + one = 2");

    text = format("{3} {2} {0} {1}", "tree", 81.98, 42, false);
    assert(text == "0 42 tree 81.98");
} 

void ArgOutOfRangeTest(){
    std::string text;
    bool catch_flag = false;
    try {
        text = format("{1} + {2} = {0}", "3", 1.5); 
    } catch(FormatError &err){
        catch_flag = true;
    }
    assert(catch_flag);
    catch_flag = false;
    try {
        text = format("{1} + {-1} = {0}", "1234", 617.0);
    } catch(FormatError &err){
        catch_flag = true;
    }
    assert(catch_flag);
}

void InvalidArgTest(){
    std::string text;
    bool catch_flag = false;
    try {
        text = format("My name is {Alex}, {1}", "Alex", 7);
    } catch(FormatError &err){
        catch_flag = true;
    }
    assert(catch_flag);
    catch_flag = false;
    try {
        text = format("My name is {0a}, {1}", "Alex", 7);
    } catch(FormatError &err){
        catch_flag = true;
    }
    assert(catch_flag);
}

void UnpairedBracketsTest(){
    std::string text;
    bool catch_flag = false;
    try {
        text = format("{2} * {0} == {1} * {3", 2, "3", 6, "4");
    } catch(FormatError &err){
        catch_flag = true;
    }
    assert(catch_flag);
    catch_flag = false;
    try {
        text = format("{2} * {0} == {1} * {3}}", 2, "3", 6, "4");
    } catch(FormatError &err){
        catch_flag = true;
    }
    assert(catch_flag);    
    catch_flag = false;
    try {
        text = format("2} * {0} == {1} * {3", 2, "3", 6, "4");
    } catch(FormatError &err){
        catch_flag = true;
    }
    assert(catch_flag);
    catch_flag = false;
    try {
        text = format("{{2} * {0} == {1} * {3", 2, "3", 6, "4");
    } catch(FormatError &err){
        catch_flag = true;
    }
    assert(catch_flag);
}


int main(){
    DefaultWorkTest();
    ArgOutOfRangeTest();
    InvalidArgTest();
    UnpairedBracketsTest();
    std::cout << "All tests passed successfully! :)\n";
}
