#include "calc_exp.h"
#include "opt.h"
#include "compare.h"
#include "next_token.h"
#include "boolean.h"
#include "string_.h"
#include "char_.h"
#include <cstring>
#include <string>
#include <cstdio>

Base *calc_exp(){
    
    char *tk0 = next_token();
    Base *res;
    if (*tk0 == '(')
    {
        char *tk1 = next_token(); 
        Opt *opt;
        Cons *cons = new Cons(NULL, NULL), *tail = cons;
        Base *val;
		if(tk1==NULL){printf("123");throw 0;}
		if(strcmp(tk1,"+")==0)opt=new Add();
		else if(strcmp(tk1,"-")==0)opt=new Sub();
		else if(strcmp(tk1,"*")==0)opt=new Mul();
        else if(strcmp(tk1,"/")==0)opt=new Div();
        //新增一元函数
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
        //新增二元函数
        else if(strcmp(tk1,"quotient")==0)opt=new Quotient();
        else if(strcmp(tk1,"remainder")==0)opt=new Remainder();
        else if(strcmp(tk1,"modulo")==0)opt=new Modulo();
        else if(strcmp(tk1,"gcd")==0)opt=new GCD();
        else if(strcmp(tk1,"lcm")==0)opt=new LCM();
        else if(strcmp(tk1,"max")==0)opt=new GetMax();
        else if(strcmp(tk1,"min")==0)opt=new GetMin();
        else if(strcmp(tk1,"expt")==0)opt=new Expt();

        else if(strcmp(tk1,"sin")==0)opt=new Sin();
        else if(strcmp(tk1,"asin")==0)opt=new Asin();
        else if(strcmp(tk1,"cos")==0)opt=new Cos();
        else if(strcmp(tk1,"acos")==0)opt=new Acos();
        else if(strcmp(tk1,"tan")==0)opt=new Tan();
        else if(strcmp(tk1,"atan")==0)opt=new Atan();
        else if(strcmp(tk1,"exp")==0)opt=new Exp();
        else if(strcmp(tk1,"log")==0)opt=new Log();
        else if(strcmp(tk1,"make-rectangular")==0)opt=new Rectangular();
        else if(strcmp(tk1,"make-polar")==0)opt=new Polar();
        else if(strcmp(tk1,"magnitude")==0)opt=new Magnitude();
        else if(strcmp(tk1,"angle")==0)opt=new Angle();
        else if(strcmp(tk1,"exact?")==0)opt=new IsExact();
        else if(strcmp(tk1,"inexact?")==0)opt=new IsInexact();
        else if(strcmp(tk1,"zero?")==0)opt=new IsZero();
        else if(strcmp(tk1,"negative?")==0)opt=new IsNegative();
        else if(strcmp(tk1,"positive?")==0)opt=new IsPositive();
        else if(strcmp(tk1,"odd?")==0)opt=new IsOdd();
        else if(strcmp(tk1,"even?")==0)opt=new IsEven();
        else if(strcmp(tk1,"number?")==0)opt=new IsNumber();
        else if(strcmp(tk1,"integer?")==0)opt=new IsInteger();
        else if(strcmp(tk1,"rational?")==0)opt=new IsRational();
        else if(strcmp(tk1,"complex?")==0)opt=new IsComplex();
        else if(strcmp(tk1,"real?")==0)opt=new IsReal();
        else if(strcmp(tk1,"equal?")==0)opt=new ToJudgeEqual();
        else if(strcmp(tk1,"<")==0)opt=new ToJudgeLessThan();
        else if(strcmp(tk1,">")==0)opt=new ToJudgeGreaterThan();
        else if(strcmp(tk1,"<=")==0)opt=new ToJudgeLessThanOrEuqalTo();
        else if(strcmp(tk1,">=")==0)opt=new ToJudgeGreaterThanOrEuqalTo();
        
        /*
        else if(strcmp(tk1,"string-length")==0)opt=new StringLength();
        else if(strcmp(tk1,"make-string")==0)opt=new MakeString();
        else if(strcmp(tk1,"string")==0)opt=new FormString();
        else if(strcmp(tk1,"string-length")==0)opt=new StrLen();
        else if(strcmp(tk1,"string-ref")==0)opt=new StrRef();
        else if(strcmp(tk1,"string=?")==0)opt=new StrEql();
        else if(strcmp(tk1,"string<?")==0)opt=new StrMoInc();
        else if(strcmp(tk1,"string<=?")==0)opt=new StrNonDec();
        else if(strcmp(tk1,"string>?")==0)opt=new StrMoDec();
        else if(strcmp(tk1,"string>=?")==0)opt=new StrNonInc();
        else if(strcmp(tk1,"string-ci=?")==0)opt=new StrCiEql();
        else if(strcmp(tk1,"string-ci<?")==0)opt=new StrCiMoInc();
        else if(strcmp(tk1,"string-ci<=?")==0)opt=new StrCiNonDec();
        else if(strcmp(tk1,"string-ci>?")==0)opt=new StrCiMoDec();
        else if(strcmp(tk1,"string-ci>=?")==0)opt=new StrCiNonInc();
        else if(strcmp(tk1,"substring")==0)opt=new SubStr();
        else if(strcmp(tk1,"string-append")==0)opt=new StrApd();
        else if(strcmp(tk1,"string-copy")==0)opt=new StrCpy();
        else if(strcmp(tk1,"number->string")==0)opt=new NumToStr();
        else if(strcmp(tk1,"string->number")==0)opt=new StrToNum();
        */
        
        else throw 0;
        while ((val = (calc_exp())))
        {
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
		res = Boolean::from_string(tk0);
        if(!res)
            res = String::from_string(tk0);
        if(!res)
            res = Rational::from_string(tk0);
		if(!res)
            res = Float::from_string(tk0);
        if(!res)
            res = Complex::from_string(tk0);
        
        if(res == NULL)
            throw 0;
    }
    return res;
}
