#include <string>
#include <sstream>

class FormatError : std::exception
{
private:
    std::string m_error;
public:
    FormatError(std::string error){
        m_error = error;
    }
    const char* what() const noexcept{
        return m_error.c_str();
    }
};

template <class T>
void get_args(std::string *arr, T cur_arg){
    std::stringstream ss;
    ss << cur_arg;
    *arr = ss.str();
}

template <class T, class... ArgsT>
void get_args(std::string *arr, T cur_arg, ArgsT... args){
    std::stringstream ss;
    ss << cur_arg;
    *arr = ss.str();
    get_args(arr + 1, args...);
}

template <class... ArgsT>
std::string format(const std::string text, ArgsT... args){
    int32_t args_count = sizeof...(ArgsT);
    std::string *arr = new std::string[args_count];
    if(args_count > 0){
        get_args(arr, args...);
    }
    std::string res = "";
    for(size_t i = 0; i < text.length(); ++i){
        if(text[i] == '}'){
            throw FormatError("Closing parenthesis before opening");
        } else if(text[i] != '{') {
            res += text[i];
            continue;
        }
        ++i;
        if(i == text.length()){
            throw FormatError("Opening parenthesis at the end");
        }
        size_t p = 0;
        int32_t num = 0;
        try {
            num = stoull(text.substr(i), &p, 10);
        } catch(std::logic_error &err) {
            throw FormatError("Argument is not a non-negative integer");
        }
        if(num < 0 || num >= args_count){
            throw FormatError("Argument is out of range");
        }
        i += p;
        if(i == text.length() && text[i] != '}'){
            throw FormatError("Missing closing parenthesis");
        } else {
            res += arr[num];
        }
    }
    return res;
}
