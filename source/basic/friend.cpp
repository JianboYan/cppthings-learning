//
//  friend.cpp
//  CppThings
//
//  Created by Ryan on 2020/10/2.
//

#include <iostream>

namespace Friend {

using namespace std;
class C;

class A
{
public:
    A(int _a):a(_a){};
//    int getC(C &c){return c.c;} // todo
    friend int geta(A &ca);  ///< 友元函数
    friend class B;          ///< 友元类
private:
    int a;
};

int geta(A &ca)
{
    return ca.a;
}

class B
{
public:
    int getb(A ca) {
        return  ca.a;
    };
    friend class C;
};

class C: public B{
    int c;
public:
//    int getb(A ca) {
//        return ca.a;  // error: 'a' is a private member of 'Friend::A'
//    };
};



int MAIN_(friend)
{
    // 通过友元函数访问私有变量
    A a(3);
    cout<<geta(a)<<endl;
    
    // 通过友元类访问私有变量
    B b;
    cout<<b.getb(a)<<endl;
    
    // =======注意点=======
    
    // 1. 友元关系没有继承性，类C里的getb方法获取不到a的私有成员
    C c;
    cout<<c.getb(a)<<endl;
    
    // 2. 友元关系没有传递性，A 设置 B为友元，B设置C为友元，C还是不能访问A
    // TODO:

    return 0;
}
}
