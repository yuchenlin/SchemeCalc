#pragma once

#define SCAST_NUMBER(x) static_cast<Number*>(x)
#include <cstring>
#include <string>
class Number {
public:
	enum{
		RATIONAL = 1,
		FLOAT = 2,
        COMPLEX=3
	} type_;
	Number(){}
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
    
};


