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
        else{
            //这是str[i]是'\\' str[i+1]可能是t n b 等等
            //res->s += str[i];
            if(i<=l-3){
                switch (str[i+1]) {
                    case '\"':
                        res->s+= '\"';
                        i++;
                        break;
                    case 't':
                        res->s += '\t';
                        i++;
                        break;
                    case 'n':
                        res->s += '\n';
                        i++;
                        break;
                    default:
                        res->s += str[i+1];
                        i++;
                        break;
                }
            }
        }
    }
    return res;
}

//需要考虑到char为空的时候的情况

String* String::make_string(Number* len, Char* c){
    String* res = new String();
    unsigned long l = getIndex(len);
    for (int i = 0; i < l; ++i) {
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


String* String::SubString(Number* start){
    return SubString(start,new Rational(s.length(),ONE));
}
String* String::SubString(Number* start , Number* end){
    String* res = new String();
    res->s = "";
    for (unsigned long i = getIndex(start); i < getIndex(end); ++i) {
        res->s += s[i];
    }
    return res;
}


Number* String::ConvertToNumber(){//默认就是十进制的
    char* todo = const_cast<char *>(s.c_str());
    Number* res;
    
    res = Rational::from_string(todo);
    if(!res)
        res = Float::from_string(todo);
    if(!res)
        res = Complex::from_string(todo);
    return res;//如果都不可以的话是NULL
}

Number* String::ConvertToNumber(Number* b){//默认就是十进制的
    unsigned long base = getIndex(b);
    assert( base==10 and "base must be 10");
    return ConvertToNumber();
}


