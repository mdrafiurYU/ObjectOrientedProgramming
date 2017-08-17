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
    Shape *subShapes[100];
    Shape *subShapesCopy[100];
    string shapeNames[100];
    ShapeArray *shapeArray;
    ShapeArray shapeArrayCopy;
    string colour;
    
    void calculateCentres();
    
public:    
    Composite(string _name, string _colour, float _xcen, float _ycen, 
            string *_shapeNames, int _nShape, ShapeArray *_shapeArray);
    
    Composite (const Composite& rhs);
    virtual Shape *duplicate();
    
    virtual ~Composite();
   
    virtual void print () const;
    virtual void scale (float scaleFac);
    virtual float computeArea () const;
    virtual float computePerimeter () const;
    virtual void draw (easygl* window) const;
    virtual bool pointInside (float x, float y) const;
    
    int getNumShapes () const;
    Shape *getShapeList () const;
    ShapeArray *getShapeArray () const;
    string *getShapeNames () const;
};

#endif	/* COMPOSITE_H */

