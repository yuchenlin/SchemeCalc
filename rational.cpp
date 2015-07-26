
#include "float.h"
#include "complex.h"
#include "rational.h"
#include <cassert>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <cstring>
#include <complex>

#include <cmath>
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
    assert(denominator_!=ZERO && "denominator is zero");
    
    if(!numerator_) //已经重载了非运算符
    {
        denominator_=ONE;//如果分子是0 直接让分母化为ONE
        return;
    }
    LongInt BIG, SMALL, tmp;
    
    LongInt num_abs = numerator_.getABS();
    LongInt den_abs = denominator_.getABS();
    
    BIG = max(num_abs, den_abs);
    SMALL = min(num_abs,den_abs);
    tmp = BIG % SMALL;
    
    while(tmp!=ZERO) // 辗转相除法 欧几里得
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
    if(denominator_ != ONE) //判断分母是否为ONE
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
        return new Rational(num,ONE);
    }
    //为了编译通过 必须有一个返回值
    return NULL;
}


//把一个Rational的值转换为double类型
Rational::operator double(){
    if(denominator_==ONE){
        return numerator_.getDouble();
    }
    double res = numerator_.getDouble() / denominator_.getDouble();
    return res;
}

bool Rational::is(int n){
    bool ok = (numerator_== denominator_ * n);
    return ok;
}



Number* Rational::abs(){
    Rational* res = new Rational();
    res->numerator_ = numerator_;
    res->denominator_ = denominator_;
    res->numerator_.removeSign();
    res->denominator_.removeSign();
    return res;
}

Number* Rational::quotient(Number* obj){
    Rational* tmpr = SCAST_RATIONAL(obj->toExact());
    assert(denominator_==ONE and tmpr->denominator_==ONE and "quotient operation is only for Integer Type !");
    return new Rational(numerator_ / tmpr->numerator_ , ONE);
}
Number* Rational::remainder(Number* obj){
    Rational* tmpr = SCAST_RATIONAL(obj->toExact());
    assert(denominator_==ONE and tmpr->denominator_==ONE and "remainder operation is only for Integer Type !");
    return new Rational(numerator_ % tmpr->numerator_ , ONE);
}

Number* Rational::modulo(Number* obj){
    Rational* tmpr = SCAST_RATIONAL(obj->toExact());
    assert(denominator_==ONE and tmpr->denominator_==ONE and "madulo operation is only for Integer Type !");
    if(numerator_.n.back() * tmpr->numerator_.n.back() >= 0) //除数和被除数同号
        return new Rational(numerator_ % tmpr->numerator_ , ONE);
    else
        return new Rational(numerator_ % tmpr->numerator_+ tmpr->numerator_ , ONE);
}
Number* Rational::numerator(){
    return new Rational(numerator_,ONE);
}

Number* Rational::denominator(){
    return new Rational(denominator_,ONE);
}


Number* Rational::imag_part(){
    return new Rational(ZERO,ONE);
}

Number* Rational::real_part(){
    return new Rational(numerator_,denominator_);
}



Number* Rational::getMax(Number* obj){
    Rational* toCheck = SCAST_RATIONAL(this->sub(obj->toExact()));
    return new Rational(toCheck->sgn()>=0 ? (*this) :(*(SCAST_RATIONAL(obj))));
}

Number* Rational::getMin(Number* obj){
    Rational* toCheck = SCAST_RATIONAL(this->sub(obj->toExact()));
    return new Rational(toCheck->sgn()<0 ? (*this) :(*(SCAST_RATIONAL(obj))));
}

Number* Rational::gcd(Number* obj){
    Rational* tmpr = SCAST_RATIONAL(obj->toExact());
    assert(denominator_==ONE and tmpr->denominator_==ONE and "gcd operation is only for Integer Type !");
    LongInt num_abs = numerator_.getABS(), den_abs = tmpr->numerator_.getABS();
    LongInt BIG = max(num_abs,den_abs);
    LongInt SMALL = min(num_abs,den_abs);
    if(SMALL==ZERO)
        return new Rational(BIG,ONE);
    LongInt tmp = BIG % SMALL;
    
    while(tmp!=ZERO) // 辗转相除法 欧几里得
    {
        BIG = SMALL;
        SMALL = tmp;
        tmp = BIG % SMALL;
    }
    
    return new Rational(SMALL,ONE);
}


Number* Rational::lcm(Number* obj){
    
    Rational* tmpr = SCAST_RATIONAL(obj->toExact());
    assert(denominator_==ONE and tmpr->denominator_==ONE and "lcm operation is only for Integer Type !");
    if(this->numerator_ == ZERO and tmpr->numerator_==ZERO)
        return new Rational(ZERO,ONE);
    return this->mul(tmpr)->div(this->gcd(tmpr))->abs();
}


Number* Rational::floor(){
    //本身是整数
    if(denominator_==ONE)
        return new Rational(numerator_,ONE);
    LongInt q = numerator_ / denominator_;
    return new Rational(sgn() >=0 ? q : q-ONE, ONE);
}

