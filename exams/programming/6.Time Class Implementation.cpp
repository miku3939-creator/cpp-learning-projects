/*【问题描述】
编写一个程序，定义一个时间类Time，包含三个属性： hour, minute 和 second
要求通过运算符重载实现如下功能:
时间输入输出(>>、<<)；
时间增加减少若干(+=、-=)，例：Time& operator+=(const Time&);Time& operator-=(const Time&)；
时间前、后自增加/减少1秒(++、--)，前自增例：Time& operator++(); 后自增例：Time operator++(int)；
【输入形式】
输入固定为两个Time实例(time1，time2),每个实例占一行；
Time实例输入格式为：hour minute second。
【输出形式】
Time实例输出格式为：hour:minute:second；
每个输出实例占一行。
依次输出以下表达式的值
time1 += (time2++)
time1 -= time2
++time2
time2 += (time1--)
--time1
time2 -= time1
【样例输入】
21 10 35
10 15 25
【样例输出】
07:26:00
21:10:34
10:15:27
07:26:01
21:10:32
10:15:29
【样例说明】
不要显示多余的提示信息，避免输出判定错误。
输出结束后不要输出任何内容，包括空格和换行。
注意判断输出信息是否符合要求。*/