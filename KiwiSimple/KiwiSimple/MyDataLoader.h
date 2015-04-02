//
//  MyDataLoader.h
//  KiwiSimple
//
//  Created by Asad Ullah Naweed on 12/2/14.
//  Copyright (c) 2014 Pat Marion. All rights reserved.
//

#ifndef KiwiSimple_MyDataLoader_h
#define KiwiSimple_MyDataLoader_h

#include <vesKiwiDataLoader.h>
#include "AsadKiwiApp.h"

class MyDataLoader: public vesKiwiDataLoader {

public:
    typedef vesKiwiDataLoader Superclass;
    vesTypeMacro(MyDataLoader);
    virtual vtkSmartPointer<vtkDataSet> loadDataset(const std::string& filename);
};

#endif
