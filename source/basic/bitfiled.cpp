//
//  bitfiled.cpp
//  CPPTest
//
//  Created by Ryan on 2020/10/1.
//  Copyright © 2020 DR. All rights reserved.
//

#include <iostream>

namespace bitfield {
using namespace std;

// 位域成员的类型，必须为 int、char、short、long
typedef struct _BitField {
    unsigned int code1: 2;
    unsigned int cdde2: 2;
    unsigned int code3: 8;
//    double s : 4; // error:Bit-field 's' has non-integral type 'double'
//    char *p : 8; // error: Bit-field 'p' has non-integral type 'char *'
}BitField;

typedef struct _BFAlign{
    unsigned int field1: 30; // 4B
    unsigned int field2: 4;  //
    unsigned int field3: 3;  //
}BFAlign;

// 由于30+4，导致filed2出现了跨2个unsinged int的位域，因此会会移位到下一个位域，被处理为：
typedef struct _BFAlign2{
    unsigned int field1: 30;
    unsigned int       : 2;  // 占位
    unsigned int field2: 4;
    unsigned int       : 0;  // 宽度为 0 的未命名位域成员令下一位域成员与下一个整数对齐
    unsigned int field3: 3;
}BFAlign2;

struct box {
    unsigned int ready:     2;
    unsigned int error:     2;
    unsigned int command:   4;
    unsigned int sector_no: 24;
    unsigned int second_filed: 24;
}b1;

union UnionData{
    struct box box;
    long data;
};

void MAIN(){
    
    // 位域结构体的大小计算
    cout << sizeof(BitField) << endl; // 4 Byte = (2 + 2 + 8) = 12bit，最少一个unsigned int大小
    
    cout << sizeof(BFAlign) << endl; // 8 Byte = (30 + padding:2 + 4 + 3 + align) = 32 + 32
    
    cout << sizeof(BFAlign2) << endl; // 12 = (30 + padding:2 + 32 + 32) = 12;
    
    
    // 位域的初始化
    
    BFAlign s = {20,8,6};
    s.field3 = 4;
    cout << s.field1 << " " << s.field2 << " " << s.field3 << endl; // 20 8 4
    
    // 利用重映射将位域归零（其实就是前面一段内存的数据被抹掉）
    b1.ready = 2;
    b1.error = 3;
    b1.command = 4;
    b1.sector_no = 1024;
    b1.second_filed = 1024;
    
    // 下方输出：2 3 4 1024 1024
    cout << b1.ready << " " << b1.error << " " << b1.command << " " << b1.sector_no << " " << b1.second_filed << endl;
    int *p = (int *)&b1;
    *p = 0; // 抹掉前面 sizeof(int)的数据
    
    // 下方输出：0 0 0 0 1024
    cout << b1.ready << " " << b1.error << " " << b1.command << " " << b1.sector_no << " " << b1.second_filed << endl;
    
    long *pl = (long *)&b1;
    *pl = 0; //抹掉前面 sizeof(long)的数据
    // 下方输出：0 0 0 0 0
    cout << b1.ready << " " << b1.error << " " << b1.command << " " << b1.sector_no << " " << b1.second_filed << endl;
    
    
    // 联合体
    UnionData ud;
    ud.box.ready = 2;
    ud.box.error = 3;
    ud.box.command = 4;
    ud.box.sector_no = 1024;
    ud.box.second_filed = 1024;
    
    cout << ud.data << endl; // 4398046773326
    
    ud.data = 1024;
    // 下发输出0 0 0 4 0
    cout << ud.box.ready << " " << ud.box.error << " " << ud.box.command << " " << ud.box.sector_no << " " << ud.box.second_filed << endl;
}
}
