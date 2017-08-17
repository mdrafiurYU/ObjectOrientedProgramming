/* 
 * File:   Polygon.cpp
 * Author: rashidmd
 * 
 * Created on November 25, 2013, 5:32 PM
 */
#include <iostream>
#include <cmath>
#include "easygl.h"
#include "Polygon.h"

using namespace std;

Polygon::Polygon (string _name, string _colour, float _xcen, float _ycen,
                t_point *_vertices, int _nPoint) 
                    : Shape(_name, _colour, _xcen, _ycen) {
    
    nPoint = _nPoint;
    
    for (int i = 0; i < nPoint; i++) {
        vertices[i].x = _vertices[i].x;
        vertices[i].y = _vertices[i].y;
    }
}


Polygon::Polygon(const Polygon& rhs) : Shape(rhs) {
    nPoint = rhs.getNumPoints();
    
    for (int i = 0; i < nPoint; i++) {
        vertices[i].x = rhs.getVertex_x(i);
        vertices[i].y = rhs.getVertex_y(i);
    }
}


Shape *Polygon::duplicate() {
    return new Polygon(*this);
}


Polygon::~Polygon() {
   // No dynamic memory to delete
}


int Polygon::getNumPoints() const {
    return nPoint;
}


float Polygon::getVertex_x(int index) const {
    return vertices[index].x;
}


float Polygon::getVertex_y(int index) const {
    return vertices[index].y;
}


void Polygon::print () const {
   Shape::print();
   cout << "Polygon";
   for (int i = 0; i < nPoint; i++) {
      cout << " (" << vertices[i].x << "," 
              << vertices[i].y << ")";
   }
   cout << endl;
}


void Polygon::scale (float scaleFac) {
   for (int i = 0; i < nPoint; i++) {
      vertices[i].x *= scaleFac;
      vertices[i].y *= scaleFac;
   }
}


float Polygon::computeArea () const {

    float area = 0;
    int j = nPoint - 1;
    
    for (int i=0; i < nPoint; i++) 
    {
        area += (vertices[j].x + vertices[i].x) * (vertices[j].y - vertices[i].y);
        j = i; 
    }

    return area / 2; 
}


float Polygon::computePerimeter () const {
    
   float perimeter = 0;
   float sideLength;
   int endIndex;
   t_point dist;
   
   for (int i = 0; i < nPoint; i++) {
      endIndex = (i + 1) % nPoint;
      dist = getVecBetweenPoints (vertices[i], vertices[endIndex]);
      sideLength = sqrt (dist.x * dist.x + dist.y * dist.y);
      perimeter += sideLength;
   }
   return perimeter;
}


void Polygon::draw (easygl* window) const {
    
   t_point coords[100];  // This data type is in easygl_constants.h
   for (int i = 0; i < nPoint; i++) {
      coords[i].x = getXcen() + vertices[i].x;
      coords[i].y = getYcen() + vertices[i].y;
   }
   window->gl_setcolor(getColour());
   window->gl_fillpoly(coords, nPoint);
}


bool Polygon::pointInside (float x, float y) const {
   // Make a point that corresponds to where you clicked. Since all my
   // vertices are relative to the triangle center, it is more convenient
   // to also shift the click point so it is an offset from the triangle 
   // center.
   t_point click;
   click.x = abs (x - getXcen());
   click.y = abs (y - getYcen());
   
   // The test is that a horizontal line (ray) from x = -infinity to the click point
   // will cross (intersect) only one side of triangle to the left of the 
   // click point.  If the point is above or below the triangle, the ray will not
   // intersect any triangle sides. If the point is to the left of the triangle
   // the ray will also not intersect any sides to the left of the point.
   // If the point is to the right of the triangle, the ray will intersect
   // two sides of the triangle to its left. Only if the point is inside the 
   // triangle will the ray intersect exactly one side to the left of the point.
   
   t_point vecOfSide;
   float distanceAlongVector, yDistance;
   int endIndex;
   int sidesToLeft = 0;
   
   for (int istart = 0; istart < nPoint; istart++) {
      endIndex = (istart + 1) % nPoint; // Next vertex after istart
      vecOfSide = getVecBetweenPoints (vertices[istart], vertices[endIndex]);
      yDistance = (click.y - vertices[istart].y);
      if (vecOfSide.y != 0) {
          distanceAlongVector = yDistance / vecOfSide.y;
      }
      else if (yDistance == 0) {
          distanceAlongVector = 0;
      }
      else {
          distanceAlongVector = 1e10; // Really infinity, but this is big enough
      }
      
      // We intersect this side if the distance (scaling) along the side vector to 
      // get to our "click" y point is between 0 and 1.  Count the first 
      // endpoint of the side as being part of the line (distanceAlongVector = 0)
      // but don't count the second endPoint; we'll intersect that point later 
      // when we check the next side.
      if (distanceAlongVector >= 0 && distanceAlongVector < 1) {
         float xIntersection = vertices[istart].x + vecOfSide.x * distanceAlongVector;
         if (xIntersection <= click.x ) 
             sidesToLeft++;
      }
   }
   
   return (sidesToLeft == 1);
}


// Private helper functions below.  Working out triangle area etc. 
// requires some vector math, so these helper functions are useful.

// Return the (x,y) vector between start and end points.
t_point Polygon::getVecBetweenPoints (t_point start, t_point end) const {
   t_point vec;
   vec.x = end.x - start.x;
   vec.y = end.y - start.y;
   return (vec);
}