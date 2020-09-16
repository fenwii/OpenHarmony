# User-Space Exception Information<a name="EN-US_TOPIC_0000001051770298"></a>

During the running of the user space, the following system exception may occur:

```
##################excFrom: User!####################
prefetch_abort fault fsr:0x5, far:0x00000000
Translation fault, section
excType: prefetch abort
processName       = shell
processID         = 3
process aspace    = 0x01000000 -> 0x3f000000
taskName          = shell
taskID            = 4
task user stack   = 0x3707d000 -> 0x3717d000
pc    = 0x0 
ulr   = 0x2000424 in /bin/shell ---> 0x424
usp   = 0x3717cd60fp    = 0x3717cd64
R0    = 0x1
R1    = 0x0
R2    = 0x0
R3    = 0x1
R4    = 0x3717cf58
R5    = 0x0
R6    = 0x3717cf54
R7    = 0x200043c
R8    = 0x84
R9    = 0x229a7560
R10   = 0x0
R11   = 0x3717cd64
R12   = 0x0
CPSR  = 0x40000030
*******backtrace begin*******
traceback 0 -- lr = 0x229123a4    fp = 0x0 lr in /lib/libc.so --> 0x213a4

  PID  PPID PGID       UID  Status CPUUSE CPUUSE10s CPUUSE1s Policy Priority MTID TaskTotal   Mode  PName
    1    -1    1         0   Ready    0.0       0.0      0.0     RR       28   16         1   user  init                            
    2    -1    2         0    Pend   10.1      10.1      0.0     RR        0    0        14 kernel  KProcess                        
    3     1    3         0 Running    0.0       0.0      0.0     RR       28    4         1   user  shell                           

  TID  PID      Status StackSize WaterLine Policy Priority    MEMUSE  TaskName
   16    1       Ready    0x3000     0x978     RR       31    0x8b0c  init                            
    0    2        Pend    0x1000     0x1d4     RR        5         0  ResourcesTask                   
    2    2        Pend    0x4000     0x4ec     RR        0         0  Swt_Task                        
    3    2        Pend    0x4000     0x1d4     RR        1         0  system_wq                       
    5    2        Pend    0x4000     0x1fc     RR        9         0  SendToSer                       
    6    2    PendTime    0x6000     0x204     RR        5         0  tcpip_thread                    
    7    2        Pend    0x3000     0x1fc     RR        5         0  sdmci_detect                    
    8    2        Pend    0x4000     0x204     RR        5         0  USB_GIANT_Task                  
    9    2        Pend    0x4000     0x204     RR        1         0  USB_NGIAN_ISOC_Task             
   10    2        Pend    0x4000     0x204     RR        2         0  USB_NGIAN_BULK_Task             
   11    2        Pend    0x4000     0x690     RR        5     0xbb0  USB_EXPLR_Task                  
   12    2        Pend    0x4000     0x204     RR        5         0  USB_CXFER_Task                  
   13    2        Pend   0x20000     0x1e4     RR        3    0xac20  eth_irq_Task                    
   14    2        Pend    0x4000     0x1d4     RR       10         0  jffs2_gc_thread                 
   15    2        Pend    0x2000     0x1f4     RR        4         0  hisi_frw                        
    4    3     Running    0x3000     0x838     RR       31    0x1100  shell                           
system memcheck over, all passed!
```

The following information is included:

1.  Basic information about the user-mode exception:

```
prefetch_abort fault fsr:0x5, far:0x00000000
Translation fault, section
excType: prefetch abort
processName       = shell
processID         = 3
process aspace    = 0x01000000 -> 0x3f000000
taskName          = shell
taskID            = 4
task user stack   = 0x3707d000 -> 0x3717d000
```

1.  Register information:

```
pc    = 0x0 
ulr   = 0x2000424 in /bin/shell ---> 0x424
usp   = 0x3717cd60fp    = 0x3717cd64
R0    = 0x1
R1    = 0x0
R2    = 0x0
R3    = 0x1
R4    = 0x3717cf58
R5    = 0x0
R6    = 0x3717cf54
R7    = 0x200043c
R8    = 0x84
R9    = 0x229a7560
R10   = 0x0
R11   = 0x3717cd64
R12   = 0x0
CPSR  = 0x40000030
```

1.  Call stack information:

```
*******backtrace begin*******
traceback 0 -- lr = 0x229123a4    fp = 0x0 lr in /lib/libc.so --> 0x213a4
```

1.  Basic information about processes and threads:

```
  PID  PPID PGID       UID  Status CPUUSE CPUUSE10s CPUUSE1s Policy Priority MTID TaskTotal   Mode  PName
    1    -1    1         0   Ready    0.0       0.0      0.0     RR       28   16         1   user  init                            
    2    -1    2         0    Pend   10.1      10.1      0.0     RR        0    0        14 kernel  KProcess                        
    3     1    3         0 Running    0.0       0.0      0.0     RR       28    4         1   user  shell                           

  TID  PID      Status StackSize WaterLine Policy Priority    MEMUSE  TaskName
   16    1       Ready    0x3000     0x978     RR       31    0x8b0c  init                            
    0    2        Pend    0x1000     0x1d4     RR        5         0  ResourcesTask                   
    2    2        Pend    0x4000     0x4ec     RR        0         0  Swt_Task                        
    3    2        Pend    0x4000     0x1d4     RR        1         0  system_wq                       
    5    2        Pend    0x4000     0x1fc     RR        9         0  SendToSer                       
    6    2    PendTime    0x6000     0x204     RR        5         0  tcpip_thread                    
    7    2        Pend    0x3000     0x1fc     RR        5         0  sdmci_detect                    
    8    2        Pend    0x4000     0x204     RR        5         0  USB_GIANT_Task                  
    9    2        Pend    0x4000     0x204     RR        1         0  USB_NGIAN_ISOC_Task             
   10    2        Pend    0x4000     0x204     RR        2         0  USB_NGIAN_BULK_Task             
   11    2        Pend    0x4000     0x690     RR        5     0xbb0  USB_EXPLR_Task                  
   12    2        Pend    0x4000     0x204     RR        5         0  USB_CXFER_Task                  
   13    2        Pend   0x20000     0x1e4     RR        3    0xac20  eth_irq_Task                    
   14    2        Pend    0x4000     0x1d4     RR       10         0  jffs2_gc_thread                 
   15    2        Pend    0x2000     0x1f4     RR        4         0  hisi_frw                        
    4    3     Running    0x3000     0x838     RR       31    0x1100  shell                           
system memcheck over, all passed!
```

Based on the preceding information, you can analyze the causes of the user-space exception.

