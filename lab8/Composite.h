/* 
 * File:   Composite.h
 * Author: rashidmd
 *
 * Created on November 27, 2013, 1:10 AM
 */

#ifndef COMPOSITE_H
#define	COMPOSITE_H

#include "Shape.h"
#include "easygl.h"
#include "ShapeArray.h"

class Composite : public Shape {
private:
    int nShape;
    string shapeColour;
    string shapeNames[100];
    Shape *subShapes[100];
    Shape *subShapesCopy[100];
    ShapeArray *shapeArray;
    ShapeArray *shapeArrayCopy;

    void calculateCentreOffset();
    void calculateCentres() const;
    void convertCentres() const;
    void print(int &multiplier);
    void setShapeColours(Shape *shapeList[], string colour);

public:
    Composite(string _name, string _colour, float _xcen, float _ycen,
        string *_shapeNames, int _nShape, ShapeArray *_shapeArray);

    Composite(Composite& rhs);
    virtual Shape *duplicate();

    virtual ~Composite();

    virtual void print() const;
    virtual void scale(float scaleFac);
    virtual float computeArea() const;
    virtual float computePerimeter() const;
    virtual void draw(easygl* window) const;
    virtual bool pointInside(float x, float y) const;

    int getNumShapes() const;
    ShapeArray *getShapeArray() const;
    Shape **getShapeList();
    string *getShapeNames();
};

#endif	/* COMPOSITE_H */

