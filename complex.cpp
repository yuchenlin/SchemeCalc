//
//  complex.cpp
//  SchemeCalc
//
//  Created by LinYuchen on 7/13/15.
//  Copyright (c) 2015 LinYuchen. All rights reserved.
//
#include <cstring>
#include <string>
#include <cassert>
#include "complex.h"



Complex::~Complex(){
    delete real;
    delete imag;
}

Complex::Complex(){
    isExact = true;
}

Complex::Complex(Number* r, Number* i):real(r),imag(i){
    isExact = (r->type_ == FLOAT and i->type_ ==  FLOAT);
}

Complex* Complex::from_string(char *expression){
    //总体思想是先判断
    return NULL;
}

Number* Complex::convert(Number *number2){
    
    return NULL;
}
Number* Complex::add(Number *number2){
    return NULL;
}
Number* Complex::sub(Number *number2){
     return NULL;
}
Number* Complex::mul(Number *number2){
     return NULL;
}
Number* Complex::div(Number *number2){
     return NULL;
}
void Complex::print(){
    
}



