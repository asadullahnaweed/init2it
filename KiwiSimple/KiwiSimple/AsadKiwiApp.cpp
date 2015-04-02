//
//  AsadKiwiApp.cpp
//  KiwiSimple
//
//  Created by Asad Ullah Naweed on 11/25/14.
//  Copyright (c) 2014 Pat Marion. All rights reserved.
//

#include "AsadKiwiApp.h"
#include <vesKiwiText2DRepresentation.h>
#include <vesCamera.h>
#include "MyDataLoader.h"

struct AsadKiwiApp::Internals {
    bool inMeasureMode;
    int resetCountdown;
    float rotAngle;
    
    MyDataLoader loader;
    vesSharedPtr<vesKiwiText2DRepresentation> textptr;
};

AsadKiwiApp::AsadKiwiApp():vesKiwiViewerApp() {
    m = new Internals;
    m->inMeasureMode = false;
    m->resetCountdown = 0;
    m->rotAngle = 0;
}

AsadKiwiApp::~AsadKiwiApp() {
    delete m;
}

bool AsadKiwiApp::setMeasureMode(bool isMeasuring) {
    if (!this->widgetInteractionIsActive()) {
        m->inMeasureMode = isMeasuring;
        return true;
    }
    else {
        return false;
    }
}

void AsadKiwiApp::handleTwoTouchPanGesture(double x0, double y0, double x1, double y1) {
    if (!m->inMeasureMode) {
        Superclass::handleTwoTouchPanGesture(x0, y0, x1, y1);
    }
    else {
        // Do nothing atm. Need to implement measuring logic.
    }
}

bool AsadKiwiApp::loadDataset(const std::string& filename) {
    this->loadText();
    return Superclass::loadDataset(filename);
}

void AsadKiwiApp::loadText() {
    m->textptr = this->addTextRepresentation(std::string("Hello World!"));
    m->textptr->setDisplayPosition(vesVector2f(50, 50));
    m->textptr->setColor(1.0, 0.0, 0.0, 1.0);
    m->textptr->setPointSize(32);
    
    //NSLog(@"%f %f %f\n%f %f %f\n%f %f %f", camPos[0], camPos[1], camPos[2], camUp[0], camUp[1], camUp[2], camTarget[0], camTarget[1], camTarget[2]);
}

void AsadKiwiApp::animationStep() {
    if (m->resetCountdown > 0) {
        m->resetCountdown--;
        if (m->resetCountdown == 0) {
            NSLog(@"Countdown was zero!");
            Superclass::resetView();
            m->rotAngle = 0;
        }
    }
    if (m->resetCountdown == 0) {
        vesVector3f camPos = this->cameraPosition();
        vesVector3f camTarget = this->cameraFocalPoint();
        vesVector3f camUp = this->cameraViewUp();
        
        vesMatrix4x4f R = makeRotationMatrix4x4(0.003, camUp[0], camUp[1], camUp[2]);
        vesVector3f t = camPos - camTarget;
        vesVector4f w = R * vesVector4f(t[0], t[1], t[2], 1);
        
        if (!this->isAnimating()) {
            this->setCameraPosition(vesVector3f(camTarget[0]+w[0], camTarget[1]+w[1], camTarget[2]+w[2]));
            this->setCameraFocalPoint(camTarget);
            this->setCameraViewUp(camUp);
        }
        /*NSLog(@"%f %f %f", camPos[0], camPos[1], camPos[2]);
        NSLog(@"%f %f %f", camTarget[0], camTarget[1], camTarget[2]);
        NSLog(@"%f %f %f", camUp[0], camUp[1], camUp[2]);*/
        //this->setCameraPosition(vesVector3f(0, 0, 1));
        m->rotAngle += 0.003;
    }
}

void AsadKiwiApp::handleSingleTouchPanGesture(double deltaX, double deltaY) {
    if (!m->inMeasureMode) {
        m->resetCountdown = 500;
        Superclass::handleSingleTouchPanGesture(deltaX, deltaY);
    }
}

void AsadKiwiApp::handleSingleTouchDown(int displayX, int displayY) {
    if (!m->inMeasureMode) {
        m->resetCountdown = 500;
        Superclass::handleSingleTouchDown(displayX, displayY);
    }
}

void AsadKiwiApp::handleSingleTouchTap(int displayX, int displayY) {
    if (!m->inMeasureMode) {
        m->resetCountdown = 500;
        Superclass::handleSingleTouchTap(displayX, displayY);
    }
}

void AsadKiwiApp::handleSingleTouchUp() {
    if (!m->inMeasureMode) {
        m->resetCountdown = 500;
        Superclass::handleSingleTouchUp();
    }
}

void AsadKiwiApp::handleTwoTouchPinchGesture(double scale) {
    if (!m->inMeasureMode) {
        m->resetCountdown = 500;
        Superclass::handleTwoTouchPinchGesture(scale);
    }
}

void AsadKiwiApp::handleTwoTouchRotationGesture(double rotation) {
    if (!m->inMeasureMode) {
        m->resetCountdown = 500;
        Superclass::handleTwoTouchRotationGesture(rotation);
    }
}

void AsadKiwiApp::handleDoubleTap(int displayX, int displayY) {
    if (!m->inMeasureMode) {
        m->resetCountdown = 500;
        Superclass::handleDoubleTap(displayX, displayY);
    }
}

void AsadKiwiApp::handleLongPress(int displayX, int displayY) {
    if (!m->inMeasureMode) {
        m->resetCountdown = 500;
        Superclass::handleLongPress(displayX, displayY);
    }
}

