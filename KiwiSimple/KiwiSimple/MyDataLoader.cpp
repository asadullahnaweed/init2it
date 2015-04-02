//
//  MyDataLoader.cpp
//  KiwiSimple
//
//  Created by Asad Ullah Naweed on 12/2/14.
//  Copyright (c) 2014 Pat Marion. All rights reserved.
//

#include "MyDataLoader.h"

#include <vtkSmartPointer.h>
#include <vtkNew.h>
#include <stdio.h>
#include <vtkXMLImageDataReader.h>
#include <vtkXMLPolyDataReader.h>

#include <vtkDataSet.h>

using namespace std;

vtkSmartPointer<vtkDataSet> MyDataLoader::loadDataset(const std::string& filename) {
    if (this->hasEnding(filename, "vti")) {
        vtkSmartPointer<vtkXMLImageDataReader> reader = vtkSmartPointer<vtkXMLImageDataReader>::New();
        reader->SetFileName(filename.c_str());
        return this->datasetFromAlgorithm(reader);
    }
    else if (this->hasEnding(filename, "vtp")) {
        vtkSmartPointer<vtkXMLPolyDataReader> reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
        reader->SetFileName(filename.c_str());
        return this->datasetFromAlgorithm(reader);
    }
    else {
        return Superclass::loadDataset(filename);
    }
}