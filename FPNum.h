//
// Created by 马浩程 on 15/12/24.
//

#ifndef ARCTAN_FPNUM_H
#define ARCTAN_FPNUM_H


#include <sys/_types/_int32_t.h>
#include <iostream>
#include <iomanip>

using namespace std;

class FPNum
{
    static int accuracy;
private:
    int32_t *intPart,*decPart;
    int intL,decL;
    bool sign;


public:
    FPNum()
    {
        sign = true;
        intL=1;
        decL=accuracy/9+1;
        intPart=new int32_t[intL+decL];
        decPart=intPart+intL;
        memset(intPart,0,(intL+decL)*4);
    }


    ~FPNum()
    {
        if(intPart)
            delete[] intPart;
    }

    void normalize();

    

    FPNum(char *s);
    FPNum(const FPNum &ins);
    FPNum & operator =(const FPNum &ins);
    FPNum operator +(const FPNum &ins);
    FPNum operator -(const FPNum &ins);
    FPNum operator *(const FPNum &ins);
    FPNum operator /(const FPNum &ins);
    FPNum operator ^(const FPNum &ins);

//    bool operator>(const FPNum & T)const;   //大数和另一个大数的大小比较
    bool operator>(const int & t)const;      //大数和一个int类型的变量的大小比较

//    BigNum(const int);       //将一个int类型的变量转化为大数


    friend ostream& operator<<(ostream&,const FPNum&);
//    friend istream& operator>>(istream&,FPNum&);


};


#endif //ARCTAN_FPNUM_H
