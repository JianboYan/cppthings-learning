//
//  struct.cpp
//  CPPTest
//
//  Created by Ryan on 2020/10/2.
//  Copyright © 2020 DR. All rights reserved.
//

#include <iostream>

/** C++结构体总结：
 1. 能将函数放在结构体声明
 2. public、protected、private 在C++结构体中可以使用。
 3. 可以不加struct定义变量。
 4. 可以继承。
 5. 若结构体的名字与函数名相同，使用结构体，只能使用带struct定义！
 */

namespace Struct{
using namespace std;
struct Base {
    int v1;      // 默认public
//    private:   // 本行注释开启后，下面的使用会无法访问到v3报错
        int v3;
    public:     //显示声明public
        int v2;
    void print(){
        printf("%s\n","hello world");
    };
};

//void Base(){ //函数可以与结构体“同名”，C++中结构体可以不带上struct来声明变量，如果函数重名了，那就必须带上struct
//    printf("%s\n","I am Base func");
//}

struct Derived:Base {

    public:
        int v2;
    void print(){
        printf("%s\n","Derived");
    };
};

int MAIN() {
    __unused struct Base base1;  //ok
    __unused Base base2; //ok
    Base base;
    base.v1=1;
    base.v3=2;
    base.print();
    printf("%d\n",base.v1);
    printf("%d\n",base.v3);
    
    
    Derived d;
    d.v1 = 1;
    d.v2 = 2;
    d.Base::v2 = 4; // 访问重名变量
    d.v3 = 3;
    
    cout << d.v1 << " " << d.v2 << " " << d.Base::v2 << " " << d.v3 << endl;
    return 0;
}

}



