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
        clasType = BOOLEAN;
    }
    bool flag;
    ~Boolean(){};
    virtual void print(){
        if(flag)
            cout<<"#t";
        else
            cout<<"#f";
    }
    
};
#endif /* defined(__SchemeCalc__boolean__) */
