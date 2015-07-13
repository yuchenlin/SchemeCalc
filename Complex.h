//
//  Complex.h
//  SchemeCalc
//
//  Created by LinYuchen on 7/13/15.
//  Copyright (c) 2015 LinYuchen. All rights reserved.
//

#ifndef SchemeCalc_Complex_h
#define SchemeCalc_Complex_h

#include "float.h"
#include "number.h"
#include "rational.h"

class Complex:public Number {
    
public:
    Rational exact_real;
    Rational exact_imag;
    Float inexact_real;
    Float inexact_imag;
    bool isExact;

    Complex();//默认时 real和imag都是0
    Complex(Number* r,Number* i); //:real(r),imag(i);
    
    virtual ~Complex();
    virtual Number *convert(Number *number2);   //转换函数
    virtual Number *add(Number *number2);       //四则运算
    virtual Number *sub(Number *number2);
    virtual Number *mul(Number *number2);
    virtual Number *div(Number *number2);
    virtual void print();                       //打印输出
    static Complex *from_string(char *expression);  //从一个string里构造一个复数
    
};

#endif