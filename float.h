#pragma once

#include "number.h"
#include <cstring>
#include <string>

#define SCAST_FLOAT(x) static_cast<Float*>(x)

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
};

