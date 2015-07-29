#pragma once
#include "opt.h"
#include "float.h"
#include "rational.h"
#include "number.h"
#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>
#include <complex>
#include <cstdlib>
#include "complex.h"
#include "string_.h"
#include "char_.h"
#include <cstring>
#define SCAST_RATIONAL(x) static_cast<Rational*>(x)
#define SCAST_FLOAT(x) static_cast<Float*>(x)
#define SCAST_COMPLEX(x) static_cast<Complex*>(x)
#define SCAST_BOOLEAN(x) static_cast<Boolean*>(x)

class Add : public Opt {
    /* Use the lowest level type */
    Number *calc(Cons *con)
    {
        Number *res = new Rational(0,1);
        Number *last;
        for (; con; con = con->cdr)
        {
            Number *opr = SCAST_NUMBER( con->car ), *conv;
            if(opr->type_>3||opr->type_<1)
                throw 0;
            last = res;
            //cout<<"opr type: "<<opr->type_<<endl;
            
            if (res->type_ >= opr->type_)
            {
                res = res->add(conv = res->convert(opr));
            }
            else
            {
                res = (conv = opr->convert(res))->add(opr);
            }
            
            delete last;
            delete conv;
            
            
        }
        return res;
    }
};
class Sub:public Opt{
    Number *calc(Cons *con)
    {
        Cons *tmp=con;
        int cnt=0;
        for(;tmp;tmp=tmp->cdr)
        {
            if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
            {
                throw 0;
            }
            cnt++;
        }
        Number *res=new Rational(0, 1),*last;
        Number *opr = SCAST_NUMBER(con->car), *conv;
        last=res;
        if(cnt==1)
        {
            if (res->type_ > opr->type_)
                res = res->sub(conv = res->convert(opr));
            else
                res = (conv = opr->convert(res))->sub(opr);
            delete last;
            delete conv;
            return res;
        }
        if (res->type_ > opr->type_)
            res = res->add(conv = res->convert(opr));
        else
            res = (conv = opr->convert(res))->add(opr);
        con=con->cdr;
        delete last;
        delete conv;
        for(;con;con=con->cdr)
        {
            opr=SCAST_NUMBER(con->car);
            last=res;
            if(res->type_>opr->type_)
                res=res->sub(conv=res->convert(opr));
            else
                res=(conv=opr->convert(res))->sub(opr);
            delete last;
            delete conv;
        }
        return res;
    }
};
class Mul : public Opt {
    /* Use the lowest level type */
    Number *calc(Cons *con)
    {
        Number *res = new Rational(1, 1), *last;
        for (; con; con = con->cdr)
        {
            if(SCAST_NUMBER(con->car)->type_>3||SCAST_NUMBER(con->car)->type_<1)
            {
                throw 0;
            }
            Number *opr = SCAST_NUMBER(con->car), *conv;
            last = res;
            if (res->type_ > opr->type_)
                res = res->mul(conv = res->convert(opr));
            else
                res = (conv = opr->convert(res))->mul(opr);
            delete last;
            delete conv;
        }
        return res;
    }
};




class Div:public Opt{
    Number *calc(Cons *con)
    {
        Cons *tmp=con;
        int cnt=0;
        for(;tmp;tmp=tmp->cdr)
        {
            if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
            {
                throw 0;
            }
            cnt++;
        }
        Number *res=new Rational(1,1),*last;
        Number *opr = SCAST_NUMBER(con->car),*conv;
        last=res;
        Number *zero = new Float(0.0);
        if(cnt==1)
        {
            if(res->type_>opr->type_)
                res=res->div(conv=res->convert(opr));
            else
                res=(conv=opr->convert(res))->div(opr);
            delete last;
            delete conv;
            return res;
        }
        if(res->type_>opr->type_)
            res=res->mul(conv=res->convert(opr));
        else
            res=(conv=opr->convert(res))->mul(opr);
        con=con->cdr;
        delete last;
        delete conv;
        for(;con;con=con->cdr)
        {
            opr=SCAST_NUMBER(con->car);
            last=res;
            if(res->type_>opr->type_)
                res=res->div(conv=res->convert(opr));
            else
                res=(conv=opr->convert(res))->div(opr);
            delete last;
            delete conv;
        }
        return res;
    }
};

