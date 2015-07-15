    //
//  complex.cpp
//  SchemeCalc
//
//  Created by LinYuchen on 7/13/15.
//  Copyright (c) 2015 LinYuchen. All rights reserved.
//
#include <cstring>
#include <string>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include "complex.h"

#include <cmath>

Complex::~Complex(){
    delete real;
    delete imag;
}

Complex::Complex(){
    isExact = true;
    type_ = COMPLEX;
}

Complex::Complex(Number* r, Number* i):real(r),imag(i){
    isExact = (r->type_ == FLOAT and i->type_ ==  FLOAT);
    type_ = COMPLEX;
}

Complex* Complex::from_string(char *expression){
    //总体思想是先判断
    string str = expression;
    if(str[str.length()-1]!='i')
        return NULL;
    int i_part_first = str.length()-1;//先从后向前找到虚部的成分 第一次出出现+or-则到了
    for (; i_part_first >=0; --i_part_first)
        if(str[i_part_first]=='+' or str[i_part_first]=='-')
            //or短路运算技巧  +  为了避免 1123+1e-123i这种情况
            if( i_part_first==0 or (str[i_part_first-1] != 'e'  and str[i_part_first-1]!='E') )
               break;
    //如果一直没有找到+或者-号 则是纯虚数 此时i_part_first = 0 或者-1
    if (i_part_first<0) 
        i_part_first = 0;
    string rstr,istr;
    //处理real
    rstr = (i_part_first == 0) ? "0" : rstr = str.substr(0,i_part_first);
    //处理imag
    istr = str.substr( i_part_first, str.length() - i_part_first-1);
    if (istr == "+")
        istr = "1";
    else if(istr == "-")
        istr = "-1";
    return new Complex(rstr,istr);
}
//从其他类型转换为Complex的时候
Number* Complex::convert(Number *obj){
    assert(obj->type_ <= type_); //确保转换是从Rational 或者 Float 或者 Complex也可以 来的
    Complex* res = new Complex();
    switch (obj->type_) {
        case RATIONAL:
            res->real = SCAST_RATIONAL(obj);
            res->isExact = true;
            break;
        case FLOAT:
            res->real = SCAST_FLOAT(obj);
            res->isExact = false;
        case COMPLEX:
            Complex* c = SCAST_COMPLEX(obj);
            res->real = c->real;
            res->imag = c->imag;
            res->isExact = c->isExact;
            break;
    }
    //有点问题 就是 我的res指针指来指去 会乱
    return res;
}

//四则运算
Number* Complex::add(Number *number2){
    
    //之前在convert里面已经convert过了所以可以直接用
    Complex* b = SCAST_COMPLEX(number2);
    Complex* res = new Complex();
    //现在的情况是 this 和 b 的exact 可能不一样 
    return NULL;
}
Number* Complex::sub(Number *number2){
     return NULL;
}
Number* Complex::mul(Number *number2){
     return NULL;
}
Number* Complex::div(Number *number2){
     return NULL;
}
void Complex::print(){
    bool empty = true;

    if(isExact){
        Rational* i = SCAST_RATIONAL(real);
        if(i->sgn()!=0){
            i->print();
            empty = false;
        }
        
        i = SCAST_RATIONAL(imag);

        if(i->sgn() > 0){
            if(!empty)
                cout<<"+";
            imag->print();
            cout<<"i";
            empty = false;
        }else if(i->sgn() < 0){
            imag->print();
            cout<<"i";
            empty = false;
        }
    }else{
        Float* i = SCAST_FLOAT(real);
        if(fabs(i->number_) != 0){
           i->print();
           empty = false;
        }
        i = SCAST_FLOAT(imag);
        
        if(i->number_ < 0){
            imag->print();
            empty = false;
            cout<<"i";
        }else if(i->number_ > 0){
            cout<<"+";
            imag->print();
            empty = false;
            cout<<"i";
        }
    }
    if(empty)
    	cout<<0;
}
//FromString的部分最后一步
Complex::Complex(string rstr,string istr){
    char* r = const_cast<char *>(rstr.c_str());
    char* i = const_cast<char *>(istr.c_str());
    
    int exactness = 0;
    //两部分都从Rational开始转换起 注意exact的改变
    real = Rational::from_string(r);
    exactness = 1;
    if(!real){
        real = Float::from_string(r);
        exactness = 0;
    }
    
    //
    imag = Rational::from_string(i);
    exactness++;
    if(!imag){
        imag = Float::from_string(i);
        exactness--;
    }
    isExact = exactness==2 ;
    //根据要求 要么同时为Rational 要么同时为Float
    if(exactness==1){//有一个是Rational
        if(real->type_==RATIONAL)//说明imag是Float
            real = imag->convert(real);
        else
            imag = real->convert(imag);
            
    }
    
}


