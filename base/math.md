数学基础
===

异或
---

- a^b：a，b相同返回0， a，b不相同返回1
- 异或又可以称为不带进位的二进制加法运算
- 运算法则
    - a ^ b ^ b = a
    - a ^ b = b ^ a

用异或实现的swap交换
```cc
#include <iostream>
using namespace std;

int main()
{
    int a, b;
    a = 3, b = 2;
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    cout << a << " " << b << endl;
    return 0;
}
```

