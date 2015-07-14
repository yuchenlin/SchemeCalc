#include "calc_exp.h"
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

int main1(){
    
    try {
        Number *res;
		for (Number *res;;) {
			res = calc_exp();
			res -> print();
            cout<<endl;
		}
	}
	catch(int){cerr<<"Wrong";}
	//system("pause");
    return 0;
}

int main(){
    char* str = "0.0-123123213213213i";
//    string s = expression;
    Complex* c;
    c = Complex::from_string(str);
    c->print();
    if(c->isExact)
        cout<<"\nexact"<<endl;
    return 0;
}