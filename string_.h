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
    virtual Base* JudgeNumber(){
        return new Boolean(false);
    }
    
    virtual Base* JudgeChar(){
        return new Boolean(false);
    }
    virtual Base* JudgeString(){
        return new Boolean(true);
    }
    
    
    
};



#endif
