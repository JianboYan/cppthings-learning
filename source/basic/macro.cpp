//
//  macro.cpp
//  CppThings
//
//  Created by Ryan on 2020/10/2.
//

#include <iostream>

namespace Macro {
using namespace std;
// 1. 特殊符号：##、# 和 \
// ## 和 # 用法参考PrefixHeader.pch里即可，\ 为续行操作符，如：

#define CMP(a,b) if (a>b){\
cout << #a " > b" #b << endl;\
}else{\
cout << #a " <= " #b << endl;\
}

#define LOG_CMD(cmd) cout << cmd << endl;
void f1(){LOG_CMD(f1)}
void f2(){LOG_CMD(f2)}

int MAIN(){
    
    CMP(2,3)
    
    // 2. 使用宏可能出现的问题
    {
        
#define fun() f1();f2();
        if (2 > 3)
            fun() // 实际f2会一直被执行
            
#define fun2() {f1();f2();}
        if (2 > 3)
            fun2() // 可以规避掉错误执行f2
        
#define fun3() \
do{ \
f1();\
f2();\
}while(0);
        
        if (2 > 3)
            fun3() // f2 不会被错误执行到了
    }
    
    
    return 0;
    
}

// 2.2 使用goto来回收资源（不推荐）
void func(){
    int *p = (int *)malloc(sizeof(int));
    *p = 10;
    cout<<*p<<endl;
    int error=1;

    if(error)
        goto END;
    // dosomething
END:
    cout<<"free"<<endl;
    free(p);
}

// 2.2 修改为使用do-while
void func2(){
    int *p = (int *)malloc(sizeof(int));
    *p = 10;
    cout<<*p<<endl;
    do{
        int error=1;
        if(error)
            break;
        //dosomething
    }while(0);
    cout<<"free"<<endl;
    free(p);
}


// 2.3 使用do-while消除空宏警告
#define EMPTYMICRO do{}while(0)

// 2.4 定义单一的函数块来完成复杂的操作
// FIX: 时机上直接定义{}代码块就可以了
void MAIN(){
    int i = 2;
    
    {
        int i = 3;
        CTLLOG_1(i); // i is 3
    }
    CTLLOG_1(i); // i is 2
    
    
}
}
