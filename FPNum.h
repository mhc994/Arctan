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
    int16_t *intPart,*decPart;
    int intL,decL;


    void normalize();
    void deleteZero();

//    FPNum(const FPNum &rhs);
//    FPNum &operator=(const FPNum &rhs);

public:
    bool sign;

    FPNum()
    {
        sign = true;
        intL=1;
        decL=accuracy/4+2;
        intPart=new int16_t[intL+decL];
        decPart=intPart+intL;
        memset(intPart,0,sizeof(int16_t[intL+decL]));
    }

    ~FPNum()
    {
        if(intPart)
            delete[] intPart;
    }

    FPNum(const char *s);
    FPNum(const string s);
    FPNum(const int intL,const int decL);
    FPNum(const FPNum &ins);
    FPNum(const int32_t v);
    FPNum & operator =(const FPNum &ins);
    FPNum operator +(const FPNum &ins);
    FPNum operator -(const FPNum &ins);
    FPNum operator -(void);
    FPNum operator *(const FPNum &ins);
    FPNum operator *(int16_t t);
    FPNum operator /(const FPNum &ins);
    FPNum operator /(const int16_t divisor);
    FPNum operator ^(const int ) const;


    bool operator >(const FPNum & t);   //和另一个FPNum比较
    bool zero();
//    bool operator >(FPNum int & t)const;      //大数和一个int类型的变量的大小比较

    friend ostream& operator<<(ostream&,const FPNum&);
//    friend istream& operator>>(istream&,FPNum&);

};

ostream &operator<<(ostream &out, const FPNum &b);

#endif //ARCTAN_FPNUM_H
