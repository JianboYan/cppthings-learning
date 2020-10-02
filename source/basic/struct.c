//
//  struct.c
//  CPPTest
//
//  Created by Ryan on 2020/10/2.
//  Copyright © 2020 DR. All rights reserved.
//

#include <stdio.h>

/** C结构体总结：
 1. 不能将函数放在结构体声明
 2. 在C结构体声明中不能使用C++访问修饰符。（ private，protected，public）
 3. 在C中定义结构体变量，如果使用了下面定义必须加struct。
 4. 结构体不能继承（没有这一概念）。
 5. 若结构体的名字与函数名相同，可以正常运行且正常的调用！    
 */

struct Base {            // public
    int v1;
//    public:      //error
        int v2;
    //private:
        int v3;
//    void print(){       // c中不能在结构体中嵌入函数
//        printf("%s\n","hello world");
//    };    //error!
};

void Base(){ // 函数可以与结构体“同名”，因为C中结构体需要带上struct来声明变量，所以并不算重名，
    printf("%s\n","I am Base func");
}

//typedef struct Base Base; // 如果struct Base被typedef为Base了，下面的函数定义就会报错：Redefinition of 'Base' as different kind of symbol

struct Base base1;  //ok
//Base base2; //error
int MAIN() {
    base1.v1=1;
//    base.print();
    printf("%d\n",base1.v1);
    Base();
    return 0;
}
