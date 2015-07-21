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
#include <complex>
#include <cmath>

using namespace std;

Complex::~Complex(){
    delete real;
    delete imag;
}

Complex::Complex(){
    isExact = true;
    type_ = COMPLEX;
}

Complex::Complex(const Complex& obj){
    type_ = COMPLEX;
    isExact = obj.isExact;
    switch (isExact) {
        case false:
            //都是float
            real = new Float(SCAST_FLOAT(obj.real)->number_);
            imag = new Float(SCAST_FLOAT(obj.imag)->number_);
            break;
        case true:
            real = new Rational(*SCAST_RATIONAL(obj.real));
            imag = new Rational(*SCAST_RATIONAL(obj.imag));
            break;
    }
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
    else if (istr=="")
        istr = "1";
    return new Complex(rstr,istr);
}
//从其他类型转换为Complex的时候
Number* Complex::convert(Number *obj){
    assert(obj->type_ <= type_); //确保转换是从Rational 或者 Float 或者 Complex也可以 来的
    Complex* res = new Complex();
    //此处容易造成指针的乱走 必须手动复制
    switch (obj->type_) {
        case RATIONAL:
            res->real = new Rational(*SCAST_RATIONAL(obj));
            res->imag = new Rational(0,1);
            res->isExact = true;
            break;
        case FLOAT:
            res->real = new Float(SCAST_FLOAT(obj)->number_);
            res->imag = new Float(0.0);
            res->isExact = false;
            break;
        case COMPLEX:
            //todo
            res = new Complex(*SCAST_COMPLEX(obj));
            break;
    }
    //之前有点问题 就是 我的res指针指来指去 会乱
    return res;
}

