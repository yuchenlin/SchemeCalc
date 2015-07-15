#include "long_int.h"
#include <cassert>
#include <cstdio>
#include <istream>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;

//通过一个小于等于longlong的数来构造vector
LongInt::LongInt(long long number) {//默认调用0
    //直接调用赋值的重载即可
    *this = number;
}

//复制构造函数
LongInt::LongInt(const LongInt& obj){
    *this = obj;
}


//析构函数
LongInt::~LongInt(){
    //vector没什么需要特地析构的
}

LongInt::LongInt(const string& str) {
    *this = str;
}


LongInt max(const LongInt &a, const LongInt &b){
    LongInt result(MAX(a, b));
    return result;
}
LongInt min(const LongInt &a, const LongInt &b){
    LongInt result(MIN(a,b));
    return result;
}
//取绝对值
LongInt LongInt::getABS() const{
    if(*this >= 0)
        return *this;
    else
        return getOpposite();
}
//取相反数
LongInt LongInt::getOpposite() const{
    LongInt res = *this;
    res.n.back() = -(res.n.back());
    return res;
}


//各个赋值方法
LongInt& LongInt::operator= (long long obj){
    n.clear();
    do{
        n.push_back(obj % _base);
        obj /= _base;
    }while(obj!=0);
    //除去前位0
    while (n.back()==0 and n.size()>1)
        n.pop_back();
    return *this;
}

//最重要的就是这个 从string来赋值
//LongInt的赋值 String构造函数 非常重要 很多错误来自于此

LongInt& LongInt::operator= (const string& obj){
    n.clear();
    int t=0;
    //通过字符串长度确定循环次数
    //负号占了一个长度
    bool isNegative = obj[0]=='-';
    bool havePosi = obj[0]=='+';
    unsigned long len = (isNegative or havePosi) ?
                            (obj.length() - 2) / _width +  1 : (obj.length() - 1) / _width +  1;
    //循环次数
    for (int i=0; i < len; ++i) {
        int tail = obj.length() - i * _width;
        int begin = max(0, tail - _width);
        //读取一段出来
        //cout<<obj.substr(begin,tail - begin).c_str()<<endl;
        sscanf(obj.substr(begin,tail - begin).c_str(), "%d" , &t);
        n.push_back(t);
    }
    //除去前位0
    while (n.back()==0 and n.size()>1)
        n.pop_back();
    //如果就是0 则补回一个
    if(isNegative){
        removeSign();
        changeSign();
        
    }
    return *this;
}
LongInt& LongInt::operator= (const LongInt& obj){
    n.clear();//首先清空所有的vector中元素
    for (int i = 0 ; i < obj.n.size(); ++i)
        n.push_back(obj.n[i]);
    return *this;
}

