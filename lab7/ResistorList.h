/* 
 * File:   ResistorList.h
 * Author: rashidmd
 *
 * Created on August 19, 2013, 11:33 AM
 */

#ifndef RESISTORLIST_H
#define	RESISTORLIST_H

#include "Rparser.h"

class ResistorList {
    
private:
    Resistor *head;
    Resistor *newResistor;
    int numRes;
    
public:
    ResistorList ();
    ~ResistorList();
    
    void insertResistor (string label, double resistance, int endpoints[2]);
    
    Resistor *getHead () const;
    int getNumRes () const;
    
    Resistor *findResistor (string label);
    
    void deleteResistor (string label);
    void deleteResistorList ();
    void print ();
};

#endif	/* RESISTORLIST_H */

