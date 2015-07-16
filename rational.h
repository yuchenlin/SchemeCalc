#pragma once
#include "number.h"
#include "long_int.h"
#include <cstring>
#include <cstring>
#include <string>
#define SCAST_RATIONAL(x) static_cast<Rational*>(x)

//避免构造大量的重复对象
static const LongInt ZERO = 0;
static const LongInt ONE = 1;


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
    
    
    
    virtual Number* abs();
    
    virtual Number* quotient(Number* obj);
    virtual Number* remainder(Number* obj);
    virtual Number* modulo(Number* obj);
    
    virtual Number* numerator();
    virtual Number* denominator();
    virtual Number* imag_part();
    virtual Number* real_part();
    
    virtual Number* getMax(Number* obj);
    virtual Number* getMin(Number * obj);
    
    virtual Number* gcd(Number* obj);
    virtual Number* lcm(Number* obj);
    
    

    virtual Number* floor();//下整
    virtual Number* ceiling();//上整
    virtual Number* truncate();//只取整数部分
    virtual Number* round();//
    
    
    
    virtual Number* sqrt();
    virtual Number* expt(Number* obj);
    
    virtual Number* toInexact();
    virtual Number* toExact();
 