//各种算法运算符
LongInt LongInt::operator + (const LongInt& obj) const{
    LongInt res;
    res.n.clear();
    int len = n.size(), obj_len = obj.n.size();
    if (*this>=0 and obj>=0)
    {
        for (int i=0, r=0; ; ++i)
        {
            if (r == 0 and i >= len and i >= obj_len) //youhua
                break;
            int t = r;//buyouhua
            if (i < len)
                t += n[i];
            if (i < obj_len)
                t += obj.n[i];
            res.n.push_back(t); //youhua
            
//            res.n.push_back(t % _base);//buyouhua
//            r = t / _base;//buyouhua
        }
        res.mode(); //youhua
        return res;
    }
    if (*this<0 && obj<0)
    {
        
        LongInt c = this->getABS() + obj.getABS();
        return c.getOpposite();
    }
    if (*this<0 && obj>=0)
    {
        return (obj-this->getABS());
    }
    if (*this>=0 && obj<0)
    {
        return (*this-obj.getABS());
    }
    return *this;
    
}
LongInt LongInt::operator - (const LongInt& obj) const{
    LongInt res;
    res.n.clear();
    int len = n.size(), obj_len = obj.n.size();
    
    
    if (*this>=0 && obj>=0)
    {
        if (*this >= obj)
        {
            //优化开始
            res = *this;
            for(int i = 0 ; i < obj.n.size() ; ++i)
                res.n[i] -= obj.n[i];
            res.mode();
            //优化结束
        }
        
        else
        {
            LongInt d = obj-*this;
            d.changeSign();
            return d;
        }
    }
    //其他情况通过递归
    if (*this >= 0 && obj < 0)
    {
        return *this+obj.getABS();
    }
    if (*this < 0 and obj >= 0)
    {
        LongInt d = this->getABS() + obj;
        d.changeSign();
        return d;
    }
    if (*this < 0 and obj < 0 )
    {
        return obj.getABS() - this->getABS();
    }
    //为了防止编译错误
	return res;
}
LongInt LongInt::operator * (const LongInt& obj) const{
    //乘法的处理 也要考虑不同的符号
    
    
    LongInt result;
    result.n.clear();
    result = 0;
    
    LongInt a = this->getABS();
    LongInt b = obj.getABS();

    bool negative = (*this<0 and obj>0) or ( *this>0 and obj<0);
    
    
    if (*this==0 or obj==0)
        return 0;
    int memory[100][100]={0};
    bool haveMem[100][100]={0};
    
    LongInt midRes;//临时中间变量
    for (int i=0;i < obj.n.size();++i)
    {
        
        midRes.n.clear();
        if (i)//如果i大于0
            for (int j=1;j<=i;++j)
                midRes.n.push_back(0);
        int r = 0;//中间余数
        for (int j = 0; ; ++j)
        {
            if (r == 0 and j >= n.size() )
                break;
            else{
                int t = r;
                if (j < n.size()){
                    if(!haveMem[a.n[j]][b.n[i]]){
                        haveMem[a.n[j]][b.n[i]] = true;
                        haveMem[b.n[i]][a.n[j]] = true;
                        memory[a.n[j]][b.n[i]] = a.n[j] * b.n[i];
                        memory[b.n[i]][a.n[j]] = a.n[j] * b.n[i];
                    }
                    t += memory[a.n[j]][b.n[i]];
                    //t += a.n[j] * b.n[i];
                }
                midRes.n.push_back(t % _base);
                r = t / _base;
            }
        }
        result += midRes;
    }
    
    if(negative)
        result.changeSign();
    return result;
}

////优化开始
//LongInt LongInt::operator * (int b){
//    LongInt res = *this;
//    for (int i=0; i<n.size(); ++i) {
//        res.n[i] *= b;
//    }
//    res.mode();
//    return res;
//}
////优化结束


//各种关系运算符
bool LongInt::operator < (const LongInt &obj) const{
    if(n.back()<0 and obj.n.back()>=0)
        return true;
    else if(n.back() >=0 and obj.n.back() <0)
        return false;
    else if(n.back() < 0 and obj.n.back() < 0 ){
        return !(this->getABS() <= obj.getABS());//递归
    }
    else if(n.back() >= 0 and obj.n.back() >=0){
       if(n.size() != obj.n.size())
           return n.size() < obj.n.size();
        for (int k = n.size() -1 ; k>=0; --k) {
            if( n[k] != obj.n[k] )
                return n[k] < obj.n[k];
        }
        return false;
    }
    return false;
}
//通过<来实现各种比较函数
bool LongInt::operator > (const LongInt &obj) const{
    return obj < (*this);
}
bool LongInt::operator <= (const LongInt &obj) const{
    return !((*this) > obj);
}
bool LongInt::operator >= (const LongInt &obj) const{
    return !((*this) < obj);
}
bool LongInt::operator == (const LongInt &obj) const{
    return !((*this)>obj or (*this)<obj);
}
bool LongInt::operator != (const LongInt &obj) const{
    return !((*this)==obj);
}
//demo的很多地方用!加一个LongInt类来判断非空
bool LongInt::operator ! () const{
    //!a 如果a是0 则返回true
    return *this == 0 ;
}
//二分探商优化 效率比短除法大大提高...



