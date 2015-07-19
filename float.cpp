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
//    assert(isInteger() and "numerator is only for integer");
    return this->toExact()->numerator();
}
Number* Float::denominator(){
//    assert(isInteger() and "denominator is only for integer");
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
    
    double *px = &number_; //取地址为了进行分析
    
    //为了进行二进制操作 用重解释转换 换成 ll的指针
    long long int* py = reinterpret_cast<long long int*>(px);
    //取出值
    long long int y=*py;
    long long int p=1;
    
    bool v[100]={0};
    
    for (int i=1;i<=64;++i)
        v[i] = y&p,y>>=1;
    
    int tmp=0;
    for (int i=63;i>=53;--i)
        tmp<<=1,tmp+=v[i];
    tmp-=1022;
    for (int i=1;i<=11;++i)
        v[52+i] = tmp&p,tmp>>=1;
    long long int i_num=0;
    
    for (int i=63;i>=1;--i)
        i_num<<=1,i_num+=v[i];
    string s_num="";
    
    while (i_num!=0)
    {
        s_num+=(char)(i_num%10+'0');
        i_num/=10;
    }
    std::reverse(s_num.begin(),s_num.end());
    LongInt num = s_num;
    return new Rational(num,_one_pow_52);
}

/*
Number* Float::toExact(){
    if(isInteger())
        return new Rational(trunc(number_),ONE);
    if(fabs(number_)<1e-8)
        return new Rational(ZERO,ONE);
    string dble;
    //主要思想是利用string来处理小数点位
    stringstream ss;
    ss<<fixed<<setprecision(7)<<number_; //把这个double输出时保留7位小数
    ss>>dble;
    int sp = dble.find("."); //找到小数点的位置
    //用扣去小数点之后的字符串初始化一个LongInt的做分子
    LongInt son(dble.substr(0,sp)+dble.substr(sp+1,dble.length()-sp-1));
    string mom = "1";
    //用和原始字符串的长度来初始化一个分母 1000000...n个0
    for (int k = 0; k< dble.length()-sp-1; ++k)
        mom.append("0");
    
    //然后用分子分母 初始化一个Rational 构造函数里进了reduce约分
    return new Rational(son,mom);
}*/









