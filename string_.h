//
//  string_.h
//  SchemeCalc
//
//  Created by LinYuchen on 7/23/15.
//  Copyright (c) 2015 LinYuchen. All rights reserved.
//

#ifndef SchemeCalc_string__h
#define SchemeCalc_string__h

#include "base.h"
#include <string>
#include <cstring>
#include <iostream>
#include "boolean.h"

using namespace std;

class String : public Base{
    
    string s;
    String(string i=""):s(i){
        classType = STRING;
    }
    ~String(){}
    virtual void print(){
        cout<<s;
    }
    
    //一堆没什么用的判断函数
    
    virtual Base* JudgeNumber(){
        return new Boolean(false);
    }
    
    virtual Base* JudgeChar(){
        return new Boolean(false);
    }
    virtual Base* JudgeString(){
        return new Boolean(true);
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
    
    static String* from_string(char* expression);
    //
    
    
    
};



#endif
