Use Terminal Like Hacker
----

###The reason why I like it
`Powerful`

- show how often I used
```
 history |
 awk '{CMD[$2]++; count++; }END \
 {for (a in CMD) print CMD[a] " "\
 CMD[a]/count*100 "% " a; } |
 grep -v "./" |
 column -c3 -s " " -t |
 sort -nr |
 nl |
 hear n10
```

###Change wrong input

- use ^ to remove addition
```
% grep fooo /var/log/auth.log

% ^o

% grep foo /var/log/auth.log
```

- use ^old^new
```
% cat myflie

% ^li^il

% cat myfile

% ansible vod -m command -a 'uptim'

% ^im^ime

% ansible vod -m command -a 'uptime'
```

- use !:gs/old/new 将 old 全部换成 new

```
% ansible nginx -m command -a 'which nginx'

% !:gs/nginx/squid

% ansible squid -m command -a 'which squid'

% ^nginx^squid^:G # zsh
```

###about HISTORY
- 了解历史记录的大小
`echo $HISTSIZE`
`1000`
- 历史记录的保存位置
`echo $HISTFILE`
`/home/xiaodong/.zhistory`
- 历史记录的保存大小
```
echo $HISTFILESIZE # bashc
1000
echo $SAVEHIST     # zsh
1000
```

- 查看历史
```
history

history | less

1  hist
2  ./code/gs/update_system.pl -n
3  emerge -C chromium
4  emerge @preserved-rebuild
5* df -h
......

history 5

history | grep string
```

- check HISTORY
```
% 
(reverse-i-search)`h': history 5
使用 Ctrl + p 访问上一条命令
% history 5
[Ctrl + p]
使用 Ctrl + n 访问下一条命令
% 
[Ctrl + n]
```

- 使用 !foo 执行以 foo 开头的命令
```
% !his
history
```

- 使用 !?foo 执行包含 foo 的命令
```
% !?is
echo $histchars
```

- 使用 !n 执行第 n 个命令
```
!10
vim lib/TunePage.pm
```

- 使用 !-n 执行倒数第 n 个命令
```
% !-2
htop

% !-1 == !!
Tip: 给命令提示符中增加历史命令编号
% export PS1='!\! \u@\h:\w\$ '
!998 xiaodong@codetoy:~$
```

- 使用 !# 引用当前行
```
% cp filename filename.old

% cp filename !#:1.old
```
