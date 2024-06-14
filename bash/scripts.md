# Shell 脚本编程

## Quote

单引号和双引号的区别

在 bash 中单引号包围的内容不会做任何修改 (在其它的 shell 中未必，比如 zsh，zsh 会对 '\\' 进行特殊处理)

``` shell
echo 'hello, $USER'
echo 'hello, \\'
echo '`echo hello`'
```

双引号会对 '\$'，'\\'，'\`'进行特殊处理

``` shell
echo "hello, $USER"
echo "hello, \\"
echo "`echo hello`"
```

>
> Reference:
>
> [Quoting](https://www.gnu.org/software/bash/manual/bash.html#Quoting)
>

## Brackets

`()` 会创建一个子shell进程，在子shell中中运行 `()` 中的命令

``` shell
a='This string'
( a=banana; mkdir $a )
echo $a
# => 'This string'
ls
# => ...
# => banana
```

`{}` 在当前 shell 进程中执行

``` shell
a='This string'
( a=banana; mkdir $a )
echo $a
# => 'banana'
ls
# => ...
# => banana
```

>
> Reference:
>
> [Bash Brackets Quick Reference](https://dev.to/rpalo/bash-brackets-quick-reference-4eh6)
>


## Redirect

现在 bug.c 中有大量的问题，错误信息很多，使用下面的指令做到每显示一屏后暂停等待
按下空格键再继续显示。

``` shell
gcc bug.c -o bug 2>&1 | more
```

## `./run.sh` and `. run.sh`

`. run.sh` 是 bash 独特的用法，其在当前的 shell 中执行 `run.sh` 脚本，而 `./run.sh` 会
创建子进程，在子 shell 中执行当前目录下的 `run.sh` 脚本里的程序

`run.sh` 的内容如下:

``` shell
#! /bin/bash

a=banana
echo $a
```

运行前将 `a` 设置为 `apple`，在运行完上述的脚本之后，使用 `echo $a` 检查目前 `a` 的值是多少
