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

FPNum arctan_simpson(FPNum a)
{
;
}

FPNum arctan_romberg(FPNum a)
{
;
}
