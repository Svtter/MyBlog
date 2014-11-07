linux下的同步和互斥
===

tags: `Linux` `sync_mutex`

Semaphore.h
---

[一份好文档，胜读十年书](www.cplusplus.com/reference/)

本文参考了诸多资料，百度百科，cplusplus等


首先介绍一个头文件
`#include <semaphore.h>`

这里面包含了大多数的所需要使用的信号量.
包含:

- `int sem_init(sem_t *sem, int pshared, unsigned int value)`
    用于初始化信号量。
    value代表信号量的初始值，
    pshare代表信号量是进程内的线程共享，还是进程间共享。

> 对于Linux而言，就是子进程共享和父进程共享——Linux中不存在线程的问题，Linux中的线程，进程均为进程，只是看进程组，子进程父进程而已。对于进程关系，可以使用`pstree`查看。

    返回0时成功，返回-1时失败，并且设置errno
    使用perror输出错误信息：
    - EINVAL
    value 超过 `SEM_VALUE_MAX`
    - ENOSYS
    pshared 非零，但系统还没有支持进程共享的信号量。

- `int sem_post(sem_t *sem)`
    这个函数相当于V操作，是一个"原子操作"——即是不会被打断(中断)的。并行计算中会出现的两个线  
    程同时对一个变量相加导致变量的值仅产生了一次变化在此处是不成立的。
    返回0时成功，返回-1时失败, 并且设置errno:
    - EINVAL
    sem 不是一个有效的信号量。
    - EOVERFLOW
    信号量允许的最大值将要被超过。


- `int sem_wait(sem_t *sem)`
    这个函数相当于P操作，也是一个"原子操作"。等待对变量-1，如果不能对变量-1，则进入等待队列
- `int sem_trywait(sem_t *sem)`
    如果变量不能-1(即`sem_t`为0),则不会进入等待队列，直接返回错误代码。
- `int sem_timedwait(sem_t *sem)`
- `int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);`
>   - return 0 (success), return -1 (failure) and set errno:
    - EINTR
    The call was interrupted by a signal handler; see signal(7).
    //调用被信号处理中断
    - EINVAL sem is not a valid semaphore.
　　//sem不是有效的信号量
    The following additional error can occur for sem_trywait():
　　//下面的错误是sem_trywait()可能发生的:
    - EAGAIN The operation could not be performed without blocking (i.e., the
　　semaphore currently has the value zero).
　　//除了锁定无法进行别的操作(如信号量当前是0值).
    The following additional errors can occur for sem_timedwait():
　　//下面的错误是sem_timedwait()可能发生的:
    - EINVAL The value of abs_timeout.tv_nsecs is less than 0, or greater than or
　　equal to 1000 million.
　　//abs_timeout.tv_nsecs 的值比0小或者大于等于1000毫秒(译者注:纳秒的值不能比0小,不能比1秒大)
    - ETIMEDOUT
　　The call timed out before the semaphore could be locked.
　　//在信号量锁定之前就超时了
    - 注意
    对这些函数,信号处理程序总是会中断阻塞,不管是否使用了sigaction(2)的SA_RESTART标志位.


```cpp
/*=============================================================================
#
# Author: svtter - svtter@qq.com
#
# QQ : 57180160
#
# Last modified: 2014-10-03 20:35
#
# Filename: producer_consumer.cc
#
# Description: 
#
=============================================================================*/
#include <cstdio>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define N 5
#define item int

// P/V操作
void P(sem_t* sem)
{
    if(sem_wait(sem))
        perror("P error!");
    
}

void V(sem_t* sem)
{
    if(sem_post(sem))
        perror("V error!");
}

sem_t mutex;
sem_t full;
sem_t empty;
item buffer[N];
int i = 0, j = -1;

void init_sem()
{
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, N);
}

void* producer(void *arg)
{
    int product;
    while(1)
    {
        //生成随机数字
        product = rand()%100;
        // cout << "producer running..." << endl;
        P(&empty);
        P(&mutex);
        buffer[i] = product;
        printf("producer produced %d @ %d pos\n",
                product, i);
        i=(i+1)%N;
        V(&mutex);
        V(&full);
        sleep(1);
    }
}

void* consumer(void *arg)
{
    int product, temp;
    while(1)
    {
        // cout << "consumer running..." << endl;
        P(&full);
        P(&mutex);
        j = (j+1)%N;
        product = buffer[j];
        V(&mutex);
        V(&empty);
        printf("Consumer consumed %d @ %d pos\n",
                product, j);
        sleep(3);
    }
}

int main()
{
    //random num
    srand(time(NULL));
    init_sem();
    
    int error;
    pthread_t producer_t, consumer_t;

    error = pthread_create(&producer_t, NULL, producer, NULL);
    if(error != 0)
        printf("error in create producer.\n");
    else
        printf("create producer success!\n");

    pthread_create(&consumer_t, NULL, consumer, NULL);
    if(error != 0)
        printf("error in create consumer.\n");
    else
        printf("create consumer success!\n");
    
    pthread_join(producer_t, NULL);
    pthread_join(consumer_t, NULL);

    return 0;
}
```
