#include "float.h"
#include "rational.h"
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <iomanip>
#include <string>
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
    assert(ABS(tmp->number_) > 1e-200 && "divide zero");
    Float *result = new Float(number_ / tmp->number_);
    return result;
}

void Float::print()
{
    cout<<setprecision(10)<<number_;
    //cout<<number_;
//    cout<<endl;
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
