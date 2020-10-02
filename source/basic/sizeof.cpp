//
//  sizeof.cpp
//  CPPTest
//
//  Created by Ryan on 2020/9/27.
//  Copyright © 2020 DR. All rights reserved.
//

#include <stdio.h>
#include<iostream>
using namespace std;
class EmptyClass{};

class MemberClass{
    char c;
    int i;
};

class MemberClass2{
    char c;
    int i;
    long l;
};

class StaticMemberClass
{
    public:
        char b;  // 8 （字节对齐）
        static int c; // 0
        static int d; // 0
        static int f; // 0
};

class VirtualFunctionClass{
    // 虚函数统一放在了vptr里
    virtual void fun();
    virtual void fun1();
    virtual void fun2();
    virtual void fun3();
};

class FunctionClass{
    void fun();
    void fun1();
    void fun2();
    void fun3();
};

class A
{
    public:
        char a;
        int b;
};

/**
 * @brief 此时B按照顺序：
 * char a
 * int b
 * short a
 * long b
 * 根据字节对齐4+4=8+8+8=24
 */
class B: public A
{
    public:
        short a;
        long b;
};
class C
{
    A a;
    char c;
};

class C1:public A
{
};

class C2:public A, public C
{
};


class VA
{
    virtual void fun() {}
};
class VB
{
    virtual void fun2() {}
};
class VC : virtual public  VA, virtual public VB
{
    public:
        virtual void fun3() {}
};


//
int MAIN()
{
    cout<<sizeof(EmptyClass)<<endl; // 1
    cout<<sizeof(MemberClass)<<endl; // 8 = 4(1+align:3) + 4
    cout<<sizeof(MemberClass2)<<endl; // 16 = 8(1+4+align:3) + 8
    cout<<sizeof(StaticMemberClass)<<endl; // 1 = 1 + 0 + 0 + 0
    cout<<sizeof(VirtualFunctionClass)<<endl; // 8 = vptr:8
    cout<<sizeof(FunctionClass)<<endl; // 1 = 1
    
    cout<<sizeof(A)<<endl; // 8 = 4(1+align:3)+4
    cout<<sizeof(B)<<endl; // 24 = 8 + 8(1:align:7) + 8
    cout<<sizeof(C)<<endl; // 12 = 4(1+align:3)+4+4(1+align:3)
    cout<<sizeof(C1)<<endl; // 8 = 8
    cout<<sizeof(C2)<<endl; // 20 = 8(A)+12(C)
    
    
    cout<<sizeof(VA)<<endl; // 8 = (8:vptr)
    cout<<sizeof(VB)<<endl; // 8 = (8:vptr)
    cout<<sizeof(VC)<<endl; // 16 = (8:vptr) + (8:vptr)
    
    
    return 0;
}
