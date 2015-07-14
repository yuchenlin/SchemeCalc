#include "calc_exp.h"
#include <iostream>
#include <cstring>
#include <string>
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
