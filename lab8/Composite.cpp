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

Composite::Composite(string _name, string _colour, float _xcen, float _ycen,
        string *_shapeNames, int _nShape, ShapeArray *_shapeArray)
: Shape(_name, _colour, _xcen, _ycen) {
    nShape = _nShape;
    shapeArray = _shapeArray;
    shapeColour = _colour;
    shapeArrayCopy = new ShapeArray();

    for (int i = 0; i < nShape; i++) {
        shapeNames[i] = _shapeNames[i];
    }

    for (int i = 0; i < nShape; i++) {
        subShapes[i] = shapeArray->findShape(shapeNames[i]);
        shapeArrayCopy->addShape(subShapes[i]->duplicate());
    }


    for (int i = 0; i < nShape; i++) {
        subShapesCopy[i] = shapeArrayCopy->findShape(shapeNames[i]);
    }

    if (shapeColour.compare("child") != 0) {
        setShapeColours(subShapesCopy, shapeColour);
    }

    calculateCentreOffset();
    calculateCentres();
}

void Composite::setShapeColours(Shape* shapeList[], string colour) {

    for (int i = 0; shapeList[i] != NULL; i++) {
        if (Composite * comp = dynamic_cast<Composite*> (shapeList[i]))
            setShapeColours(comp->getShapeList(), colour);
        else
            shapeList[i]->setColour(colour);
    }
}

Composite::Composite(Composite& rhs) : Shape(rhs) {

    nShape = rhs.getNumShapes();
    shapeArray = rhs.getShapeArray();
    shapeArrayCopy = new ShapeArray();

    for (int i = 0; i < nShape; i++) {
        shapeNames[i] = rhs.getShapeNames()[i];
    }

    for (int i = 0; i < nShape; i++) {
        subShapes[i] = shapeArray->findShape(shapeNames[i]);
        shapeArrayCopy->addShape(subShapes[i]->duplicate());
    }

    for (int i = 0; i < nShape; i++) {
        subShapesCopy[i] = shapeArrayCopy->findShape(shapeNames[i]);
    }

    calculateCentreOffset();
    calculateCentres();
}

Shape *Composite::duplicate() {
    return new Composite(*this);
}

ShapeArray *Composite::getShapeArray() const {
    return shapeArrayCopy;
}

Shape **Composite::getShapeList() {
    return subShapesCopy;
}

string *Composite::getShapeNames() {

    return shapeNames;
}

int Composite::getNumShapes() const {
    return nShape;
}

Composite::~Composite() {

    delete shapeArrayCopy;
    shapeArrayCopy = NULL;
}

void Composite::draw(easygl* window) const {

    calculateCentres();

    for (int i = 0; i < nShape; i++) {
        subShapesCopy[i]->draw(window);
    }
}

void Composite::print() const {

    Shape::print();
    int mult = 1;
    cout << "composite components: " << nShape << endl;
    cout << "{" << endl;
    convertCentres();

    for (int i = 0; i < nShape; i++) {

        if (Composite * comp = dynamic_cast<Composite*> (subShapesCopy[i])) {
            cout << "   ";
            comp->print(mult);
        } else {
            cout << "   ";
            subShapesCopy[i]->print();
        }
    }
    cout << "}" << endl;
    calculateCentres();
}

void Composite::print(int &multiplier) {

    for (int i = 0; i < nShape; i++) {
        if (subShapes[i]->getName().compare(this->getName()) == 0) {
            this->setColour(subShapes[i]->getColour());
        }
    }
    Shape::print();
    cout << "composite components: " << nShape << endl;
    for (int i = 0; i < multiplier; i++) {
        cout << "   ";
    }
    cout << "{" << endl;
    multiplier++;
    convertCentres();

    for (int i = 0; i < nShape; i++) {

        if (Composite * comp = dynamic_cast<Composite*> (subShapesCopy[i])) {
            for (int i = 0; i < multiplier; i++) {
                cout << "   ";
            }
            comp->print(multiplier);
        } else {
            for (int j = 0; j < multiplier; j++) {
                cout << "   ";
            }

            string tempColour = subShapesCopy[i]->getColour();
            for (int j = 0; j < nShape; j++) {
                if (subShapes[j]->getName().compare(subShapesCopy[i]->getName()) == 0) {
                    subShapesCopy[i]->setColour(subShapes[j]->getColour());
                }
            }
            subShapesCopy[i]->print();

            for (int j = 0; j < nShape; j++) {
                if (subShapes[j]->getName().compare(subShapesCopy[i]->getName()) == 0) {
                    subShapesCopy[i]->setColour(tempColour);
                }
            }
        }
    }
    multiplier--;
    for (int j = 0; j < multiplier; j++) {
        cout << "   ";
    }

    cout << "}" << endl;
    calculateCentres();
}

void Composite::scale(float scaleFac) {

    for (int i = 0; i < nShape; i++) {
        subShapesCopy[i]->scale(scaleFac);
        subShapesCopy[i]->setXcenOffset(subShapesCopy[i]->getXcenOffset() * scaleFac);
        subShapesCopy[i]->setYcenOffset(subShapesCopy[i]->getYcenOffset() * scaleFac);
    }
}

float Composite::computeArea() const {

    float area = 0;

    for (int i = 0; i < nShape; i++) {
        area += subShapesCopy[i]->computeArea();
    }

    return area;
}

float Composite::computePerimeter() const {

    float perimeter = 0;

    for (int i = 0; i < nShape; i++) {
        perimeter += subShapesCopy[i]->computePerimeter();
    }

    return perimeter;
}

bool Composite::pointInside(float x, float y) const {

    for (int i = 0; i < nShape; i++) {
        if (subShapesCopy[i]->pointInside(x, y))
            return true;
    }

    return false;
}


// Private helper functions

void Composite::calculateCentreOffset() {

    float xcenOffset, ycenOffset;

    for (int i = 0; i < nShape; i++) {
        xcenOffset = subShapes[i]->getXcen() - this->getXcen();
        ycenOffset = subShapes[i]->getYcen() - this->getYcen();

        subShapesCopy[i]->setXcenOffset(xcenOffset);
        subShapesCopy[i]->setYcenOffset(ycenOffset);
    }
}

void Composite::calculateCentres() const {

    for (int i = 0; i < nShape; i++) {
        subShapesCopy[i]->setXcen(subShapesCopy[i]->getXcenOffset() + this->getXcen());
        subShapesCopy[i]->setYcen(subShapesCopy[i]->getYcenOffset() + this->getYcen());
    }
}

void Composite::convertCentres() const {

    for (int i = 0; i < nShape; i++) {
        subShapesCopy[i]->setXcen(subShapesCopy[i]->getXcenOffset());
        subShapesCopy[i]->setYcen(subShapesCopy[i]->getYcenOffset());
    }
}