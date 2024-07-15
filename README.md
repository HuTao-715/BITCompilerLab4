# BITCompilerLab4

BIT北理工 编译原理实验4 希冀平台



# 使用说明

下载CompilerLab4文件夹到不包含中文的路径，使用VScode打开。

采用任意方法cmake构建，例如，下载Cmake和Cmake Tool插件，ctrl+shift+P调出命令，选择Cmake：快速入门，选择从编译器创建并选择编译器，然后输入项目名称确定。点击控制台下方底边栏的运行按钮进行构建，然后ctrl+C结束运行。

找到exe程序所在位置

```cmd
cd out/build/Compiler #替换成自己的路径
```

将input.txt复制到同一个文件夹下，或者也可以自己创建任意名称的测试文件

通过控制台运行

```cmd
./Compilerlab4.exe input.txt
```

# 扩展源代码
该程序可以采用两种方式生成文法分析器：
第一种，运行时输入产生式。这种方式可以动态接受产生式输入，但是需要进行LR分析，耗时较长，可以在测试时使用。
产生式的格式：
+ 其中[non]代表非终结符，<ter>代表终结符，{act}代表语义动作；由于只做了简单的动作匹配，所以名字中的符号不要与后半括号相同。
+ act中同一个命令的参数用空格分隔，不同命令用分号分隔，不能处理换行符。
+ 具体的可以仿照gensLab4.txt中产生式
在如图Compiler.cpp中的Compiler::compile()中，将注释调整到如下状态，即接受输入+带参数的构造函数调用

![image](https://github.com/user-attachments/assets/385bc4d6-eed3-4e42-acfb-7a46ea22a1c9)

第二种，通过默认构造函数直接生成文法分析器，耗时较短，可以用来提交到平台。默认的构造函数代码可以由下面将要提到的第一种输出方式自动产生。
将注释调整到如下状态，即只有一个默认构造函数。

![image](https://github.com/user-attachments/assets/01d6b984-ae23-4e91-bc9c-02cd1b056246)


该程序可以产生两种输出：
第一种，输出上面提到的构造函数代码到工作目录下（exe所在）的initcode.txt中
需要取消以下两行代码注释

![image](https://github.com/user-attachments/assets/d14c3c50-8ce5-4a60-9577-cb841d3112a7)

第二种，接受简化C语言代码输入进行编译，需要恢复注释。

该程序的SDT的语义动作部分只实现了若干种，如果需要扩展，需要在SynAnalyzer::scan中添加新的if else自己实现命令解析

![image](https://github.com/user-attachments/assets/373fe1e8-bd58-49a6-bd97-41b75899e01e)

其中getTarget(root, cmd.args[i])->attrs[cmd.args[j]]的含义是命令第i个参数所代表的节点的，名为命令第j个参数的属性值所在的变量


