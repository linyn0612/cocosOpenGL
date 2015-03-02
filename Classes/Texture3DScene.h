//
//  Texture3DScene.h
//  cocosOpenGL
//
//  Created by 林跃南 on 15/2/28.
//
//

#ifndef __cocosOpenGL__Texture3DScene__
#define __cocosOpenGL__Texture3DScene__

#include <stdio.h>
#include <cocos2d.h>

USING_NS_CC;

class Texture3DScene : public Layer{
public:
    
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Texture3DScene);
    
public:
    
    virtual void visit(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags);
    void onDraw();
    
private:
    
    CustomCommand _command;
    
    GLProgram *program;
    
    GLint _colorLocation;
    GLint _positionLocation;
    GLint _textureLocation;
    
    GLuint _textureUniform;
    
    GLuint _textureID;
    //GLuint _textureID2;

    GLuint vertexBuffer;
    GLuint indexBuffer;
 
    GLuint _vertexBuffer2;
    GLuint _indexBuffer2;
    
};

#endif /* defined(__cocosOpenGL__Texture3DScene__) */
