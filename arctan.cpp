//
// Created by 马浩程 on 15/12/29.
//

#include "arctan.h"

using namespace std;

FPNum arctan_taylor(FPNum a)//最佳逼近(泰勒展开)计算Arctan(x)
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
    //return s;
}

FPNum derivate(FPNum a)
{
    FPNum one("1");
    return one/(one+a*a);
}

FPNum arctan_simpson( FPNum a)//利用复化辛普森公式计算Arctan(x)
{
    if(!a.sign)
        return -arctan_simpson(-a);
    if(a>FPNum("1.1"))
        return ( arctan_simpson(".2")*(int16_t)8 - arctan_simpson(FPNum("1")/(int16_t)239)*(int16_t)2 - arctan_simpson(FPNum("1")/a) );

    FPNum result("0");
    int n = (int)pow(10,(FPNum::accuracy-4)/4);
    for (int16_t i = 0; i < n; i++)
        result = result + derivate(a*i/n) + derivate(a*(2*i+1)/2/n)*4 + derivate(a*(i+1)/n);

    return result*a/n/6;
}

FPNum arctan_romberg( FPNum a)//利用龙贝格方法计算Arctan(x)
{//todo end condition
    if(!a.sign)
        return -arctan_romberg(-a);
    if(a>FPNum("1.1"))
        return ( arctan_romberg(".2")*(int16_t)8 - arctan_romberg(FPNum("1")/(int16_t)239)*(int16_t)2 - arctan_romberg(FPNum("1")/a) );

    typedef FPNum* pNum;

    int imax=a.accuracy*2;//根据递推公式,步数大于该值时,受限于FPNum类的截断误差,龙贝格方法数值已不再改变,因此算法必在此之前已结束
    int imin=a.accuracy/5;
    if(imin<10)
        imin =10;

    pNum *tList=new pNum[imax*imax];//T表,实际利用率较低,但考虑到mmax不会太大,因此不作改进
    pNum *m2=new pNum[imax];

    int i ;
    for ( i = 0; i < imax-1; i++)
    {
        FPNum result("0"),one("1"),two("2");

        m2[i] = new FPNum( (i==0) ? one : (*m2[i-1]*(int16_t)2) );

        //构造第一列
        for (FPNum j("0"); *m2[i] > j; j=j+one)
            result = result + derivate(a * j / *m2[i]) + derivate(a * (j + one) / *m2[i]);
        tList[0*imax+i]=new FPNum((result * a / 2) / (*m2[i])) ;

        //构造其他列
        for(int j=1; j<=i;j++)
        {
            FPNum m4 = (*m2[j])*(*m2[j]);
            tList[(j)*imax+(i-j)] = new FPNum( ( *tList[(j-1)*imax+(i-j+1)] * m4 - *tList[(j-1)*imax+(i-j)] ) / (m4-one) );
        }

        if(i>imin)
            if( (*tList[(i)*imax+0] - *tList[(i-1)*imax+1] ).zeroAtAccuracy())//判断精度是否足够
            {
                i++;
                break;
            }

    }

    FPNum r(*tList[(i-2)*imax+1]);

    for(int j=0;j<i;j++)
        for(int k=0;k<i-j;k++)
            delete tList[j*imax+k];
    delete[] tList;

    return r;

}
