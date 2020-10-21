#include <iostream>
#include <string>
#include <cassert>
#include "Parser.h"

std::string text_after_parsing;

/* Функция обработки токенов-чисел увеличивающая каждую цифру на 1 (по модулю 10) */
void DigitTokenShift(std::string &word){
    for(auto &d : word){
        if( d == '9'){
            d = '0';
        } else {
            d += 1;
        }
    }
    text_after_parsing += word;
    text_after_parsing += " ";
}

/*Функция обработки токенов не числовых строк, переводящая все буквы в верхний регистр */ 
void StringTokenToUpper(std::string &word){
    for(auto &c : word){
        c = toupper(c);
    }
    text_after_parsing += word;
    text_after_parsing += " ";
}

void StartPrint(){
    text_after_parsing += "\nWe are starting to parse the text\n";
}

void EndPrint(){
    text_after_parsing += "\nParsing completed\n";
}

void DefaultWorkTest(){
    std::string text = "Education at CMC 2020 \n combines in-depth theoretical studies, extensive\n"
	               "  practical exercises, and 19-20 research. 42 34 How do I convert  "
		       " an integer to a hex        string in\nC++?";
    std::string text_for_testing = "\nWe are starting to parse the text\nEDUCATION AT CMC 3131 "
	                           "COMBINES IN-DEPTH THEORETICAL STUDIES, "
                                   "EXTENSIVE PRACTICAL EXERCISES, AND 19-20 RESEARCH. "
                                   "53 45 HOW DO I CONVERT AN INTEGER TO A HEX STRING IN C++? \nParsing completed\n";
    TokenParser parser;
    parser.SetDigitTokenCallback(DigitTokenShift);
    parser.SetStringTokenCallback(StringTokenToUpper);
    parser.SetStartCallback(StartPrint);
    parser.SetEndCallback(EndPrint);
    parser.Parse(text);
    assert(text_after_parsing == text_for_testing);
    text_after_parsing = "";
}

void TestWithoutStringCallback(){
    std::string text = "Education at CMC 2020 combines in-depth theoretical studies, "
	               " extensive practical exercises, and 19-20 research."
                       "  42 34 How do I convert an integer to a hex string in C++?";
    std::string text_for_testing = "\nWe are starting to parse the text\n3131 53 45 \nParsing completed\n";
    TokenParser parser;
    parser.SetDigitTokenCallback(DigitTokenShift);
    parser.SetStartCallback(StartPrint);
    parser.SetEndCallback(EndPrint);
    parser.Parse(text);
    assert(text_after_parsing == text_for_testing);
    text_after_parsing = "";
}

void TestWithoutDigitCallback(){
    std::string text = "Education at CMC 2020 combines in-depth theoretical studies, "
	               "extensive practical exercises, and 19-20 research."
                       "  42 34 How do I convert an integer to a hex string in C++?";
    std::string text_for_testing = "\nWe are starting to parse the text\nEDUCATION AT CMC "
	                           "COMBINES IN-DEPTH THEORETICAL STUDIES, "
                                   "EXTENSIVE PRACTICAL EXERCISES, AND 19-20 RESEARCH. "
                                   "HOW DO I CONVERT AN INTEGER TO A HEX STRING IN C++? \nParsing completed\n";
    TokenParser parser;
    parser.SetStringTokenCallback(StringTokenToUpper);
    parser.SetStartCallback(StartPrint);
    parser.SetEndCallback(EndPrint);
    parser.Parse(text);
    assert(text_after_parsing == text_for_testing);
    text_after_parsing = "";
}

void TestWithoutStartEndCallback(){
    std::string text = "Education at CMC 2020 combines in-depth theoretical studies, "
	               " extensive practical exercises, and 19-20 research."
                       "  42 34 How do I convert an integer to a hex string in C++?";
    std::string text_for_testing = "EDUCATION AT CMC 3131 COMBINES IN-DEPTH THEORETICAL STUDIES, "
                                   "EXTENSIVE PRACTICAL EXERCISES, AND 19-20 RESEARCH. "
                                   "53 45 HOW DO I CONVERT AN INTEGER TO A HEX STRING IN C++? ";
    TokenParser parser;
    parser.SetStringTokenCallback(StringTokenToUpper);
    parser.SetDigitTokenCallback(DigitTokenShift);
    parser.Parse(text);
    assert(text_after_parsing == text_for_testing);
    text_after_parsing = "";
}

void TestWithEmptyString(){
    std::string text = "";
    std::string text_for_testing = "";
    TokenParser parser;
    parser.SetDigitTokenCallback(DigitTokenShift);
    parser.SetStringTokenCallback(StringTokenToUpper);
    parser.Parse(text);
    assert(text_after_parsing == text_for_testing);
}


int main(){
    DefaultWorkTest();
    TestWithoutStringCallback();
    TestWithoutDigitCallback();
    TestWithoutStartEndCallback();
    TestWithEmptyString();
    std::cout << "All tests passed successfully :)" << std::endl;
    return 0;
}
