#include <iostream>
#include <cmath>
#include "easygl.h"
#include "Rectangle.h"
using namespace std;


// Constructor. First set up base class (Shape), then store the 
// vertices, which are 3 (x,y) points giving offsets from the Shape center 
// to each triangle vertex.

Rectangle::Rectangle(string _name, string _colour, float _xcen, float _ycen,
        float _width, float _height)
: Shape(_name, _colour, _xcen, _ycen) {

    width = _width;
    height = _height;
}

Rectangle::Rectangle(const Rectangle& rhs) : Shape(rhs) {
    width = rhs.getWidth();
    height = rhs.getHeight();
}

Shape *Rectangle::duplicate() {
    return new Rectangle(*this);
}

Rectangle::~Rectangle() {
    // No dynamic memory to delete
}

float Rectangle::getWidth() const {
    return width;
}

float Rectangle::getHeight() const {
    return height;
}

void Rectangle::print() const {
    Shape::print();
    cout << "rectangle " << "width: " << width << " height: " << height << endl;
}

void Rectangle::scale(float scaleFac) {
    width *= scaleFac;
    height *= scaleFac;
}

float Rectangle::computeArea() const {
    // 1/2 * base * height
    // The height requires some trigonometry to compute, for an arbitrary triangle.
    // Some manipulation gives a simpler formula to use in this case, which I use below.
    // Compute two vectors, from one vertex to each of the other two.
    // Then use the formula below to get area.
    float area;

    area = width * height;
    return area;
}

float Rectangle::computePerimeter() const {
    float perimeter;

    perimeter = 2 * (width + height);
    return perimeter;
}

void Rectangle::draw(easygl* window) const {
    // Load up the data structure needed by easygl, and draw the triangle
    // using the easygl::draw_polygon call.
    float xright, ytop, xleft, ybottom;

    xright = getXcen() + (width / 2);
    xleft = getXcen() - (width / 2);
    ytop = getYcen() + (height / 2);
    ybottom = getYcen() - (height / 2);

    window->gl_setcolor(getColour());
    window->gl_fillrect(xleft, ybottom, xright, ytop);
}

bool Rectangle::pointInside(float x, float y) const {
    // Make a point that corresponds to where you clicked. Since all my
    // vertices are relative to the triangle center, it is more convenient
    // to also shift the click point so it is an offset from the triangle 
    // center.
    t_point click;
    click.x = abs(x - getXcen());
    click.y = abs(y - getYcen());

    if ((click.x > (width / 2)) && (click.y > (height / 2)))
        return false;
    else
        return true;
}

