# find

## 用法

``` sh
find [-H | -L | -P] [-EXdsx] [-f path] path ... [expression]
find [-H | -L | -P] [-EXdsx] -f path [path ...] [expression]
```

## 用量

### 查找指定后缀的文件

``` shell
find root_path -name '*.ext'
```

### 查找 path 或 name 匹配的文件

``` shell
find root_path -path '**/path/**/*.ext' -or -name '*pattern*'
```

### 以大小写不区分的方式查找名字匹配的文件夹

``` shell
find root_path -type d -iname '*lib*'
```

### 对每一个文件运行命令 (使用 `{}` 访问文件名)

``` shell
find root_path -name '*.ext' -exec wc -l {} \;
```

### 将今天修改过的文件传递给其它命令作为参数

``` shell
find root_path -daystart -mtime -1 -exec tar -cvf archive.tar {} \+
```

>
> 可以将 `\+` 换为 `+`，结果相同
>

### 找到空文件并删除

``` shell
find root_path -type f -empty -delete
```
