#pragma once

#define SCAST_NUMBER(x) static_cast<Number*>(x)
#include <cstring>
#include <string>
#include "base.h"
#include "boolean.h"


class Number : public Base{
public:
	enum{
		RATIONAL = 1,
		FLOAT = 2,
        COMPLEX=3
	} type_;
	Number(){
        clasType = NUMBER;
    }
	virtual ~Number(){}
	virtual Number* convert(Number *number2) = 0;
	virtual Number *add(Number *number2)  = 0;
	virtual Number *sub(Number *number2)  = 0;
	virtual Number *mul(Number *number2)  = 0;
	virtual Number *div(Number *number2)  = 0;
	virtual void print() = 0;
    
    //week2 新增函数
    virtual Number* abs()=0;
    virtual Number* sqrt()=0;
    virtual Number* floor()=0;
    virtual Number* ceiling()=0;
    virtual Number* truncate()=0;
    virtual Number* round()=0;
    virtual Number* numerator()=0;
    virtual Number* denominator()=0;
    virtual Number* imag_part()=0;
    virtual Number* real_part()=0;
    virtual Number* toInexact()=0;
    virtual Number* toExact()=0;
    //二元函数
    virtual Number* quotient(Number* obj)=0;
    virtual Number* remainder(Number* obj)=0;
    virtual Number* modulo(Number* obj)=0;
    virtual Number* gcd(Number* obj)=0;
    virtual Number* lcm(Number* obj)=0;
    virtual Number* expt(Number* obj)=0;
    
    virtual Number* getMax(Number* obj)=0;
    virtual Number* getMin(Number * obj)=0;
    
    //Week3新增函数
    
    //三角函数
    virtual Number* sin()=0;
    virtual Number* cos()=0;
    virtual Number* tan()=0;
    virtual Number* asin()=0;
    virtual Number* acos()=0;
    virtual Number* atan()=0;
    
    //幂和对数
    virtual Number* exp()=0;
    virtual Number* log()=0;
    
//    //复数运算
    //这两个只支持实数两个实数阿的 这两个只是支持实数的运算
    virtual Number* rectangular(Number* obj)=0; //二元函数
    virtual Number* polar(Number* obj)=0; //二元函数
    virtual Number* magnitude()=0; //一元
    virtual Number* angle()=0;//一元

//    //判断类函数
//    //精度判断
    virtual Boolean* JudgeExact()=0;
    virtual Boolean* JudgeInExact()=0;
//    //属性判断
    virtual Boolean* JudgeZero()=0;
    virtual Boolean* JudgeNegative()=0;
    virtual Boolean* JudgePositive()=0;
    virtual Boolean* JudgeOdd()=0;
    virtual Boolean* JudgeEven()=0;
    
   //类型判断
    virtual Boolean* JudgeNumber(){ //此函数不是抽象函数
        return new Boolean(true);
    }
    virtual Boolean* JudgeInteger()=0;
    virtual Boolean* JudgeRational()=0;
    virtual Boolean* JudgeReal()=0;
    virtual Boolean* JudgeComplex()=0;
    //不等判断
    virtual Boolean* JudgeLessThan(Number* obj)=0;
    virtual Boolean* JudgeGreaterThan(Number* obj)=0;
    virtual Boolean* JudgeLessThanOrEuqalTo(Number* obj)=0;
    virtual Boolean* JudgeGreaterThanOrEuqalTo(Number* obj)=0;
   
};


