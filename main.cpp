#include "calc_exp.h"
#include <iostream>
using namespace std;

int main() {
    
    try {
        Number *res;
		for (Number *res;;) {
			res = calc_exp();
            cout<<"Ans:\t";
			res -> print();
            cout<<endl;
		}
	}
	catch(int){cerr<<"Wrong";}
	//system("pause");
    return 0;
}

int main1(){
    LongInt a = (string)"123412347892134798023174";
    LongInt b = (string)"231432423142314";
    cout<<a/b<<endl;
    return 0;
}