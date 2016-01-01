//
// Created by 马浩程 on 15/12/24.
//

#ifndef ARCTAN_FPNUM_H
#define ARCTAN_FPNUM_H

#include <stdint.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <cstdio>

using namespace std;

class FPNum
{
private:
    int16_t *intPart,*decPart;//数据部分指针
    int intL,decL;//数据部分长度

    void normalize();//处理进位借位和符号
    void deleteZero();//删除前部的0

public:
    bool sign;//符号
    static int accuracy;//十进制小数位数

    ~FPNum()//析构函数
    {
        if(intPart)
            delete[] intPart;
    }

    FPNum();//无参构造函数,返回0
    FPNum(const char *s);//字符串构造函数
    FPNum(const string s);//由string构造
    FPNum(const int intL,const int decL);//给定长度的构造函数,返回0
//    FPNum(const int32_t v);//由整数构造

    FPNum(const FPNum &ins);//拷贝构造函数
    FPNum & operator =(const FPNum &ins);//重载=

    FPNum operator +(const FPNum &ins);//重载+
    FPNum operator -(const FPNum &ins);//重载-
    FPNum operator -(void);//重载负号
    FPNum operator *(const FPNum &ins);//重载*
    FPNum operator *(int16_t t);//重载*(整数)
    FPNum operator /(const FPNum &ins);//重载/
    FPNum operator /(const int16_t divisor);//重载/(整数)
    FPNum operator ^(const int ) const;//重载幂运算

    bool operator >(const FPNum & t);   //和另一个FPNum比较
    bool zero();//判断是否为0
    bool zeroAtAccuracy();//判断在accuracy指定的精度下是否为0

    friend ostream& operator<<(ostream&,const FPNum&);//输出
};

ostream &operator<<(ostream &out, const FPNum &b);//输出

#endif //ARCTAN_FPNUM_H
