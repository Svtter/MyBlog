#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#define DEBUG 1

int num=0;
pthread_mutex_t mylock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t qready=PTHREAD_COND_INITIALIZER;
void * thread_func(void *arg)
{
    int i=(int)arg; 
    int ret;
    sleep(5-i);//线程睡眠,然最先生成的线程，最后苏醒
    pthread_mutex_lock(&mylock);//调用pthread_cond_wait前，必须获得互斥锁
    while(i!=num)
    {
#ifdef DEBUG
        printf("thread %d waiting\n",i);
#endif
        ret=pthread_cond_wait(&qready,&mylock);//该函数把线程放入等待条件的线程列表，然后对互斥锁进行解锁，这两部都是原子操作。并且在pthread_cond_wait返回时，互斥量再次锁住。
        if(ret==0)
        {
#ifdef DEBUG
            printf("thread %d wait success\n",i);
#endif
        }else
        {
#ifdef DEBUG
            printf("thread %d wait failed:%s\n",i,strerror(ret));
#endif
        }
    }
    printf("thread %d is running \n",i);
    num++;
    pthread_mutex_unlock(&mylock);//解锁
    pthread_cond_broadcast(&qready);//唤醒等待该条件的所有线程
    return (void *)0;
}
int main(int argc, char** argv) {
    
    int i=0,err;
    pthread_t tid[4];
    void *tret;
    for(;i<4;i++)
    {
        err=pthread_create(&tid[i],NULL,thread_func,(void *)i);
        if(err!=0)
        {
            printf("thread_create error:%s\n",strerror(err));
            exit(-1);
        }
    }
    for (i = 0; i < 4; i++)
    {
        err = pthread_join(tid[i], &tret);
        if (err != 0)
        {
            printf("can not join with thread %d:%s\n", i,strerror(err));
            exit(-1);
        }
    }
    return 0;
}
