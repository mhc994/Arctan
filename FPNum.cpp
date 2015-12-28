//
// Created by 马浩程 on 15/12/24.
//

#include "FPNum.h"

int FPNum::accuracy = 20;



FPNum::FPNum(const int intL,const int decL)
{
    sign = true;
    this->intL=intL;
    this->decL=decL;
    intPart=new int16_t[intL+decL];
    decPart=intPart+intL;
    memset(intPart,0,sizeof(int16_t)*(intL+decL));
}

FPNum::FPNum(char *s)
{
    sign = true;
    intL=1;
    decL=accuracy/4+2;

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
        decL=accuracy/4+2;

        intPart=new int16_t[intL+decL];
        decPart=intPart+intL;
        memset(intPart,0,sizeof(int16_t) * (intL+decL));

        char *decPartC=new char[decL*4];
        memset(decPartC,0, sizeof(char)*(decL*4));
        for(int i=0; i<decL*4 && i<l ;i++)
            decPartC[i]=s[i]-'0';

        for (int i=0; i<decL; i++)//小数部分
            for(int b=0;b<4;b++)
                decPart[i]=decPart[i]*10+decPartC[i*4+b];

        delete[] decPartC;
//        decPartC = 0;
    }
    else if(dotPos==-1)  //输入格式为 XXXXXX(无小数部分)
    {
        intL=(l%4)?(l/4+1):(l/4);
        decL=accuracy/4+2;

        intPart=new int16_t[intL+decL];
        decPart=intPart+intL;
        memset(intPart,0,sizeof(int16_t[intL+decL]));


        char *intPartC=new char[intL*4];
        memset(intPartC,0,sizeof(char)*(intL*4));

        for(int i=0; i<l ;i++)
            intPartC[intL*4-l+i]=s[i]-'0';

        for (int i=0; i<intL; i++)//整数部分
            for(int b=0;b<4;b++)
                intPart[i]=intPart[i]*10+intPartC[i*4+b];

        delete[] intPartC;
//        intPartC = 0;
    }
    else// 输入格式为 XXXX.XXXX
    {
        int intLC=dotPos,decLC=l-dotPos-1;
        intL = (intLC%4)?(intLC/4+1):(intLC/4);
        decL = accuracy/4+2;

        intPart=new int16_t[intL+decL];
        decPart=intPart+intL;
        memset(intPart,0,sizeof(int16_t)*(intL+decL));


        char *decPartC=new char[decL*4];
        memset(decPartC,0,sizeof(char)*(decL*4));
        for(int i=0; i<decL*4 && i<decLC ;i++)
            decPartC[i]=s[i+intLC+1]-'0';

        for (int i=0; i<decL; i++)//小数部分
            for(int b=0;b<4;b++)
                decPart[i]=decPart[i]*10+decPartC[i*4+b];

        delete[] decPartC;
//        decPartC = 0;


        char *intPartC=new char[intL*4];
        memset(intPartC,0,sizeof(char)*(intL*4));

        for(int i=0; i<intLC ;i++)
            intPartC[intL*4-intLC+i]=s[i]-'0';

        for (int i=0; i<intL; i++)//整数部分
            for(int b=0;b<4;b++)
                intPart[i]=intPart[i]*10+intPartC[i*4+b];

        delete[] intPartC;
//        intPartC = 0;
    }

    deleteZero();

}

FPNum::FPNum(const FPNum &ins)
{
    intL = ins.intL;
    decL = ins.decL;
    sign = ins.sign;

    intPart = new int16_t[intL+decL];
    decPart = intPart + intL;

    memcpy(intPart,ins.intPart, sizeof(int16_t)*(intL+decL));
}

FPNum &FPNum::operator=(const FPNum &ins)
{
    if(&ins == this)
        return *this;

    if(intPart)
        delete[] intPart;

    intL = ins.intL;
    decL = ins.decL;
    sign = ins.sign;

    intPart = new int16_t[intL+decL];
    decPart = intPart + intL;
    memcpy(intPart,ins.intPart, sizeof(int16_t)*(intL+decL));

    return *this;
}

