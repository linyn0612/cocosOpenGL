//
//  test4dym.cpp
//  cocosOpenGL
//
//  Created by 林跃南 on 15/3/9.
//
//

#include "test4dym.h"

Scene* Test4DymScene::createScene(){
    
    auto scene = Scene::create();
    auto layer = Test4DymScene::create();
    scene->addChild(layer);
    return scene;
    
}

bool Test4DymScene::init(){
    
    if (!Layer::init()) {
        return false;
    }
    
    winSize = Director::getInstance()->getWinSize();
    //    auto sprite = graySprite::create("iphone/HelloWorld.png");
    //    sprite->setPosition(winSize/2);
    //    this->addChild(sprite);
    //    return true;
    
    //GLchar * fragSource = (GLchar*) String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename("gray.frag").c_str())->getCString();
    //GLchar * vertSource = (GLchar*) String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename("gray.vert").c_str())->getCString();
    
    auto s = Sprite::create("iphone/HelloWorld.png");
    //GLProgram * p = new GLProgram();
    //p->autorelease();
    //p->initWithByteArrays(vertSource, fragSource);
    
    //p->initWithFilenames("gray.vsh", "gray.fsh");
    //auto p = GLProgram::createWithByteArrays(vertSource, fragSource);
    //auto p = GLProgram::createWithByteArrays(cocos2d::ccPositionTextureColor_noMVP_vert, cocos2d::ccPositionTextureColor_noMVP_frag);
    
    
    /////////////////////////////
    //load shader
    //gray shader
    //auto p = GLProgram::createWithFilenames("gray.vert", "gray.frag");
    //horizontalcolor shader
    //auto p = GLProgram::createWithFilenames("gray.vert", "HorizontalColor.fsh");
    auto p = GLProgram::createWithFilenames("gray.vert", "mywhitebo.fsh");
    //auto p = GLProgram::createWithFilenames("gray.vert", "example_Blur.fsh");
    
    
    
    p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
    p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
    p->link();
    p->updateUniforms();
    p->use();
    p->setUniformsForBuiltins();
    auto glProgramState = GLProgramState::getOrCreateWithGLProgram(p);
    s->setGLProgramState(glProgramState);
    
    
    s->setGLProgram(p);
    s->setPosition(winSize/2);
    addChild(s);
    
    
    return true;
}

