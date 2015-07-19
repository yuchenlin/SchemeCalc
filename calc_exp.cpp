#include "calc_exp.h"
#include "opt.h"
#include "compare.h"
#include "next_token.h"
#include <cstring>
#include <string>
#include <cstdio>

Number *calc_exp(){
    char *tk0 = next_token();
    Number *res;
    if (*tk0 == '(')
    {
        char *tk1 = next_token(); 
        Opt *opt;
        Cons *cons = new Cons(NULL, NULL), *tail = cons;
        Number *val;
		if(tk1==NULL){printf("123");throw 0;}
		if(strcmp(tk1,"+")==0)opt=new Add();
		else if(strcmp(tk1,"-")==0)opt=new Sub();
		else if(strcmp(tk1,"*")==0)opt=new Mul();
        else if(strcmp(tk1,"/")==0)opt=new Div(); 
        else if(strcmp(tk1,"abs")==0)opt=new Abs();
        else if(strcmp(tk1,"sqrt")==0)opt=new Sqrt();
        else if(strcmp(tk1,"floor")==0)opt=new Floor();
        else if(strcmp(tk1,"ceiling")==0)opt=new Ceiling();
        else if(strcmp(tk1,"truncate")==0)opt=new Truncate();
        else if(strcmp(tk1,"round")==0)opt=new Round();
        else if(strcmp(tk1,"numerator")==0)opt=new Numerator();
        else if(strcmp(tk1,"denominator")==0)opt=new Denominator();
        else if(strcmp(tk1,"imag-part")==0)opt=new ImagPart();
        else if(strcmp(tk1,"real-part")==0)opt=new RealPart();
        else if(strcmp(tk1,"exact->inexact")==0)opt=new ToInexact();
        else if(strcmp(tk1,"inexact->exact")==0)opt=new GetExact();
		else throw 0;
        while ((val = calc_exp()))
        {
           // cout << "test";
            tail->cdr = new Cons(val, NULL);
            tail = tail->cdr;
        }
        res = opt->calc(cons->cdr);
        for (Cons *np; cons; cons = np)
        {
            np = cons->cdr;
            delete cons;
        }
    }
    else if (*tk0 == ')')
	{
        return NULL;
	}
    else
    {
        
        // 增加尝试复数
		res=Rational::from_string(tk0);
		if(!res)
            res = Float::from_string(tk0);
        if(!res)
            res = Complex::from_string(tk0);
		if(res==NULL)      
            throw 0;
    }
    return res;
}
