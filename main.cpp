#include "calc_exp.h"
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

int main1(){
    
    try {
        Base *res;
//        for(;;){
            res = calc_exp();
            res -> print();
            cout<<endl;
//        }
	}
	catch(int){cerr<<"Wrong";}
    return 0;
}

int main(){
    Boolean b(true);
    b.print();
}