//
//  Complex.h
//  SchemeCalc
//
//  Created by LinYuchen on 7/13/15.
//  Copyright (c) 2015 LinYuchen. All rights reserved.
//

#ifndef SchemeCalc_Complex_h
#define SchemeCalc_Complex_h
#define SCAST_COMPLEX(x) static_cast<Complex*>(x)
#include <cstring>
#include <string>
#include "float.h"
#include "number.h"
#include "rational.h"

class Complex:public Number {
    
public:
    Number* real; //实部
    Number* imag; //虚部
    bool isExact; //精确性

    Complex();//默认时 real和imag都是0
    Complex(Number* r,Number* i);
    Complex(string rstr,string istr);//fromString时构造利用
    Complex(const Complex& obj);
    virtual ~Complex();
    virtual Number *convert(Number *number2);   //转换函数
    virtual Number *add(Number *number2);       //四则运算
    virtual Number *sub(Number *number2);
    virtual Number *mul(Number *number2);
    virtual Number *div(Number *number2);
    virtual void print();                       //打印输出
    static Complex *from_string(char *expression);  //从一个string里构造一个复数
    void ToInexact();
    
    
    
    
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

#endif
