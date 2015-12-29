//
// Created by 马浩程 on 15/12/29.
//

#include "arctan.h"


FPNum arctan_taylor(FPNum a)
{
    if(!a.sign)
        return -arctan_taylor(-a);
    if(a>FPNum("1.1"))
        return ( arctan_taylor(".2")*(int16_t)8 - arctan_taylor(FPNum("1")/(int16_t)239)*(int16_t)2 - arctan_taylor(FPNum("1")/a) );
    if(a>FPNum(".41"))
        return arctan_taylor(FPNum("0.4"))+arctan_taylor((a-FPNum(".4"))/(FPNum("1")+FPNum(".4")*a));

    FPNum s(a),ni(a);
    for(int16_t i=1; 1;i++)
    {
        ni= -ni*a*a*(2*i-1)/(2*i+1);
        s=s+ni;
        if(ni.zero())
            return s;
    }
    return s;
}

FPNum derivate(FPNum a)
{
    FPNum one("1");
    return one/(one+a*a);
}

FPNum arctan_simpson( FPNum a)
{//todo end condition
    if(!a.sign)
        return -arctan_simpson(-a);
    if(a>FPNum("1.1"))
        return ( arctan_simpson(".2")*(int16_t)8 - arctan_simpson(FPNum("1")/(int16_t)239)*(int16_t)2 - arctan_simpson(FPNum("1")/a) );

    FPNum result("0");
    int n = 10000;
    for (int16_t i = 0; i < n; i++)
        result = result + derivate(a*i/n) + derivate(a*(2*i+1)/2/n)*4 + derivate(a*(i+1)/n);

    return result*a/n/6;
}

FPNum arctan_romberg( FPNum a)
{//todo end condition
    if(!a.sign)
        return -arctan_romberg(-a);
    if(a>FPNum("1.1"))
        return ( arctan_romberg(".2")*(int16_t)8 - arctan_romberg(FPNum("1")/(int16_t)239)*(int16_t)2 - arctan_romberg(FPNum("1")/a) );

    FPNum results[10][10];


    for (int i = 0; i < 10; i++)
    {
        FPNum result("0");
        int n = (int16_t)pow(2,i);

        for (int16_t j = 0; j < n; j++)
            result = result + derivate(a * j / n) + derivate(a * (j + 1) / n);
        results[0][i]=(result * a /(2*n));
    }
    for (int i = 9; i > 0; i--)
    {
        int32_t n = (int32_t)pow(4, 10-i);

        for(int j=0; j<i;j++)
            results[10-i][j]=(results[9-i][j+1]*n-results[9-i][j])/(n-1);
    }
    return results[9][0];
}
