数学基础
===

异或
---

- a^b：a，b相同返回0， a，b不相同返回1
- 异或又可以称为不带进位的二进制加法运算
- 运算法则
    - a ^ b ^ b = a
    - a ^ b = b ^ a

<div class="md-section-divider"></div>

<p><span class="MathJax_Preview"></span><div style="text-align: center;" aria-readonly="true" role="textbox" class="MathJax_Display"><span style="" id="MathJax-Element-1-Frame" class="MathJax"><nobr><span style="width: 5.453em; display: inline-block;" id="MathJax-Span-1" class="math"><span style="display: inline-block; position: relative; width: 4.183em; height: 0px; font-size: 130%;"><span style="position: absolute; clip: rect(1.664em, 1000em, 3.087em, -0.378em); top: -2.692em; left: 0em;"><span id="MathJax-Span-2" class="mrow"><span style="font-family: MathJax_Math; font-style: italic;" id="MathJax-Span-3" class="mi">f<span style="display: inline-block; overflow: hidden; height: 1px; width: 0.06em;"></span></span><span style="font-family: MathJax_Main;" id="MathJax-Span-4" class="mo">(</span><span style="font-family: MathJax_Math; font-style: italic;" id="MathJax-Span-5" class="mi">x</span><span style="font-family: MathJax_Main;" id="MathJax-Span-6" class="mo">)</span><span style="font-family: MathJax_Main; padding-left: 0.278em;" id="MathJax-Span-7" class="mo">=</span><span style="padding-left: 0.278em;" id="MathJax-Span-8" class="msubsup"><span style="display: inline-block; position: relative; width: 0.988em; height: 0px;"><span style="position: absolute; clip: rect(1.866em, 1000em, 2.607em, -0.398em); top: -2.452em; left: 0em;"><span style="font-family: MathJax_Math; font-style: italic;" id="MathJax-Span-9" class="mi">x</span><span style="display: inline-block; width: 0px; height: 2.452em;"></span></span><span style="position: absolute; top: -2.721em; left: 0.577em;"><span style="font-size: 70.7%; font-family: MathJax_Main;" id="MathJax-Span-10" class="mn">2</span><span style="display: inline-block; width: 0px; height: 2.308em;"></span></span></span></span></span><span style="display: inline-block; width: 0px; height: 2.692em;"></span></span></span><span style="border-left: 0em solid; display: inline-block; overflow: hidden; width: 0px; height: 1.599em; vertical-align: -0.388em;"></span></span></nobr></span></div><script id="MathJax-Element-1" type="math/tex; mode=display">f(x) = x^2</script></p>


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

