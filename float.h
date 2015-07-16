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

