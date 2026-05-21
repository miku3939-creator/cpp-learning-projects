//<phase_6>:
  4010e8:       41 56                   push   %r14
  4010ea:       41 55                   push   %r13
  4010ec:       41 54                   push   %r12
  4010ee:       55                      push   %rbp
  4010ef:       53                      push   %rbx//存寄存器
  4010f0:       48 83 ec 50             sub    $0x50,%rsp//开栈空间
  4010f4:       4c 8d 6c 24 30          lea    0x30(%rsp),%r13
  4010f9:       4c 89 ee                mov    %r13,%rsi
  4010fc:       e8 fe 04 00 00          call   4015ff <read_six_numbers>
  401101:       4d 89 ee                mov    %r13,%r14
  401104:       41 bc 00 00 00 00       mov    $0x0,%r12d//i=0;
  40110a:       4c 89 ed                mov    %r13,%rbp//栈帧指针调整//大循环
  40110d:       41 8b 45 00             mov    0x0(%r13),%eax//栈底数
  401111:       83 e8 01                sub    $0x1,%eax
  401114:       83 f8 05                cmp    $0x5,%eax
  401117:       76 05                   jbe    40111e <phase_6+0x36>
  401119:       e8 ab 04 00 00          call   4015c9 <explode_bomb>//数大于6爆炸
  40111e:       41 83 c4 01             add    $0x1,%r12d//i++；第一次i=1;
  401122:       41 83 fc 06             cmp    $0x6,%r12d
  401126:       74 22                   je     40114a <phase_6+0x62>//i==6结束循环
  401128:       44 89 e3                mov    %r12d,%ebx
  40112b:       48 63 c3                movslq %ebx,%rax//小循环
  40112e:       8b 44 84 30             mov    0x30(%rsp,%rax,4),%eax//eax=栈顶+4i+30,即栈底向上第i个数
  401132:       39 45 00                cmp    %eax,0x0(%rbp)
  401135:       75 05                   jne    40113c <phase_6+0x54>
  401137:       e8 8d 04 00 00          call   4015c9 <explode_bomb>//eax=栈底，爆炸
  40113c:       83 c3 01                add    $0x1,%ebx//i+1;
  40113f:       83 fb 05                cmp    $0x5,%ebx
  401142:       7e e7                   jle    40112b <phase_6+0x43>//i<=5;继续循环;
  401144:       49 83 c5 04             add    $0x4,%r13//i=6
  401148:       eb c0                   jmp    40110a <phase_6+0x22>//栈底向下一个int,外循环;
  40114a:       48 8d 74 24 48          lea    0x48(%rsp),%rsi
  40114f:       4c 89 f0                mov    %r14,%rax//前一个栈帧
  401152:       b9 07 00 00 00          mov    $0x7,%ecx
  401157:       89 ca                   mov    %ecx,%edx//循环三
  401159:       2b 10                   sub    (%rax),%edx 
  40115b:       89 10                   mov    %edx,(%rax)//7-栈底数
  40115d:       48 83 c0 04             add    $0x4,%rax//11-栈底数
  401161:       48 39 f0                cmp    %rsi,%rax//if 0x48+%rsp！=11-栈底数
  401164:       75 f1                   jne    401157 <phase_6+0x6f>//跳 j1

  401166:       be 00 00 00 00          mov    $0x0,%esi//else 相等
  40116b:       eb 20                   jmp    40118d <phase_6+0xa5>// j1

  40116d:       48 8b 52 08             mov    0x8(%rdx),%rdx// j6:
  401171:       83 c0 01                add    $0x1,%eax
  401174:       39 c8                   cmp    %ecx,%eax 
  401176:       75 f5                   jne    40116d <phase_6+0x85>//if eax+1！=ecx j2
  401178:       eb 05                   jmp    40117f <phase_6+0x97>//else j7

  40117a:       ba f0 42 60 00          mov    $0x6042f0,%edx//j2 ：
  40117f:       48 89 14 74             mov    %rdx,(%rsp,%rsi,2)// j7 : *(rsp+rsi*2 )=$0x6042f0,
  401183:       48 83 c6 04             add    $0x4,%rsi//rsi+=4;
  401187:       48 83 fe 18             cmp    $0x18,%rsi//if rsi==0x18 j3
  40118b:       74 15                   je     4011a2 <phase_6+0xba>

  40118d:       8b 4c 34 30             mov    0x30(%rsp,%rsi,1),%ecx//  j1 : =*(0x48+%rsp+%rsp+0x30)
  401191:       83 f9 01                cmp    $0x1,%ecx//if ecx<1
  401194:       7e e4                   jle    40117a <phase_6+0x92>// j2

  401196:       b8 01 00 00 00          mov    $0x1,%eax//else ecx>1
  40119b:       ba f0 42 60 00          mov    $0x6042f0,%edx //edx=$0x042f0
  4011a0:       eb cb                   jmp    40116d <phase_6+0x85>//j6

  4011a2:       48 8b 1c 24             mov    (%rsp),%rbx// j3 : 
  4011a6:       48 8d 44 24 08          lea    0x8(%rsp),%rax
  4011ab:       48 8d 74 24 30          lea    0x30(%rsp),%rsi
  4011b0:       48 89 d9                mov    %rbx,%rcx

  4011b3:       48 8b 10                mov    (%rax),%rdx//j5:
  4011b6:       48 89 51 08             mov    %rdx,0x8(%rcx)
  4011ba:       48 83 c0 08             add    $0x8,%rax
  4011be:       48 39 f0                cmp    %rsi,%rax//if rsp+10==rsp+30
  4011c1:       74 05                   je     4011c8 <phase_6+0xe0>// j4

  4011c3:       48 89 d1                mov    %rdx,%rcx//else rcx=rsp+8
  4011c6:       eb eb                   jmp    4011b3 <phase_6+0xcb>//j5

  4011c8:       48 c7 42 08 00 00 00    movq   $0x0,0x8(%rdx)// j4 : *(rsp+0x10)=0;
  4011cf:       00
  4011d0:       bd 05 00 00 00          mov    $0x5,%ebp
  
  4011d5:       48 8b 43 08             mov    0x8(%rbx),%rax//j9:
  4011d9:       8b 00                   mov    (%rax),%eax
  4011db:       39 03                   cmp    %eax,(%rbx)
  4011dd:       7d 05                   jge    4011e4 <phase_6+0xfc>//if*(rbx)>*(rbx+8) j8

  4011df:       e8 e5 03 00 00          call   4015c9 <explode_bomb>
  4011e4:       48 8b 5b 08             mov    0x8(%rbx),%rbx//j8 :
  4011e8:       83 ed 01                sub    $0x1,%ebp
  4011eb:       75 e8                   jne    4011d5 <phase_6+0xed>//ebp!=1 j9
  4011ed:       48 83 c4 50             add    $0x50,%rsp
  4011f1:       5b                      pop    %rbx
  4011f2:       5d                      pop    %rbp
  4011f3:       41 5c                   pop    %r12
  4011f5:       41 5d                   pop    %r13
  4011f7:       41 5e                   pop    %r14
  4011f9:       c3                      ret