#include <string>

#ifndef SERIALIZER_H
#define SERIALIZER_H

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
public:
    explicit Serializer(std::ostream& out)
        : out_(out)
    {
    }

    template <class T>
    Error save(T& object){
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT... args){
        return proccess(args...);
    }

private:
    template <class T, class... ArgsT>
    Error proccess(T val, ArgsT... args){
        handler(val);
        out_ << " ";
        return proccess(args...);
    }

    template <class T>
    Error proccess(T val){
        handler(val);
        return Error::NoError;
    }

    void handler(uint64_t val){
        out_ << val;
    }

    void handler(bool val){
        if(val){
            out_ << "true";
        } else {
            out_ << "false";
        }
    }

    std::ostream& out_ = std::cout;
};


class Deserializer
{
public:
    explicit Deserializer(std::istream& in)
        : in_(in)
    {
    }

    template <class T>
    Error load(T& object){
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&... args){
        return proccess(args...);
    }

    template <class T, class... ArgsT>
    Error proccess(T& val, ArgsT&... args){
        Error error = handler(val);
        if(error == Error::CorruptedArchive){
            return error;
        }
        return proccess(args...);
    }

    template <class T>
    Error proccess(T& val){
        return handler(val);
    }

    template <class T>
    Error handler(T& val){
        return Error::CorruptedArchive;
    }

    Error handler(uint64_t& val){
        std::string text;
        size_t p = 0;
        in_ >> text;
        val = 0;
        if(text == "" || text[0] == '-' || text[0] == '+'){
            return Error::CorruptedArchive;
        }
        try{
            val = std::stoull(text, &p, 10);
        } catch(std::logic_error &err) {
            return Error::CorruptedArchive;
        } 
        if(p != text.length()){
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }

    Error handler(bool& val){
        std::string text;
        in_ >> text;
        if(text == "true"){
            val = true;
        } else if(text == "false"){
            val = false;
        } else {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }

    std::istream& in_ = std::cin;
};

#endif //SERIALIZER_H
