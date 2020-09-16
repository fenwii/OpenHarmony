# Introduction to the Shell<a name="EN-US_TOPIC_0000001053967735"></a>

The Shell provided by the OpenHarmony kernel supports commonly used commissioning commands, including those related to the system, files, networks, and dynamic loading. In addition, you can add custom commands to the shell of the OpenHarmony kernel to address your service needs.

-   System-related commands: querying information about system tasks, kernel semaphores, system software timers, CPU usage, and current interrupts

-   File-related commands: basic  **ls**  and  **cd**  functions

-   Network-related commands: querying the IP addresses of other devices connected to the development board, querying the IP address of the local device, testing the network connectivity, and setting the access point \(AP\) and station modes of the development board

    For details about the process of adding commands, see  [Development Guidelines](shell-command-development-guidelines.md#section22071515161018)  and  [Shell Command Programming Example](shell-command-programming-example.md).


## Important Notes<a name="section12298165312328"></a>

Note the following when using the shell:

-   You can use the  **exec**  command to run executable files.
-   The shell supports English input in default mode. If you enter Chinese characters in the UTF-8 format, you can delete them only by pressing the backspace key for three times.

-   When entering shell commands, file names, and directory names, you can press  **Tab**  to enable automatic completion. If there are multiple completions, multiple items are printed based on the same characters they have. If more than 24 lines of completions are available, the system displays message "Display  all num  possibilities?\(y/n\)", asking you to determine whether to print all items. You can enter  **y**  to print all items or enter  **n**  to exit the printing. If more than 24 lines are printed after your selection, the system displays "--More--". In this case, you can press  **Enter**  to continue the printing or press  **q**  \(or  **Ctrl+c**\) to exit.

-   The shell working directory is separated from the system working directory. You can run commands such as  **cd**  and  **pwd**  on the shell to perform operations on the shell working directory, and run commands such as  **chdir**  and  **getcwd**  to perform operations on the system working directory. Pay special attention when an input parameter in a file system operation command is a relative path.

-   Before using network shell commands, you need to call the  **tcpip\_init**  function to initialize the network and set up the Telnet connection. By default, the kernel does not call  **tcpip\_init**.

-   You are not advised to run shell commands to perform operations on device files in the  **/dev**  directory, which may cause unexpected results.

-   The shell functions do not comply with the POSIX standards and are used only for commissioning.

    >![](public_sys-resources/icon-notice.gif) **NOTICE:** 
    >The shell functions are used for commissioning only and can be enabled only in the Debug version \(by enabling the  **LOSCFG\_DEBUG\_VERSION**  configuration item using  **menuconfig**\).


