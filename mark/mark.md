Markdown中插入数学公式的方法
===

> [日期：2014-08-02] 来源：Linux社区  作者：xiahouzuoxin [字体：大 中 小]  

自从使用Markdown以来，就开始一直使用Markdown+Github在写文章，整理自己的所学所思。本文亦是通过这种方式完成的。

然而，Markdown自由书写的特性很好，唯独遇到数学公式时就要煞费苦心——每次都是先使用Latex书写(在线的Latex编辑器参考[1])，然后保存为图片，使用img标签进行引用，当公式很多的时候稍显复杂。

本文的方法使用html的语法，调用[1]的公式生成API，在线生成Latex数学公式，免去将公式保存为图片的麻烦。当然，弊端也是有的，公式太多，可能会造成刷新比一般的网页慢一些。

- 使用LiteIDE编写Markdown文档 http://www.linuxidc.com/Linux/2014-07/104664.htm

- Remarkjs: 使用 Markdown 做幻灯 http://www.linuxidc.com/Linux/2014-04/99416.htm

- Markdown编辑器CuteMarkEd的新功能 http://www.linuxidc.com/Linux/2014-02/96567.htm

- Markdown 语法说明 http://www.linuxidc.com/Linux/2013-09/90719.htm

- (Linux下Markdown的安装及常用语法)[http://www.linuxidc.com/Linux/2013-09/90718.htm]

方法一：使用Google Chart的服务器

<img src="http://chart.googleapis.com/chart?cht=tx&chl= 在此插入Latex公式" style="border:none;">

一个例子，

<img src="http://chart.googleapis.com/chart?cht=tx&chl=\Large x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}" style="border:none;">

公式显示结果为：



适用了下，Google Chart服务器的响应速度还可以，但据说可能复杂一些的Latex公式可能无法解析。

方法二：使用forkosh服务器

forkosh上提供了关于Latex公式的一份简短而很有用的帮助，参考[1]和[2].

使用forkosh插入公式的方法是

> <img src="http://www.forkosh.com/mathtex.cgi? 在此处插入Latex公式">

给个例子，

<img src="http://www.forkosh.com/mathtex.cgi? \Large x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}">

显示结果为：



因为网页插入公式的原理是调用“某某网站的服务器”动态生成的，所有保证公式正常显示的前提是该网址能一直存在着为我等小生做些小小的服务。forkosh我是用了快2年了，一直很好，推荐！

参考

[1] http://www.forkosh.com/mathtextutorial.html

[2] http://www.forkosh.com/mathtex.html

本文永久更新链接地址：http://www.linuxidc.com/Linux/2014-08/104996.htm

本篇文章来源于 Linux公社网站(www.linuxidc.com)  原文链接：http://www.linuxidc.com/Linux/2014-08/104996.htm
