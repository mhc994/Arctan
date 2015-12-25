//
// Created by 马浩程 on 15/12/24.
//

#include "FPNum.h"

int FPNum::accuracy = 20;

//void FPNum::normalize()
//{
//
//}
//
FPNum::FPNum(char *s)
{
    sign = true;
    intL=1;
    decL=accuracy/9+1;
    intPart=new int32_t[intL+decL];

    while(*s==' ')//跳过开头的空格
        s++;

    int l=(int)strlen(s);

    if(l==0)
        throw "输入为空.";

    if(s[0]=='+'||s[0]=='-')//如果有符号则处理符号
    {
        sign=(s[0]=='+');
        s++;l--;
        if(!l)
            throw "输入为空.";
    }
    else
        sign=true;

    int dotPos=-1;
    for(int i=0;i<l;i++)//检查小数点数量和位置
    {
        if(s[i]<'0'||s[i]>'9')
        {
            if(s[i]=='.'&&dotPos==-1)
                dotPos=i;
            else
                throw "输入格式不正确,请输入形如123.456的数字.";
        }
    }

    if(dotPos==0)  //输入格式为 .XXXXX(无整数部分)
    {
        if(l<2)
            throw "输入格式不正确,请输入形如123.456的数字.";

        s++;l--;

        intL=1;
        decL=accuracy/9+1;

        intPart=new int32_t[intL+decL];
        decPart=intPart+intL;
        memset(intPart,0,(intL+decL)*4);

        char *decPartC=new char[decL*9];
        memset(decPartC,0,decL*9);
        for(int i=0; i<decL*9 && i<l ;i++)
            decPartC[i]=s[i]-'0';

        for (int i=0; i<decL; i++)//小数部分
            for(int b=0;b<9;b++)
                decPart[i]=decPart[i]*10+decPartC[i*9+b];

        delete[] decPartC;
    }
    else if(dotPos==-1)  //输入格式为 XXXXXX(无小数部分)
    {
        intL=(l%9)?(l/9+1):(l/9);
        decL=accuracy/9+1;

        intPart=new int32_t[intL+decL];
        decPart=intPart+intL;
        memset(intPart,0,(intL+decL)*4);


        char *intPartC=new char[intL*9];
        memset(intPartC,0,intL*9);

        for(int i=0; i<l ;i++)
            intPartC[intL*9-l+i]=s[i]-'0';

        for (int i=0; i<intL; i++)//整数部分
            for(int b=0;b<9;b++)
                intPart[i]=intPart[i]*10+intPartC[i*9+b];

        delete[] intPartC;
    }
    else// 输入格式为 XXXX.XXXX
    {
        int intLC=dotPos,decLC=l-dotPos-1;
        intL = (intLC%9)?(intLC/9+1):(intLC/9);
        decL = accuracy/9+1;

        intPart=new int32_t[intL+decL];
        decPart=intPart+intL;
        memset(intPart,0,(intL+decL)*4);


        char *decPartC=new char[decL*9];
        memset(decPartC,0,decL*9);
        for(int i=0; i<decL*9 && i<decLC ;i++)
            decPartC[i]=s[i+intLC+1]-'0';

        for (int i=0; i<decL; i++)//小数部分
            for(int b=0;b<9;b++)
                decPart[i]=decPart[i]*10+decPartC[i*9+b];

        delete[] decPartC;


        char *intPartC=new char[intL*9];
        memset(intPartC,0,intLC*9);

        for(int i=0; i<intLC ;i++)
            intPartC[intL*9-intLC+i]=s[i]-'0';

        for (int i=0; i<intL; i++)//整数部分
            for(int b=0;b<9;b++)
                intPart[i]=intPart[i]*10+intPartC[i*9+b];

        delete[] intPartC;


    }

}

//FPNum::FPNum(const FPNum &ins)
//{
//
//}
//
//FPNum &FPNum::operator=(const FPNum &ins)
//{
//    return <#initializer#>;
//}
//
//FPNum FPNum::operator+(const FPNum &ins)
//{
//    return FPNum();
//}
//
//FPNum FPNum::operator-(const FPNum &ins)
//{
//    return FPNum();
//}
//
//FPNum FPNum::operator*(const FPNum &ins)
//{
//    return FPNum();
//}
//
//FPNum FPNum::operator/(const FPNum &ins)
//{
//    return FPNum();
//}
//
//FPNum FPNum::operator^(const FPNum &ins)
//{
//    return FPNum();
//}
//
//bool FPNum::operator>(const int &t) const
//{
//    return false;
//}
//
ostream &operator<<(ostream &out, const FPNum &b)
{
      //重载输出运算符

    out<<(b.sign?' ':'-');
    int i;
    for(i=0;i<b.intL;i++)
        out<<' '<<setfill('0')<<setw(9)<<b.intPart[i];
    out<<'.';
    for(int j=0;j<b.decL;j++)
        out<<setfill('0')<<setw(9)<<b.decPart[j]<<' ';
    return out;
}
