#pragma once
#include <vector>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdio>
#include <string>
#define MAX(x,y) ((x)<(y)?(y):(x))
#define MIN(x,y) ((x)<(y)?(x):(y))
using namespace std;
class LongInt{
    //流输入输出运算符
    friend ostream& operator << (ostream &out, const LongInt& x)
    {
        int x_size = x.n.size();
        if (x.n.back() && x_size>=1)
            out << x.n.back();
        else if (!x.n.back() && x_size ==1)
            out << x.n.back();
        for (int i=x_size-2;i>=0;--i)
        {
            char buf[40];
            //sprintf(buf, "%08d", x.n[i]);
            sprintf(buf, "%02d", x.n[i]);
            string b = buf;
            for (int j=0;j<b.length();++j)
                out << buf[j];
        }
        return out;
    }
    friend istream& operator >> (istream &in, LongInt& x)
    {
        string s;
        if (!(in >> s)) return in;
        x = s;
        return in;
    }
    
    
    
    friend LongInt max(const LongInt &long_int1, const LongInt &long_int2);
    friend LongInt min(const LongInt &long_int1, const LongInt &long_int2);

private:
public:
    static const int _base = 100;
    static const int _width = 2;
    vector<int> n;
    
    
    
    ~LongInt();
    LongInt(long long int num = 0) ;
    LongInt(const LongInt& obj);
    LongInt(const string& str);
    LongInt& operator = (long long num);
    LongInt& operator = (const LongInt& obj);
    LongInt& operator = (const string& obj);
    
    //各种计算运算符
    LongInt operator + (const LongInt& obj) const;
    LongInt operator - (const LongInt& obj) const;
    LongInt operator / (const LongInt& b) const;
    LongInt operator % (const LongInt& b) const;
    LongInt operator * (const LongInt& obj) const;
    
    LongInt& operator += (const LongInt& obj);
    LongInt& operator -= (const LongInt& obj);
    LongInt& operator *= (const LongInt& obj){
        *this = *this * obj;
        return *this;
    }
    LongInt& operator /= (const LongInt& obj){
        *this = *this / obj;
        return *this;
    }
    LongInt& operator %= (const LongInt& obj){
        *this = *this % obj;
        return *this;
    }
    //二分试商之后的修复函数
    void mode();
    //各种逻辑运算符
    bool operator < (const LongInt& obj) const;
    bool operator > (const LongInt& obj) const ;
    bool operator <= (const LongInt& obj) const;
    bool operator >= (const LongInt& obj) const;
    bool operator != (const LongInt& obj) const;
    bool operator == (const LongInt& obj) const;
    bool operator ! () const;

    LongInt getABS () const;
    LongInt getOpposite () const;
    void changeSign();
    void removeSign();
    //尽量不要重载double
    double getDouble();
};