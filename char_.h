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
        cout<<"#\\"<<c;
    }
    
    static Char* from_string(char* xpr){
        string x = xpr;
        if(x.length()==3 and x[0]=='#' and x[1]=='\\'){
            return new Char(xpr[2]);
        }
        return NULL;
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
    
    
    Char* GetUpper(){
        return new Char(toupper(c));
    }
    
    Char* GetLower(){
        return new Char(tolower(c));
    }
    
    Rational* GetNumber(){
        return new Rational((int)c,ONE);
    }
    
    Boolean* JudgeSpace(){
        return new Boolean(c==' ');
    }
    
    Boolean* JudgeCapitalAlpha(){
        return new Boolean(c>='A' and c<='Z');
    }
    
    Boolean* JudgeSmallerAlpha(){
        return new Boolean(c>='a' and c<='z');
    }
    
    Boolean* JudgeAlpha(){
        return new Boolean(isalpha(c));
    }
    
    Boolean* JudgeDigit(){
        return new Boolean(isdigit(c));
    }
    
    
    Boolean* JudgeCharEqual(Char* obj){
       return new Boolean(c == obj->c);
    }
    //判断的时候是 所有的数字 小于大写字母 小于小写字母
    //    (char<? #\9 #\A #\a) Yes
    
    Boolean* JudgeCharSmaller(Char* obj){
        return new Boolean(c < obj->c);
    }
    
    Boolean* JudgeCharSmallerOrEqual(Char* obj){
        return new Boolean(c <= obj->c);
    }
    Boolean* JudgeCharBigger(Char* obj){
        return new Boolean(c > obj->c);
    }
    Boolean* JudgeCharBiggerOrEqual(Char* obj){
        return new Boolean(c >= obj->c);
    }
    
    Boolean* JudgeCharCIEqual(Char* obj){
        return new Boolean(tolower(c)==tolower(obj->c));
    }
    Boolean* JudgeCharCISmaller(Char* obj){
        return new Boolean(tolower(c)<tolower(obj->c));
    }
    
    Boolean* JudgeCharCISmallerOrEqual(Char* obj){
        return new Boolean(tolower(c)<=tolower(obj->c));
    }
    Boolean* JudgeCharCIBigger(Char* obj){
        return new Boolean(tolower(c)>tolower(obj->c));
    }
    Boolean* JudgeCharCIBiggerOrEqual(Char* obj){
        return new Boolean(tolower(c)>=tolower(obj->c));
    }
    
    
};

#endif
