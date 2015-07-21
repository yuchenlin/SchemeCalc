#include "float.h"
#include "rational.h"
#include "complex.h"
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <iomanip>
#include <string>
#include <cmath>
#include <sstream>
#include <complex>

#define ABS(x) ((x)<0?(-(x)):(x))

Float::Float(double number) : number_(number)
{
    type_ = FLOAT;
}

Float::~Float()
{
    
}

Number* Float::convert(Number *number2)
{
    assert(number2->type_ <= type_);
    //cout<<number2->type_<<endl;
    Float *result = new Float();
    switch(number2->type_)
    {
        case RATIONAL:
        {
            Rational *tmp_r = SCAST_RATIONAL(number2);
            result->number_ = (double) *tmp_r;
            break;
        }
        case FLOAT:
        {
            Float *tmp = SCAST_FLOAT(number2);
            result->number_ = tmp->number_;
            break;
        }
        default:
            assert(0 && "type_ not defined");
    }
    return result;
    
}

Number *Float::add(Number *number2)
{
    Float *tmp = SCAST_FLOAT(number2);
    //cout<<number_<<' '<<tmp->number_<<endl;
    Float *result = new Float(number_ + tmp->number_);
    return result;
}

Number *Float::sub(Number *number2)
{
    Float *tmp = SCAST_FLOAT(number2);
    Float *result = new Float(number_ - tmp->number_);
    return result;
}

Number *Float::mul(Number *number2)
{
    Float *tmp = SCAST_FLOAT(number2);
    Float *result = new Float(number_ * tmp->number_);
    return result;
}

Number *Float::div(Number *number2)
{
    Float *tmp = SCAST_FLOAT(number2);
    //assert(ABS(tmp->number_) > 1e-315 && "divide zero");
    Float *result = new Float(number_ / tmp->number_);
    return result;
}

void Float::print()
{
    cout<<setprecision(18)<<number_;
    //cout<<number_;
//    cout<<endl;
    //1.1111111111111112
}


Float *Float::from_string(char *expression)
{
    string s = expression;
    char *end_pointer;
    double res = 0.0;
    res = strtod(expression, &end_pointer);//转换成double
//    stringstream ss;
//    ss<<s;
//    ss>>res;
    //如果是空的 或者 中间断了
    if (end_pointer == expression or end_pointer != expression + s.length())
        return NULL;
    return new Float(res);
}





Number* Float::abs(){
    return new Float(ABS(number_));
}
bool Float::isInteger(){
    return number_ ==  trunc(number_);
}
Number* Float::quotient(Number* obj){
    Float* tempf = SCAST_FLOAT(obj);
    assert(tempf->isInteger() and isInteger() and "quotient is only for integer");
    return this->div(obj)->truncate();
    
}
Number* Float::remainder(Number* obj){
    Float* tempf = SCAST_FLOAT(obj);
    assert(tempf->isInteger() and isInteger() and "remainder is only for integer");
    return new Float(fmod(number_, tempf->number_));
}
Number* Float::modulo(Number* obj){
    Float* tempf = SCAST_FLOAT(obj);
    assert(tempf->isInteger() and isInteger() and "modulo is only for integer");
    bool flag = not (number_ * tempf->number_ >=0);
    return new Float(fmod(number_, tempf->number_) + flag * tempf->number_);
}

Number* Float::gcd(Number* obj){
    Float* tempf = SCAST_FLOAT(obj);
    assert(tempf->isInteger() and isInteger() and "modulo is only for integer");
    double b,s;
    b = max(number_,tempf->number_);
    s = min(number_,tempf->number_);
    double t = fmod(b,s);
    while(t){
        b = s;
        s = t;
        t = fmod(b, s);
    }
    return new Float(s);
}
Number* Float::lcm(Number* obj){
    return SCAST_FLOAT(this->mul(obj)->div(this->gcd(obj)));
}

Number* Float::expt(Number* obj){
    
    if(number_>=0)
        return new Float(pow(number_, SCAST_FLOAT(obj)->number_));
    else{
        Complex* c = new Complex();
        c = SCAST_COMPLEX(c->convert(this));
        Complex* d = SCAST_COMPLEX(c->convert(obj));
        return c->expt(d);
    }
}
Number* Float::sqrt(){
    if(number_>=0){
        return new Float(::sqrt(number_));
    }else{
        Complex* c = new Complex(new Float(0),new Float(::sqrt(fabs(number_))));
        c->isExact = false;
        return c;
    }
}
Number* Float::floor(){
    return new Float(::floor(number_));
}
Number* Float::ceiling(){
    return new Float(::ceil(number_));
}
Number* Float::truncate(){
    return new Float(::trunc(number_));
}
Number* Float::round(){
    //round nearbyint rint  据说round在某些版本的g++有错误
    return new Float(::round(number_));
}
Number* Float::getMax(Number* obj){
    return new Float(max(number_,SCAST_FLOAT(obj)->number_));
}
Number* Float::getMin(Number* obj){
    return new Float(min(number_, SCAST_FLOAT(obj)->number_));
}
//不知道这两个什么鬼 要先转换成Exact才可以吧
Number* Float::numerator(){
    return this->toExact()->numerator();
}
Number* Float::denominator(){
    return this->toExact()->denominator();
}


Number* Float::imag_part(){
    return new Float(0.0);
}
Number* Float::real_part(){
    return new Float(number_);
}
Number* Float::toInexact(){
    return new Float(number_);
}


Number* Float::toExact(){
    if(isInteger())
        return new Rational(::trunc(number_),ONE);
    double son = number_, mom = 1;
    while (son != trunc(son)){
        son *= 2;
        mom *= 2;
    }
    return new Rational(LongInt(son),LongInt(mom));
}


Number* Float::sin(){
    return new Float(::sin(number_));
}

Number* Float::asin(){
    return new Float(::asin(number_));
}

Number* Float::cos(){
    return new Float(::cos(number_));
}
Number* Float::acos(){
    return new Float(::acos(number_));
}
Number* Float::tan(){
    return new Float(::tan(number_));
}
Number* Float::atan(){
    return new Float(::atan(number_));
}
Number* Float::exp(){
    return new Float(::exp(number_));
}
Number* Float::log(){
    return new Float(::log(number_));
}

Number* Float::rectangular(Number* obj){
    Complex* res = new Complex();
    res->isExact = false;
    res->real = new Float(number_);
    res->imag = new Float(SCAST_FLOAT(obj)->number_);
    return res;
}

Number* Float::polar(Number* obj){
    complex<double> cres;
    cres = std::polar(number_,SCAST_FLOAT(obj)->number_);
    Complex* res = new Complex();
    res->isExact = false;
    res->real = new Float(std::real(cres));
    res->imag = new Float(std::imag(cres));
    return res;
}

Number* Float::magnitude(){
    return new Float(number_);
}

Number* Float::angle(){
    complex<double> cres(0,number_);
    return new Float(std::arg(cres));
}


