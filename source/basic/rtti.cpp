//
//  rtti.cpp
//  CPPTest
//
//  Created by Ryan on 2020/10/1.
//  Copyright © 2020 DR. All rights reserved.
//

#include <stdio.h>
#include<iostream>
#include<typeinfo>

using namespace std;
class B { virtual void fun() {} };
class D: public B { };
class C{ };

int MAIN()
{
    B *b = new D;  // 向上转型
    B &obj = *b;
    D *d = dynamic_cast<D*>(b);   // 向下转型
    if(d != NULL) cout << "works"<<endl;
    else cout << "cannot cast B* to D*";
 
    C *c = dynamic_cast<C*>(b);   // 错误转型
    if (c != NULL) cout << "works"<<endl;
    else cout << "cannot cast B* to C*";
    
    // 引用的动态转型需要try-catch
    try {
        __unused D& dobj = dynamic_cast<D&>(obj);
        cout << "works"<<endl;
        
    } catch (bad_cast bc) { // ERROR
        cout<<bc.what()<<endl;
    }
    
    try {
        __unused C& dobj = dynamic_cast<C&>(obj);
        cout << "works"<<endl;
    } catch (bad_cast bc) { // ERROR
        cout<<bc.what()<<endl;
    }
    
//    B *b = dynamic_cast<B*>(c);  // c不是多态类型，编译报错，C或其父类必须有虚函数
//    __unused D& dobj = dynamic_cast<D&>(*c); // c不是多态类型，编译报错，C或其父类必须有虚函数
    
    
    return 0;
}
