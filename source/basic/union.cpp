//
//  union.cpp
//  CppThings
//
//  Created by Ryan on 2020/10/2.
//

#include <iostream>

/**
 联合（union）是一种节省空间的特殊的类，一个 union 可以有多个数据成员，但是在任意时刻只有一个数据成员可以有值。当某个成员被赋值后其他成员变为未定义状态。联合有如下特点：
 1. 默认访问控制符为 public
 2. 可以含有构造函数、析构函数
 3. 不能含有引用类型的成员
 4. 不能继承自其他类，不能作为基类
 5. 不能含有虚函数
 6. 匿名 union 在定义所在作用域可直接访问 union 成员
 7. 匿名 union 不能包含 protected 成员或 private 成员
 8. 全局匿名联合必须是静态（static）的
 */
namespace Union {
using namespace std;

union UnionDemo {
    int a;
    UnionDemo(){}
    ~UnionDemo(){}
    double d;
    long *pl;
//    char &b; // error: Union member 'b' has reference type 'char &'
//    virtual void vfunc(){} // error: Unions cannot have virtual functions，不能继承，virtual就没有含义了
    void func(){} // 联合体可以有函数
};

UnionDemo ud;

//union UnionDemo2 : UnionDemo{}; // error: Unions cannot have base classes

struct StructUnion{
    int a;
    union{
        int b;
        long c;
//        void ufun(){ // error: Functions cannot be declared in an anonymous union，匿名联合体不能有函数
//            cout << f << endl;
//        }
//    private: // error: Anonymous union cannot contain a private data member，一旦private，就谁都访问不到了
        float f;
    };
    void func(){
        CTLLOG_1(f);
    }
    double d;
};

int MAIN(){
    
    StructUnion su;
    su.func();
    su.b = 4;
    CTLLOG_1(su.c);
    
    su.func();
    
    
    return 0;
}
}

