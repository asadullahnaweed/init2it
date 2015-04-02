//
//  AsadKiwiApp.h
//  KiwiSimple
//
//  Created by Asad Ullah Naweed on 11/25/14.
//  Copyright (c) 2014 Pat Marion. All rights reserved.
//

#ifndef KiwiSimple_AsadKiwiApp_h
#define KiwiSimple_AsadKiwiApp_h

#include <vesKiwiViewerApp.h>

class AsadKiwiApp: public vesKiwiViewerApp {
    
public:
    typedef vesKiwiViewerApp Superclass;
    vesTypeMacro(AsadKiwiApp);
    
    AsadKiwiApp();
    ~AsadKiwiApp();
    
    bool setMeasureMode(bool isMeasuring);
    virtual void handleSingleTouchPanGesture(double deltaX, double deltaY);
    virtual void handleSingleTouchDown(int displayX, int displayY);
    virtual void handleSingleTouchTap(int displayX, int displayY);
    virtual void handleSingleTouchUp();
    virtual void handleTwoTouchPanGesture(double x0, double y0, double x1, double y1);
    virtual void handleTwoTouchPinchGesture(double scale);
    virtual void handleTwoTouchRotationGesture(double rotation);
    virtual void handleDoubleTap(int displayX, int displayY);
    virtual void handleLongPress(int displayX, int displayY);
    virtual void loadText();
    
    virtual void animationStep();
    virtual bool loadDataset(const std::string& filename);
    
private:
    struct Internals;
    Internals * m;
};

#endif
