//
//  base.h
//  SchemeCalc
//
//  Created by LinYuchen on 7/20/15.
//  Copyright (c) 2015 LinYuchen. All rights reserved.
//

#ifndef __SchemeCalc__base__
#define __SchemeCalc__base__
class Base {
    
public:
    enum{
        BOOLEAN = 1,
        NUMBER =2,
        STRING = 3,
        CHAR=4
    }classType;
    
    Base(){};
    virtual ~Base(){};
    virtual void print() = 0;
    
    virtual Base* JudgeNumber()=0;
    
    virtual Base* JudgeString()=0;
    virtual Base* JudgeChar()=0;
    
    //精度判断
    virtual Base* JudgeExact()=0;
    virtual Base* JudgeInExact()=0;
    //属性判断
    virtual Base* JudgeZero()=0;
    virtual Base* JudgeNegative()=0;
    virtual Base* JudgePositive()=0;
    virtual Base* JudgeOdd()=0;
    virtual Base* JudgeEven()=0;
    
    //类型判断
    virtual Base* JudgeInteger()=0;
    virtual Base* JudgeRational()=0;
    virtual Base* JudgeReal()=0;
    virtual Base* JudgeComplex()=0;
    
    virtual Base* JudgeEqual(Base* obj)=0;
};




#endif /* defined(__SchemeCalc__Base__) */
