//
//  virtual.cpp
//  CPPTest
//
//  Created by Ryan on 2020/9/27.
//  Copyright © 2020 DR. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;
namespace abstractDemo{



class Interface1 {
public:
    virtual void f(){
        cout << "A:f" << endl;
    }; // 纯虚函数
    void g(){
        this->f();
    }
};

class Interface2 {
public:
    virtual void f(){
        cout << "A2:f" << endl;
    }; // 纯虚函数
};

class B : public Interface1, public Interface2{
    
};

class B1:public Interface1{
public:
    void f(){ cout<<"B:f()"<<endl;}
};


class Base  {
    
    public:
    int a;
        Base():a(1){
            cout << "Constructor: Base" << endl;
            
        }
        virtual ~Base()   {
            cout << "Destructor : Base" << endl;
            
        }
     void function(){
        cout << "Base: function" << endl;
    }
    virtual void virtual_function(){
        cout << "Base: virtual function" << endl;
    }
};

class Derived: public Base {
    public:
        int b;
        Derived()   {
            cout << "Constructor: Derived" << endl;
            
        }
        ~Derived()   {
            cout << "Destructor : Derived" << endl;
            
        }
    void function(){
        cout << "Derived: function" << endl;
        this->Base::function();
    }
    virtual void virtual_function(){
        cout << "Derived: function" << endl;
        this->Base::function();
    }
};


void MAIN(){
    auto a = new B();
    a->Interface1::f();
    a->Interface2::f();
    
    auto b = B1();
    b.g();
    
    Base *base = new Base();
    base->a = 2;
    Base *de = new Derived();
    de->a = 3;
    
    de->function();  // call base's funtion
    de->virtual_function();  // call derived's function
    
    cout << base->a << endl;
    cout << de->a << endl;
    
}
}
