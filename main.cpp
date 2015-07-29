#include "calc_exp.h"
#include "boolean.h"
#include "string_.h"
#include "char_.h"
#include <iostream>
#include <cstring>
#include <string>
#include <complex>
#include <cmath>
using namespace std;

int main1(){
    
    try {
        Base *res;
        for(;;){
            res = calc_exp();
            res -> print();
            cout<<endl;
        }
	}
	catch(int){cerr<<"Wrong";}
    return 0;
}

int main(){
    
    cout<<String::getLower("ADss_zxcADDD00,123,,")<<endl;
    return 0;
}

