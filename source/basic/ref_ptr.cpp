//
//  ref_ptr.cpp
//  CppThings
//
//  Created by Ryan on 2020/10/2.
//

#include <iostream>
#include <vector>

namespace RefPtr{
using namespace std;

// 1. 指针与引用的区别
// 1.1. 定义初始化
//    int &ri; // error: Declaration of reference variable 'ri' requires an initializer
int i;
int &ri = i; // 定义必须初始化
int *pi; // 定义可以不初始化

// 1.2. 指针可以为空，引用不可以
void test_p(int* p)
{
    if(p != nullptr)    //对p所指对象赋值时需先判断p是否为空指针
        *p = 3;
    return;
}

void test_r(int& r)
{
    r = 3; //由于引用不能为空，所以此处无需判断r的有效性就可以对r直接赋值
    return;
}


int MAIN(){

    // 1.3. 引用不能更换目标
    int num = 1, count = 2;
    int &rn = num;
    rn = count; // 并不是重新修改引用到count，只是修改num的值为count的值
    CTLLOG_1(rn); // rn is 2
    CTLLOG_1(num); // num is 2
    rn = 3;
    CTLLOG_1(count); // count is 2
    CTLLOG_1(num); // num is 3
    
    return 0;
}

// 2. 引用定义
int MAIN(){
    // 2.1 左值引用: 常规引用，一般表示对象的身份
    // 2.2 右值引用：就是必须绑定到右值（一个临时对象、将要销毁的对象）的引用，一般表示对象的值
    //  2.2.1 右值引用可实现转移语义（Move Sementics）和精确传递（Perfect Forwarding）
    //  2.2.2 右值引用可以消除两个对象交互时不必要的对象拷贝，节省运算存储资源，提高效率
    //  2.2.3 右值引用能够更简洁明确地定义泛型函数
    int num = 2;
//    int &i = 1; // error: Non-const lvalue reference to type 'int' cannot bind to a temporary of type 'int'
    int &i = num;
//    int && ii = i; // error: Rvalue reference to type 'int' cannot bind to lvalue of type 'int'
    int &&ii = 2;
    ii = 3;
    
    CTLLOG_1(ii);// ii is 3。❓：说好的引用不能转换目标呢？
    
    
    // 2.3. 引用折叠
    // 2.3.1 X& &、X& &&、X&& & 可折叠成 X&
    // 2.3.2 X&& && 可折叠成 X&&
//    int& &ri = i; // error: 'ri' declared as a reference to a reference
    
    // TODO: 增加示例
    
    return 0;
}

// 2.4. 引用参数
void test(const vector<int> &data)
{
    
}



int MAIN()
{
    vector<int> data{1,2,3,4,5,6,7,8};
    test(data);
    
    // 2.5. 引用型返回值
    vector<int> v(10);
    v[5] = 10;    //[]操作符返回引用，然后vector对应元素才能被修改
                  //如果[]操作符不返回引用而是指针的话，赋值语句则需要这样写
//    *v[5] = 10;   //这种书写方式，完全不符合我们对[]调用的认知，容易产生误解 error: Indirection requires pointer operand ('std::__1::__vector_base<int, std::__1::allocator<int> >::value_type' (aka 'int') invalid)
    
    return 0;
}

// 3. 指针与引用的性能差距
// 结论：使用引用和指针生成的汇编代码完全一样，所以其实引用就是指针的一种简便使用，这点从debug状态下，引用的值为指向对象的地址就可以看出来
// 多说一句，空指针的发明是一个价值10亿美元的糟糕设计，引用算是对指针里会出现空指针的一种设计完善。

}




