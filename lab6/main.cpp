/* 
 * File:   Main.cpp
 * Author: vaughn
 *
 * Created on November 20, 2012, 2:14 PM
 */

#include <iostream>
#include "Shape.h"
#include "ShapeArray.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Polygon.h"
#include "Composite.h"
#include <fstream>

using namespace std;



/*********** Function declarations ***********/

int parser (ShapeArray& shapeArray);
bool parseNameAndColour (stringstream& linestream, string& name, 
          string& colour);
void addTri(stringstream& linestream, ShapeArray& shapeArray);
void addRect(stringstream& linestream, ShapeArray& shapeArray);
void addCirc(stringstream& linestream, ShapeArray& shapeArray);
void addPoly(stringstream& linestream, ShapeArray& shapeArray);
void addComposite (stringstream& linestream, ShapeArray& shapeArray);


/************** Function definitions *********/

int main(int argc, char** argv) {

   ShapeArray shapeArray;
   int returnVal;
   
   returnVal = parser(shapeArray);
   return returnVal;
}


// Parse commands and execute them, updating the state of the ShapeArray 
// object as necessary, until EOF.
int parser (ShapeArray& shapeArray) {
   string str;
   cout << "> ";  // Prompt for input
   ifstream in_stream("infile.txt");
   
   while (getline(in_stream, str)) {   // While more input data, get one line at a time
      stringstream linestream(str);  // Build a stringstream from the line.
      string command;
      
      linestream >> command;   // First word on the line is the command
      
      if (!linestream.fail()) {
         // Call the appropriate routine to execute the command
         if (command == "tri") {
            addTri(linestream, shapeArray);
         }
         else if (command == "rect") {
            addRect(linestream, shapeArray);
         }
         else if (command == "circ") {
            addCirc (linestream, shapeArray);
         }
         else if (command == "poly") {
            addPoly (linestream, shapeArray);
         }
         else if (command == "composite") {
            addComposite (linestream, shapeArray);
         }
         else if (command == "translate") {
            shapeArray.translate (linestream);
         }
         else if (command == "scale") {
            shapeArray.scale (linestream);
         }
         else if (command == "remove") {
            shapeArray.remove (linestream);
         }
         else if (command == "printall") {
            shapeArray.printAll (linestream);
         }
         else if (command == "area") {
            shapeArray.computeArea (linestream);
         }
         else if (command == "perimeter") {
            shapeArray.computePerimeter (linestream);
         }
         else if (command == "draw") {
            shapeArray.handleDraw(linestream);
         }
         else {
            cout << "Error: invalid command\n";
         }
      }
      else {   // Extracting the command from the linestream failed.
         cout << "Error: invalid command\n";
      }
      
      cout << "> ";   // Prompt for input
   }
   return 0;
}


// Parse a name and colour from the line stored in linestream. Return true
// if successful, false if there is an input error.
// Pass back the name and colCode by reference.
bool parseNameAndColour (stringstream& linestream, string& name, 
          string& colour) {
   
   linestream >> name;
   if (linestream.fail()) {
      cout << "Error: missing or invalid name\n";
      return false;
   }
   
   linestream >> colour;
   if (linestream.fail()) {
      cout << "Error: missing or invalid colour\n";
      return false;
   }
   
   return true;
}


void addTri(stringstream& linestream, ShapeArray& shapeArray) {
   string name, colour;
   float xcoords[3], ycoords[3], xcen, ycen;
   if (!parseNameAndColour (linestream, name, colour)) 
      return;
   
   linestream >> xcoords[0] >> ycoords[0] >> xcoords[1] >> ycoords[1] 
              >> xcoords[2] >> ycoords[2];
   if (linestream.fail ()) {
      cout << "Error: invalid coordinates\n";
      return;
   }
 
   // Want to store this shape as a center, and point offsets from the 
   // center.
   xcen = 0;
   ycen = 0;
   for (int i = 0; i < 3; i++) {
      xcen += xcoords[i];
      ycen += ycoords[i];
   }
   xcen /= 3;
   ycen /= 3;
   
   for (int i = 0; i < 3; i++) {
      xcoords[i] -= xcen;
      ycoords[i] -= ycen;
   }
      
   Triangle* tri = new Triangle (name, colour, xcen, ycen, xcoords, ycoords);
   shapeArray.addShape (tri);
   cout << "Success\n";
}


