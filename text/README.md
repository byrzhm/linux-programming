# 文本处理

## redirect and pipeline

## more/less

查看文件

## cat/od

cat - concatenate and print files

``` shell
cat file.txt
cat -n file.txt
```

od - octal, decimal, hex, ASCII dump

``` shell
od -t x1 x.dat # x1 十六进制 一个一组
od -c file.txt # 以C语言的方式，逐字符打印
```

## head/tail

head - display first lines of a file

``` shell
head -n 15 ab.c
```

tail - display the last part of a file

``` shell
tail -n 15 ab.c
```

## tee

tee - duplicate standard input

The `tee` utility copies standard input to standard output, making a copy in zero or more files. The output is unbuffered.

## wc

``` shell
wc sum.c
wc -l sum.c
```

## sort

``` shell
sort -n ... # 算术值比较
sort ... # 字典序比较
```

## tr

tr - translate characters

``` shell
# 把标准输入拷贝到标准输出, string1 中出现的字符替换为 string2 中对应的字符
tr string1 string2

cat report | tr '[a-z]' '[A-Z]' # 小写字母改为大写字母
```

## uniq

``` shell
uniq options
uniq options input-file
uniq options input-file output-file

# -u 只保留没有重复的行
# -d 只保留有重复的行
# 上下紧邻的相同的行才称为重复的行

# 示例文件
# Linux
# Windows
# Windows
# Linux
# Linux
# Linux
# MACOS
```