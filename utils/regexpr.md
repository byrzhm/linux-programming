# 正则表达式

## 元字符

- \. : 匹配任意单字符
- \* : 正则表达式的0次或任意多次出现
- \[ : 集合相关
- \\ : 转义
- \^ : 头部或补集
- \$ : 尾部

## 转义

使用反斜线可以取消特殊字符的特殊含义

## 集合

- \[abcd] 匹配 a 或 b 或 c 或 d
- \[a-z] 匹配任意小写字母
- \[^a-z] 补集，匹配任意非小写字母

## 扩展正则表达式

...

## grep/egrep/fgrep: 在文件中查找字符串 (筛选)

- options:
    - -F, --fixed-strings \
    Fixed strings (instead of regular expressions)
    - -G, --basic-regexp \
    Basic regular expression (BRE)
    - -E, --extended-regexp
    Extended regular expression (ERE)
    - -P, --perl-regexp \
    Perl-compatible regular expression (PCRE)


## sed: 流编辑(加工)

## awk: 逐行扫描进行文本处理的一门语言 (筛选与加工)
