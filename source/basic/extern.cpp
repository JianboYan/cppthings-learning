//
//  extern.cpp
//  CPPTest
//
//  Created by Ryan on 2020/10/1.
//  Copyright © 2020 DR. All rights reserved.
//

#include <iostream>

// 知识点:
// 由于C++支持方法重载，因此编译后的函数名其实会根据参数和返回值进行处理（mangling），所以C++调用C代码的时候如果告诉编译器不要对C的函数处理，那么就会找不到符号
// 所以在调用C方法时需要extern "C"

extern "C"{ // 去掉extern "C"会找不到符号
#include "c_source.h"

// mul方法放在extern "C" 外面C文件中会找不到符号
int mul(int a, int b){
    return a * b;
}
}


namespace Extern {
using namespace std;



void MAIN(){
    cout << add(1, 2) << endl;
    cout << mul(2, 2) << endl;
}

}
