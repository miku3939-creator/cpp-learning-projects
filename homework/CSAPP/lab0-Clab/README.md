This is the handout directory for the C Lab.

************************
Updating your Makefile
************************

You will first need to fix Makefile before you can use the autograders.
You must update the rule for qtest to include the queue.o as a requirement
and use queue.o in the linking process.

************************
Running the autograders:
************************

Before running the autograders, compile(编译) your code to create the testing program qtest
    linux> make

Check the correctness of your code:
    linux> make test

******
Using qtest:
******

qtest provides a command interpreter that can create and manipulate queues.

Run ./qtest -h to see the list of command-line options

When you execute .qtest, it will give a command prompt "cmd>".  Type "help" to see a list of available commands


******
Files:
******

# You will handing in these two files
queue.h                 Modified version of declarations including new fields you want to introduce
queue.c                 Implementation of the queue methods

# Tools for evaluating your queue code
Makefile                Builds the evaluation program qtest
README                  This file
driver.py*              The C lab driver program, runs qtest on a standard set of traces

# Helper files

console.{c,h}:          Implements command-line interpreter for qtest
report.{c,h}:           Implements printing of information at different levels of verbosity
harness.{c,h}:          Customized version of malloc and free to provide rigorous testing framework
qtest.c                 Code for qtest

# Trace files

traces/trace-XX-CAT.cmd Trace files used by the driver.  These are input files for qtest.
                        They are short and simple.  We encourage to study them to see what tests are being performed.
                        XX is the trace number (1-14).  CAT describes the general nature of the test.

trace/trace-eg.cmd:     A simple, documented trace file to demonstrate the operation of qtest

更新你的 Makefile
你首先需要修复 Makefile，然后才能使用自动评分器。
你必须更新 qtest 的规则，将 queue.o 作为依赖项包含进来，并在链接过程中使用 queue.o。

运行自动评分器
在运行自动评分器之前，先编译你的代码以创建测试程序 qtest：

bash
linux> make
检查代码的正确性：

bash
linux> make test
使用 qtest
qtest 提供了一个命令解释器，可以创建和操作队列。

运行 ./qtest -h 查看命令行选项列表。

当你执行 ./qtest 时，它会显示命令提示符 cmd>。输入 help 查看可用命令列表。

文件说明
你需要提交的这两个文件：
queue.h：修改后的声明文件，包含你想要引入的新字段

queue.c：队列方法的实现

用于评估队列代码的工具：
Makefile：构建评估程序 qtest

README：本文件

driver.py*：C 实验驱动程序，在标准 trace 文件集上运行 qtest

辅助文件：
console.{c,h}：实现 qtest 的命令行解释器

report.{c,h}：实现不同详细级别下的信息打印

harness.{c,h}：定制的 malloc 和 free 版本，提供严格的测试框架

qtest.c：qtest 的代码

Trace 文件：
traces/trace-XX-CAT.cmd：驱动程序使用的 trace 文件。这些是 qtest 的输入文件。
它们短小简单。我们鼓励你研究它们，了解正在执行的测试内容。

XX 是 trace 编号（1-14）

CAT 描述测试的一般性质

traces/trace-eg.cmd：一个简单的、带有文档说明的 trace 文件，用于演示 qtest 的操作



