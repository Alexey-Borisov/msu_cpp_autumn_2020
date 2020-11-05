#include <string>
#include <iomanip>

#ifndef BIGINT_H
#define BIGINT_H

enum
{
    BASE = 10,
    BASE_EXP = 1
};

class BigInt
{
public:
    char sign = 1;
    int32_t *buffer = nullptr;
    size_t buffer_size = 0;

    BigInt(){};
    BigInt(const std::string &str);
    BigInt(const int &other);

    BigInt(const BigInt &other);
    BigInt& operator=(const BigInt &other);
    BigInt& operator=(const std::string &other);
    BigInt& operator=(const int &other);

    BigInt(BigInt &&other);
    BigInt& operator=(BigInt &&other);

    ~BigInt();

    BigInt operator+(const int &other) const;
    BigInt operator+(const BigInt &other) const;

    BigInt operator-(const int &other) const;
    BigInt operator-(const BigInt &other) const;

    BigInt operator*(const int &other) const;
    BigInt operator*(const BigInt &other) const;

    bool operator==(const BigInt &other) const;
    bool operator==(const int &other) const;

    bool operator!=(const BigInt &other) const;
    bool operator!=(const int &other) const;

    bool operator<(const BigInt &other) const;
    bool operator<(const int &other) const;

    bool operator<=(const BigInt &other) const;
    bool operator<=(const int &other) const;

    bool operator>(const BigInt &other) const;
    bool operator>(const int &other) const;

    bool operator>=(const BigInt &other) const;
    bool operator>=(const int &other) const;

    BigInt operator-() const;

    friend std::ostream& operator<<(std::ostream& ostream, const BigInt &bigint);
    friend void normalize(BigInt &bigint);
    friend BigInt abs(const BigInt &bigint);
};

BigInt::BigInt(const std::string &str){
    int32_t digit_start = 0;
    if(str[0] == '-'){
        sign = -1;
        digit_start = 1;
    } else if(str[0] == '+'){
        digit_start = 1;
    }
    int32_t digit_len = str.length() - digit_start;
    buffer_size = (digit_len - 1) / BASE_EXP + 1;
    buffer = new int32_t[buffer_size];
    for(size_t i = 0; i < buffer_size; ++i){
        buffer[i] = 0;
    }
    int32_t num = 0, idx = 0, cur_exp = 1;
    for(int32_t i = str.length() - 1; i >= digit_start; --i){
        num += (str[i] - '0') * cur_exp;
        cur_exp *= 10;
        if(num + cur_exp >= BASE){
            buffer[idx] = num;
            num = 0;
            cur_exp = 1;
            idx++;
        }
    }
    if(num > 0){
        buffer[idx] = num;
    }
}

BigInt::BigInt(const int &other){
    if(other < 0){
        sign = -1;
    } else {
        sign = 1;
    }
    int other_copy = sign * other;
    while(other_copy > 0){
        buffer_size++;
        other_copy /= BASE;
    }
    buffer = new int32_t[buffer_size];
    other_copy = sign * other;
    size_t idx = 0;
    while(other_copy > 0){
        buffer[idx] = other_copy % BASE;
        other_copy /= BASE;
        idx++;
    }
}

BigInt::BigInt(const BigInt &other){
    //std::cout << "CopyConstructor\n";
    sign = other.sign;
    buffer_size = other.buffer_size;
    buffer = new int32_t[buffer_size];
    for(size_t i = 0; i < buffer_size; ++i){
        buffer[i] = other.buffer[i];
    }
}

BigInt::~BigInt(){
    if(buffer != nullptr){
        delete[] buffer;
    }
}

BigInt& BigInt::operator=(const BigInt &other){
    //std::cout << "CopyOperator\n";
    if(buffer != nullptr){
        delete[] buffer;
    }
    sign = other.sign;
    buffer_size = other.buffer_size;
    buffer = new int32_t[buffer_size];
    for(size_t i = 0; i < buffer_size; ++i){
        buffer[i] = other.buffer[i];
    }
    return *this;
}

BigInt& BigInt::operator=(const std::string &other){
    BigInt res(other);
    *this = std::move(res);
    return *this;
}

BigInt& BigInt::operator=(const int &other){
    BigInt bigint(other);
    return *this = bigint;
}

BigInt::BigInt(BigInt &&other){
    //std::cout << "MoveConstructor\n";
    sign = other.sign;
    buffer_size = other.buffer_size;
    buffer = other.buffer;
    other.buffer = nullptr;
}

