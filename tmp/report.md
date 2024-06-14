# shell 脚本编程，生成 TCP 活动状况报告

## 设计

### `netstat --statistics` / `netstat -s`

`netstat -s` 的输出如下:

<img src="images/Screenshot 2024-05-26 at 09.35.36.png" width="50%">

<div style="page-break-after: always"></div>

<img src="images/Screenshot 2024-05-26 at 09.35.54.png" width="50%">

<img src="images/Screenshot 2024-05-26 at 09.36.01.png" width="50%">

下面的信息表示 TCP 发送了多少报文，接收了多少报文

```
    10148 segments received
    8451 segments sent out
```

<div style="page-break-after: always"></div>

因为 segment 是 TCP 报文的专用名词，因此可以用 `grep` 直接获得对应行的信息

![](images/Screenshot%202024-05-26%20at%2009.34.59.png)

设置两个变量 recvPktTotal, sendPktTotal 分别表示目前为止收到的包的数量和发送的包的数量

![](images/Screenshot%202024-05-26%20at%2009.56.30.png)

datetime 输出

![](images/Screenshot%202024-05-26%20at%2010.07.17.png)

### 现在编写 shell 脚本

#### 首先定义三个工具函数

第一个工具函数，获得目前为止收到的 TCP 报文数量

![](images/Screenshot%202024-05-26%20at%2011.05.37.png)

第二个工具函数，获得目前为止发送的 TCP 报文数量

![](images/Screenshot%202024-05-26%20at%2011.05.46.png)

第三个工具函数，根据现在收发的报文数量和上一次收发的报文数量的差值，决定输出 ' '，'+' 还是 '-'

![](images/Screenshot%202024-05-26%20at%2011.05.58.png)

#### 循环开始准备

因为第一次输出没有办法与之前比较，因此从循环中剥离出来单独处理

![](images/Screenshot%202024-05-26%20at%2011.07.06.png)

#### 主循环

先 `sleep $sleepTime` 休眠一段时间，然后获取该段时间收发的报文数量，并与之前对比，最后输出，循环往复

![](images/Screenshot%202024-05-26%20at%2011.07.18.png)

## 测试

将 `sleepTime` 设置为较少的值可以帮助调试

### `sleepTime=5` 运行结果如下

![](images/Screenshot%202024-05-26%20at%2011.29.20.png)

### `sleepTime=10` 运行结果如下

![](images/Screenshot%202024-05-26%20at%2011.31.39.png)

### 没有提供命令行参数的情况下默认为 60

![](images/Screenshot%202024-05-26%20at%2011.39.26.png)

<div style="page-break-after: always"></div>

## 源码

``` sh
#! /bin/bash

if [ $# -eq 1 ]; then
        sleepTime=$1
else
        sleepTime=60
fi

# get the total received tcp packet number
getRecvPktTotal() {
        netstat -s | grep -E '[0-9]+ segments received' | grep -o -E '[0-9]+'
        # netstat -s | grep -E '[0-9]+ segments received' | awk '{print $1}'
}

# get the total sent tcp packet number
getSendPktTotal() {
        netstat -s | grep -E '[0-9]+ segments sent out' | grep -o -E '[0-9]+'
        # netstat -s | grep -E '[0-9]+ segments sent out' | awk '{print $1}'
}

# based on sum of packet number information set the output flag ' ' or '+' or '-'
diffFlag() {
        if [ "$1" -le 10 ] && [ "$1" -ge 0 ]; then
                echo ' '
        elif [ "$1" -gt 10 ]; then
                echo '+'
        else
                echo '-'
        fi
}

prevRecvPktTotal=$(getRecvPktTotal)
prevSendPktTotal=$(getSendPktTotal)

sleep $sleepTime

datetime=$(date +"%Y-%m-%d %H:%M")
recvPktTotal=$(getRecvPktTotal)
sendPktTotal=$(getSendPktTotal)
recvPktCurr=$((recvPktTotal - prevRecvPktTotal))
sendPktCurr=$((sendPktTotal - prevSendPktTotal))
sumPkt=$((recvPktCurr + sendPktCurr))

prevRecvPktTotal=$recvPktTotal
prevSendPktTotal=$sendPktTotal
prevSumPkt=$sumPkt

echo "$datetime $recvPktCurr $sendPktCurr $sumPkt"

while true
do
        sleep $sleepTime

        datetime=$(date +"%Y-%m-%d %H:%M")
        recvPktTotal=$(getRecvPktTotal)
        sendPktTotal=$(getSendPktTotal)
        recvPktCurr=$((recvPktTotal - prevRecvPktTotal))
        sendPktCurr=$((sendPktTotal - prevSendPktTotal))
        sumPkt=$((recvPktCurr + sendPktCurr))

        difference=$((sumPkt - prevSumPkt))
        flag=$(diffFlag "$difference")

        prevRecvPktTotal=$recvPktTotal
        prevSendPktTotal=$sendPktTotal
        prevSumPkt=$sumPkt

        echo "$datetime $recvPktCurr $sendPktCurr $sumPkt $flag"

done

```
