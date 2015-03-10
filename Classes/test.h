//
//  test.h
//  cocosOpenGL
//
//  Created by 林跃南 on 15/3/5.
//
//

#ifndef __cocosOpenGL__test__
#define __cocosOpenGL__test__

#include <stdio.h>
#include "cocos2d.h"
#include "mySprites/graySprite.h"

USING_NS_CC;

class TestScene :public Layer{

public:
    
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(TestScene);

    
private:
    
    Size winSize;
    
};

#endif /* defined(__cocosOpenGL__test__) */
