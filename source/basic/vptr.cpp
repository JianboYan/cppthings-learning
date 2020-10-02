//
//  vptr.cpp
//  CPPTest
//
//  Created by Ryan on 2020/10/1.
//  Copyright © 2020 DR. All rights reserved.
//

#include <stdio.h>
#include <iostream>
namespace vptr{

using namespace std;

/**
 * @brief 函数指针
 */
typedef void (*Fun)();

/**
 * @brief 基类
 */
class Base
{
    public:
        Base(){};
        virtual void fun1()
        {
            cout << "Base::fun1()" << endl;
        }
        virtual void fun2()
        {
            cout << "Base::fun2()" << endl;
        }
        virtual void fun3(){
            cout << "Base::fun3()" << endl;
        }
        ~Base(){};
};

/**
 * @brief 派生类
 */
class Derived: public Base
{
    public:
        Derived(){};
        void fun1()
        {
            cout << "Derived::fun1()" << endl;
        }
        void fun2()
        {
            cout << "DerivedClass::fun2()" << endl;
        }
        ~Derived(){};
};
/**
 * @brief 获取vptr地址与func地址,vptr指向的是一块内存，这块内存存放的是虚函数地址，这块内存就是我们所说的虚表
 *
 * @param obj obj
 * @param offset offset
 *
 * @return ret
 */
Fun getAddr(void* obj,unsigned int offset)
{
    cout<<"======================="<<endl;
    void* vptr_addr = (void *)*(long *)obj;  //64位操作系统，占8字节，通过*(long *)obj取出前8字节，即vptr指针
    printf("vptr_addr:%p\n",vptr_addr);

    /**
     * @brief 通过vptr指针访问virtual table，因为虚表中每个元素(虚函数指针)在64位编译器下是8个字节，因此通过*(long *)vptr_addr取出前8字节，
     * 后面加上偏移量就是每个函数的地址！
     */
    void* func_addr = (void *)*((long *)vptr_addr+offset);
    printf("func_addr:%p\n",func_addr);
    return (Fun)func_addr;
}

int MAIN(){
    Base ptr;
    Derived d;
    Base *pt = new Derived(); // 基类指针指向派生类实例
    Base &pp = ptr; // 基类引用指向基类实例
    Base &p = d; // 基类引用指向派生类实例
    cout<<"基类对象直接调用"<<endl;
    ptr.fun1();
    cout<<"基类对象调用基类实例"<<endl;
    pp.fun1();
    cout<<"基类指针指向派生类实例并调用虚函数"<<endl;
    pt->fun1();
    cout<<"基类引用指向派生类实例并调用虚函数"<<endl;
    p.fun1();

    // 手动查找vptr 和 vtable
    Fun f1 = getAddr(pt, 0);
    (*f1)();
    Fun f2 = getAddr(pt, 1);
    (*f2)();
    
    Fun f3 = getAddr(pt, 2);
    (*f3)();
    
    // 对应的地址并不是可执行函数
//    Fun crash = getAddr(pt, 3);
//    (*crash)();
    
    delete pt;
    
    class Normal{
        void fun1(){cout << "Derived::fun1()" << endl;}
        void fun2(){cout << "DerivedClass::fun2()" << endl;}
    };
    // 如果不带虚函数，这么获取就崩溃
//    Normal n;
//    Fun fn = getAddr(&n, 0);
//    fn();
    
    return 0;
    
}
}
