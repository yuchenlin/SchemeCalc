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
#define SCAST_CHAR(x) static_cast<Char*>(x)
using namespace std;

class Char: public Base{
public:
    char c;
    Char(){classType = CHAR;}
    Char(char i):c(i){
        classType = CHAR;
    }
    ~Char(){}
    virtual void print(){
        cout<<c;
    }

    //一堆没什么用的判断函数
    
    virtual Base* JudgeNumber(){
        return new Boolean(false);
    }
    
    virtual Base* JudgeChar(){
        return new Boolean(true);
    }
    virtual Base* JudgeString(){
        return new Boolean(false);
    }
    
    virtual Base* JudgeExact(){
        return new Boolean(false);
    }
    virtual Base* JudgeInExact(){
        return new Boolean(false);
    }
    virtual Base* JudgeZero(){
        return new Boolean(false);
    }
    virtual Base* JudgeNegative(){
        return new Boolean(false);
    }
    virtual Base* JudgePositive(){
        return new Boolean(false);
    }
    virtual Base* JudgeOdd(){
        return new Boolean(false);
    }
    virtual Base* JudgeEven(){
        return new Boolean(false);
    }
    virtual Base* JudgeInteger(){
        return new Boolean(false);
    }
    virtual Base* JudgeRational(){
        return new Boolean(false);
    }
    virtual Base* JudgeReal(){
        return new Boolean(false);
    }
    virtual Base* JudgeComplex(){
        return new Boolean(false);
    }
    
    virtual Base* JudgeEqual(Base* obj){
        if(obj->classType == Base::CHAR and SCAST_CHAR(obj)->c == c)
            return new Boolean(true);
        else
            return new Boolean(false);
    }
    
};

#endif