FPNum FPNum::operator+(const FPNum &ins)
{

    FPNum sum( (intL>ins.intL?intL:ins.intL)+1 ,decL);
    int len = sum.intL+decL;
    int16_t *n1=new int16_t[2*len];
    int16_t *n2=n1+len;
    memset(n1,0, sizeof(int16_t[2*len]));

    int j=0;
    if(sign)
        for(int i = len - intL - decL ; i < len ; i++,j++)
            n1[i]=intPart[j];
    else
        for(int i = len - intL - decL ; i < len ; i++,j++)
            n1[i]=-intPart[j];

    j=0;
    if(ins.sign)
        for(int i = len - ins.intL - ins.decL ; i < len ; i++,j++)
            n2[i]=ins.intPart[j];
    else
        for(int i = len - ins.intL - ins.decL ; i < len ; i++,j++)
            n2[i]=-ins.intPart[j];

    for(int i=0;i<len;i++)
    {
        sum.intPart[i] = n1[i]+n2[i];
    }

    delete[] n1;

    sum.normalize();
    sum.deleteZero();
    return sum;
}

FPNum FPNum::operator-(const FPNum &ins)
{
    FPNum sum( (intL>ins.intL?intL:ins.intL)+1 ,decL);
    int len = sum.intL+decL;
    int32_t *n1=new int32_t[2*len];
    int32_t *n2=n1+len;
    memset(n1,0, sizeof(int32_t[2*len]));

    int j=0;
    if(sign)
        for(int i = len - intL - decL ; i < len ; i++,j++)
            n1[i]=intPart[j];
    else
        for(int i = len - intL - decL ; i < len ; i++,j++)
            n1[i]=-intPart[j];

    j=0;
    if(!ins.sign)
        for(int i = len - ins.intL - ins.decL ; i < len ; i++,j++)
            n2[i]=ins.intPart[j];
    else
        for(int i = len - ins.intL - ins.decL ; i < len ; i++,j++)
            n2[i]=-ins.intPart[j];

    for(int i=0;i<len;i++)
    {
        sum.intPart[i] = n1[i]+n2[i];
    }

    delete[] n1;

    sum.normalize();
    sum.deleteZero();
    return sum;
}

FPNum FPNum::operator*(const FPNum &ins)
{
    int l1=intL+decL,l2=ins.intL+ins.decL;
    int lpro=l1+l2;

    int16_t *pro=new int16_t[lpro];
    memset(pro,0,sizeof(int16_t)*lpro);

    for(int i=l1-1;i>=0;i--)
        for(int j=l2-1;j>=0;j--)
        {
            int32_t proB=intPart[i]*(int32_t)ins.intPart[j];

            pro[i+j]+=(int16_t)(proB/10000);
            pro[i+j+1]+=(int16_t)(proB%10000);

            while(pro[i + j + 1] > 9999)
            {//todo / and %
                pro[i+j+1] -= 10000;
                pro[i+j]++;
            }
            while(pro[i + j] > 9999)
            {
                pro[i+j] -= 10000;
                pro[i+j-1]++;
            }
        }

    int zeroNum=0,proDecL=decL+ins.decL,proIntL=lpro-proDecL;

    while( 0==(pro[zeroNum]) && (zeroNum+1)<proIntL )
    {
        zeroNum++;
    }
    int resIntL=proIntL-zeroNum,resDecL=decL;
    FPNum res(resIntL,resDecL);
    memcpy(res.intPart,pro+zeroNum,sizeof(int16_t)*(resIntL+resDecL));
    res.sign=!(sign^ins.sign);

    delete[] pro;

    return res;
}


FPNum FPNum::operator /(const int16_t divisor)
{
    if(divisor==0)
    {
        throw "除零错@FPNum::operator /(const int32_t divisor)";
    }

    FPNum q(intL,decL);
    int64_t div=divisor,res=0;

    if(divisor>0)
        q.sign=sign;
    else
    {
        q.sign = !sign;
        div = -divisor;
    }

    for(int i=0;i<intL+decL;i++)
    {
        res = res * 10000 + intPart[i];
        q.intPart[i]=(int16_t)(res/div);
        res=res%div;
    }

    q.deleteZero();

    return q;
}