BigInt& BigInt::operator=(BigInt &&other){
    //std::cout << "MoveOperator\n";
    sign = other.sign;
    buffer_size = other.buffer_size;
    if(buffer != nullptr){
        delete[] buffer;
    }
    buffer = other.buffer;
    other.buffer = nullptr;
    return *this;
}

BigInt BigInt::operator+(const BigInt &other) const{
    if(*this < 0 && other >= 0){
        return other - (-*this);
    } else if(*this >= 0 && other < 0){
        return *this - (-other);
    } else if(*this < 0 && other < 0){
        return -(-*this + (-other));
    }
    BigInt mx, mn;
    if(buffer_size > other.buffer_size){
        mx = *this;
        mn = other;
    } else {
        mx = other;
        mn = *this;
    }
    BigInt res;
    res.buffer_size = mx.buffer_size + 1;
    res.buffer = new int32_t[res.buffer_size];
    size_t idx = 0, flag = 0;
    for(; idx < mn.buffer_size; ++idx){
        res.buffer[idx] = mx.buffer[idx] + mn.buffer[idx] + flag;
        flag = 0;
        if(res.buffer[idx] >= BASE){
            res.buffer[idx] -= BASE;
            flag = 1;
        }
    }
    for(; idx < mx.buffer_size; ++idx){
        res.buffer[idx] = mx.buffer[idx] + flag;
        flag = 0;
        if(res.buffer[idx] >= BASE){
            res.buffer[idx] -= BASE;
            flag = 1;
        }
    }
    res.buffer[idx] = flag;
    normalize(res);
    return res;
}

BigInt BigInt::operator+(const int &other) const{
    BigInt bigint(other);
    return *this + bigint;
}

BigInt operator+(const int &left, const BigInt &right){
    BigInt bigint(left);
    return bigint + right;
}

BigInt BigInt::operator-(const BigInt &other) const{
    if(this->sign == -1 && other.sign == 1){
        return -(-*this - (-other));
    } else if(this->sign == -1 && other.sign == -1){
        return (-other) - (-*this);
    } else if(other.sign == -1){
        return *this + (-other);
    } else if(*this < other){
        return -(other - *this);
    }
    BigInt res;
    res.buffer_size = buffer_size;
    res.buffer = new int32_t[res.buffer_size];
    size_t idx = 0;
    int32_t flag = 0;
    for(; idx < other.buffer_size; ++idx){
        if(buffer[idx] >= other.buffer[idx] + flag){
            res.buffer[idx] = buffer[idx] - other.buffer[idx] - flag;
            flag = 0;
        } else {
            res.buffer[idx] = BASE + buffer[idx] - other.buffer[idx] - flag;
            flag = 1;
        }
    }
    for(; idx < buffer_size; ++idx){
        if(buffer[idx] >= flag){
            res.buffer[idx] = buffer[idx] - flag;
            flag = 0;
        } else {
            res.buffer[idx] = BASE + buffer[idx] - flag;
            flag = 1;
        }
    }
    normalize(res);
    return res;
}

BigInt BigInt::operator-(const int &other) const{
    BigInt bigint(other);
    return *this - bigint;
}

BigInt operator-(const int &left, const BigInt &right){
    BigInt bigint(left);
    return bigint - right;
}

BigInt BigInt::operator*(const BigInt &other) const{
    if(abs(*this) > abs(other)){
        return other * (*this);
    }
    BigInt res;
    if(*this == 0){
        res.sign = 1;
    } else {
        res.sign = sign * other.sign;
    }
    res.buffer_size = buffer_size + other.buffer_size;
    res.buffer = new int32_t[res.buffer_size];
    for(size_t i = 0; i < res.buffer_size; ++i){
        res.buffer[i] = 0;
    }
    size_t flag = 0, idx_1 = 0, idx_2 = 0;
    for(; idx_1 < buffer_size; ++idx_1){
        idx_2 = 0;
        for(; idx_2 < other.buffer_size; ++idx_2){
            res.buffer[idx_1 + idx_2] += buffer[idx_1] * other.buffer[idx_2] + flag;
            if(res.buffer[idx_1 + idx_2] >= BASE){
                flag = res.buffer[idx_1 + idx_2] / BASE;
                res.buffer[idx_1 + idx_2] %= BASE;
            } else {
                flag = 0;
            }
        }
        res.buffer[idx_1 + idx_2] += flag;
        if(res.buffer[idx_1 + idx_2] >= BASE){
            flag = res.buffer[idx_1 + idx_2] / BASE;
            res.buffer[idx_1 + idx_2] %= BASE;
        } else {
            flag = 0;
        }
    }
    if(flag != 0){
        res.buffer[idx_1 + idx_2] += flag;
    }
    normalize(res);
    return res;
}

