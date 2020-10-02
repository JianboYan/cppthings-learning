//
//  using.cpp
//  CppThings
//
//  Created by Ryan on 2020/10/2.
//

#include <iostream>
#include <vector>

// 1. 基础使用

using namespace std;
void func()
{
    cout<<"::func"<<endl;
}

namespace Using {
#define isNs1 1
//#define isGlobal 2

namespace ns1 {
    void func()
    {
        cout<<"ns1::func"<<endl;
    }
}

namespace ns2 {
#ifdef isNs1
using ns1::func;    /// ns1中的函数，访问最近的namespace
//using ::ns1::func;    /// 全局ns1中的函数
#elif isGlobal
    using ::func; /// 全局中的函数
#else
    void func()
    {
        cout<<"other::func"<<endl;
    }
#endif
}

int MAIN()
{
    
    
    /**
     * 这就是为什么在c++中使用了cmath而不是math.h头文件
     */
    ns2::func(); // 会根据当前环境定义宏的不同来调用不同命名空间下的func()函数
    
    
    // 2. 改变数据可见性
    {
        class Base{
        public:
            std::size_t size() const { return n;  }
        protected:
            std::size_t n;
        };
        class Derived : private Base {
        public:
            using Base::size; // 把private继承而来的数据重新开放为public
        protected:
            using Base::n;    // 把private继承而来的数据重新开放为protected
        };
        
        Derived derived;
        CTLLOG_1(derived.size());
    }
    
    
    
    // 3. 函数重载
    {
        class Base{
        public:
            void f(){ cout<<"f()"<<endl;
            }
            void f(int n){
                cout<<"Base::f(int)"<<endl;
            }
        };

        class Derived : private Base {
        public:
            using Base::f; // 使用using声明语句指定一个名字而不指定形参列表，可以把该函数的所有重载实例添加到派生类的作用域中
            void f(int n){ // 按需要重载函数
                cout<<"Derived::f(int)"<<endl;
            }
        };
        
        Derived d;
        d.f();
        d.f(1);
    }
    
    // 4. 取代typedef
    {
        typedef vector<int> V1;
        using V2 = vector<int>;
        V1 vec1 = V1();
        V2 vec2 = V2();
        vec1.push_back(1);
        vec1.push_back(2);
        
        vec2.push_back(2);
        vec2.push_back(4);
        
    }
    
    
    
    return 0;
}
}