FPNum FPNum::operator/(const FPNum &divisor)
{
    //处理除数
    int divisorZeroNum=0,divisorL=divisor.intL+divisor.decL;
    while (divisor.intPart[divisorZeroNum]==0 && divisorZeroNum<divisorL)
        divisorZeroNum++;
    int ld=divisorL-divisorZeroNum;
    if(ld==0)
        throw "除零错@FPNum::operator/(const FPNum &divisor)";
    if(ld==1)
        return *this/divisor.intPart[divisorL];

    int16_t *div=new int16_t[ld];
    memcpy(div,divisor.intPart+divisorZeroNum,sizeof(int16_t)*ld);


    //处理被除数
    deleteZero();
    int ls=intL+decL+decL;
    int16_t *s=new int16_t[ls];
    memset(s,0, sizeof(int16_t)*ls);
    memcpy(s,intPart, sizeof(int16_t)*(intL+decL));

    //为商分配内存
    FPNum q(intL+decL-ld+1,decL);
    int lq=q.intL+q.decL;
    q.sign=!(sign^divisor.sign);

    //为每一步的余数分配内存并赋初值
    int32_t *res=new int32_t[ld+1];
    res[0]=0;res[1]=0;
    for (int i = 2; i < ld+1; i++)//初值
        res[i] = s[i-2];

    //除法计算
    for(int i=0;i<lq;i++)
    {
        for(int j=0;j<ld;j++)
            res[j]=res[j+1];
        res[ld]=s[ld+i-1];

        q.intPart[i]=(int16_t) ((res[0]*(int64_t)100000000+res[1]*(int64_t)10000+res[2])/(div[0]*(int64_t)10000+div[1]));

        for(int j=ld-1;j>=0;j--)
        {
            res[j+1] -= (div[j] * (int32_t)q.intPart[i])%10000;
            res[j] -= (div[j] * (int32_t)q.intPart[i])/10000;
            while(res[j+1]<0)
            {
                res[j+1] += 10000;
                res[j]--;
            }
        }

        while(res[0]<0)
        {
            q.intPart[i]--;
            for(int j=ld;j>=0;j--)
            {
                res[j+1] += div[j];
                if(res[j+1]>=10000)
                {
                    res[j+1]-=10000;
                    res[j]++;
                }
            }
        }

    }

    delete[] div;
    delete[] res;
    delete[] s;

    if(q.intL==0)
    {
        int16_t *newData=new int16_t[lq+1];
        memcpy(newData+1,q.intPart,sizeof(int16_t)*ld);
        newData[0]=0;

        delete[] q.intPart;
        q.intPart=newData;
        q.intL=1;
        q.decPart=q.intPart+q.decL;
    }

    return q;
}



//FPNum FPNum::operator^(const int t)
//{
//    return FPNum();
//}
//
//bool FPNum::operator>(const int &t) const
//{
//    return false;
//}
//
ostream &operator<<(ostream &out, const FPNum &b) //重载输出运算符
{
    out<<(b.sign?' ':'-');
    int i;
    for(i=0;i<b.intL;i++)
        out<<' '<<setfill('0')<<setw(4)<<b.intPart[i];
    out<<'.';
    for(int j=0;j<b.decL;j++)
        out<<setfill('0')<<setw(4)<<b.decPart[j]<<' ';
    return out;
}

void FPNum::normalize()
{
    for(int i=intL+decL-1;i>0;i--)
    {//todo / & %
        while(intPart[i]<0)
        {
            intPart[i-1]--;
            intPart[i]+=10000;
        }
        while(intPart[i]>=10000)
        {
            intPart[i-1]++;
            intPart[i]-=10000;
        }
    }
    if(intPart[0]<0)
    {
        sign = !sign;
        for (int i = intL+decL-1; i >= 0; i--)
            intPart[i] = -intPart[i];
        normalize();
    }
}

void FPNum::deleteZero()
{
    if(intL<2)
        return;

    int16_t *old=intPart,*data=intPart,zeroNum=0;
    while( 0==(*data) && data<(decPart-1) )
    {
        data++;
        zeroNum++;
    }

    if(zeroNum==0)
        return;

    intL -= zeroNum;
    intPart = new int16_t[intL+decL];
    decPart = intPart+intL;
    memcpy(intPart,data,sizeof(int16_t)*(intL+decL));
    delete[] old;
}
