# 与Linux标准库的差异<a name="ZH-CN_TOPIC_0000001053240737"></a>

本章节描述了OpenHarmony内核承载的标准库与Linux标准库之间存在的关键差异。更多差异详见C库API文档说明。

## 进程<a name="section249218475301"></a>

1.  OpenHarmony用户态进程优先级只支持静态优先级且用户态可配置的优先级范围为10\(最高优先级\)-31\(最低优先级）。
2.  OpenHarmony用户态线程优先级只支持静态优先级且用户态可配置的优先级范围为0\(最高优先级\)-31\(最低优先级）。
3.  OpenHarmony调度策略支持SCHED\_RR和SCHED\_FIFO。
4.  sched\_yield\(\)为进程主动放弃CPU；thrd\_yield\(\)为线程主动放弃CPU。

## 内存<a name="section55731513163117"></a>

## 与Linux mmap的差异<a name="section1943551142314"></a>

mmap接口原型为：void \*mmap \(void \*addr, size\_t length, int prot, int flags, int fd, off\_t offset\)。

其中，参数fd的生命周期实现与Linux glibc存在差异。具体体现在，glibc在成功调用mmap进行映射后，可以立即释放fd句柄。在OpenHarmony内核中，不允许用户在映射成功后立即关闭相关fd，只允许在取消映射munmap后再进行fd的close操作。如果用户不进行fd的close操作，操作系统将在进程退出时对该fd进行回收。

## 代码举例<a name="section16947155092514"></a>

Linux目前支持的情况如下：

```
int main(int argc, char *argv[])
{
    int fd;
    void *addr = NULL;
    ...
    fd = open(argv[1], O_RDONLY);
    if (fd == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }
    addr = mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, offset);
    if (addr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    close(fd); /* close immediately, OpenHarmony do not support this way */ 
    ...
    exit(EXIT_SUCCESS);
}
```

OpenHarmony支持的情况如下：

```
int main(int argc, char *argv[])
{
    int fd;
    void *addr = NULL;
    ...
    fd = open(argv[1], O_RDONLY);
    if (fd == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }
    addr = mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, offset);
    if (addr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    ...
    munmap(addr, length);
    close(fd); /* close after munmap */
    exit(EXIT_SUCCESS);
}
```

## 文件系统<a name="section1746965493115"></a>

**系统目录：**用户无法对其进行修改，或是设备挂载。包含/dev，/proc，/app，/bin，/data，/etc，/lib，/system，/usr目录。

**用户目录：**用户可以在该目录下进行文件创建、读写，但**不能进行设备挂载**。用户目录指/storage目录。

除**系统目录**与**用户目录**之外，用户可以自行创建文件夹进行设备的挂载。但是要注意，已挂载的文件夹及其子文件夹不允许重复或者嵌套挂载，非空文件夹不允许挂载。

## 信号<a name="section1198254310333"></a>

-   信号默认行为不支持STOP、CONTINUE、COREDUMP功能。
-   无法通过信号唤醒正在睡眠状态（举例：进程调用sleep函数进入睡眠）的进程。原因：信号机制无唤醒功能，当且仅当进程被CPU调度运行时才能处理信号内容。
-   进程退出后会发送SIGCHLD给父进程，发送动作无法取消。
-   信号仅支持1-30号信号，接收方收到多次同一信号，仅执行一次回调函数。

## Time<a name="section0833419133414"></a>

OpenHarmony当前时间精度以tick计算，系统默认10ms/tick。sleep、timeout系列函数时间误差<=20ms。

