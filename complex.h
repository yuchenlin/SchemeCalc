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
    
    
    //三角函数
    virtual Number* sin();
    virtual Number* cos();
    virtual Number* tan();
    virtual Number* asin();
    virtual Number* acos();
    virtual Number* atan();
    
    virtual Number* exp();
    virtual Number* log();

    virtual Number* rectangular(Number* obj);
    virtual Number* polar(Number* obj);

    //for real
    virtual Number* magnitude();
    virtual Number* angle();

    
    bool isReal();//
    
    bool isInteger();//
    
};

#endif