LongInt LongInt::operator / (const LongInt &obj) const{
    assert(obj!=0 && "devide zero");
    
    bool negative = (*this<0 and obj>0) or (*this>0 and obj<0);
    
    LongInt a = this->getABS() , b = obj.getABS();
    //两类特殊情况
    if(a < b)
        return 0;
    if(a == b)
        return negative ? -1 : 1;
    //cout<<a<<endl;
    //cout<<b<<endl;
    LongInt ans=a,res=0;
    int i,left,right,mid;
    //尝试除法不要mode?
    LongInt memory[100];
    bool haveMem[100] = {0};
    for( i = a.n.size()-1; i>=0; --i)
    {
        //大数乘_base 要优化 直接移位
        res.n.insert(res.n.begin(), 0);
        res += a.n[i];
        
        left=0 , right = _base-1;
        while(left<right)
        {
            mid = (left+right+1) >> 1;
            if(!haveMem[mid]){
                haveMem[mid] = true;
                memory[mid] = b * mid;
            }
            //if( b * mid > res)
            if (memory[mid] > res)
                right = mid-1;
            else
                left = mid;
        }
        ans.n[i]=left;
        
        if(!haveMem[left]){
            haveMem[left] = true;
            memory[left] = b * left;
        }
        
        res -= memory[left];
        
    }
    //cout<<res<<endl;
    ans.mode();
    if(negative)
        ans.changeSign();
    return ans;
}

//取余数 不考虑效率的做法....
LongInt LongInt::operator % (const LongInt &obj) const{
    
    assert(obj!=0 && "devide zero");
    
    bool negative = (*this < 0);
    LongInt a = this->getABS() , b = obj.getABS();
    //两类特殊情况
    if(a <= b)
        return 0;
    //cout<<a<<endl;
    //cout<<b<<endl;
    LongInt ans=a,res=0;
    int i,left,right,mid;
    //尝试除法不要mode?
    LongInt memory[100];
    bool haveMem[100] = {0};
    for( i = a.n.size()-1; i>=0; --i)
    {
        //大数乘_base 要优化 直接移位
        res.n.insert(res.n.begin(), 0);
        res += a.n[i];
        
        left=0 , right = _base-1;
        while(left<right)
        {
            mid = (left+right+1) >> 1;
            if(!haveMem[mid]){
                haveMem[mid] = true;
                memory[mid] = b * mid;
            }
            //if( b * mid > res)
            if (memory[mid] > res)
                right = mid-1;
            else
                left = mid;
        }
        if(!haveMem[left]){
            haveMem[left] = true;
            memory[left] = b * left;
        }
        
        res -= memory[left];
        
    }
    if(negative)
        res.changeSign();
    return res;
}

void LongInt::changeSign(){
    n.back() = -(n.back());
}
void LongInt::removeSign(){
    if(n.back()<0)
        n.back() = -(n.back());
}
void LongInt::mode()
{
    n.push_back(0);
    for(int i=0;i<n.size();++i)
    {
        for(;n[i]<0; --n[i+1],n[i] += _base);
        for(;n[i]>=_base; ++n[i+1],n[i] -= _base);
    }
    
    while (n.back()==0 and n.size()>1)
        n.pop_back();
}


double LongInt::getDouble(){
    bool negative = n.back() < 0;
    removeSign();
    
    double res = 0;
    
    for (int i = n.size()-1; i >=0; --i) {
        res = res * _base + n[i];
    }
    return negative ?  -res : res;
}

LongInt& LongInt::operator += (const LongInt& obj){
    if(obj<0 or *this<0){
        *this = *this + obj;
        return *this;
    }
    
    int len = max(n.size(), obj.n.size());
    int this_size = n.size();
    for (int k = 0; k < len - this_size; ++k) {
        n.push_back(0);
    }
    for (int i = 0; i< len; ++i) {
        if(i < obj.n.size() )
            n[i] += obj.n[i];
    }
    mode();
    return *this;
}

LongInt& LongInt::operator -= (const LongInt& obj){
    if(*this > obj and obj > 0){
        for (int i = 0; i< obj.n.size(); ++i) {
                n[i] -= obj.n[i];
        }
        mode();
    }else
        *this = *this - obj;
    return *this;
}

