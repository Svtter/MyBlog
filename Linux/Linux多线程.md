Linux多线程
===

典型的UNIX系统都支持一个进程创建多个线程(thread)。
在Linux进程基础中提到，Linux以进程为单位组织操作，Linux中的线程也都基于进程。
尽管实现方式有异于其它的UNIX系统，但Linux的多线程在逻辑和使用上与真正的多线程并没有差别。

- 了解进程之间的关系，进程组，进程，父进程
`ps -o pid,pgid,ppid,comm | cat`


- 显示进程树
`pstree`
