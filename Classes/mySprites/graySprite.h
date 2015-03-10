//
//  graySprite.h
//  cocosOpenGL
//
//  Created by 林跃南 on 15/3/6.
//
//

#ifndef __cocosOpenGL__graySprite__
#define __cocosOpenGL__graySprite__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class graySprite : public Sprite {
    
public:
    
    static graySprite* create(const std::string & filename);
    virtual bool init(const std::string & filename);
    
public:
    
    virtual void visit(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags);
    void onDraw();
    
private:
    
    std::string *filename;
    
    GLProgram *program;
    CustomCommand _command;
    
    Mat4 _modelViewMV;
    
    GLint _positionLoc;
    GLint _texCoordLoc;
    GLint _colorLoc;
    
    GLuint _mapLoc;
    GLuint _textureID;
    //GLuint _textureID2;
    
    GLuint VAO;
    GLuint vertexBuffer;
    GLuint indexBuffer;
    
};

#endif /* defined(__cocosOpenGL__graySprite__) */
