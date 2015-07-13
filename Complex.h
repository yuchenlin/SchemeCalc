//
//  Complex.h
//  SchemeCalc
//
//  Created by LinYuchen on 7/13/15.
//  Copyright (c) 2015 LinYuchen. All rights reserved.
//

#ifndef SchemeCalc_Complex_h
#define SchemeCalc_Complex_h
#include "number.h"
#include "rational.h"

class Complex:public Number {
    
public:
    Rational real;
    Rational imag;
    bool isExact;
    
    Complex(Rational r,Rational i):real(r),imag(i){
        
    }
};

#endif
