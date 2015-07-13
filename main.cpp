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
    LongInt a = (string)"12345678989012312313";
    LongInt b = (string)"231402780973409871324803721094709231";
    b-=a;
    cout<<b<<endl;
    return 0;
}