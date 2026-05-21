/*【题目内容】

你刚刚开始在一家公司工作，他们要实现一组过程来操作一个数据结构，要将 4 个有符号字节封装成一个 32 位unsigned。一个字中的字节从 0 (最低有效字节)编号到 3 (最高有效字节)。分配给你的任务是:为一个使用补码运算和算术右移的机器编写一个具有如下原型的函数:

Declaration of data type where 4 bytes are packed into an unsigned 

typedef unsigned packed_t;



 Extract byte from word. Return as signed integer 

int xbyte(packed_t word, int bytenum);



也就是说，函数会从 32 位 unsigned 中抽取出指定的字节，再把它符号扩展为一个 32 位 int。

你的前任(因为水平不够高而被解雇了)编写了下面的代码:



 Failed attempt at xbyte 

int xbyte(packed_t word, int bytenum) {

    return (word >> (bytenum << 3)) & 0xFF;

}

给出函数的正确实现，只能使用左右移位、最多一个减法和强制类型转换。

【提交形式】

提交 .c 文件。

【位级整数编码规则】

在本章作业中，我们特意限制了你能使用的编程结构，来帮你更好地理解 C 语言的位级、逻辑和算术运算。在回答这些问题时，你的代码必须遵守以下规则：

假设：

- 整数用补码形式表示；

- 有符号数的右移是算术右移；

- 数据类型 int 是 w 位长的。对于某些题目，会给定 w 的值，但是在其他情况下，只要 w 是 8 的整数倍，你的代码就应该能工作。你可以用表达式 sizeof(int) << 3 来计算 w。

禁止使用：

- 条件语句（if 或者 ?:）、循环、分支语句、函数调用和宏调用；

- 除法、模运算和乘法；

- 相对比较运算（>、<、≤ 和 ≥）。

-  int 、unsigned 和 unsigned int 以外的数据类型（包括但不限于 char、long）。


允许的运算：

- 所有的位级和逻辑运算；

- 左移和右移，但是位移量只能在 0 到 w−1 之间；

- 加法和减法；

- 相等（==）和不等（!=）测试。（在有些题目中，也不允许这些运算）；

- 整型常数 INT_MAX 和 INT_MIN；

- 对 int 和 unsigned int 进行强制类型转换，无论是显式的还是隐式的。*/

/* Declaration of data type where 4 bytes are packed into an unsigned */

typedef unsigned packed_t;

/* Extract byte from word. Return as signed integer */

int xbyte(packed_t word, int bytenum)
{
   
return (((int)(word >>(bytenum<<3))<<24)>>24);

}