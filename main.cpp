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


int main()
{
    char* s = "123i";
    Complex* c = Complex::from_string(s);
    c->print();
    
	return 0;
}

