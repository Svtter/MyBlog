#include <unistd.h>
#include <signal.h>
#include <stdio.h>

char parent[] = "a message from parrent";
char child[] = "a message from child";

main ()
{
    int chan1[2], chan2[2];
    int pid;
    char buf[100];
    pipe(chan1);
    pipe(chan2);
    pid=fork();
    if(pid > 0)
    {
        close(chan1[0]);
        close(chan2[1]);
        write(chan1[1], parent, sizeof(parent));
        close(chan1[1]);
        read(chan2[0],buf, 100);
        printf("%s\n", buf);
        close(chan2[0]);
    }
    else if(pid == 0)
    {
        close(chan1[1]);
        close(chan2[0]);
        read(chan1[0], buf, 100);
        printf("%s\n", buf);
        write(chan2[1], child, sizeof(child));
        close(chan2[1]);
        close(chan1[0]);
    }
}
