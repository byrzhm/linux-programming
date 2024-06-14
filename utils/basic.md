# 基础命令行命令

## who/who am i/whoami

列出当前已登入系统的用户

- 第一列: 用户名
- 第二列: 终端设备的设备文件名

## uptime

显示系统的运行时间，以及系统平均负载

``` shell
uptime
# current time | the length of time the system has been up
# | the number of users | the load average of the system over
# the last 1, 5, and 15 minutes
#
# 22:20  up 30 days,  2:12, 2 users, load averages: 1.58 2.07 2.09
```

>
> Reference:
>
> [man uptime](https://man7.org/linux/man-pages/man1/uptime.1.html)
>

## top

显示排序后的进程信息

- Start `top`, all options are available in the interface:
    top

- Start `top` sorting processes by internal memory size (default order - process ID):
    top -o mem

- Start `top` sorting processes first by CPU, then by running time:
    top -o cpu -O time

- Start `top` displaying only processes owned by given user:
    top -user user_name

- Display help about interactive commands:
    ?

>
> Reference:
>
> [man top](https://man7.org/linux/man-pages/man1/top.1.html)
>

## ps

process status

- UID
- PID
- C
- STIME
- SZ
- TTY
- COMMAND
- WCHAN
- TIME
- PRI
- STAT: S(Sleep), R(Run), Z(Zombie)

> - List all running processes:
>
>   ``` shell
>   ps aux
>   ```
>
> - List all running processes including the full command string:
>
>   ``` shell
>   ps auxww
>   ```
>
> - Search for a process that matches a string:
>
>   ``` shell
>   ps aux | grep string
>   ```
>
> - Get the parent PID of a process:
>
>   ``` shell
>   ps -o ppid= -p pid
>   ```
>
> - Sort processes by memory usage:
>
>   ``` shell
>   ps -m
>   ```
>
> - Sort processes by CPU usage:
>
>   ``` shell
>   ps -r
>   ```
>

## free (linux only)

## vmstat (linux only)
