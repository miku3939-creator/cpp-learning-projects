概要
本实验主要是锻炼你的编程能力。你需要熟练掌握C语言编程的基本技能，尤其是在本课程的后期实验中，你会发现本实验要求的这些技能会非常有用。这个实验主要检测以下这些技能：

显式内存管理

创建和操作基于指针的数据结构

实现输入无效参数也能正确运行的健壮代码，如 NULL 指针

在 Makefile 中创建规则

这个实验需要实现一个同时支持后进先出（LIFO）和先进先出（FIFO）的队列。提供的底层数据结构是一个单链表，你需要改进这些代码使一些操作更加高效。（如果你还不知道什么叫“单链表”，不用担心，网络上有无穷的有关单链表的说明，学会正确高效使用搜索引擎或是AI工具，你将受益无穷。）

试验初始文件
点击“实验数据”，再点击“一键载入实验容器”，clab-handout.tar将被导入目录 /mnt/cgshare。拷贝至你的工作目录，解开文件包：

cp /mnt/cgshare/clab-handout.tar ~/Desktop/
cd ~/Desktop/
linux > tar xvf clab-handout.tar
本实验以及后续的实验都需要在Linux平台上完成，对于Linux常用命令不熟悉的同学可以参考：
https://www.runoob.com/w3cnote/linux-common-command-2.html

底层数据结构
文件queue.h定义的结构如下：

/* Linked list element */
typedef struct ELE {
	int value;
	struct ELE *next;
} list_ele_t;

/* Queue structure */
typedef struct {
	list_ele_t *head; /* Linked list of elements */
} queue_t;
如Figure 1所示，代码要实现一个队列。队列的顶层表示是类型为queue_t的结构，在最初代码中，这个结构只包含一个字段“head”，你需要自行添加其他字段。队列被表示为单链表，其中每个元素由结构list_ele_t表示，该结构包含字段“value”和“next”，分别存储队列值和一个指向下一个元素的指针。尽管可以在不更改list_ele_t的情况下实现本实验要求的所有函数，但欢迎你对list_ele_t进行更改，例如将单链表转换为双链表。



在我们给你的C代码中，队列是一个类型为queue_t 的指针。 我们区分两种特殊情况：一个*NULL队列是指针设置为NULL的队列。 而一个空（empty）队列是一个指向一个有效的queue_t结构的队列，该queue_t结构的head字段被设置为NULL。除了能正确处理包含一个或多个元素的队列，你的代码还要能正确处理这两种情况。

编程任务
你的任务是修改queue.h和queue.c中的代码以实现以下功能：

q_new：创建一个新的空队列

q_free: 释放队列使用的所有存储空间

q_insert_head：在队列的头部插入新元素（LIFO）

q_insert_tail：在队列的尾部插入新元素（FIFO）

q_remove_head：从队列的头部删除一个元素

q_size: 计算队列中元素的个数

q_reverse：对列表重新排列，使得队列中元素的顺序都反转过来

更多细节可以在这两个文件的注释中找到，包括如何处理无效操作（例如，从空队列或NULL队列中移除元素），以及函数应该具有哪些副作用和返回值。

以下是关于如何实现这些功能的一些重要注意事项：

当q_new和q_insert_head需要动态分配内存时，使用malloc或calloc来实现（如果不熟悉这两个函数，可以在命令行中输入man malloc或man calloc来查阅手册；或者搜索引擎之）；

其中q_insert_tail 和 q_size需要满足时间复杂度为O(1)，即所需的时间与队列大小无关。你可以通过在queue_t数据结构中添加其他字段来实现此功能；

q_reverse的实现不需要分配额外的内存。你的代码应该修改现有链表中的指针。 在实现反向操作时，直接或间接调用malloc、calloc或free都视为错误；

测试代码会在超过1,000,000个元素的队列上对你的程序进行测试，所以不能使用递归函数来遍历这样的长列表，因为这需要太多的栈空间。（后续课程中，我们将深入学习这背后的原理，cool吧？）

Build
拿到初始的代码时，敲make命令并不会开始build你的代码：

linux> make
你需要修改用于构造qtest的Makefile文件，你要在build和链接过程中添加queue.o。有关Makefile规则的说明可以参考 Using make and writing Makefiles。

其中的“An example of building an executable from multiple .o files”部分对本作业很有帮助。正确的修改Makefile能使得在输入make命令时，如果 queue.o发生了变化，就重新生成qtest。

测试
如果你的Makefile书写正确，编译器将生成一个可执行程序qtest，提供一个命令界面，你可以使用该界面创建，修改和检查队列。 关于可用命令的文档可以通过启动该程序并运行help命令找到：

linux> ./qtest
cmd>help
以下文件（traces/trace-eg.cmd）演示了一个示例命令序列：

# Demonstration of queue testing framework
# Initial queue is NULL.
show
# Create empty queue
new
# Fill it with some values. First at the head
ih 2
ih 1
ih 3
# Now at the tail
it 5
it 1
# Reverse it
reverse
# See how long it is
size
# Delete queue. Goes back to a NULL queue.
free
# Exit program
quit
在批处理模式下运行qtest能看到这些命令的效果：

linux> ./qtest -f traces/trace-eg.cmd
在初始代码中很多操作都没有正确实现。

traces目录包含11个trace文件，其格式为trace-k-cat.txt，其中k是trace号，cat指明它测试的属性的类别。每个trace由一系列命令组成，与上面显示的相似，来测试程序的正确性、健壮性和性能的不同方面。你可以使用这些trace文件直接与qtest进行交互，测试和调试你的程序。

评价
评测阶段，我们会用15个trace文件对你的程序进行评估，除了已经发给你们的11个外，每种类型新增加一个trace（共4个）。每一个trace有一个分数值（6或7分不等），总计为100分(提供给你的11个trace总分为67分)。每执行正确一个结果获得相应的分数。程序driver.py在trace上运行qtest并计算分数。你可以在本地使用以下命令直接调用它：

linux> ./driver.py
或者

linux> make test
本地测试通过后，进行在线评测。将下面三个文件都拷贝到桌面上：

unix> cp Makefile queue.c queue.h ~/Desktop
然后点击“提交评测”，自动评测即可。


重要的文件建议保存在工作路径：/mnt/cgshare下，如果容器出现故障，桌面还原之后，点击 “更多” / “工作目录文件浏览器” 找回。

