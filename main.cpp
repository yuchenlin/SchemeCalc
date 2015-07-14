#include "calc_exp.h"
#include <iostream>
using namespace std;

int main(){
    
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

int main1(){
    LongInt a = (string)"524134";
    LongInt b = (string)"123";
//    int a = -524134;
//    int b = -123;
    cout<<a%b<<endl;
    return 0;
}