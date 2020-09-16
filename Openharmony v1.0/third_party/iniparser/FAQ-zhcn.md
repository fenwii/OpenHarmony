# iniparser FAQ #

## iniparser线程安全吗 ?

从版本4开始，iniparser被设计成线程安全的，你需要围绕它处理你自己的互斥逻辑。
选择不在库中添加线程安全，是为开发者提供更多的自由，特别是在处理他们自己的读
逻辑。如获取互斥锁，用iniparser阅读条目，然后释放互斥体。

## 你的构建系统不可移植，让我来帮助你...

我们已经收到了来各地的开发人员的无数贡献，将Makefile修改为他们认为是“标准”的
内容，但是我们不得不拒绝。 默认情况下，Debian的标准Makefile与SuSE或RedHat完
全没有关系，没有可能的方式将它们全部合并。 构建系统对于每个环境来说都是特别的，
尝试推动任何声称是标准的东西是完全没有意义的。 在这个项目中提供的Makefile纯粹
是为了快速的把库跑起来。

## iniparser_dump() 速度慢

dump函数是基于fprintf的，在嵌入式平台上它可能导致很慢。你可以把fprintf换成
sprintf和fwrite的组合，或者可以使用setvbfu()来改变fprintf的缓存参数。比如：

setvbuf(f, NULL, _IOFBF, 0);

## 用我的c++编译器不能编译iniparser!

看文档：iniparser是一个C库。虽然C++兼容C，但它却是另外一门语言。让iniparser在
C++编译器下工作，会是一份繁重的工作。祝你好运！
