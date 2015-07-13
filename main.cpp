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