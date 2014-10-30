Ubuntu默认安装的中文环境为`zh_CN.utf8`,然后很多windows 的文档还是以GB2312或GBK编码保存的,因此十分有必要

在Ubuntu下生成GBK或GB2312的locale.具体方法如下:

1.修改/var/lib/locales/supported.d/local文件,在文件中添加

`zh_CN.GBK GBK`

`zh_CN.GB2312 GB2312`

2.sudo dpkg-reconfigure --force locales

然后在输出的结果中会出现

`zh_CN.GB2312 done`

`zh_CN.GBK done`


Windows的默认编码为GBK，Linux的默认编码为UTF-8。在Windows下编辑的中文，在Linux下显示为乱码。为了解决此问题，修改Linux的默认编码为GBK。方法如下：

方法1：

`vi   /etc/sysconfig/i18n`

默认为:

`LANG="en_US.UTF-8"`
`SYSFONT="latarcyrheb-sun16"`

修改为:

`LANG="zh_CN.GBK"`
`SUPPORTED="zh_CN.UTF-8:zh_CN:zh"`
`SYSFONT="latarcyrheb-sun16"`

方法2：
`vi /etc/profile`

`export LC_ALL="zh_CN.GBK"`
`export LANG="zh_CN.GBK"`

 


运行locale指令得到当前系统编码设置的详细资料。

一、locale的五脏六腑

1、 语言符号及其分类(LC_CTYPE)
2、 数字(LC_NUMERIC)
3、 比较和排序习惯(LC_COLLATE)
4、 时间显示格式(LC_TIME)
5、 货币单位(LC_MONETARY)
6、 信息主要是提示信息,错误信息, 状态信息, 标题, 标签, 按钮和菜单等(LC_MESSAGES)
7、 姓名书写方式(LC_NAME)
8、 地址书写方式(LC_ADDRESS)
9、 电话号码书写方式(LC_TELEPHONE)
10、度量衡表达方式(LC_MEASUREMENT)
11、默认纸张尺寸大小(LC_PAPER)
12、对locale自身包含信息的概述(LC_IDENTIFICATION)。

二、理解locale的设置

设定locale就是设定12大类的locale分类属性，即 12个LC_*。除了这12个变量可以设定以外，为了简便起见，还有两个变量：LC_ALL和LANG。

它们之间有一个优先级的关系：LC_ALL > LC_* > LANG

可以这么说，LC_ALL是最上级设定或者强制设定，而LANG是默认设定值。

三 具体设定locale的方法（zh_CN.UTF-8、zh_CN.GBK）

freebsd的设置：

1.GDM登录改为终端登录后startx启动图形桌面

2.在~/.cshrc中增加如下语句,（根据自己使用的shell进行相应设置）

`setenv LANG zh_CN.GBK`
`setenv LC_ALL zh_CN.GBK`
`setenv LC_CTYPE zh_CN.GBK`

3.修改/etc/fstab的默认值：

linux 设置：

1.修改/etc/sysconfig/i18n文件，LANG="zh_CN.UTF-8"或LANG="zh_CN.GBK"

普通用户修改~/.profile

...
export LANG zh_CN.GBK
...

2.修改/etc/fstab的默认值
