//
//  graySprite.cpp
//  cocosOpenGL
//
//  Created by 林跃南 on 15/3/6.
//
//

#include "graySprite.h"

graySprite* graySprite::create(const std::string  & filename){

    graySprite * ret = new graySprite();
    if (ret && ret->init(filename))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool graySprite::init(const std::string  & filename){
    
    if (!Sprite::init()) {
        return false;
    }
    //textureID
    _textureID = Director::getInstance()->getTextureCache()->addImage(filename)->getName();

    program = GLProgram::createWithFilenames("gray.vert", "gray.frag");
    //program = new GLProgram();
    //program->initWithFilenames("gray.vert", "gray.frag");
    program->link();
    program->updateUniforms();
    
    //vao
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    
    //vbo
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    
    //index
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    
    
    return true;
}


void graySprite::onDraw(){
    
    
    //push matrix
    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    
    typedef struct {
        float Position[3];
        float Color[4];
        float TexCoord[2];
    }Vertex;
    
#define TEX_COORD_MAX 1
    
    Vertex Vertices[] = {
        
        {{-0.5,0.5,0},{0,1,0,1},{0,0}},
        {{-0.5,-0.5,0},{0,1,0,1},{0,TEX_COORD_MAX}},
        {{0.5,-0.5,0},{0,1,0,1},{TEX_COORD_MAX,TEX_COORD_MAX}},
        {{0.5,0.5,0},{0,1,0,1},{TEX_COORD_MAX,0}},
        
    };
    
    GLubyte Indices[] = {
        0,1,2,
        2,3,0,
    };
    
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
    
    _positionLoc = glGetAttribLocation(program->getProgram(), "a_position");
    _texCoordLoc = glGetAttribLocation(program->getProgram(), "a_texCoord");
    _colorLoc = glGetAttribLocation(program->getProgram(), "a_color");
    _mapLoc = glGetUniformLocation(program->getProgram(), "CC_Texture0");
    
    
    program->use();
    program->setUniformsForBuiltins();
     
    glEnableVertexAttribArray(_positionLoc);
    glEnableVertexAttribArray(_texCoordLoc);
    glEnableVertexAttribArray(_colorLoc);
    
    glVertexAttribPointer(_positionLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Position));
    glVertexAttribPointer(_colorLoc, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Color));
    glVertexAttribPointer(_texCoordLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoord));
    
    glEnable(GL_DEPTH_TEST);
    glBindVertexArray(VAO);
    
    GL::bindTexture2DN(0, _textureID);
    glUniform1i(_mapLoc, 0);
    
    glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_BYTE, 0 );
    glBindVertexArray(0);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,6);
    CHECK_GL_ERROR_DEBUG();
    glDisable(GL_DEPTH_TEST);
    
    Director::getInstance()->popMatrix(cocos2d::MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    Director::getInstance()->popMatrix(cocos2d::MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

}


void graySprite::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags){

    Sprite::visit(renderer, parentTransform, parentFlags);
    _command.init(_globalZOrder);
    _command.func = CC_CALLBACK_0(graySprite::onDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_command);
}