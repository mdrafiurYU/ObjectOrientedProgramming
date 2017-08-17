/* 
 * File:   Composite.cpp
 * Author: rashidmd
 * 
 * Created on November 27, 2013, 1:10 AM
 */
#include <iostream>
#include <cmath>
#include "easygl.h"
#include "Composite.h"
#include "ShapeArray.h"

using namespace std;

Composite::Composite (string _name, string _colour, float _xcen, float _ycen,
                      string *_shapeNames, int _nShape, ShapeArray *_shapeArray)
                        : Shape(_name, _colour, _xcen, _ycen) {
    nShape = _nShape;
    shapeArray = _shapeArray;
    colour = _colour;
    
    for (int i = 0; i < nShape; i++) {
        shapeNames[i] = _shapeNames[i];
    }
    
    for (int i = 0; i < nShape; i++) {
        subShapes[i] = shapeArray->findShape(shapeNames[i]);
        shapeArrayCopy.addShape(subShapes[i]->duplicate());
    }
    
    for (int i = 0; i < nShape; i++) {
        subShapesCopy[i] = shapeArrayCopy.findShape(shapeNames[i]);
    }
    
    calculateCentres();
}


Composite::Composite (const Composite& rhs) : Shape(rhs) {
    nShape = rhs.getNumShapes();
    shapeArray = rhs.getShapeArray();
    colour = rhs.getColour();
    
    for (int i = 0; i < nShape; i++) {
        shapeNames[i] = rhs.getShapeNames()[i];
    }
    
    for (int i = 0; i < nShape; i++) {
        subShapes[i] = shapeArray->findShape(shapeNames[i]);
        shapeArrayCopy.addShape(subShapes[i]->duplicate());
    }
    
    for (int i = 0; i < nShape; i++) {
        subShapesCopy[i] = shapeArrayCopy.findShape(shapeNames[i]);
    }
    
    calculateCentres();
}
      
    
Shape *Composite::duplicate() {
    return new Composite(*this);
}


ShapeArray *Composite::getShapeArray () const {
    return shapeArray;
}


string *Composite::getShapeNames () const {
    string *names = new string[100];
    for (int i = 0; i < nShape; i++) {
        names[i] = shapeNames[i];
    }
    return names;
}


int Composite::getNumShapes () const {
    return nShape;
}


Composite::~Composite() {
    ;
}


void Composite::draw (easygl* window) const {
    
    if(colour.compare("child") != 0)
        window->gl_setcolor(getColour());
    else
        ;
    
    for (int i = 0; i < nShape; i++) {
        subShapesCopy[i]->draw(window);
    }
}

void Composite::print () const {
    Shape::print();
    cout << "composite components: " << nShape << endl;
    cout << "{" << endl;
    for (int i = 0; i < nShape; i++) {
        cout << "   ";
        subShapesCopy[i]->print();
    }
    cout << "}" << endl;
}

void Composite::scale (float scaleFac) {
    
    for (int i = 0; i < nShape; i++) {
        subShapesCopy[i]->scale(scaleFac);
        subShapesCopy[i]->setXcen(subShapesCopy[i]->getXcen() * scaleFac);
        subShapesCopy[i]->setYcen(subShapesCopy[i]->getYcen() * scaleFac);
    }
}

float Composite::computeArea () const {
    
    float area = 0;
    
    for (int i = 0; i < nShape; i++) {
        area += subShapesCopy[i]->computeArea();
    }
    
    return area;
}

float Composite::computePerimeter () const {
    
    float perimeter = 0;
    
    for (int i = 0; i < nShape; i++) {
        perimeter += subShapesCopy[i]->computePerimeter();
    }
    
    return perimeter;
}


bool Composite::pointInside (float x, float y) const {
    
    for (int i = 0; i < nShape; i++) {
        if(subShapes[i]->pointInside(x, y))
            return true;
    }
    
    return false;
}


void Composite::calculateCentres() {
    
    for (int i = 0; i < nShape; i++) {
        subShapesCopy[i]->setXcen(subShapes[i]->getXcen() - this->getXcen());
        subShapesCopy[i]->setYcen(subShapes[i]->getYcen() - this->getYcen());
    }
}