BigInt BigInt::operator*(const int &other) const{
    BigInt bigint(other);
    return (*this) * bigint;
}

BigInt operator*(const int &left, const BigInt &right){
    BigInt bigint(left);
    return bigint * right;
}

bool BigInt::operator==(const BigInt &other) const{
    if(buffer_size != other.buffer_size || sign != other.sign){
        return false;
    }
    for(size_t i = 0; i < buffer_size; ++i){
        if(buffer[i] != other.buffer[i]){
            return false;
        }
    }
    return true;
}

bool BigInt::operator==(const int &other) const{
    BigInt bigint(other);
    return *this == bigint;
}

bool operator==(const int &left, const BigInt &right){
    BigInt bigint(left);
    return bigint == right;
}

bool BigInt::operator!=(const BigInt &other) const{
    return !(*this == other);
}

bool BigInt::operator!=(const int &other) const{
    BigInt bigint(other);
    return *this != bigint;
}

bool operator!=(const int &left, const BigInt &right){
    BigInt bigint(left);
    return bigint != right;
}

bool BigInt::operator<(const BigInt &other) const{
    if(sign < other.sign){
        return true;
    } else if(sign > other.sign){
        return false;
    } else if(sign == -1){
        return -*this > -other;
    }
    if(buffer_size < other.buffer_size){
        return true;
    } else if(buffer_size > other.buffer_size){
        return false;
    }
    for(int32_t i = buffer_size - 1; i >= 0; --i){
        if(buffer[i] < other.buffer[i]){
            return true;
        } else if(buffer[i] > other.buffer[i]){
            return false;
        }
    }
    return false;
}

bool BigInt::operator<(const int &other) const{
    BigInt bigint(other);
    return *this < bigint;
}

bool operator<(const int &left, const BigInt &right){
    BigInt bigint(left);
    return bigint < right;
}

bool BigInt::operator<=(const BigInt &other) const{
    return *this < other || *this == other;
}

bool BigInt::operator<=(const int &other) const{
    BigInt bigint(other);
    return *this <= bigint;
}

bool operator<=(const int &left, const BigInt &right){
    BigInt bigint(left);
    return bigint <= right;
}

bool BigInt::operator>(const BigInt &other) const{
    if(*this == other){
        return false;
    }
    return !(*this < other);
}

bool BigInt::operator>(const int &other) const{
    BigInt bigint(other);
    return *this > bigint;
}

bool operator>(const int &left, const BigInt &right){
    BigInt bigint(left);
    return bigint > right;
}

bool BigInt::operator>=(const BigInt &other) const{
    return *this > other || *this == other;
}

bool BigInt::operator>=(const int &other) const{
    BigInt bigint(other);
    return *this >= bigint;
}

bool operator>=(const int &left, const BigInt &right){
    BigInt bigint(left);
    return bigint >= right;
}

BigInt BigInt::operator-() const{
    BigInt res = *this;
    res.sign *= -1;
    return res;
}

std::istream& operator>>(std::istream& istream, BigInt &bigint){
    std::string str;
    istream >> str;
    BigInt res(str);
    bigint = std::move(res);
    return istream;
}

std::ostream& operator<<(std::ostream& ostream, const BigInt &bigint){
    if(bigint.sign == -1){
        ostream << "-";
    }
    ostream << bigint.buffer[bigint.buffer_size - 1];
    for (int32_t i = bigint.buffer_size - 2; i >= 0; --i){
        ostream << std::setfill('0') << std::setw(BASE_EXP) << bigint.buffer[i];
    }
    return ostream;
}

void normalize(BigInt &bigint){
    size_t idx = bigint.buffer_size - 1;
    while(idx > 0){
        if(bigint.buffer[idx] != 0){
            break;
        }
        idx--;
    }
    bigint.buffer_size = idx + 1;
    int *buffer_change = new int32_t[bigint.buffer_size];
    for(size_t i = 0; i < bigint.buffer_size; ++i){
        buffer_change[i] = bigint.buffer[i];
    }
    delete[] bigint.buffer;
    bigint.buffer = buffer_change;
}

BigInt abs(const BigInt &bigint){
    BigInt res = bigint;
    res.sign = 1;
    return res;
}

#endif //BIGINT_H
