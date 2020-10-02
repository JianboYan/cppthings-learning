//
//  virtual.cpp
//  CPPTest
//
//  Created by Ryan on 2020/10/1.
//  Copyright © 2020 DR. All rights reserved.
//

#include <iostream>

#if 1
#define VIRTUAL virtual
#else
#define VIRTUAL
#endif

namespace virtualDemo{
using namespace std;
class Employee
{
    public:
    int addition = 0;
    virtual void raiseSalary()
    {
        cout<<0 + addition<<endl;
    }

    virtual void promote(int addition = 20)
    { /* common promote code */
        Employee::addition += addition;
    }

    VIRTUAL ~Employee(){
        cout << "Decontruct Employee" << endl;
    }
};

class Manager: public Employee {
    virtual void raiseSalary()
    {
        cout<<100 + addition <<endl;
    }

    virtual void promote(int addition = 50)
    { /* Manager specific promote */
        Employee::addition += addition;
    }
    
    VIRTUAL ~Manager(){
        cout << "Decontruct Manager" << endl;
    }
};
class Engineer: public Employee {
    virtual void raiseSalary()
    {
        cout<<200+addition<<endl;
    }
    virtual void promote(int addition = 100)
    { /* Manager specific promote */
        Employee::addition += addition;
    }
public:
    // 即使类种析构函数并不是主动声明为虚析构，因为父类是虚析构，所以也还是会处理为虚析构
    ~Engineer(){
        cout << "Decontruct Engineer" << endl;
    }
};

class SoftwareEngineer: public Engineer {
    // 即使类种析构函数并不是主动声明为虚析构，因为父类是虚析构，所以也还是会处理为虚析构
    ~SoftwareEngineer(){
        cout << "Decontruct SoftwareEngineer" << endl;
    }
};

// Similarly, there may be other types of employees
// We need a very simple function to increment salary of all employees
// Note that emp[] is an array of pointers and actual pointed objects can
// be any type of employees. This function should ideally be in a class
// like Organization, we have made it global to keep things simple
void globalRaiseSalary(Employee *emp[], int n)
{
    for (int i = 0; i < n; i++)
        emp[i]->raiseSalary(); // Polymorphic Call: Calls raiseSalary()
    // according to the actual object, not
    // according to the type of pointer
}
int MAIN(){
    Employee *emp[]= {new Manager(),new Engineer};
    globalRaiseSalary(emp,2);
    
    // 虚函数是动态绑定的，默认参数是静态绑定的。默认参数的使用需要看指针或者应用本身的类型，而不是对象的类型！
    emp[0]->promote(); // 120，而不是150
    emp[1]->promote(); // 220，而不是300
    globalRaiseSalary(emp,2);

    ///======虚析构函数======
    // VIRTUAL宏为空的情况下，输出Decontruct Employee，
    // 否则输出：
    // Decontruct Manager
    // Decontruct Employee
    delete emp[0];

    // VIRTUAL宏为空的情况下，输出Decontruct Employee
    // 否则输出：
    // Decontruct Engineer
    // Decontruct Employee
    delete emp[1];
    
    // VIRTUAL宏为空的情况下，输出Decontruct Employee
    // 否则输出
    // Decontruct SoftwareEngineer
    // Decontruct Engineer
    // Decontruct Employee
    Employee *se = new SoftwareEngineer;
    delete se;
    
    
    return 0;
}
}

namespace VirtualFunction {
using namespace std;
class Base {
    private:
        virtual void fun() { cout << "Base Fun" << endl; }
        friend int main_138();// MAIN的行号
};

class Derived: public Base {
    public:
    void fun() { cout << "Derived Fun" << endl; }
};



int MAIN(){
    Base *b = new Derived;
    b->fun(); // Base的fun函数是私有的，main无法访问，需要把MAIN声明为友元，注意根据MAIN所在的行号修改友元函数名
    
    return 0;
}
}

#if 0
class VirtualError {
public:
    virtual static void func1(){
        // 静态函数不可以声明为虚函数，同时也不能被const 和 volatile关键字修饰:
        // 1. static成员函数不属于任何类对象或类实例，所以即使给此函数加上virutal也是没有任何意义
        // 2. 虚函数依靠vptr和vtable来处理,vptr是一个指针，在类的构造函数中创建生成，并且只能用this指针来访问它，静态成员函数没有this指针，所以无法访问vptr。
    }
    
    virtual VirtualError(){
        // 构造函数不可以声明为虚函数。同时除了inline|explicit之外，构造函数不允许使用其它任何关键字。
        // 尽管虚函数表vtable是在编译阶段就已经建立的，但指向虚函数表的指针vptr是在运行阶段实例化对象时才产生的。
        // 如果类含有虚函数，编译器会在构造函数中添加代码来创建vptr。
        // 而且构造函数声明为虚函数没有任何意义，构造函数的调用必须是确定类型
    }
    
    
};
#endif
