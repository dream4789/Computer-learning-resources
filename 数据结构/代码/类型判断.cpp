//
// Created by xulon on 2023/6/26.
//
#include "stdio.h"

#define DETECTION(X) {(X-(float)X)?printf("%lf:float\n", X):printf("%ld:int\n",X);}

int main()
{
    DETECTION(1);
    DETECTION(1.1);
    DETECTION(12121212);
    DETECTION(480000.1);
    DETECTION(112132);
    DETECTION(999999999);
    return 0;
}