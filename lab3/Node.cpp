#include "Rparser.h"

Node::Node ()
{
   numRes = 0;
   
   for(int i = 0; i < MAX_RESISTORS_PER_NODE; i++)
       resIDArray[i] = -1;
}

Node::~Node ()
{
   ;
}

void Node::resetNode ()
{
   numRes = 0;
   
   for(int i = 0; i < MAX_RESISTORS_PER_NODE; i++)
       resIDArray[i] = -1;
}

bool Node::addResistor (int rIndex)
{
   int index = 0;
   while (index < MAX_RESISTORS_PER_NODE)
   {
       if(resIDArray[index] == -1)
       {
           resIDArray[index] = rIndex;
           numRes++;
           return true;
       }
       
       index++;
   }
   
   return false;
}

void Node::print (int nodeIndex)
{
   cout << "Connections at node " << nodeIndex << ": " << numRes << " resistor(s)" << endl;
   
   for(int i = 0; i < numRes; i++)
   {
       cout << "  ";
       resistorArray[resIDArray[i]].print();
   }
}
