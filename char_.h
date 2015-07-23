//
//  char_.h
//  SchemeCalc
//
//  Created by LinYuchen on 7/23/15.
//  Copyright (c) 2015 LinYuchen. All rights reserved.
//

#ifndef SchemeCalc_char__h
#define SchemeCalc_char__h
#include <iostream>
#include "base.h"
#include "boolean.h"

using namespace std;

class Char: public Base{
    char c;
    Char(){classType = CHAR;}
    Char(char i):c(i){
        classType = CHAR;
    }
    ~Char(){}
    virtual void print(){
        cout<<c;
    }
    virtual Base* JudgeNumber(){
        return new Boolean(false);
    }
    
    virtual Base* JudgeChar(){
        return new Boolean(true);
    }
    virtual Base* JudgeString(){
        return new Boolean(false);
    }
    
    
};

#endif
