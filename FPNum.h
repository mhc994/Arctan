//
// Created by 马浩程 on 15/12/24.
//

#ifndef ARCTAN_FPNUM_H
#define ARCTAN_FPNUM_H


#include <sys/_types/_int32_t.h>


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
    }


    ~FPNum()
    {
        if(intPart)
            delete[] intPart;
    }

};


#endif //ARCTAN_FPNUM_H
