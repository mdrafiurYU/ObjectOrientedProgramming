/* 
 * File:   NodeList.h
 * Author: rashidmd
 *
 * Created on October 31, 2013, 3:12 AM
 */

/* 
 * File:   NodeList.h
 * Author: rashidmd
 *
 * Created on August 19, 2013, 11:34 AM
 */

#ifndef NODELIST_H
#define	NODELIST_H

#include "Rparser.h"

class NodeList {
    
private:
    Node *head;
    Node *newNode;
    double ChangeOfVoltage;
    
public:
    NodeList();
    ~NodeList();
    
    Node *insertNode (int ID, bool isSetV_);
    Resistor *resistorExists (string label);
    
    Node *findNode (int ID);
    ResistorList *findResList (string label);
    
    void setChangeOfVoltage (double voltageDiff);
    double getChangeOfVoltage () const;
    
    void calculateNodeVoltages ();
    void initializeNodeVoltages ();
    void changeResistance (Resistor *targetResistor, double resistance);

    bool isAnySet ();
    bool isAllSet ();

    void deleteResistor (Resistor *targetResistor);
    void deleteNode (int ID);
    void deleteNodeList ();

    void printNode (int nodeID);
    void printNodeVoltages (bool isAllSet);
    void printList ();
    void draw ();
    void set_draw_coords (float& xleft, float& ybottom, float& xright, float& ytop);
};

#endif	/* NODELIST_H */

