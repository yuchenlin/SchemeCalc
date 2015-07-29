//
//  boolean.h
//  SchemeCalc
//
//  Created by LinYuchen on 7/20/15.
//  Copyright (c) 2015 LinYuchen. All rights reserved.
//

#ifndef __SchemeCalc__boolean__
#define __SchemeCalc__boolean__

#include <stdio.h>
#include "base.h"
#include <iostream>
using namespace std;
class Boolean : public Base{
    
public:
    Boolean(bool f = false):flag(f){
        classType = BOOLEAN;
    }
    bool flag;
    ~Boolean(){};
    virtual void print(){
        if(flag)
            cout<<"#t";
        else
            cout<<"#f";
    }
    
    virtual Base* JudgeNumber(){
        return new Boolean(false);
    }
    
    
    virtual Base* JudgeChar(){
        return new Boolean(false);
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
    
    static Boolean* from_string(char* expression){
        string todo = expression;
        if(todo == "#f")
            return new Boolean(false);
        else if(todo == "#t" )
            return new Boolean(true);
        else
            return NULL;
    }
    
};

#endif /* defined(__SchemeCalc__boolean__) */
