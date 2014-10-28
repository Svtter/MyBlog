Openmp
===

随手记录一下这个令人惊奇的东西。

写了一个枚举排序的代码。

```cc
double parallel_enum_sort(int b[], int bt[])
{
    double t1, t2;
    t1 = omp_get_wtime();
    int i, j, k;
#pragma omp parallel for private(i, j, k)
    for(i = omp_get_thread_num()+1; i <= MAXN; i += NUM_THREADS)
    {
        k = 1;
        for(j = 1; j <= MAXN;  j++)
        {
            if(b[i] > b[j] || (b[i] == b[j] && (i > j)))
                k++;
        }
        bt[k] = b[i];
    }
    t2 = omp_get_wtime();
    return (t2 - t1);
}

```
这段代码在vc下，clang的编辑器下可以，在gcc下也可以。
但是MAXN大小不能过大，否则会越界。个人认为可能和数组大小有关。

另外，如果将代码更改为

```cc
double parallel_enum_sort(int b[], int bt[])
{
    double t1, t2;
    t1 = omp_get_wtime();
    int i, j, k;
#pragma omp parallel private(i, j, k)
    {
        for(i = omp_get_thread_num()+1; i <= MAXN; i += NUM_THREADS)
        {
            k = 1;
            for(j = 1; j <= MAXN;  j++)
            {
                if(b[i] > b[j] || (b[i] == b[j] && (i > j)))
                    k++;
            }
            bt[k] = b[i];
        }
    }
    t2 = omp_get_wtime();
    return (t2 - t1);
}
```

gcc 编辑器将不会顾及MAXN的值，不会并行工作，并且也不提示已经越界
vc, clang  会提示该问题，依然并行处理。
    
依据High Perfomance Mark的解释，是因为没有定义任何*worksharing*
。他的原话是：
> not declared any parallel worksharing.

然后就是一句总结：能用parallel for的时候，不要用parallel.

之后再次测试这段程序，发现一开始的排序算法有错误，serial的排序有误，
parallel也有相应的错误，但是没有找到。