Number* Rational::ceiling(){
    //本身是整数
    if(denominator_==ONE)
        return new Rational(numerator_,ONE);
    LongInt q = numerator_ / denominator_;
    return new Rational( sgn() >=0 ? q+ONE : q, ONE);
}

Number* Rational::truncate(){
    if(denominator_==ONE)    //本身是整数
        return new Rational(numerator_,ONE);
    return new Rational( numerator_ / denominator_, ONE);
}

Number* Rational::round(){
    Number* res;
    Rational* one_two = new Rational(ONE,LongInt(2));
    if(sgn()>=0)//正数
        res = this->add(one_two)->floor();
    else
        res = this->sub(one_two)->ceiling();
    delete one_two;
    return res;
}



Number* Rational::sqrt(){
//    assert( sgn()>=0 and "sqrt is for positive number" );
    if(sgn()>=0){
        double res = *this; //已经重载了double的类型转换
        res = ::sqrt(res);
        return new Float(res);
    }else{
        double res = *this;
        res = ::sqrt(fabs(res));
        Complex* c = new Complex(new Float(0),new Float(res));
        c->isExact = false;
        return c;
    }
}


Number* Rational::expt(Number* obj){
    if(sgn()<0){
        Complex* c = new Complex();
        c = SCAST_COMPLEX(c->convert(this));
        Complex* d = SCAST_COMPLEX(c->convert(obj));
        return c->expt(d);
    }else{
        Float* tmpf = new Float();
        tmpf = SCAST_FLOAT(tmpf->convert(obj));
        return new Float(pow(double(*this), double(*SCAST_RATIONAL(obj))));
    }
}

Number* Rational::sin(){
    return new Float(::sin(double(*this)));
}

Number* Rational::asin(){
    Float* f = new Float((double)(*this));
    return f->asin();
}

Number* Rational::cos(){
    return new Float(::cos((double)(*this)));
}
Number* Rational::acos(){
    Float* f = new Float((double)(*this));
    return f->acos();
}
Number* Rational::tan(){
    return new Float(::tan(double(*this)));
}
Number* Rational::atan(){
    return new Float(::atan(double(*this)));
}


Number* Rational::exp(){
    return new Float(::exp(double(*this)));
}
Number* Rational::log(){
    return (new Float(double(*this)))->log();
}

Number* Rational::magnitude(){
    return (new Rational(numerator_,denominator_))->abs();
}

Number* Rational::angle(){
    complex<double> cres(double(*this),0);
    return new Float(std::arg(cres));
}

Number* Rational::rectangular(Number* obj){
    Complex* res = new Complex();
    if(obj->type_==FLOAT){
        res->isExact = false;
        res->real = this->toInexact();
        res->imag = obj->toInexact();
    }else{
        res->isExact = true;
        res->real = this->toExact();
        res->imag = obj->toExact();
    }
    return res;
}

Number* Rational::polar(Number* obj){ 
    return this->toInexact()->polar(obj->toInexact());

}

Number* Rational::toInexact(){
    return new Float(*this);
}

Number* Rational::toExact(){
    return new Rational(*this);
}


Boolean* Rational::JudgeExact(){
    return new Boolean(true);
}


Boolean* Rational::JudgeInExact(){
    return new Boolean(false);
}

Boolean* Rational::JudgeZero(){
    return new Boolean(numerator_ == ZERO);
}

Boolean* Rational::JudgeNegative(){
    return new Boolean(sgn() < 0);
}

Boolean* Rational::JudgePositive(){
    return new Boolean(sgn() > 0);
}

Boolean* Rational::JudgeOdd(){
    if(JudgeInteger()->flag){
        return new Boolean(numerator_ %2 == ONE);
    }else
        assert(0 and "for integer");
        return NULL;
}

Boolean* Rational::JudgeEven(){
    if(JudgeInteger()->flag){
        return new Boolean(numerator_ %2 == ZERO);
    }else
        assert(0 and "for integer");
        return NULL;
}
//类型判断
Boolean* Rational::JudgeInteger(){
    return new Boolean(denominator_ == ONE);
}
Boolean* Rational::JudgeRational(){
    return new Boolean(true);
}
Boolean* Rational::JudgeReal(){
    return new Boolean(true);
}
Boolean* Rational::JudgeComplex(){
    return new Boolean(true);
} 
// 不等判断


Boolean* Rational::JudgeLessThan(Number* obj){
    Rational* toCheck = SCAST_RATIONAL(this->sub(obj->toExact()));
    return new Boolean(toCheck->sgn() < 0 );
}
Boolean* Rational::JudgeGreaterThan(Number* obj){
    return obj->JudgeLessThan(this);
}
Boolean* Rational::JudgeLessThanOrEuqalTo(Number* obj){
    Boolean* res = obj->JudgeGreaterThan(this);
    res->flag = not res->flag;
    return res;
}
Boolean* Rational::JudgeGreaterThanOrEuqalTo(Number* obj){
    Boolean* res = this->JudgeLessThan(obj);
    res->flag = not res->flag;
    return res;
}