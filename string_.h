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
#include "rational.h"
#include "boolean.h"
#include "char_.h"
#include "complex.h"
#include "float.h"
#define SCAST_STRING(x) static_cast<String*>(x)

using namespace std;

class String : public Base{
public:
    string s;
    String(string i=""):s(i){
        classType = STRING;
    }
    ~String(){}
    virtual void print(){
        cout<<"\""<<s<<"\"";
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
    
    virtual Base* JudgeEqual(Base* obj){
        if(obj->classType == Base::STRING and SCAST_STRING(obj)->s == s)
            return new Boolean(true);
        else
            return new Boolean(false);
   }
    
    String* gen_string(Char* c){
        return new String(s+= c->c);
    }
    static String* from_string(char* expression);
    static String* make_string(Number* len,Char* c);
    static string getLower(string todo){
        string res="";
        for (int i = 0; i < todo.length(); ++i) {
            res += isalpha(todo[i]) ?
            tolower( todo[i]) : todo[i];
        }
        return res;
    }
    static unsigned long getIndex(Number* index){
        if(not index->JudgeInteger() or index->JudgeNegative())
            return -1;
        unsigned long ind = 0;
        ind = (double)*SCAST_RATIONAL(index->toExact()->real_part()->numerator());
        return ind;
    }
    //
    
    Base* getLength(){
        return new Rational(s.length(),ONE);
    }
    
    Char* getRef(Number* index);
    Boolean* JudgeStringEqual(String* obj){
        return new Boolean(s == obj->s);
    }
    Boolean* JudgeStringSmaller(String* obj){
        return new Boolean(s < obj->s);
    }
    Boolean* JudgeStringSmallerOrEqual(String* obj){
        return new Boolean(s <= obj->s);
    }
    Boolean* JudgeStringBigger(String* obj){
        return new Boolean(s > obj->s);
    }
    Boolean* JudgeStringBiggerOrEqual(String* obj){
        return new Boolean(s >= obj->s);
    }
    
    Boolean* JudgeStringCIEqual(String* obj){
        return new Boolean(getLower(s) == getLower(obj->s));
    }
    Boolean* JudgeStringCISmaller(String* obj){
        return new Boolean(getLower(s) < getLower(obj->s));
    }
    Boolean* JudgeStringCISmallerOrEqual(String* obj){
        return new Boolean(getLower(s) <= getLower(obj->s));
    }
    Boolean* JudgeStringCIBigger(String* obj){
        return new Boolean(getLower(s) > getLower(obj->s));
    }
    Boolean* JudgeStringCIBiggerOrEqual(String* obj){
        return new Boolean(getLower(s) >= getLower(obj->s));
    }
    
    String* SubString(Number* start);
    String* SubString(Number* start , Number* end);
    
    String* Append(String* str){
        return new String(s+=str->s);
    }
    
    String* Copy(){
        return new String(s);
    }
    
    Number* ConvertToNumber();
    Number* ConvertToNumber(Number* base);
    
};



#endif
