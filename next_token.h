//
//  next_token.h
//  SchemeCalc
//
//  Created by LinYuchen on 7/31/15.
//  Copyright (c) 2015 LinYuchen. All rights reserved.
//

#ifndef SchemeCalc_next_token_h
#define SchemeCalc_next_token_h
#pragma once

#include <cstdio>
#include <cassert>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
FILE *input = stdin;
string s="";
int len=0;

char *next_token() {
    
    
    char *res = NULL;
	string ans;
    int cur=0;
    char ch;
    bool startString = false;
    while (!cur)
    {
        if( startString==false and( len > 0 && (s[0] == '(' || s[0] == ')')))
        {
            ans=s;
            cur=len;
            s="";
            len=0;
            break;
        }
        if ((ch = fgetc(input)) == EOF) break;
        
        if(startString){
            s+=(char)ch;
            len++;
            //judge end
            int last_quo = s.find_last_of('\"');
            if(last_quo > 0 and s[last_quo-1]!='\\'){// string is end
                startString = false;
            }
        }else{
            //有可能是char
            if(s=="#\\" and ch!=' '){
                s+=ch;
                len++;
            }else{
                switch (ch)
                {
                    case '\"':
                        startString = true;
                        s+=(char)ch;
                        len++;
                        break;
                    case '(':
                    case ')':
                        if(len>0)
                            ans=s;cur=len;
                        s="";
                        s=s+(char)ch;
                        len=1;
                        break;
                    default:
                        if (isspace(ch))
                        {
                            if(len>0)
                                ans=s;cur=len;
                            s="";
                            len=0;
                        }
                        else
                        {
                            s=s+(char)ch;
                            len++;
                        }
                }
            }
        }
        
    }
    if(cur>0)
    {
        res=new char[cur+2];
        for(int i=0;i<=cur-1;i++)
            res[i]=ans[i];
		res[cur]='\0';
    }
    return res;
}


//
//
//char *next_token2(){
//    
//    char* res = NULL;
//    
//    if(cur>0)
//    {
//        res=new char[cur+2];
//        for(int i=0;i<=cur-1;i++)
//            res[i]=ans[i];
//        res[cur]='\0';
//    }
//    
//    
//    
//}

#endif
