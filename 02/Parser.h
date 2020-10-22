#include <string>
#include <functional>

#ifndef PARSER_H
#define PARSER_H

class TokenParser
{
    private:
        std::function<void()> StartHandler = nullptr;
        std::function<void()> EndHandler = nullptr;
        std::function<void(std::string&)> DigitTokenHandler = nullptr;
        std::function<void(std::string&)> StringTokenHandler = nullptr;
        std::string word;
        bool digit_flag = true;

        void SelectFunction(){
            if(word.empty()){
                return;
            }
            if(digit_flag){
                if(DigitTokenHandler != nullptr){
                    DigitTokenHandler(word);
                }
            } else if(StringTokenHandler != nullptr){
                StringTokenHandler(word);
            }
        }

    public:
        void Parse(const std::string &text){
            if(StartHandler != nullptr){
                StartHandler();
            }
            for(auto &c : text){
                if(isspace(c)){
                    if(word.empty()){
                        continue;
                    }
                    SelectFunction();
                    digit_flag = true;
                    word = "";
                    continue;
                }
                if(!isdigit(c)){
                    digit_flag = false;
                }
                word += c;
            }
            SelectFunction();
            if(EndHandler != nullptr){
                EndHandler();
            }
        }

        void SetStartCallback(std::function<void()> user_function){
            StartHandler = user_function;
        }

        void SetEndCallback(std::function<void()> user_function){
            EndHandler = user_function;
        }

        void SetDigitTokenCallback(std::function<void(std::string&)> user_function){
            DigitTokenHandler = user_function;
        }

        void SetStringTokenCallback(std::function<void(std::string&)> user_function){
            StringTokenHandler = user_function;
        }
};

#endif // PARSER_H
