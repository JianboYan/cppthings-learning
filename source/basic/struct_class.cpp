//
//  struct_class.cpp
//  CppThings
//
//  Created by Ryan on 2020/10/2.
//

#include <stdio.h>

/**
 struct 与 class 的区别：
 总的来说，struct 更适合看成是一个数据结构的实现体，class 更适合看成是一个对象的实现体
 1. struct 作为数据结构的实现体，它默认的数据访问控制是 public 的，而 class 作为对象的实现体，它默认的成员变量访问控制是 private 的。
 2. 默认的继承访问权限。struct 是 public 的，class 是 private 的。
 3. struct默认可以使用大括号初始化，class不行。
 
 */
namespace StructClass {
struct StructBase{
    int a;
    void func(){}
};
struct StructDerived : StructBase{};

class ClassBase{
    int a;
};

class ClassBase2{
public:
    int a2;
};

class ClassDerived : ClassBase, ClassBase2{
};


int MAIN(){
    
    StructBase sb = {1};
    
    StructDerived sd;
    sd.a = 1; // 默认是public继承
    
//    ClassBase cb = {1}; // error: No matching constructor for initialization of 'StructClass::ClassBase'
//    cb.a = 1; // error: 'a' is a private member of 'StructClass::ClassBase'
    
    ClassDerived cd;
//    cd.a2 = 1; // error: 'a2' is a private member of 'StructClass::ClassBase2', 默认是private继承
    
    
    return 0;
}
}
