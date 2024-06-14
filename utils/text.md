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

### head - display first lines of a file

- Output the first few lines of a file

``` shell
head -n 8 path/to/file
# head --lines 8 path/to/file
# head --lines=8 path/to/file
```

- Output the first few bytes of a file

``` shell
head -c 8 path/to/file
# head --bytes 8 path/to/file
# head --bytes=8 path/to/file
```

*Following Only for Linux*

- Output everything but the last few lines of a file:

``` shell
head -n -8 path/to/file
# head --lines -8 path/to/file
# head --lines=-8 path/to/file
```

- Output everything but the last few bytes of a file:

``` shell
head -c -8 path/to/file
# head --bytes -8 path/to/file
# head --bytes=-8 path/to/file
```

### tail - display the last part of a file

- Show last 'count' lines in file:

``` shell
tail -n 8 path/to/file
```

- Print a file from a specific line number:

``` shell
tail -n +8 path/to/file
```

- Print a specific count of bytes from the end of a given file:

``` shell
tail -c 8 path/to/file
```

- Print the last lines of a given file and keep reading it until `Ctrl + C`:

``` shell
tail -f path/to/file
```

- Keep reading file until `Ctrl + C`, even if the file is inaccessible:

``` shell
tail -F path/to/file
```

- Show last 'count' lines in 'file' and refresh every 'seconds' seconds:

``` shell
tail -n 8 -s 10 -f path/to/file
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