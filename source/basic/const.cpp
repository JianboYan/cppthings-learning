//
//  const.cpp
//  CPPTest
//
//  Created by Ryan on 2020/9/27.
//  Copyright © 2020 DR. All rights reserved.
//

#include <iostream>

using namespace std;

extern const int ca = 1;
int ia;

class Apple
{
private:
    int people[100];
public:
    Apple(int i);
    static const int apple_number = 200;
    const int apple_type = 1;
    static int apple_s; //
    void take(int num) const;
    int add(int num);
    int add(int num) const;
    int getCount() const;

};
/// apple_numer有static修饰就可以在外部赋值了
//const int Apple::apple_number = 100;

// 不带const的static成员必须在外部初始化
int Apple::apple_s = 1;; // 注释这行，会导致下面的Apple::apple_s = 2;编译报错，找不到符号，也就是static修饰的符号必须在外部初始化出来

Apple::Apple(int i)
{
    Apple::apple_s = 2;
}
int Apple::add(int num){
    take(num);
    return num;
}
//int Apple::add(int num) const{
//    take(num);
//    return num;
//}
void Apple::take(int num) const
{
    cout<<"take func "<<num<<endl;
}
int Apple::getCount() const
{
    take(1);
//    add(1); //
    return apple_number;
}

int MAIN()
{
    Apple a(2);
    cout<<a.getCount()<<endl;
    a.add(10);
    CTLLOG_1(Apple::apple_number);
    CTLLOG_1(a.apple_type);
    CTLLOG_1(a.apple_number);
//    const Apple b(3);
//    b.add(100);
    return 0;
}
