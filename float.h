#pragma once

#include "number.h"
#include "long_int.h"
#include "string_.h"
#include "boolean.h"
#include <cstring>
#include <string>
#include <cmath>

#define SCAST_FLOAT(x) static_cast<Float*>(x)
const LongInt _one_pow_52("4503599627370496");

class Float : public Number {
public:
    Float(double number = 0);
    virtual ~Float();
    
    virtual Number* convert(Number *number2);
    virtual Number* add(Number *number2);
    virtual Number* sub(Number *number2);
    virtual Number* mul(Number *number2);
    virtual Number* div(Number *number2);
    virtual void print();
    static Float *from_string(char *expression);
    double number_;
    
    virtual Number* abs();
    virtual Number* quotient(Number* obj);
    virtual Number* remainder(Number* obj);
    virtual Number* modulo(Number* obj);
    virtual Number* gcd(Number* obj);
    virtual Number* lcm(Number* obj);
    virtual Number* expt(Number* obj);
    virtual Number* sqrt();
    virtual Number* floor();
    virtual Number* ceiling();
    virtual Number* truncate();
    virtual Number* round();
    virtual Number* getMax(Number* obj);
    virtual Number* getMin(Number* obj);
    virtual Number* numerator();
    virtual Number* denominator();
    virtual Number* imag_part();
    virtual Number* real_part();
    virtual Number* toInexact();
    virtual Number* toExact();
    bool isInteger();//
    
    
    //三角函数
    virtual Number* sin();
    virtual Number* cos();
    virtual Number* tan();
    virtual Number* asin();
    virtual Number* acos();
    virtual Number* atan();
    
    virtual Number* exp();
    virtual Number* log();

    virtual Number* rectangular(Number* obj); //二元函数
    virtual Number* polar(Number* obj); //二元函数
    virtual Number* magnitude();
    virtual Number* angle();

   //精度判断
    virtual Boolean* JudgeExact();
    virtual Boolean* JudgeInExact();
   //属性判断
    virtual Boolean* JudgeZero();
    virtual Boolean* JudgeNegative();
    virtual Boolean* JudgePositive();
    virtual Boolean* JudgeOdd();
    virtual Boolean* JudgeEven();

    //类型判断
    virtual Boolean* JudgeInteger();
    virtual Boolean* JudgeRational();
    virtual Boolean* JudgeReal();
    virtual Boolean* JudgeComplex();
    //不等判断
    virtual Boolean* JudgeLessThan(Number* obj);
    virtual Boolean* JudgeGreaterThan(Number* obj);
    virtual Boolean* JudgeLessThanOrEuqalTo(Number* obj);
    virtual Boolean* JudgeGreaterThanOrEuqalTo(Number* obj);
    
    virtual Base* JudgeEqual(Base* obj){
        double tocheck = number_ - SCAST_FLOAT(obj)->number_;
        return new Boolean((fabs(tocheck)<(1e-10)));
    }
    
    virtual string NumberToString()
    {
        stringstream ss;
        ss<<number_;
        string s; ss>>s;
        return s;
    }
};