//四则运算
Number* Complex::add(Number *number2){
    
    //之前在convert里面已经convert过了所以可以直接用
    Complex* obj = SCAST_COMPLEX(number2);
    Complex* res = new Complex();
    //现在的情况是 this 和 b 的exact 可能不一样 如果不同，需要把exact的转换一下
    if(isExact != obj->isExact){
        this->ToInexact();
        obj->ToInexact();
    }
    res->isExact = isExact;
    res->real = real->add(obj->real);
    res->imag = imag->add(obj->imag);
    return res;
}
Number* Complex::sub(Number *number2){
    Complex* obj = SCAST_COMPLEX(number2);
    Complex* res = new Complex();
    if(isExact != obj->isExact){
        this->ToInexact();
        obj->ToInexact();
    }
    res->isExact = isExact;
    res->real = real->sub(obj->real);
    res->imag = imag->sub(obj->imag);
    return res;
}
Number* Complex::mul(Number *number2){
     //(a+bi)(c+di)=(ac-bd)+(bc+ad)i
    Complex* obj = SCAST_COMPLEX(number2);
    Complex* res = new Complex();
    if(isExact != obj->isExact){
        this->ToInexact();
        obj->ToInexact();
    }
    res->isExact = isExact;
    res->real = real->mul(obj->real)->sub(imag->mul(obj->imag));
    res->imag = imag->mul(obj->real)->add(real->mul(obj->imag));
    return res;
}
Number* Complex::div(Number *number2){
    Complex* obj = SCAST_COMPLEX(number2);
    Complex* res = new Complex();
    if(isExact != obj->isExact){
        this->ToInexact();
        obj->ToInexact();
    }
    Number* den = obj->real->mul(obj->real)->add(obj->imag->mul(obj->imag));
    res->isExact = isExact;
    res->real = real->mul(obj->real)->add(imag->mul(obj->imag))->div(den);
    res->imag = imag->mul(obj->real)->sub(real->mul(obj->imag))->div(den);
    return res;
}
void Complex::print(){
    if(isExact){
        Rational* i = SCAST_RATIONAL(real);
        i->print();
        i = SCAST_RATIONAL(imag);

        if(i->sgn() > 0){
            cout<<"+";
            if(not i->is(1))
                imag->print();
            cout<<"i";
        }else if(i->sgn() < 0){
            if(i->is(-1))
                cout<<"-";
            else
                imag->print();
            cout<<"i";
        }
    }else{
        Float* i = SCAST_FLOAT(real);
        i->print();
        i = SCAST_FLOAT(imag);
        
        if(i->number_ >= 0)
            cout<<"+";
        imag->print();
        cout<<"i";
    }
}
//FromString的部分最后一步
Complex::Complex(string rstr,string istr){
    type_ = COMPLEX;
    
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


void Complex::ToInexact(){
    if(isExact){
        isExact = false;
        Float* tempf = new Float();
        if(real->type_==RATIONAL){
            real = tempf->convert(real);
        }
        if(imag->type_==RATIONAL){
            imag = tempf->convert(imag);
        }
        delete tempf;
    }
}
//判断this是不是一个实数
bool Complex::isReal(){
    bool ok = false;
    switch (imag->type_) {
        case Number::RATIONAL:
            ok = SCAST_RATIONAL(imag)->numerator_ == ZERO;
            break;
        case Number::FLOAT:
            ok = fabs(SCAST_FLOAT(imag)->number_) < 1e-250;
            break;
    }
    return ok;
}


Number* Complex::abs(){
    //根据Racket只有imag为0才可以用abs
    assert(isReal() and "abs is only for rational");
    return real->abs();
}

bool Complex::isInteger(){
    bool cando = false;
    if(isReal()){
        if(this->isExact){
            cando = SCAST_RATIONAL(this->real)->denominator_==ONE;
        }else
            cando = SCAST_FLOAT(this->real)->isInteger();
    }
    return cando;
}
Number* Complex::quotient(Number* obj){
    Complex* tempc = SCAST_COMPLEX(obj);
    assert(isInteger() and tempc->isInteger() and "quotient is only for integer");
    //分类讨论
    if(this->isExact and tempc->isExact){
        return new Rational
        (SCAST_RATIONAL(this->real->quotient(tempc->real))->numerator_,ONE);
    }else
        return new Float
        (SCAST_FLOAT(this->real->quotient(tempc->real))->number_);
}


Number* Complex::remainder(Number* obj){
    Complex* tempc = SCAST_COMPLEX(obj);
    assert(isInteger() and tempc->isInteger() and "remainder is only for integer");
    //分类讨论 
    if(this->isExact and tempc->isExact){
        return new Rational
        (SCAST_RATIONAL(this->real->remainder(tempc->real))->numerator_,ONE);
    }else
        return new Float
        (SCAST_FLOAT(this->real->remainder(tempc->real))->number_);
    
}

Number* Complex::modulo(Number* obj){
    Complex* tempc = SCAST_COMPLEX(obj);
    assert(isInteger() and tempc->isInteger() and "modulo is only for integer");
    //分类讨论 
    if(this->isExact and tempc->isExact){
        return new Rational
        (SCAST_RATIONAL(this->real->modulo(tempc->real))->numerator_,ONE);
    }else
        return new Float
        (SCAST_FLOAT(this->real->modulo(tempc->real))->number_);
    
}
Number* Complex::gcd(Number* obj){
    Complex* tempc = SCAST_COMPLEX(obj);
    assert(isInteger() and tempc->isInteger() and "gcd is only for integer");
    //分类讨论

    if(this->isExact and tempc->isExact){
        return new Rational
        (SCAST_RATIONAL(this->real->gcd(tempc->real))->numerator_,ONE);
    }else
        return new Float
        (SCAST_FLOAT(this->real->gcd(tempc->real))->number_);
    
}
Number* Complex::lcm(Number* obj){
    Complex* tempc = SCAST_COMPLEX(obj);
    assert(isInteger() and tempc->isInteger() and "lcm is only for integer");
    //分类讨论

    if(this->isExact and tempc->isExact){
        return new Rational
        (SCAST_RATIONAL(this->real->lcm(tempc->real))->numerator_,ONE);
    }else
        return new Float
        (SCAST_FLOAT(this->real->lcm(tempc->real))->number_);
    
}

Number* Complex::expt(Number* obj){
    Complex* tempc = SCAST_COMPLEX(obj);
    Complex* a = SCAST_COMPLEX(this->toInexact());
    Complex* b = SCAST_COMPLEX(tempc->toInexact());
    
    complex<double> ca(SCAST_FLOAT(a->real)->number_,SCAST_FLOAT(a->imag)->number_);
    complex<double> cb(SCAST_FLOAT(b->real)->number_,SCAST_FLOAT(b->imag)->number_);
    complex<double> cres = std::exp(cb*(std::log(ca)));
    Complex* res = new Complex();
    res->isExact = false;
    res->real = new Float(::real(cres));
    res->imag = new Float(::imag(cres));
    delete a;
    delete b;
    return res;
}


Number* Complex::sqrt(){
    assert(isReal() and "sqrt is only for real number");
    return real->sqrt();
}

Number* Complex::floor(){
    assert(isReal() and "floor is only for real number");
    return real->floor();
}
Number* Complex::ceiling(){
    assert(isReal() and "ceiling is only for real number");
    return real->ceiling();
}
Number* Complex::truncate(){
    assert(isReal() and "truncate is only for real number");
    return real->truncate();
} 
Number* Complex::round(){
    assert(isReal() and "round is only for real number");
    return real->truncate();
} 
Number* Complex::numerator(){
    assert(isReal() and isExact and "numerator is for integer");
    return real->numerator();
}  
Number* Complex::denominator(){
    assert(isReal() and isExact and "denominator is for integer");
    return real->denominator();
} 
Number* Complex::getMax(Number* obj){
    Complex* tempc = SCAST_COMPLEX(obj);
    assert(isReal() and tempc->isReal() and "getMax is only for real numbers");
    return real->getMax(tempc->real);
} 
Number* Complex::getMin(Number* obj){
    Complex* tempc = SCAST_COMPLEX(obj);
    assert(isReal() and tempc->isReal() and "getMin is only for real numbers");
    return real->getMin(tempc->real);
} 

Number* Complex::imag_part(){
    return imag;
} 
Number* Complex::real_part(){
    return real;
} 
Number* Complex::toExact(){
    Complex* res = new Complex();
    res->isExact = true;
    res->real = real->toExact();
    res->imag = imag->toExact();
    return res;
    
} 
Number* Complex::toInexact(){
    Complex* res = new Complex();
    res->isExact = false;
    res->real = real->toInexact();
    res->imag = imag->toInexact();
    return res;
} 


Number* Complex::sin(){
    Complex* a = SCAST_COMPLEX(this->toInexact());
    complex<double> ca
    (SCAST_FLOAT(a->real)->number_,
        SCAST_FLOAT(a->imag)->number_);
    complex<double> cres = std::sin(ca);
    Complex* res = new Complex();
    res->isExact = false;
    res->real = new Float(::real(cres));
    res->imag = new Float(::imag(cres));
    delete a;
    return res;
}

Number* Complex::asin(){
    Complex* a = SCAST_COMPLEX(this->toInexact());
    complex<double> ca
    (SCAST_FLOAT(a->real)->number_,
     SCAST_FLOAT(a->imag)->number_);
    complex<double> cres = std::asin(ca);
    Complex* res = new Complex();
    res->isExact = false;
    res->real = new Float(::real(cres));
    res->imag = new Float(::imag(cres));
    delete a;
    return res;
}

Number* Complex::cos(){
    Complex* a = SCAST_COMPLEX(this->toInexact());
    complex<double> ca
    (SCAST_FLOAT(a->real)->number_,
     SCAST_FLOAT(a->imag)->number_);
    complex<double> cres = std::cos(ca);
    Complex* res = new Complex();
    res->isExact = false;
    res->real = new Float(::real(cres));
    res->imag = new Float(::imag(cres));
    delete a;
    return res;
}
Number* Complex::acos(){
    Complex* a = SCAST_COMPLEX(this->toInexact());
    complex<double> ca
    (SCAST_FLOAT(a->real)->number_,
     SCAST_FLOAT(a->imag)->number_);
    complex<double> cres = std::acos(ca);
    Complex* res = new Complex();
    res->isExact = false;
    res->real = new Float(::real(cres));
    res->imag = new Float(::imag(cres));
    delete a;
    return res;
}
Number* Complex::tan(){
    Complex* a = SCAST_COMPLEX(this->toInexact());
    complex<double> ca
    (SCAST_FLOAT(a->real)->number_,
     SCAST_FLOAT(a->imag)->number_);
    complex<double> cres = std::tan(ca);
    Complex* res = new Complex();
    res->isExact = false;
    res->real = new Float(::real(cres));
    res->imag = new Float(::imag(cres));
    delete a;
    return res;
}
Number* Complex::atan(){
    Complex* a = SCAST_COMPLEX(this->toInexact());
    complex<double> ca
    (SCAST_FLOAT(a->real)->number_,
     SCAST_FLOAT(a->imag)->number_);
    complex<double> cres = std::atan(ca);
    Complex* res = new Complex();
    res->isExact = false;
    res->real = new Float(::real(cres));
    res->imag = new Float(::imag(cres));
    delete a;
    return res;
}

Number* Complex::exp(){
    Complex* a = SCAST_COMPLEX(this->toInexact());
    complex<double> ca
    (SCAST_FLOAT(a->real)->number_,
     SCAST_FLOAT(a->imag)->number_);
    complex<double> cres = std::exp(ca);
    Complex* res = new Complex();
    res->isExact = false;
    res->real = new Float(::real(cres));
    res->imag = new Float(::imag(cres));
    delete a;
    return res;
}

Number* Complex::log(){
    Complex* a = SCAST_COMPLEX(this->toInexact());
    complex<double> ca
    (SCAST_FLOAT(a->real)->number_,
     SCAST_FLOAT(a->imag)->number_);
    complex<double> cres = std::log(ca);
    Complex* res = new Complex();
    res->isExact = false;
    res->real = new Float(::real(cres));
    res->imag = new Float(::imag(cres));
    delete a;
    return res;
}






