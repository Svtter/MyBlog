/*
*简单的生产者 消费者模型
*/
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

/*封装 P/V 操作*/
void P(sem_t* sem)
{
    if(sem_wait(sem))
        perror("P operating error");
}
void V(sem_t* sem)
{
    if(sem_post(sem))
        perror("V operating error");
}

/*定义共享缓冲区*/
static char share_buf[50];
/*定义两个信号量以及其初始化函数*/
sem_t empty_sem;
sem_t full_sem;
void init_sem()
{
    sem_init(&empty_sem,0,1);
    sem_init(&full_sem,0,0);
}

/*生产者*/
void* produce(void* arg)
{
    char buf[50]={0};
    while(1){
        printf("Input message>>\n");
        fgets(buf,sizeof(buf),stdin);
        printf("Produce item is>>%s",buf);

        /*将消息放入缓冲区*/
        P(&empty_sem);
        memcpy(share_buf,buf,sizeof(buf));
        V(&full_sem);
    }
    return NULL;   
}

/*消费者*/
void* consumer(void* arg)
{
    char buf[50]={0};
    while(1){
        P(&full_sem);
        memcpy(buf,share_buf,sizeof(share_buf));
        V(&empty_sem);

                /*显示获得信息*/
        printf("Consume item is<<%s",buf);
    }
    return NULL;
}

int main()
{   
    pthread_t produce_tid;
    pthread_t consumer_tid;

    init_sem();

    pthread_create(&produce_tid,NULL,produce,NULL);
    pthread_create(&consumer_tid,NULL,consumer,NULL);
   
    pthread_join(produce_tid,NULL);
    pthread_join(consumer_tid,NULL);
   
    return 0;
}
