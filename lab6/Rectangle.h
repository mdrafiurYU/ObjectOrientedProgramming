/* 
 * File:   Rectangle.h
 * Author: rashidmd
 *
 * Created on June 19, 2013, 8:49 PM
 */

#ifndef RECTANGLE_H
#define	RECTANGLE_H

#include "Shape.h"
#include "easygl.h"

class Rectangle : public Shape {
private:
   // t_point is a structure defined in easygl.h.  It has two members,
   // .x and .y, storing a 2D point.  We store 3 points in relVertex; 
   // each is the (x,y) offset of one triangle vertex from the shape 
   // center.
   float width, height;
   
   // Private helper functions.
   
public:
   Rectangle (string _name, string _colour, float _xcen, float _ycen,
            float _width, float _height);
   
   Rectangle (const Rectangle& rhs);
   
   // virtual keyword is optional in all the function declarations below, since
   // the base class Shape already declared them virtual. But it is good 
   // practice to repeat it again here, for clarity.
   virtual ~Rectangle();
   
   
   virtual void print () const;
   virtual void scale (float scaleFac);
   virtual float computeArea () const;
   virtual float computePerimeter () const;
   virtual void draw (easygl* window) const;
   virtual bool pointInside (float x, float y) const;
   
   float getWidth () const;
   float getHeight () const;
   
   virtual Shape *duplicate();
};

#endif	/* RECTANGLE_H */

