//
//  Texture3DScene.cpp
//  cocosOpenGL
//
//  Created by 林跃南 on 15/2/28.
//
//

#include "Texture3DScene.h"

USING_NS_CC;

Scene* Texture3DScene::createScene(){
    
    auto scene = Scene::create();
    auto layer = Texture3DScene::create();
    scene->addChild(layer);
    return scene;

}

void Texture3DScene::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags){
    
    Layer::visit(renderer, parentTransform, parentFlags);
    _command.init(_globalZOrder);
    _command.func = CC_CALLBACK_0(Texture3DScene::onDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_command);
    
}



bool Texture3DScene::init(){
    
    if (!Layer::init()) {
        return false;
    }
    
    //program
    program = new GLProgram;
    program->initWithFilenames("textureVertexShader.vert", "textureFragmentShader.frag");
    program->link();
    program->updateUniforms();
    
    //textureID
    _textureID = Director::getInstance()->getTextureCache()->addImage("touxiang.jpg")->getName();
    //_textureID2 = Director::getInstance()->getTextureCache()->addImage("iphone/HelloWorld.png")->getName();
    
    //vbo
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    
    //vbo index
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    
    return true;
}

void Texture3DScene::onDraw(){

    //push matrix
    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    
    //camera
    //modelview matrix
    Mat4 modelViewMatrix;
    Mat4::createLookAt(Vec3(0,0,5), cocos2d::Vec3(0,0,0), Vec3(0,1,0), &modelViewMatrix);
    //suoxiao
    modelViewMatrix.translate(0, 0, -5);
    //rotate
    static float rotation = 0;
    modelViewMatrix.rotate(Vec3(1,1,1), CC_DEGREES_TO_RADIANS(rotation));
    rotation++;
    if (rotation > 360) {
        rotation = 0;
    }
    //projection matrix
    Mat4 projectionMatrix;
    Mat4::createPerspective(60, 480/320, 1.0, 42, &projectionMatrix);
    
    //multiply Matrix
    Director::getInstance()->multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, projectionMatrix);
    Director::getInstance()->multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, modelViewMatrix);
    
    typedef struct {
        float Position[3];
        float Color[4];
        float TexCoord[2];
    }Vertex;
    
#define TEX_COORD_MAX   1
    
    Vertex Vertices[] = {
        // Front
        {{1, -1, 0}, {1, 0, 0, 1}, {TEX_COORD_MAX, 0}},
        {{1, 1, 0}, {0, 1, 0, 1}, {TEX_COORD_MAX, TEX_COORD_MAX}},
        {{-1, 1, 0}, {0, 0, 1, 1}, {0, TEX_COORD_MAX}},
        {{-1, -1, 0}, {0, 0, 0, 1}, {0, 0}},
        // Back
        {{1, 1, -2}, {1, 0, 0, 1}, {TEX_COORD_MAX, 0}},
        {{-1, -1, -2}, {0, 1, 0, 1}, {TEX_COORD_MAX, TEX_COORD_MAX}},
        {{1, -1, -2}, {0, 0, 1, 1}, {0, TEX_COORD_MAX}},
        {{-1, 1, -2}, {0, 0, 0, 1}, {0, 0}},
        // Left
        {{-1, -1, 0}, {1, 0, 0, 1}, {TEX_COORD_MAX, 0}},
        {{-1, 1, 0}, {0, 1, 0, 1}, {TEX_COORD_MAX, TEX_COORD_MAX}},
        {{-1, 1, -2}, {0, 0, 1, 1}, {0, TEX_COORD_MAX}},
        {{-1, -1, -2}, {0, 0, 0, 1}, {0, 0}},
        // Right
        {{1, -1, -2}, {1, 0, 0, 1}, {TEX_COORD_MAX, 0}},
        {{1, 1, -2}, {0, 1, 0, 1}, {TEX_COORD_MAX, TEX_COORD_MAX}},
        {{1, 1, 0}, {0, 0, 1, 1}, {0, TEX_COORD_MAX}},
        {{1, -1, 0}, {0, 0, 0, 1}, {0, 0}},
        // Top
        {{1, 1, 0}, {1, 0, 0, 1}, {TEX_COORD_MAX, 0}},
        {{1, 1, -2}, {0, 1, 0, 1}, {TEX_COORD_MAX, TEX_COORD_MAX}},
        {{-1, 1, -2}, {0, 0, 1, 1}, {0, TEX_COORD_MAX}},
        {{-1, 1, 0}, {0, 0, 0, 1}, {0, 0}},
        // Bottom
        {{1, -1, -2}, {1, 0, 0, 1}, {TEX_COORD_MAX, 0}},
        {{1, -1, 0}, {0, 1, 0, 1}, {TEX_COORD_MAX, TEX_COORD_MAX}},
        {{-1, -1, 0}, {0, 0, 1, 1}, {0, TEX_COORD_MAX}},
        {{-1, -1, -2}, {0, 0, 0, 1}, {0, 0}}
    };
    GLubyte indices[] = {
        // Front
        0, 1, 2,
        2, 3, 0,
        // Back
        4, 5, 6,
        4, 5, 7,
        // Left
        8, 9, 10,
        10, 11, 8,
        // Right
        12, 13, 14,
        14, 15, 12,
        // Top
        16, 17, 18,
        18, 19, 16,
        // Bottom
        20, 21, 22,
        22, 23, 20
    };
    
    //bind
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    //setting
    _positionLocation = glGetAttribLocation(program->getProgram(), "a_position");
    _colorLocation = glGetAttribLocation(program->getProgram(), "a_color");
    _textureLocation = glGetAttribLocation(program->getProgram(), "TextureCoord");
    _textureUniform = glGetAttribLocation(program->getProgram(), "CC_Texture0");
    
    //programe
    program->use();
    program->setUniformsForBuiltins();
    
    //enable
    glEnableVertexAttribArray(_positionLocation);
    glEnableVertexAttribArray(_colorLocation);
    glEnableVertexAttribArray(_textureLocation);
    
    //pointer
    glVertexAttribPointer(_positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Position));
    glVertexAttribPointer(_colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Color));
    glVertexAttribPointer(_textureLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoord));
    
    GL::bindTexture2DN(0, _textureID);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDrawElements(GL_TRIANGLES,  36, GL_UNSIGNED_BYTE, 0);
    glUniform1i(_textureUniform, 0);
    
}








