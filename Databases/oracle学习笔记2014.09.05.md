oracle学习笔记2014.09.05
----------


```
测试数据库配置的信息
全局数据库名：xiuhao
系统标识符(SID)：xiuhao
服务器参数文件名：c:\oracle\dbs\spfilexiuhao.ora

database control URL: http://C-1:5500/em

sys以及system解锁

```


###edit
以文本格式打开当前命令/

###/
执行当前命令

###l [num]
显示缓存区命令

###get [file]
把file中的文件加入到缓冲区

###c /[str] /[str]
修改当前语句中的内容

###spo[ol] [file]
- 将执行的命令以及结果保存到file中
- 使用spo off终止保存

###使用cmd登陆sqlplus
在密码后添加as sysdba

###锁定\解锁用户
- alter user [username] account unlock;
- ***需要sys权限***

###链接用户
- conn [username]/[passwd]
- conn / as sysdba(默认sys用户)
- 如果使用sys，需要密码后添加 as sysdba

###查询块大小
- select name,value from V$parameter where name='db_block_size';
- 需要使用sys

###
