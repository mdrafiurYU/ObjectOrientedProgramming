#include "Rparser.h"

Resistor::Resistor(string name_, double resistance_, int endpoints_[])
{
    name = name_;
    resistance = resistance_;
    
    endpointNodeIDs[0] = endpoints_[0];
    endpointNodeIDs[1] = endpoints_[1];
    
    next = NULL;
}

Resistor::~Resistor()
{
    ;
}

string Resistor::getName() const
{
    return name;
}

double Resistor::getResistance() const
{
    return resistance;
}

void Resistor::setResistance(double resistance_)
{
    resistance = resistance_;
}

void Resistor::print()
{
    cout.width(MAX_RESISTOR_NAME_LEN); cout << std::left << name;
    cout.width(RESISTOR_FIELD_WIDTH); cout << std::right;
    cout << setprecision(2) << resistance << " Ohms ";
    cout << endpointNodeIDs[0] << " -> " << endpointNodeIDs[1] << endl;
}

Resistor *Resistor::getNext() const
{
    return next;
}

void Resistor::setNext(Resistor *resPtr)
{
    next = resPtr;
}

int *Resistor::getEndpoints()
{
    return endpointNodeIDs;
}

void drawResistor (double leftNodeCen, double rightNodeCen, double yCoord) 
{
	gl_setcolor (BLACK);
	gl_fillarc (leftNodeCen, yCoord, 5, 0., 360.);
	gl_fillarc (rightNodeCen, yCoord, 5, 0., 360.);
	
	gl_drawline (leftNodeCen, leftNodeCen + 40); // First part of straight line
	gl_drawline (rightNodeCen - 40, righttNodeCen); // last part of straight line
	
	double line1Start_x = leftNodeCen_x + 40;
	double line1End_x = line1Start_x + 10;
	
	//double line1Start_y = 80;
	double line1End_y = yCoord - 10;
}

