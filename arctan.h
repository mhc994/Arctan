//
// Created by 马浩程 on 15/12/29.
//

#ifndef ARCTAN_ARCTAN_H
#define ARCTAN_ARCTAN_H

#include "FPNum.h"

FPNum arctan_taylor( FPNum a);//最佳逼近(泰勒展开)计算Arctan(x)
FPNum arctan_simpson( FPNum a);//利用复化辛普森公式计算Arctan(x)
FPNum arctan_romberg( FPNum a);//利用龙贝格方法计算Arctan(x)

#endif //ARCTAN_ARCTAN_H
