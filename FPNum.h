//
// Created by 马浩程 on 15/12/24.
//

#ifndef ARCTAN_FPNUM_H
#define ARCTAN_FPNUM_H

#include <stdint.h>
#include <iostream>
#include <iomanip>

using namespace std;

class FPNum
{
private:
    int16_t *intPart,*decPart;
    int intL,decL;
    void normalize();
    void deleteZero();

public:
    bool sign;
    static int accuracy;

    ~FPNum()
    {
        if(intPart)
            delete[] intPart;
    }

    FPNum();
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

    friend ostream& operator<<(ostream&,const FPNum&);
};

ostream &operator<<(ostream &out, const FPNum &b);

#endif //ARCTAN_FPNUM_H
