#include <string>

#ifndef PARSER_H
#define PARSER_H

class TokenParser
{   void (*StartHandler)() = nullptr;
    void (*EndHandler)() = nullptr;
    void (*DigitTokenHandler)(std::string&) = nullptr;
    void (*StringTokenHandler)(std::string&) = nullptr;
    public:
        void Parse(const std::string &text){
            std::string word;
            bool digit_flag = true;
            if(StartHandler != nullptr){
                StartHandler();
            }
            for(auto &c : text){
                if(isspace(c)){
                    if(word.empty()){
                        continue;
                    } else if(digit_flag){
                        if(DigitTokenHandler != nullptr){
                            DigitTokenHandler(word);
                        }
                    } else {
                        if(StringTokenHandler != nullptr){
                            StringTokenHandler(word);
                        }
                    }
                    digit_flag = true;
                    word = "";
                    continue;
                }
                if(!isdigit(c)){
                    digit_flag = false;
                }
                word += c;
            }
            if(!word.empty()){
                if(digit_flag){
                    if(DigitTokenHandler != nullptr){
                        DigitTokenHandler(word);
                    }
                } else {
                    if(StringTokenHandler != nullptr){
                        StringTokenHandler(word);
                    }
                }
            }
            if(EndHandler != nullptr){
                EndHandler();
            }
        }

        void SetStartCallback(void (*user_function)(void)){
            StartHandler = user_function;
        }

        void SetEndCallback(void (*user_function)(void)){
            EndHandler = user_function;
        }

        void SetDigitTokenCallback(void (*user_function)(std::string&)){
            DigitTokenHandler = user_function;
        }

        void SetStringTokenCallback(void (*user_function)(std::string&)){
            StringTokenHandler = user_function;
        }
};

#endif // PARSER_H
