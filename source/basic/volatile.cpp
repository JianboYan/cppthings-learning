//
//  volatile.cpp
//  CPPTest
//
//  Created by Ryan on 2020/10/1.
//  Copyright © 2020 DR. All rights reserved.
//

#include <stdio.h>
#include <strings.h>
#include <iostream>

// 注意：切换编译器优化等级来对比汇编代码

using namespace std;

volatile const int vglobal = 10;

namespace Volatile {

// volatile的意思是让编译器每次操作该变量时一定要从内存中真正取出，而不是使用已经存在寄存器中的值。

volatile int  *output = ( int *)0xff800000; //定义一个IO端口；

int square(int *ptr)
{
    // movl   -0x14(%rbp), %esi  // 随时从内存里读取
    // imull  -0x14(%rbp), %esi
    return *ptr * *ptr;
    
    // 去掉volatile直接变为：
    // movl   $0x2710, %esi             ; imm = 0x2710 = 10000 // 直接编译器计算出来立即数赋值
}


int MAIN()
{
    int j = 100;
    
    CTLLOG_1(square(&j));
    
    int i;
    for(i=0;i< 10;i++)
    {
//        *output = i;
    }
    
    // 上面的代码在设置了编译器优化的情况下会把代码优化为（x86_64架构）：
//     pushq  %rbp
//     movq   %rsp, %rbp
//     movq   0x11c5(%rip), %rax        ; Volatile::output
//     movl   $0x9, (%rax)      // 直接复制为9
//     xorl   %eax, %eax
//     popq   %rbp
//     retq
    
    
    // 用volatile修饰output后会去掉对应优化，（x86_64架构）变为：
//     pushq  %rbp
//     movq   %rsp, %rbp
//     xorl   %eax, %eax            // i初始化为0
//     movq   0x11c3(%rip), %rcx    // output地址给rcx
//     movl   %eax, (%rcx)          // rcx地址的数据赋值为i // 代码地址->0x1000072ed
//     incl   %eax                  // i自增
//     cmpl   $0xa, %eax            // 和10进行比较
//     jne    0x1000072ed           // 不等于则跳回上面 代码地址->0x1000072ed
//     xorl   %eax, %eax
//     popq   %rbp
//     retq
    
    
    // 总结：
    // 1. volatile 关键字是一种类型修饰符，用它声明的类型变量表示可以被某些编译器未知的因素（操作系统、硬件、其它线程等）更改。所以使用 volatile 告诉编译器不应对这样的对象进行优化
    // 2. volatile 关键字声明的变量，每次访问时都必须从内存中取出值（没有被 volatile 修饰的变量，可能由于编译器的优化，从 CPU 寄存器中取值）
    // 3. const 可以是 volatile （如只读的状态寄存器）
    // 4. 指针可以是 volatile
    
    const volatile int local = 10;
    int *ptr = (int*) &local;
    
    int *vptr = (int*) &vglobal;

//    printf("Initial value of local : %d \n", local);
//    *ptr = 100;
//    *vptr = 100; // 在高优化下，直接被去掉了，低优化下直接因为访问只读数据崩溃，因此不太明白支持volatile const的意义所在
    printf("Modified value of local: %d \n", local);  // Modified value of local: 100

    printf("Modified value of global: %d \n", vglobal); // Modified value of local: 10

    
    return 0;
}
}
