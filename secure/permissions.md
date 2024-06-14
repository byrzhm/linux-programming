# permissions

## 命令

### chmod

Change the access permissions of a file or directory.

More information: https://www.gnu.org/software/coreutils/chmod.

- Give the [u]ser who owns a file the right to e[x]ecute it:
    chmod u+x path/to/file

- Give the [u]ser rights to [r]ead and [w]rite to a file/directory:
    chmod u+rw path/to/file_or_directory

- Remove e[x]ecutable rights from the [g]roup:
    chmod g-x path/to/file

- Give [a]ll users rights to [r]ead and e[x]ecute:
    chmod a+rx path/to/file

- Give [o]thers (not in the file owner's group) the same rights as the [g]roup:
    chmod o=g path/to/file

- Remove all rights from [o]thers:
    chmod o= path/to/file

- Change permissions recursively giving [g]roup and [o]thers the ability to [w]rite:
    chmod -R g+w,o+w path/to/directory

- Recursively give [a]ll users [r]ead permissions to files and e[X]ecute permissions to sub-directories within a directory:
    chmod -R a+rX path/to/directory


## 问题集

1. Linux 中某个普通磁盘文件对所有用户赋予了读写权限，但删除该文件失败。原因?

应该是文件所处的目录没有写权限。因为要删除这个文件，只需要能对文件所在的目录可
写，对文件自身的权限没有任何要求。

2. 在当前目录/home/sun下执行 chmod 000 . 命令后，随后执行 chmod 777 . 失败。
为什么会失败？这样导致当前目录无法访问，如何解除这一困境？

. 代表当前目录，chmod 000 . 命令修改了当前目录的读写可执行权限，使得无法对当前
目录中名称为 "." 的文件进行检索访问和修改目录结构。因而 chmod 777 . 会失败。

使用 chmod 777 /home/sun 可以解除这一困境，因为这个命令访问的是 /home 目录，
***只要 /home 目录有 x 属性，就可以修改这个目录下的 sun 的属性。
这个过程中对当前目录的属性没有任何要求。***

3. 在 Windows 下输入命令名，系统首先检索当前目录下是否有这个可执行文件，检索
不到，会逐个检查 PATH 环境变量列出的各目录。 Linux 不自动检索当前目录，而且环境
变量 PATH 中一般不含当前目录 ./，为什么？

出于安全方面的考虑，假如用户 a 在 /tmp 目录下创建名为 ls 的恶意程序，并对所有
用户赋予执行权限 x。当用户 b 在 /tmp 目录下执行命令 ls，由于 PATH 中含有 ./ 分
量，将以用户 b 的身份执行 /tmp/ls，因而造成安全问题。

4. 用户 liu 有一个重要的文件 `report.txt`，为保证该文件不会被无意的修改，移走和
删除应当采取什么措施?

为了保证文件不会被无意地修改，取消文件的写权限；为保证文件不会被无意地移走和删除，取消该文件所在
目录的写权限

>
> 尝试创建文件夹 tmp，并在其中创建文件 `report.txt`
>

5. 目录的 x 权限起什么作用？root用户拥有的目录树 eldk 下有许多子目录。每个子目录中也有若干个
文件。现在 root 用户希望把这个目录树下所有子目录对所有用户开放 x 权限，但普通文件的权限不修改。
怎样才能完成这个工作？

(1) 目录的 x 权限意味着分析路径名过程中可检索该目录

(2) 完成这个要求可以使用 find 命令便利目录树 eldk，符合规定条件 "类型是目录" (-type d)，执
行指定动作 "修改权限" (-exec chmod a+x {} \\;) 完整的命令为：

``` shell
find eldk -type d -exec chmod a+x {} \;
```
