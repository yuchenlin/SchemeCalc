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
#include <cstring>
#define SCAST_RATIONAL(x) static_cast<Rational*>(x)
#define SCAST_FLOAT(x) static_cast<Float*>(x)
#define SCAST_COMPLEX(x) static_cast<Complex*>(x)

class Add : public Opt {
    /* Use the lowest level type */
    Number *calc(Cons *con)
    {
		Number *res = new Rational(0,1);
		Number *last;
        for (; con; con = con->cdr)
        {
			if(con->car->type_>3||con->car->type_<1)
                throw 0;
            Number *opr = con->car, *conv;
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
			if(tmp->car->type_>3||tmp->car->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res=new Rational(0, 1),*last;
		Number *opr = con->car, *conv;
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
			opr=con->car;
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
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            Number *opr = con->car, *conv;
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
			if(tmp->car->type_>3||tmp->car->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res=new Rational(1,1),*last;
		Number *opr=con->car,*conv;
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
			opr=con->car;
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
        
        int cnt = 0;
        for (; con; con = con->cdr)
        {
            if(con->car->type_>3||con->car->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = con->car ;
        Number *res = opr->abs();
        return res;
    }
};

class Sqrt : public Opt{
    Number* calc(Cons* con){
        
        int cnt = 0;
        for (; con; con = con->cdr)
        {
            if(con->car->type_>3||con->car->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = con->car ;
        Number *res = opr->sqrt();
        return res;
    }
};

class Floor : public Opt{
    Number* calc(Cons* con){
        
        int cnt = 0;
        for (; con; con = con->cdr)
        {
            if(con->car->type_>3||con->car->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = con->car ;
        Number *res = opr->floor();
        return res;
    }
};

class Ceiling : public Opt{
    Number* calc(Cons* con){
        
        int cnt = 0;
        for (; con; con = con->cdr)
        {
            if(con->car->type_>3||con->car->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = con->car ;
        Number *res = opr->ceiling();
        return res;
    }
};
class Truncate : public Opt{
    Number* calc(Cons* con){
        
        int cnt = 0;
        for (; con; con = con->cdr)
        {
            if(con->car->type_>3||con->car->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = con->car ;
        Number *res = opr->truncate();
        return res;
    }
};

class Round : public Opt{
    Number* calc(Cons* con){
        
        int cnt = 0;
        for (; con; con = con->cdr)
        {
            if(con->car->type_>3||con->car->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = con->car ;
        Number *res = opr->round();
        return res;
    }
};

class Numerator : public Opt{
    Number* calc(Cons* con){
        
        int cnt = 0;
        for (; con; con = con->cdr)
        {
            if(con->car->type_>3||con->car->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = con->car ;
        Number *res = opr->numerator();
        return res;
    }
};

class Denominator : public Opt{
    Number* calc(Cons* con){
        
        int cnt = 0;
        for (; con; con = con->cdr)
        {
            if(con->car->type_>3||con->car->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = con->car ;
        Number *res = opr->denominator();
        return res;
    }
};

class ImagPart : public Opt{
    Number* calc(Cons* con){
        
        int cnt = 0;
        for (; con; con = con->cdr)
        {
            if(con->car->type_>3||con->car->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = con->car ;
        Number *res = opr->imag_part();
        return res;
    }
};

class RealPart : public Opt{
    Number* calc(Cons* con){
        
        int cnt = 0;
        for (; con; con = con->cdr)
        {
            if(con->car->type_>3||con->car->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = con->car ;
        Number *res = opr->real_part();
        return res;
    }
};
class GetExact : public Opt{
    Number* calc(Cons* con){
        
        int cnt = 0;
        for (; con; con = con->cdr)
        {
            if(con->car->type_>3||con->car->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = con->car ;
        Number *res = opr->toExact();
        return res;
    }
};

class ToInexact : public Opt{
    Number* calc(Cons* con){
        
        int cnt = 0;
        for (; con; con = con->cdr)
        {
            if(con->car->type_>3||con->car->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt > 1)    throw 0;
        Number *opr = con->car ;
        Number *res = opr->toInexact();
        return res;
    }
};

//二元函数

class Quotient : public Opt{
    Number* calc(Cons* con){
        Cons *tmp = con;
        int cnt = 0;
        for (; tmp; tmp=tmp->cdr) {
            if(tmp->car->type_>3 or tmp->car->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt>2)
            assert(0 and "Quotient is only for two values");
        Number* opr1 = con->car, *opr2 = con->cdr->car,*conv;
        Number* res,* last;
        
        if(opr1->type_ >= opr2->type_)
            res = opr1->quotient(conv = opr1->convert(opr2));
        else
            res = (conv = opr2->convert(opr1) )->quotient(opr1);
        
        delete conv;
        return res;
    }
};



class Remainder : public Opt{
    Number* calc(Cons* con){
        Cons *tmp = con;
        int cnt = 0;
        for (; tmp; tmp=tmp->cdr) {
            if(tmp->car->type_>3 or tmp->car->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt>2)
            assert(0 and "Remainder is only for two values");
        Number* opr1 = con->car, *opr2 = con->cdr->car,*conv;
        Number* res,* last;
        
        if(opr1->type_ > opr2->type_)
            res = opr1->remainder(conv = opr1->convert(opr2));
        else
            res = (conv = opr2->convert(opr1) )->remainder(opr1);
        
        delete conv;
        return res;
    }
};


class Modulo : public Opt{
    Number* calc(Cons* con){
        Cons *tmp = con;
        int cnt = 0;
        for (; tmp; tmp=tmp->cdr) {
            if(tmp->car->type_>3 or tmp->car->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt>2)
            assert(0 and "Modulo is only for two values");
        Number* opr1 = con->car, *opr2 = con->cdr->car,*conv;
        Number* res,* last;
        
        if(opr1->type_ > opr2->type_)
            res = opr1->modulo(conv = opr1->convert(opr2));
        else
            res = (conv = opr2->convert(opr1) )->modulo(opr1);
        
        delete conv;
        return res;
    }
};
class GCD : public Opt{
    Number* calc(Cons* con){
        Cons *tmp = con;
        int cnt = 0;
        for (; tmp; tmp=tmp->cdr) {
            if(tmp->car->type_>3 or tmp->car->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt>2)
            assert(0 and "GCD is only for two values");
        Number* opr1 = con->car, *opr2 = con->cdr->car,*conv;
        Number* res,* last;
        
        if(opr1->type_ > opr2->type_)
            res = opr1->gcd(conv = opr1->convert(opr2));
        else
            res = (conv = opr2->convert(opr1) )->gcd(opr1);
        
        delete conv;
        return res;
    }
};

class LCM : public Opt{
    Number* calc(Cons* con){
        Cons *tmp = con;
        int cnt = 0;
        for (; tmp; tmp=tmp->cdr) {
            if(tmp->car->type_>3 or tmp->car->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt>2)
            assert(0 and "LCM is only for two values");
        Number* opr1 = con->car, *opr2 = con->cdr->car,*conv;
        Number* res,* last;
        
        if(opr1->type_ > opr2->type_)
            res = opr1->lcm(conv = opr1->convert(opr2));
        else
            res = (conv = opr2->convert(opr1) )->lcm(opr1);
        
        delete conv;
        return res;
    }
};


class Expt : public Opt{
    Number* calc(Cons* con){
        Cons *tmp = con;
        int cnt = 0;
        for (; tmp; tmp=tmp->cdr) {
            if(tmp->car->type_>3 or tmp->car->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt>2)
            assert(0 and "Expt is only for two values");
        Number* opr1 = con->car, *opr2 = con->cdr->car,*conv;
        Number* res,* last;
        
        if(opr1->type_ > opr2->type_)
            res = opr1->expt(conv = opr1->convert(opr2));
        else
            res = (conv = opr2->convert(opr1) )->expt(opr1);
        
        delete conv;
        return res;
    }
};

class GetMax : public Opt{
    Number* calc(Cons* con){
        Cons *tmp = con;
        int cnt = 0;
        for (; tmp; tmp=tmp->cdr) {
            if(tmp->car->type_>3 or tmp->car->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt>2)
            assert(0 and "getMax is only for two values");
        Number* opr1 = con->car, *opr2 = con->cdr->car,*conv;
        Number* res,* last;
        
        if(opr1->type_ > opr2->type_)
            res = opr1->getMax(conv = opr1->convert(opr2));
        else
            res = (conv = opr2->convert(opr1) )->getMax(opr1);
        
        delete conv;
        return res;
    }
};



class GetMin : public Opt{
    Number* calc(Cons* con){
        Cons *tmp = con;
        int cnt = 0;
        for (; tmp; tmp=tmp->cdr) {
            if(tmp->car->type_>3 or tmp->car->type_<1)
                throw 0;
            cnt++;
        }
        if(cnt>2)
            assert(0 and "getMin is only for two values");
        Number* opr1 = con->car, *opr2 = con->cdr->car,*conv;
        Number* res,* last;
        
        if(opr1->type_ > opr2->type_)
            res = opr1->getMin(conv = opr1->convert(opr2));
        else
            res = (conv = opr2->convert(opr1) )->getMin(opr1);
        
        delete conv;
        return res;
    }
};












