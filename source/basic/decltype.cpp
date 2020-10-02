//
//  decltype.cpp
//  CppThings
//
//  Created by Ryan on 2020/10/2.
//

#include <iostream>
#include <vector>

namespace Decltype {
using namespace std;

int MAIN(){
    
    // 1. 基本使用
    // 1.1. 推导类型,类似typeof
    int a = 4;
    decltype(a) i = 2;
    CTLLOG_1(i);
    
    typeof(a) ti = 4;
    CTLLOG_1(ti);
    
    // 1.2 与using/typedef合用，用于定义类型
    using size_t = decltype(sizeof(0));//sizeof(a)的返回值为size_t类型
    __unused size_t s = 100;
    
    using ptrdiff_t = decltype((int*)0 - (int*)0);
    __unused ptrdiff_t p = 0;
    
    using nullptr_t = decltype(nullptr);
    __unused nullptr_t np = 0;
    
    vector<int >vec;
    typedef decltype(vec.begin()) vectype;
    vec.push_back(1);
    vec.push_back(2);
    for (vectype vt = vec.begin(); vt != vec.end(); vt ++){
        CTLLOG_1(*vt);
    }
    
    // 1.3 重用匿名类型
    {
        struct
        {
            int d ;
            double b;
        }as;
        
        as.d = 2;
        
        decltype(as) as2 ;//定义了一个上面匿名的结构体
        CTLLOG_1(as.d); // as.d is 2
        CTLLOG_1(as2.d); // as2.d is 0
    }
    
    return 0;
}

// 1.4 泛型编程中结合auto，用于追踪函数的返回值类型
template <typename T>
auto multiply(T x, T y)->decltype(x*y)
{
    return x*y;
}

}


namespace DecltypeRegulations {
using namespace std;
int MAIN(){
    // 2. 判别规则
    int arr[5] = { 0 };
    //规则一：推导为其类型
    decltype (arr) var1; //int 标记符表达式
        
    int *ptr = arr;
    decltype (ptr) var2;//int *  标记符表达式

    struct S{ double d; }s ;
    decltype(s.d) var3;//double 成员访问表达式
    
    void Overloaded(int);
    void Overloaded(char);//重载的函数
    //decltype(Overloaded) var4;//重载函数。编译错误。
    
    //规则二：将亡值。推导为类型的右值引用。 int&&
    int && RvalRef();
    decltype (RvalRef()) var5 = 1;

    //规则三：左值，推导为类型的引用。
    int i = 4;
    decltype ((i))var6 = i;     //int&, 注意是((i))
    var6 = 6;
    CTLLOG_1(i); // i is 6
    
    decltype (true ? i : i) var7 = i; //int&  条件表达式返回左值。
    var7 = 7;
    CTLLOG_1(i); // i is 7
    
    decltype (++i) var8 = i; //int&  ++i返回i的左值。
    var8 = 8;
    CTLLOG_1(i); // i is 8

    decltype(arr[5]) var9 = i;//int&. []操作返回左值
    var9 = 9;
    CTLLOG_1(i); // i is 9

    decltype(*ptr)var10 = i;//int& *操作返回左值
    var10 = 10;
    CTLLOG_1(i); // i is 10

    decltype("hello")var11 = "hello"; //const char(&)[9]  字符串字面常量为左值，且为const左值。
//    var11[0] = 'H'; // error: Cannot assign to variable 'var11' with const-qualified type 'decltype("hello")' (aka 'const char (&)[6]')

    //规则四：以上都不是，则推导为本类型
    decltype(1) var12; // FIX: const int ==> int
//    var12 = "hello"; // error: Assigning to 'decltype(1)' (aka 'int') from incompatible type 'const char [6]'
    

    const bool Func(int);
    decltype(Func(1)) var13=true;// FIX: const bool ==> bool
    var13 = false;

    decltype(i++) var14 = i;//int i++返回右值
    var14 = 14; //
    CTLLOG_1(i); // i is 10, 并不是饮用
    
    
    
    return 0;
}
}
