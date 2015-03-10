//
//  constantUtil.cpp
//  cocosOpenGL
//
//  Created by 林跃南 on 15/3/5.
//
//

#include "constantUtil.h"

static Constant* sharedConst = NULL;

Constant * Constant::getInstance(){

    if (sharedConst == NULL) {
        sharedConst = new Constant;
    }
    
    return sharedConst;
}

Constant::Constant(){
    machineID = 0;
}

Constant::~Constant(){
    sharedConst = NULL;
}