void addRect(stringstream& linestream, ShapeArray& shapeArray) {
    string name, colour;
    float xcen, ycen, width, height;
    
    if (!parseNameAndColour (linestream, name, colour))
       return;
    
    linestream >> xcen >> ycen >> width >> height;
    if (linestream.fail()) {
       cout << "Error: invalid center, width or height\n";
       return;
    }
    
   // Create a Rectangle and add it to the shape database.
   // Uncomment line below to add to shape database.
    Rectangle* rect = new Rectangle (name, colour, xcen, ycen, width, height);
    shapeArray.addShape (rect);
    cout << "Success\n";
}


void addCirc(stringstream& linestream, ShapeArray& shapeArray) {
    string name, colour;
    float xcen, ycen, radius;
    
    if (!parseNameAndColour (linestream, name, colour))
       return;
    
    linestream >> xcen >> ycen >> radius;
    if (linestream.fail()) {
       cout << "Error: invalid center or radius\n";
       return;
    }

   // Now decide how you want to store the circle and
   // make a Circle. Uncomment the line below to add to the shape database.
    Circle* circ = new Circle (name, colour, xcen, ycen, radius);
    shapeArray.addShape (circ);
    cout << "Success\n";
}


void addPoly(stringstream& linestream, ShapeArray& shapeArray) {
   string name, colour;
   const int maxVertices = 100;
   int nPoint = 0;
   t_point vertices[maxVertices];
   float xcen, ycen;
   
   if (!parseNameAndColour (linestream, name, colour)) 
      return;
   
   while (!linestream.fail()) {
      linestream >> vertices[nPoint].x >> vertices[nPoint].y;
      if (!linestream.fail ()) 
         nPoint++;
   }

   if (nPoint < 3) {
      cout << "Error: Polygon must have at least 3 vertices.\n";
      return;
   }
   
   xcen = 0;
   ycen = 0;
   for (int i = 0; i < nPoint; i++) {
      xcen += vertices[i].x;
      ycen += vertices[i].y;
   }
   xcen /= nPoint;
   ycen /= nPoint;

   // Now decide how you want to store these points, and make a
   // Polygon. Uncomment line below to add the Polygon to the 
   // shapeArray database.
   Polygon* poly = new Polygon (name, colour, xcen, ycen, vertices, nPoint);
   shapeArray.addShape (poly);
   cout << "Success\n";
}


void addComposite(stringstream& linestream, ShapeArray& shapeArray) {
   
   // Bonus part of lab.  Need to write your own parsing code to 
   // get all the composite information, then create a new Composite
   // object and add it to the shape database.
   string name, colour;
   float xcen, ycen;
   const int maxShapes = 100;
   int nShape = 0;
   string shapeNames[maxShapes];
   
   if (!parseNameAndColour (linestream, name, colour)) 
      return;
   
   while (!linestream.fail()) {
      linestream >> shapeNames[nShape];
      if (!linestream.fail ()) 
         nShape++;
   }
   
   for (int i = 0; i < nShape; i++) {
       if(!shapeArray.findShape(shapeNames[i])) {
           cout << "Error: shape " << shapeNames[i] << " does not exist" << endl;
           return;
       }
    }

   xcen = 0;
   ycen = 0;
   for (int i = 0; i < nShape; i++) {
      xcen += (shapeArray.findShape(shapeNames[i]))->getXcen();
      ycen += (shapeArray.findShape(shapeNames[i]))->getYcen();
   }
   xcen /= nShape;
   ycen /= nShape;
   
   Composite* comp = new Composite(name, colour, xcen, ycen, shapeNames, nShape, &shapeArray);    
   shapeArray.addShape (comp); 
   cout << "Success\n";
}
