#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //program
    auto program = new GLProgram();
    program->initWithFilenames("myVertextShader.vert", "myFragmentShader.frag");
    program->link();
    program->updateUniforms();
    
    this->setGLProgram(program);
    //vao
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    
    Vertex data[] = {
        // Front
        {{1, -1, 0}, {1, 0, 0, 1}},
        {{1, 1, 0}, {0, 1, 0, 1}},
        {{-1, 1, 0}, {0, 0, 1, 1}},
        {{-1, -1, 0}, {0, 0, 0, 1}},
        // Back
        {{1, 1, -2}, {1, 0, 0, 1}},
        {{-1, -1, -2}, {0, 1, 0, 1}},
        {{1, -1, -2}, {0, 0, 1, 1}},
        {{-1, 1, -2}, {0, 0, 0, 1}},
        // Left
        {{-1, -1, 0}, {1, 0, 0, 1}},
        {{-1, 1, 0}, {0, 1, 0, 1}},
        {{-1, 1, -2}, {0, 0, 1, 1}},
        {{-1, -1, -2}, {0, 0, 0, 1}},
        // Right
        {{1, -1, -2}, {1, 0, 0, 1}},
        {{1, 1, -2}, {0, 1, 0, 1}},
        {{1, 1, 0}, {0, 0, 1, 1}},
        {{1, -1, 0}, {0, 0, 0, 1}},
        // Top
        {{1, 1, 0}, {1, 0, 0, 1}},
        {{1, 1, -2}, {0, 1, 0, 1}},
        {{-1, 1, -2}, {0, 0, 1, 1}},
        {{-1, 1, 0}, {0, 0, 0, 1}},
        // Bottom
        {{1, -1, -2}, {1, 0, 0, 1}},
        {{1, -1, 0}, {0, 1, 0, 1}},
        {{-1, -1, 0}, {0, 0, 1, 1}},
        {{-1, -1, -2}, {0, 0, 0, 1}}
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
    
    //vbo
    glGenBuffers(1, &vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    
    //position get
    GLuint positionLocation = glGetAttribLocation(program->getProgram(), "a_position");
    //enable
    glEnableVertexAttribArray(positionLocation);
    //one point's position
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, Position));
    
    //set for color
    //    glGenBuffers(1, &colorVBO);
    //    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    //    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    
    GLuint colorPosition = glGetAttribLocation(program->getProgram(), "a_color");
    //enable
    glEnableVertexAttribArray(colorPosition);
    //one point's color
    glVertexAttribPointer(colorPosition, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Color));
    
    //vbo index
    GLuint indexVBO;
    glGenBuffers(1, &indexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) , indices, GL_STATIC_DRAW);
    
    program->autorelease();
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    //this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR));

    return true;
}


void HelloWorld::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags){
    
    Layer::visit(renderer, parentTransform, parentFlags);
    _command.init(_globalZOrder);
    _command.func = CC_CALLBACK_0(HelloWorld::onDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_command);
    
}

void HelloWorld::onDraw()
{
    //push matrix
    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    
    //camera
    //modelview matrix
    Mat4 modelViewMatrix;
    Mat4::createLookAt(Vec3(0,0,20), cocos2d::Vec3(0,0,0), Vec3(0,1,0), &modelViewMatrix);
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
    
    //ondraw program setting
    auto glProgram = getGLProgram();
    glProgram->use();
    //set uniform values, the order of the line is very important
    //method1
    // glProgram->setUniformsForBuiltins(modelViewMatrix);
    glProgram->setUniformsForBuiltins();
    //use vao
    glBindVertexArray(vao);
    
    GLuint uColorLocation = glGetUniformLocation(glProgram->getProgram(), "u_color");
    
    float uColor[] = {1.0, 1.0, 1.0, 1.0};
    glUniform4fv(uColorLocation,1, uColor);
    
    //    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE,(GLvoid*)0);
    
    glBindVertexArray(0);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 36);
    CHECK_GL_ERROR_DEBUG();
    
    
    //pop matrix
    Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    
    Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

    
    /*
    auto glprogram = getGLProgram();
    glprogram->use();
    glprogram->setUniformsForBuiltins();
    auto size = Director::getInstance()->getWinSize();
    float vertercies[] ={
        0,0,
        size.width,0,
        size.width/2,size.height
    };
    float color[] = {
        0,1,0,1,
        1,0,0,1,
        0,0,1,1
    };
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertercies);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, color);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 3);
    CHECK_GL_ERROR_DEBUG();
    */
}







void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
