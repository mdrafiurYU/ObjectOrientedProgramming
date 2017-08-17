/* 
 * File:   Resistor.h
 * Author: rashidmd
 *
 * Created on August 19, 2013, 11:33 AM
 */

#ifndef RESISTOR_H
#define	RESISTOR_H

#include <string>
#include <iostream>

using namespace std;
        
class Resistor {

private:
    double resistance;
    string name;
    int endpointNodeIDs[2];
    Resistor *next;
    
public:
    Resistor (string name_, double resistance_, int endpoints_[2]);
    ~Resistor ();
    
    string getName () const;
    double getResistance () const;
    Resistor *getNext () const;
    void setNext (Resistor *resPtr);
    int *getEndpoints ();
    
    void setResistance (double resistance_);
    
    void print ();
    
    void drawResistor();
        
};

#endif	/* RESISTOR_H */

