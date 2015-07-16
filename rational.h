#pragma once
#include "number.h"
#include "long_int.h"
#include <cstring>
#include <cstring>
#include <string>
#define SCAST_RATIONAL(x) static_cast<Rational*>(x)

class Rational:public Number{
public:
    LongInt numerator_; //分子
	LongInt denominator_; //分母
    //构造函数
	Rational(LongInt num=0, LongInt den=1);
    Rational(const Rational& obj);
    void reduce();
    int sgn(){
        return numerator_.n.back()*denominator_.n.back();
    }
    //各种虚函数
	virtual ~Rational(); //析构函数
    virtual Number *convert(Number *number2);   //转换函数
	virtual Number *add(Number *number2);       //四则运算
	virtual Number *sub(Number *number2);
	virtual Number *mul(Number *number2);
	virtual Number *div(Number *number2);
	virtual void print();                       //打印输出
    operator double ();
	static Rational *from_string(char *expression); //从一个string里构造一个有理数
    bool is(int n);
    
    
    
    virtual Number* abs(){return NULL;};
    virtual Number* quotient(Number* obj){return NULL;};
    virtual Number* remainder(Number* obj){return NULL;};
    virtual Number* modulo(Number* obj){return NULL;};
    virtual Number* gcd(Number* obj){return NULL;};
    virtual Number* lcm(Number* obj){return NULL;};
    virtual Number* expt(Number* obj){return NULL;};
    virtual Number* sqrt(){return NULL;};
    virtual Number* floor(){return NULL;};
    virtual Number* ceiling(){return NULL;};
    virtual Number* truncate(){return NULL;};
    virtual Number* round(){return NULL;};
    virtual Number* getMax(Number* obj){return NULL;};
    virtual Number* getMin(Number * obj){return NULL;};
    virtual Number* numerator(){return NULL;};
    virtual Number* denominator(){return NULL;};
    virtual Number* imag_part(){return NULL;};
    virtual Number* real_part(){return NULL;};
    virtual Number* toInexact(){return NULL;};
    virtual Number* toExact(){return NULL;};
};
 



