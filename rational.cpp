

#include "rational.h"
#include <cassert>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <cstring>


Rational::Rational(LongInt num, LongInt den):numerator_(num),denominator_(den)
{
    type_=RATIONAL;
    reduce();
}
Rational::Rational(const Rational& obj):numerator_(obj.numerator_),denominator_(obj.denominator_){
    type_=RATIONAL;
}

Rational::~Rational()
{
    
}
//约分函数

void Rational::reduce()
{
    assert(denominator_!=0 && "denominator is zero");
    
    if(!numerator_) //已经重载了非运算符
    {
        denominator_=1;//如果分子是0 直接让分母化为1
        return;
    }
    LongInt BIG, SMALL, tmp;
    
    LongInt num_abs = numerator_.getABS();
    LongInt den_abs = denominator_.getABS();
    
    BIG = max(num_abs, den_abs);
    SMALL = min(num_abs,den_abs);
    tmp = BIG % SMALL;
    
    while(tmp!=0) // 辗转相除法 欧几里得
    {
        BIG = SMALL;
        SMALL = tmp;
        tmp = BIG % SMALL;
    }
    numerator_ = numerator_ / SMALL;
    denominator_ = denominator_ / SMALL;
    
    if(denominator_.n.back() < 0 )//如果分母是负数
    {
        numerator_.changeSign();
        denominator_.changeSign();
    }
}


Number *Rational::convert(Number *number2)
{
    assert(number2->type_ <= type_);
    Rational *result=new Rational();
    switch(number2->type_)
    {
        case RATIONAL:
        {
            Rational *tmp = SCAST_RATIONAL(number2);
            result->numerator_ = tmp->numerator_;
            result->denominator_ = tmp->denominator_;
            break;
        }
        default:
            assert(0 && "type_ not defined");
    }
    result->reduce();
    return result;
}

Number *Rational::add(Number *number2)
{
    Rational *tmp = SCAST_RATIONAL(number2);
    Rational *result = new Rational();
    result->numerator_ = numerator_*tmp->denominator_ + denominator_*tmp->numerator_;
    result->denominator_ = denominator_ * tmp->denominator_;
    result->reduce();//最后进行约分
    return result;
}

//分数减法
Number *Rational::sub(Number *number2)
{
    Rational *tmp = SCAST_RATIONAL(number2);
    Rational *result = new Rational();
    result->numerator_ = numerator_*tmp->denominator_ - denominator_*tmp->numerator_;
    result->denominator_ = denominator_ * tmp->denominator_;
    result->reduce();//最后要进行约分
    return result;
}

Number *Rational::mul(Number *number2)
{
    Rational *tmp = SCAST_RATIONAL(number2);
    Rational *result = new Rational();
    result->numerator_ = numerator_ * tmp->numerator_;
    result->denominator_ = denominator_ * tmp->denominator_;
    result->reduce();
    return result;
}

Number *Rational::div(Number *number2)
{
    Rational *tmp = SCAST_RATIONAL(number2);
    Rational *result = new Rational();
    result->numerator_ = numerator_ * tmp->denominator_;
    result->denominator_ = denominator_ * tmp->numerator_;
    result->reduce();
    return result;
}

void Rational::print()
{
    cout<<numerator_;//先输出分子
    if(denominator_ != 1) //判断分母是否为1
    {
        cout<<'/';
        cout<<denominator_;
    }
//    cout<<endl;
}

//从string里读入一个Rational
Rational *Rational::from_string(char *expression)
{
    char* sp = strchr(expression, '/');
    char* end = strchr(expression,'\0');
    char* d_pos = strchr(expression,'.');
    char* E_pos = strchr(expression,'E');
    char* e_pos = strchr(expression,'e');
    char* i_pos = strchr(expression,'i');
    
    if ( i_pos or d_pos or E_pos or e_pos)//有小数点 或者e的存在则 不是rational
        return NULL;//会去构造一个Float
    if(sp) //如果存在分式标记
    {
        
        //分子的长度
        int num_len = sp - expression;
        
        //临时字符数组 存储分子部分
        char* num_cs = new char [num_len+2];
        strncpy(num_cs, expression, num_len);
        num_cs[num_len]='\0';
        string strForNum = num_cs;//赋值给一个string
        LongInt num = strForNum;//再用string来初始化一个Longint作为分子
        delete [] num_cs;//释放临时变量
        
        
        //分母部分的处理 同样的顺序
        int den_len = end - sp - 1;
        char* den_cs = new char [den_len+2];
        //注意是从sp+1开始读取
        strncpy(den_cs, sp+1, den_len);
        den_cs[den_len]='\0';
        string strForDen=den_cs;
        LongInt den = strForDen;
        delete [] den_cs;
        return new Rational(num,den);
    }
    else //如果不存在分式标记 可以看做分母是1
    {
        //只需要计入分子即可 分母为1
        
        int num_len = end - expression;
        char* num_cs = new char [num_len+2];
        strncpy(num_cs, expression, num_len);
        num_cs[num_len]='\0';
        
        string num_str = num_cs;
        
        LongInt num = num_str;
        delete [] num_cs;
        return new Rational(num,1);
    }
    //为了编译通过 必须有一个返回值
    return NULL;
}

//把一个Rational的值转换为double类型
Rational::operator double(){
    if(denominator_==1){
        return numerator_.getDouble();
    }
    double res = numerator_.getDouble() / denominator_.getDouble();
    return res;
}
