//
//  assert.cpp
//  CPPTest
//
//  Created by Ryan on 2020/10/1.
//  Copyright © 2020 DR. All rights reserved.
//

#define NDEBUG // <---- 断言杀手，必须在最前面

#include <iostream>

int MAIN(){
    
    int x = 7;

    /*  Some big code in between and let's say x
    is accidentally changed to 9  */
    x = 9;

    // Programmer assumes x to be 7 in rest of the code
    assert(x==7); // signal: SIGABRT

    /* Rest of the code */
    
    /*
     开头有NDEBUG的宏则断言不生效，否则输出：
     Assertion failed: (x==7), function assert1, file /Users/uc/Documents/workspace/exprimentalC/CPPTest/CPPTest/assert.cpp, line 19.
     */
    
    return 0;
}