//一元函数


class Abs : public Opt{
    Number* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            if(SCAST_NUMBER(contmp->car)->type_>3||SCAST_NUMBER(contmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = SCAST_NUMBER(con->car);
        Number *res = opr->abs();
        return res;
    }
};

class Sqrt : public Opt{
    Number* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            if(SCAST_NUMBER(contmp->car)->type_>3||SCAST_NUMBER(contmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = SCAST_NUMBER(con->car);
        Number *res = opr->sqrt();
        return res;
    }
};

class Floor : public Opt{
    Number* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            if(SCAST_NUMBER(contmp->car)->type_>3||SCAST_NUMBER(contmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = SCAST_NUMBER(con->car);
        Number *res = opr->floor();
        return res;
    }
};

class Ceiling : public Opt{
    Number* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            if(SCAST_NUMBER(contmp->car)->type_>3||SCAST_NUMBER(contmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = SCAST_NUMBER(con->car);
        Number *res = opr->ceiling();
        return res;
    }
};
class Truncate : public Opt{
    Number* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            if(SCAST_NUMBER(contmp->car)->type_>3||SCAST_NUMBER(contmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = SCAST_NUMBER(con->car);
        Number *res = opr->truncate();
        return res;
    }
};

class Round : public Opt{
    Number* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            if(SCAST_NUMBER(contmp->car)->type_>3||SCAST_NUMBER(contmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = SCAST_NUMBER(con->car);
        Number *res = opr->round();
        return res;
    }
};

class Numerator : public Opt{
    Number* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            if(SCAST_NUMBER(contmp->car)->type_>3||SCAST_NUMBER(contmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = SCAST_NUMBER(con->car);
        Number *res = opr->numerator();
        return res;
    }
};

class Denominator : public Opt{
    Number* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            if(SCAST_NUMBER(contmp->car)->type_>3||SCAST_NUMBER(contmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = SCAST_NUMBER(con->car);
        Number *res = opr->denominator();
        return res;
    }
};

class ImagPart : public Opt{
    Number* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            if(SCAST_NUMBER(contmp->car)->type_>3||SCAST_NUMBER(contmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = SCAST_NUMBER(con->car);
        Number *res = opr->imag_part();
        return res;
    }
};

class RealPart : public Opt{
    Number* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            if(SCAST_NUMBER(contmp->car)->type_>3||SCAST_NUMBER(contmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = SCAST_NUMBER(con->car);
        Number *res = opr->real_part();
        return res;
    }
};
class GetExact : public Opt{
    Number* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            if(SCAST_NUMBER(contmp->car)->type_>3||SCAST_NUMBER(contmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = SCAST_NUMBER(con->car);
        Number *res = opr->toExact();
        return res;
    }
};

class ToInexact : public Opt{
    Number* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            if(SCAST_NUMBER(contmp->car)->type_>3||SCAST_NUMBER(contmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = SCAST_NUMBER(con->car);
        Number *res = opr->toInexact();
        return res;
    }
};
class Sin : public Opt{
    Number* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            if(SCAST_NUMBER(contmp->car)->type_>3||SCAST_NUMBER(contmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = SCAST_NUMBER(con->car);
        Number *res = opr->sin();
        return res;
    }
};

class Asin : public Opt{
    Number* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            if(SCAST_NUMBER(contmp->car)->type_>3||SCAST_NUMBER(contmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = SCAST_NUMBER(con->car);
        Number *res = opr->asin();
        return res;
    }
};
class Cos : public Opt{
    Number* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            if(SCAST_NUMBER(contmp->car)->type_>3||SCAST_NUMBER(contmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = SCAST_NUMBER(con->car);
        Number *res = opr->cos();
        return res;
    }
};
class Acos : public Opt{
    Number* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            if(SCAST_NUMBER(contmp->car)->type_>3||SCAST_NUMBER(contmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = SCAST_NUMBER(con->car);
        Number *res = opr->acos();
        return res;
    }
};
class Tan : public Opt{
    Number* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            if(SCAST_NUMBER(contmp->car)->type_>3||SCAST_NUMBER(contmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = SCAST_NUMBER(con->car);
        Number *res = opr->tan();
        return res;
    }
};
class Atan : public Opt{
    Number* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            if(SCAST_NUMBER(contmp->car)->type_>3||SCAST_NUMBER(contmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = SCAST_NUMBER(con->car);
        Number *res = opr->atan();
        return res;
    }
};
class Log : public Opt{
    Number* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            if(SCAST_NUMBER(contmp->car)->type_>3||SCAST_NUMBER(contmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = SCAST_NUMBER(con->car);
        Number *res = opr->log();
        return res;
    }
};
class Exp : public Opt{
    Number* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            if(SCAST_NUMBER(contmp->car)->type_>3||SCAST_NUMBER(contmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = SCAST_NUMBER(con->car);
        Number *res = opr->exp();
        return res;
    }
};

class Magnitude : public Opt{
    Number* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            if(SCAST_NUMBER(contmp->car)->type_>3||SCAST_NUMBER(contmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = SCAST_NUMBER(con->car);
        Number *res = opr->magnitude();
        return res;
    }
};
class Angle : public Opt{
    Number* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            if(SCAST_NUMBER(contmp->car)->type_>3||SCAST_NUMBER(contmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = SCAST_NUMBER(con->car);
        Number *res = opr->angle();
        return res;
    }
};

class IsNumber : public Opt{
    Boolean* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Base *opr = (con->car);
        Boolean *res =SCAST_BOOLEAN(opr->JudgeNumber());
        return res;
    }
};

class IsExact : public Opt{
    Boolean* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Base *opr = (con->car);
        Boolean *res = SCAST_BOOLEAN(opr->JudgeExact());
        return res;
    }
};
class IsInexact : public Opt{
    Boolean* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Base *opr = (con->car);
        Boolean *res = SCAST_BOOLEAN(opr->JudgeInExact());
        return res;
    }
};
class IsZero : public Opt{
    Boolean* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Base *opr = (con->car);
        Boolean *res = SCAST_BOOLEAN(opr->JudgeZero());
        return res;
    }
};
class IsNegative : public Opt{
    Boolean* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Base *opr = (con->car);
        Boolean *res = SCAST_BOOLEAN(opr->JudgeNegative());
        return res;
    }
};
class IsPositive : public Opt{
    Boolean* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Base *opr = (con->car);
        Boolean *res = SCAST_BOOLEAN(opr->JudgePositive());
        return res;
    }
};
class IsOdd : public Opt{
    Boolean* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Base *opr = (con->car);
        Boolean *res = SCAST_BOOLEAN(opr->JudgeOdd());
        return res;
    }
};
class IsEven : public Opt{
    Boolean* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Base *opr = (con->car);
        Boolean *res = SCAST_BOOLEAN(opr->JudgeEven());
        return res;
    }
};
class IsInteger : public Opt{
    Boolean* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Base *opr = (con->car);
        Boolean *res = SCAST_BOOLEAN(opr->JudgeInteger());
        return res;
    }
};
class IsRational : public Opt{
    Boolean* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Base *opr = (con->car);
        Boolean *res = SCAST_BOOLEAN(opr->JudgeRational());
        return res;
    }
};

class IsComplex : public Opt{
    Boolean* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Base *opr = (con->car);
        Boolean *res = SCAST_BOOLEAN(opr->JudgeComplex());
        return res;
    }
};


class IsReal : public Opt{
    Boolean* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Base *opr = (con->car);
        Boolean *res = SCAST_BOOLEAN(opr->JudgeReal());
        return res;
    }
};

//字符串一元函数

class StringLength : public Opt{
    Number* calc(Cons* con){
        Cons* contmp = con;
        int cnt = 0;
        for (; contmp; contmp = contmp->cdr)
        {
            cnt++;
        }
        if(cnt > 1)    throw 0;
        String *opr = SCAST_STRING(con->car);
        Number *res = SCAST_NUMBER(opr->getLength());
        return res;
    }
};



//二元函数


class Rectangular : public Opt{
    Number* calc(Cons* con){
        Cons *tmp = con;
        int cnt = 0;
        for (; tmp; tmp=tmp->cdr) {
            if(SCAST_NUMBER(tmp->car)->type_>3 or SCAST_NUMBER(tmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt>2)
            assert(0 and "Rectangular is only for two values");
        Number* opr1 = SCAST_NUMBER(con->car), *opr2 = SCAST_NUMBER(con->cdr->car),*conv;
        Number* res,* last;
        
        if(opr1->type_ >= opr2->type_)
            res = opr1->rectangular(conv = opr1->convert(opr2));
        else
            res = (conv = opr2->convert(opr1) )->rectangular(opr2);
        
        delete conv;
        return res;
    }
};
class Polar : public Opt{
    Number* calc(Cons* con){
        Cons *tmp = con;
        int cnt = 0;
        for (; tmp; tmp=tmp->cdr) {
            if(SCAST_NUMBER(tmp->car)->type_>3 or SCAST_NUMBER(tmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt>2)
            assert(0 and "Polar is only for two values");
        Number* opr1 = SCAST_NUMBER(con->car), *opr2 = SCAST_NUMBER(con->cdr->car),*conv;
        Number* res,* last;
        
        if(opr1->type_ >= opr2->type_)
            res = opr1->polar(conv = opr1->convert(opr2));
        else
            res = (conv = opr2->convert(opr1) )->polar(opr2);
        
        delete conv;
        return res;
    }
};

class Quotient : public Opt{
    Number* calc(Cons* con){
        Cons *tmp = con;
        int cnt = 0;
        for (; tmp; tmp=tmp->cdr) {
            if(SCAST_NUMBER(tmp->car)->type_>3 or SCAST_NUMBER(tmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt>2)
            assert(0 and "Quotient is only for two values");
        Number* opr1 = SCAST_NUMBER(con->car), *opr2 = SCAST_NUMBER(con->cdr->car),*conv;
        Number* res,* last;
        
        if(opr1->type_ >= opr2->type_)
            res = opr1->quotient(conv = opr1->convert(opr2));
        else
            res = (conv = opr2->convert(opr1) )->quotient(opr2);
        
        delete conv;
        return res;
    }
};



class Remainder : public Opt{
    Number* calc(Cons* con){
        Cons *tmp = con;
        int cnt = 0;
        for (; tmp; tmp=tmp->cdr) {
            if(SCAST_NUMBER(tmp->car)->type_>3 or SCAST_NUMBER(tmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt>2)
            assert(0 and "Remainder is only for two values");
        Number* opr1 = SCAST_NUMBER(con->car), *opr2 = SCAST_NUMBER(con->cdr->car),*conv;
        Number* res,* last;
        
        if(opr1->type_ > opr2->type_)
            res = opr1->remainder(conv = opr1->convert(opr2));
        else
            res = (conv = opr2->convert(opr1) )->remainder(opr2);
        
        delete conv;
        return res;
    }
};


class Modulo : public Opt{
    Number* calc(Cons* con){
        Cons *tmp = con;
        int cnt = 0;
        for (; tmp; tmp=tmp->cdr) {
            if(SCAST_NUMBER(tmp->car)->type_>3 or SCAST_NUMBER(tmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt>2)
            assert(0 and "Modulo is only for two values");
        Number* opr1 = SCAST_NUMBER(con->car), *opr2 = SCAST_NUMBER(con->cdr->car),*conv;
        Number* res,* last;
        
        if(opr1->type_ > opr2->type_)
            res = opr1->modulo(conv = opr1->convert(opr2));
        else
            res = (conv = opr2->convert(opr1) )->modulo(opr2);
        
        delete conv;
        return res;
    }
};

class Expt : public Opt{
    Number* calc(Cons* con){
        Cons *tmp = con;
        int cnt = 0;
        for (; tmp; tmp=tmp->cdr) {
            if(SCAST_NUMBER(tmp->car)->type_>3 or SCAST_NUMBER(tmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt>2)
            assert(0 and "Expt is only for two values");
        Number* opr1 = SCAST_NUMBER(con->car), *opr2 = SCAST_NUMBER(con->cdr->car),*conv;
        Number* res,* last;
        
        if(opr1->type_ > opr2->type_)
            res = opr1->expt(conv = opr1->convert(opr2));
        else
            res = (conv = opr2->convert(opr1) )->expt(opr2);
        
        delete conv;
        return res;
    }
};
//二元  可连续的多元函数

class GCD : public Opt{
    Number* calc(Cons* con){
        
        Number* res,*last;
        res = new Rational(0,1);
        for (; con; con=con->cdr) {
            if(SCAST_NUMBER(con->car)->type_>3 or SCAST_NUMBER(con->car)->type_<1)
                throw 0;
            Number* opr = SCAST_NUMBER(con->car), *conv;
            last = res;
            if(res->type_ > opr->type_)
                res = res->gcd(conv= res->convert(opr));
            else
                res = (conv = opr->convert(res))->gcd(opr);
            delete last;
            delete conv;
        }
        return res;
    }
};



class LCM : public Opt{
    Number* calc(Cons* con){
        
        Number* res,*last;
        res = new Rational(1,1);
        for (; con; con=con->cdr) {
            if(SCAST_NUMBER(con->car)->type_>3 or SCAST_NUMBER(con->car)->type_<1)
                
                throw 0;
            Number* opr = SCAST_NUMBER(con->car), *conv;
            
            last = res;
            if(res->type_ > opr->type_)
                res = res->lcm(conv= res->convert(opr));
            else
                res = (conv = opr->convert(res))->lcm(opr);
            delete last;
            delete conv;
        }
        return res;
    }
};





class GetMax : public Opt{
    Number* calc(Cons* con){
        Cons *tmp = con;
        int cnt = 0;
        for (; tmp; tmp=tmp->cdr) {
            if(SCAST_NUMBER(tmp->car)->type_>3 or SCAST_NUMBER(tmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt==0) throw 0;
        
        Number* res,* last;
        Number* opr = SCAST_NUMBER(con->car), *conv;
        
        res = opr;
        con = con->cdr;//取出第一个
        for (; con; con=con->cdr) {
            opr = SCAST_NUMBER(con->car);
            last = res;
            if(res->type_ > opr->type_)
                res = res->getMax(conv = res->convert(opr));
            else
                res = (conv = opr->convert(res))->getMax(opr);
            delete last;
            delete conv;
        }
        return res;
    }
};



class GetMin : public Opt{
    Number* calc(Cons* con){
        Cons *tmp = con;
        int cnt = 0;
        for (; tmp; tmp=tmp->cdr) {
            if(SCAST_NUMBER(tmp->car)->type_>3 or SCAST_NUMBER(tmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt==0) throw 0;
        
        
        Number* res,* last;
        Number* opr = SCAST_NUMBER(con->car), *conv;
        
        res = opr;
        con = con->cdr;
        for (; con; con=con->cdr) {
            opr = SCAST_NUMBER(con->car);
            last = res;
            if(res->type_ > opr->type_)
                res = res->getMin(conv = res->convert(opr));
            else
                res = (conv = opr->convert(res))->getMin(opr);
            delete last;
            delete conv;
        }
        return res;
    }
};


class ToJudgeEqual : public Opt{
    Boolean* calc(Cons* con){
        Cons *tmp=con;
        int cnt=0;
        for(;tmp;tmp=tmp->cdr)
        {
            cnt++;
        }
        if (cnt>2)
            assert(0 && "error");
        
        Base *opr1 = con->car ,
             *opr2 = con->cdr->car;
        Boolean* res;
        if (opr1->classType != opr2->classType)
            return new Boolean(false);
        else
        {
            if (opr1->classType == Base::NUMBER)
            {
                Number* a = SCAST_NUMBER(opr1);
                Number* b = SCAST_NUMBER(opr2);
                Number* conv;
                int tocheck = SCAST_BOOLEAN(a->JudgeExact())->flag
                                    + SCAST_BOOLEAN(b->JudgeExact())->flag;
                if(tocheck ==0 or tocheck==2){
                    if(a->type_ > b->type_)
                        res = SCAST_BOOLEAN(a->JudgeEqual(conv = a->convert(b)));
                    else
                        res = SCAST_BOOLEAN((conv = b->convert(a))->JudgeEqual(b));
                }else{
                    return new Boolean(false);
                }
            }else{
                res = SCAST_BOOLEAN(opr1->JudgeEqual(opr2));
            }
        }
        return res;
    }
};

class ToJudgeLessThan : public Opt{
    Boolean* calc(Cons* con){
        Cons *tmp = con;
        int cnt = 0;
        for (; tmp; tmp=tmp->cdr) {
            if(SCAST_NUMBER(tmp->car)->type_>3 or SCAST_NUMBER(tmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt==0) throw 0;
        bool ok = true;
        
        Number* res,* last;
        Number* opr = SCAST_NUMBER(con->car), *conv;
        
        res = opr;
        con = con->cdr;
        for (; con; con=con->cdr) {
            opr = SCAST_NUMBER(con->car);
            last = res;
            if(res->type_ > opr->type_){
                ok = res->JudgeLessThan(conv = res->convert(opr))->flag;
            }
            else{
                //res = (conv = opr->convert(res))->getMin(opr);
                ok = (conv = opr->convert(res))->JudgeLessThan(opr)->flag;
            }
            res = opr;
            if(!ok)
                break;
            delete last;
            delete conv;
        }
        return new Boolean(ok);
    }
};
class ToJudgeGreaterThan : public Opt{
    Boolean* calc(Cons* con){
        Cons *tmp = con;
        int cnt = 0;
        for (; tmp; tmp=tmp->cdr) {
            if(SCAST_NUMBER(tmp->car)->type_>3 or SCAST_NUMBER(tmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt==0) throw 0;
        bool ok = true;
        
        Number* res,* last;
        Number* opr = SCAST_NUMBER(con->car), *conv;
        
        res = opr;
        con = con->cdr;
        for (; con; con=con->cdr) {
            opr = SCAST_NUMBER(con->car);
            last = res;
            if(res->type_ > opr->type_){
                ok = res->JudgeGreaterThan(conv = res->convert(opr))->flag;
            }
            else{
                //res = (conv = opr->convert(res))->getMin(opr);
                ok = (conv = opr->convert(res))->JudgeGreaterThan(opr)->flag;
            }
            res = opr;
            if(!ok)
                break;
            delete last;
            delete conv;
        }
        return new Boolean(ok);
    }
};
class ToJudgeLessThanOrEuqalTo : public Opt{
    Boolean* calc(Cons* con){
        Cons *tmp = con;
        int cnt = 0;
        for (; tmp; tmp=tmp->cdr) {
            if(SCAST_NUMBER(tmp->car)->type_>3 or SCAST_NUMBER(tmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt==0) throw 0;
        bool ok = true;
        
        Number* res,* last;
        Number* opr = SCAST_NUMBER(con->car), *conv;
        
        res = opr;
        con = con->cdr;
        for (; con; con=con->cdr) {
            opr = SCAST_NUMBER(con->car);
            last = res;
            if(res->type_ > opr->type_){
                ok = res->JudgeLessThanOrEuqalTo(conv = res->convert(opr))->flag;
            }
            else{
                //res = (conv = opr->convert(res))->getMin(opr);
                ok = (conv = opr->convert(res))->JudgeLessThanOrEuqalTo(opr)->flag;
            }
            res = opr;
            if(!ok)
                break;
            delete last;
            delete conv;
        }
        return new Boolean(ok);
    }
};
class ToJudgeGreaterThanOrEuqalTo : public Opt{
    Boolean* calc(Cons* con){
        Cons *tmp = con;
        int cnt = 0;
        for (; tmp; tmp=tmp->cdr) {
            if(SCAST_NUMBER(tmp->car)->type_>3 or SCAST_NUMBER(tmp->car)->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt==0) throw 0;
        bool ok = true;
        
        Number* res,* last;
        Number* opr = SCAST_NUMBER(con->car), *conv;
        
        res = opr;
        con = con->cdr;
        for (; con; con=con->cdr) {
            opr = SCAST_NUMBER(con->car);
            last = res;
            if(res->type_ > opr->type_){
                ok = res->JudgeGreaterThanOrEuqalTo(conv = res->convert(opr))->flag;
            }
            else{
                //res = (conv = opr->convert(res))->getMin(opr);
                ok = (conv = opr->convert(res))->JudgeGreaterThanOrEuqalTo(opr)->flag;
            }
            res = opr;
            if(!ok)
                break;
            delete last;
            delete conv;
        }
        return new Boolean(ok);
    }
};







