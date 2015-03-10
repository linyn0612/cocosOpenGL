//
//  test4dym.h
//  cocosOpenGL
//
//  Created by 林跃南 on 15/3/9.
//
//

#ifndef __cocosOpenGL__test4dym__
#define __cocosOpenGL__test4dym__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class Test4DymScene :public Layer{
    
public:
    
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Test4DymScene);
    
    
private:
    
    Size winSize;
    
};
#endif /* defined(__cocosOpenGL__test4dym__) */
