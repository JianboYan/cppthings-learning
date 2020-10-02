//
//  double_colon.cpp
//  CppThings
//
//  Created by Ryan on 2020/10/2.
//

#include <iostream>

using namespace std;
// 全局namespace和局部namespace重名的情况
namespace ns1 {
    void func()
    {
        cout<<"ns1::func outter"<<endl;
    }
}

namespace DoubleColon {
// 全局namespace和局部namespace重名的情况
namespace ns1 {
    void func()
    {
        cout<<"ns1::func inner"<<endl;
    }
}

int MAIN(){
    // 函数在不同位置会影响结果，基本原则是就近原则
    ns1::func(); //  ns1::func inner
    
    ::ns1::func(); // ns1::func outter
    
    return 0;
}
}

int count=0;    // 全局(::)的count

class A {
public:
    static int count;  // 类A的count (A::count)

};
// 静态变量必须在此处定义
int A::count;

int MAIN(){
    // 重名namespace访问
    {
        ns1::func(); //  ns1::func outter
        ::ns1::func(); // ns1::func outter
    }
    
    // 用::指定访问区域
    {
        ::count = 1;  // 设置全局的count为1
        A::count = 5; // 设置类A的count为2
        CTLLOG_1(::count);
        CTLLOG_1(A::count);
        
        int count=3; // 局部count
        count=4;     // 设置局部的count为4
        CTLLOG_1(count);
    }
    
    
    return 0;
}
