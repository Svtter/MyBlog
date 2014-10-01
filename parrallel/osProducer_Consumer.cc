/*=============================================================================
#
# Author: svtter - svtter@qq.com
#
# QQ : 57180160
#
# Last modified: 2014-10-01 17:51
#
# Filename: osProducer_Consumer.cc
#
# Description: 
#       利用omp并行计算实现同步
#
=============================================================================*/
#include <iostream>
#include <queue>
#include "omp.h"


using namespace std;

#define NUM_THREADS 1
#define semaphore int
#define item int
#define N 4

semaphore mutex=1, empty=N, full=0;
item buffer[N];
int i=0, j=0;


void wakeup()
{
}

void block()
{


// 设定P，V为不可中断的操作，以此来模拟

void P(semaphore &S)
{
    S--;
    if (S)
        block();
}

void V(semaphore S)
{
    S++;
    if (S <= 0)
        wakeup();
}
    



void Producer()
{
    //protice next product
    int product = i;
    P(empty);
    P(mutex);
    buffer[i] = product;
    i=(i+1)%N;
    V(mutex);
    V(full);
}

int main()
{
    omp_set_num_threads(NUM_THREADS);
    return 0;
}
    
