/* 
 * File:   Node.h
 * Author: rashidmd
 *
 * Created on August 19, 2013, 11:33 AM
 */

#ifndef NODE_H
#define	NODE_H

#define MAX_RESISTOR_NAME_LEN 20
#define RESISTOR_FIELD_WIDTH 8

class ResistorList;
class NodeList;

class Node {

private:
    int nodeID;
    ResistorList *ResList;
    Node *next;
    double nodeVoltage;
    bool isSetV;
    
    double xLeft, yBottom, xRight, yTop;
    
public:
    Node(int ID, bool isSetV_);
    ~Node();
    
    ResistorList *getResList () const;
    
    void print (int nodeIndex, int numRes);
    
    int getNodeID () const;
    Node *getNext () const;
    bool getSetV_status () const;
    double getNodeVoltage () const;
    
    double getNode_xLeft_coord () const;
    double getNode_yBottom_coord () const;
    double getNode_xRight_coord () const;
    double getNode_yTop_coord () const;
    
    void setNode_draw_coord (double xLeft_, double yBottom_, double xRight_, double yTop_);
    
    double calculateVoltage (int nodeid, NodeList &list);
    
    void initNodeVoltage ();
    void setNext (Node *nodePtr);
    void setNodeVoltage (double newVoltage);
    void findSetVoltageChange (double newVoltage, NodeList &list);
    void setV_status (bool isSetV_);
    void drawNode ();
};

#endif	/* NODE_H */

