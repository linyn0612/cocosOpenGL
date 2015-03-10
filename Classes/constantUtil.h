//
//  constantUtil.h
//  cocosOpenGL
//
//  Created by 林跃南 on 15/3/5.
//
//

#ifndef __cocosOpenGL__constantUtil__
#define __cocosOpenGL__constantUtil__

#include <stdio.h>
#include "cocos2d.h"

class Constant{
    
public:
    
    Constant();
    ~Constant();
public:
    
    int machineID;
    //machineID 0: iPadMini
    //machineID 1: iPhone5/5s
    //machineID 2: iPhone4/4s
    //machineID 3: iPhone6
    //machineID 4: iPhone6p
    
public:
    
    static Constant * getInstance(void);
    
};


#endif /* defined(__cocosOpenGL__constantUtil__) */
