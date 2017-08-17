#include "Rparser.h"

Resistor::Resistor()
{
   ;
}

Resistor::Resistor(int rIndex_, string name_, double resistance_, int endpoints_[])
{
   rIndex = rIndex_;
   name = name_;
   resistance = resistance_;
   
   endpointNodeIDs[0] = endpoints_[0];
   endpointNodeIDs[1] = endpoints_[1];
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
   std::cout.width(MAX_RESISTOR_NAME_LEN); std::cout << std::left << name;
   std::cout.width(RESISTOR_FIELD_WIDTH); std::cout << std::right;
   std::cout << std::setprecision(1) << resistance << " Ohms ";
   cout << endpointNodeIDs[0] << " -> " << endpointNodeIDs[1] << endl;
}
