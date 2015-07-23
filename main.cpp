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

int main(){
    
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

int main1(){
    complex<double> ca(1.1, 1.2);
    cout<<asin(ca)<<endl;
    cout<<"sad"<<endl;
    return 0;
}