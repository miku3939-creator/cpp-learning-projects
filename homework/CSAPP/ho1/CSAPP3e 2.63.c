/*CSAPP3e 2.63

【题目内容】

将下面的 C 函数代码补充完整。函数 srl 用算术右移(由值 xsra 给出)来完成逻辑右移，后面的其他操作不包括右移或者除法。函数 sra 用逻辑右移(由值 xsrl 给出)来完成算术右移，后面的其他操作不包括右移或者除法。注意，可以通过计算 sizeof(int) << 3 来确定数据类型 int 的位数 w，位移量 k 的取值范围为 0~w-1 。

【提交形式】

提交 .c 文件。

unsigned srl(unsigned x, int k) {

    Perform shift arithmetically 

    unsigned xsra = (int) x >> k ;

   // 补全代码







}



int sra(int x, int k) {

    Perform shift logically 

    int xsrl = (unsigned) x >> k ;

    // 补全代码







}

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
unsigned srl(unsigned x, int k)
{

    /* Perform shift arithmetically */

    unsigned xsra = (int)x >> k;

    // 补全代码
    int w = sizeof(int) << 3;
    int n = ~0;
    n = n << (w - k);
    n = ~n;
    return xsra & n;
}

int sra(int x, int k)
{

    /* Perform shift logically */

    int xsrl = (unsigned)x >> k;

    // 补全代码
    int w = sizeof(int) << 3;
    int n = ~0;
    n = n << (w - k);
    int m=1<<(w-1);
    m=(!(m&x))-1;
    n=n&m;
    return xsrl | n;
}