//
//  enum.cpp
//  CppThings
//
//  Created by Ryan on 2020/10/2.
//

#include <iostream>
using namespace std;

namespace TranditionalEnum {

//enum Color; // error: ISO C++ forbids forward references to 'enum' types

// 1.传统enum
// 1.1 enum 作用域不受限，很容易引起命名冲突
enum Color {RED,BLUE};
//enum Feeling {EXCITED,BLUE}; // error: Redefinition of enumerator 'BLUE'

int MAIN()
{
    // 1.2. enum会隐式转为int
    assert(Color::RED == 0); // pass
    
    // 1.3. 用来表征枚举变量的实际类型不能明确指定，从而无法支持枚举类型的前向声明（就是预先在定义未出现时的类型声明）。

    return 0;
}

}

namespace ClassicSolution{

// 在C中，为了避免冲突，一般都会选择加上前缀，如上面的例子修改为：
enum Feeling{
    Feeling_EXCITED,
    Feeling_BLUE,
};

// C++用命名空间来解决
namespace Color
{
    enum Type
    {
        RED=15,
        YELLOW,
        BLUE
    };
};

// 还可以用结构体全局常量来解决
const struct Color1
{
    enum Type
    {
        RED=102,
        YELLOW,
        BLUE
    };
}ColorDefine;

// C++11的枚举类
enum class Color2
{
    RED=2,
    YELLOW,
    BLUE
};

enum class Color3:char;  // 前向声明

enum class Color3:char
{
    RED='r',
    BLUE
};

int MAIN(){
    // 2.1. 命名空间解法
    Color::Type c = Color::RED;  // 可以忽略Type::
    c = Color::Type::YELLOW;
    assert(c == 16);
    
    // 2.2. 结构体解法
    assert(ColorDefine.RED == 102);
    assert(ColorDefine.YELLOW == 103);
//    ColorDefine.RED = 1; // error: Expression is not assignable
    
    // 2.3. 枚举类解法
    Color2 c2 = Color2::RED;
    CTLLOG_1(static_cast<int>(c2));
    
    char c3 = static_cast<char>(Color3::RED);
    CTLLOG_1(c3);
    
    
    // 3. 类中的枚举
    
    {
        // 原文说不能在类声明中初始化 const 数据成员，实际测试是可以的。
        class A{
        public:
            const int SIZE = 100;
        };
        A a;
        CTLLOG_1(a.SIZE); // a.SIZE is 100
        
        class Person{
        public:
            typedef enum {
                BOY = 0,
                GIRL
            }Gender;
        };
        
        Person p;
        CTLLOG_1(p.BOY); // p.BOY is 0

        CTLLOG_1(Person::GIRL); // Person::GIRL is 1
    }
    
    return 0;
}
}


