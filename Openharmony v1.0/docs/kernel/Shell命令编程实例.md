# Shell命令编程实例<a name="ZH-CN_TOPIC_0000001052451603"></a>

## 实例描述<a name="section87143612316"></a>

在下面的两个例子中，演示如何使用静态注册命令方式和动态注册命令方式新增一个Shell命令：**test**。

## 静态注册方式<a name="section1660495712314"></a>

开发流程如下：

1.  定义一个新增命令所要调用的执行函数cmd\_test。

2.  使用SHELLCMD\_ENTRY函数添加新增命令项。

3.  在链接选项liteos\_tables\_ldflags.mk中添加链接该新增命令项参数。

4.  重新编译代码后运行。


## 静态注册编程实例<a name="section0410326242"></a>

1.  定义命令所要调用的函数cmd\_test：

    ```
    #include "shell.h" 
    #include "shcmd.h"  
    int cmd_test(void) 
    {     
        printf("hello everybody!\n");     
        return 0; 
    }
    ```

2.  添加新增命令项：

    ```
    SHELLCMD_ENTRY(test_shellcmd, CMD_TYPE_EX, "test", 0, (CMD_CBK_FUNC)cmd_test);
    ```

3.  在链接选项中添加链接该新增命令项参数：

    在liteos\_tables\_ldflags.mk文件的LITEOS\_TABLES\_LDFLAGS项下添加-utest\_shellcmd。

4.  重新编译代码：

    ```
    make clean;make
    ```

5.  用help命令查看当前系统所有的注册命令，可以发现test命令已经注册。（以下命令集合仅供参考，以实际编译运行情况为准。）

    ```
    OHOS # help
    *******************shell commands:*************************
    
    arp           cat           cd            chgrp         chmod         chown         cp            cpup          
    date          dhclient      dmesg         dns           format        free          help          hwi           
    ifconfig      ipdebug       kill          log           ls            lsfd          memcheck      mkdir         
    mount         netstat       oom           partinfo      partition     ping          ping6         pwd           
    reset         rm            rmdir         sem           statfs        su            swtmr         sync          
    systeminfo    task          telnet        test          tftp          touch         umount        uname         
    watch         writeproc     
    ```


## 动态注册方式<a name="section6804126192412"></a>

开发流程如下：

1.  使用osCmdReg函数添加新增命令项。

2.  重新编译后运行。


## 动态注册编程实例<a name="section17474410102419"></a>

1.  在用户应用函数中调用osCmdReg函数动态注册命令。

    ```
    #include "shell.h" 
    #include "shcmd.h"  
    int cmd_test(void) 
    {     
        printf("hello everybody!\n");     
        return 0; 
    }  
    void app_init(void) 
    {      
        ....      
        ....      
        osCmdReg(CMD_TYPE_EX, "test", 0,(CMD_CBK_FUNC)cmd_test);      
        .... 
    }
    ```

2.  重新编译代码：

    ```
    make clean;make
    ```

3.  用help命令查看当前系统所有的注册命令，可以发现test命令已经注册。

    ```
    OHOS # help
    *******************shell commands:*************************
    
    arp           cat           cd            chgrp         chmod         chown         cp            cpup          
    date          dhclient      dmesg         dns           format        free          help          hwi           
    ifconfig      ipdebug       kill          log           ls            lsfd          memcheck      mkdir         
    mount         netstat       oom           partinfo      partition     ping          ping6         pwd           
    reset         rm            rmdir         sem           statfs        su            swtmr         sync          
    systeminfo    task          telnet        test          tftp          touch         umount        uname         
    watch         writeproc     
    ```


