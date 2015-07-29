//
//  string_.cpp
//  SchemeCalc
//
//  Created by LinYuchen on 7/23/15.
//  Copyright (c) 2015 LinYuchen. All rights reserved.
//

#include "string_.h"



String* String::from_string(char* xpr){
    string str = xpr;
    unsigned long l = str.length();
    if( l < 2 )
        return NULL;
    if(str[0] != '\"' or str[l-1]!='\"')
        return NULL;
    if(l == 3 and str[l-2] == '\\')
        return NULL;
    if(l >= 4 and str[l-2]=='\\' and str[l-3] != '\\')
        return NULL;
    
    String* res = new String();
    res->s = "";
    for(int i = 1; i < l - 1; ++i){
        if(str[i]!='\\')
            res->s += str[i];
        else//跳过
            res->s += str[++i];
    }
    return res;
}

//需要考虑到char为空的时候的情况

String* String::make_string(Number* len, Char* c){
    String* res = new String();
    if(not len->JudgeInteger() or len->JudgeNegative())
        return NULL;
    unsigned long l = getIndex(len);
    for (int i = 1; i < l; ++i) {
        res->s += c->c;
    }
    return res;
}



Char* String::getRef(Number* index){
    Char* res  = new Char();
    if(not index->JudgeInteger() or index->JudgeNegative())
        return NULL;
    unsigned long ind = getIndex(index);
    res->c = s[ind];
    return res;
}


String* String::SubStr(Number* start){
    return SubStr(start,new Rational(s.length(),ONE));
}
String* String::SubStr(Number* start , Number* end){
    String* res = new String();
    res->s = "";
    for (unsigned long i = getIndex(start); i < getIndex(end); ++i) {
        res->s += s[i];
    }
    return res;
}









