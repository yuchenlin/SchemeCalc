//
//  base.h
//  SchemeCalc
//
//  Created by LinYuchen on 7/20/15.
//  Copyright (c) 2015 LinYuchen. All rights reserved.
//

#ifndef __SchemeCalc__base__
#define __SchemeCalc__base__

#include "boolean.h"
class Base {
    
public:
    enum{
        BOOLEAN = 1,
        NUMBER =2
    }clasType;
    
    Base(){};
    virtual ~Base(){};
    virtual void print() = 0;

    virtual Boolean* JudgeNumber()=0;
};




#endif /* defined(__SchemeCalc__Base__) */
