#include "Rparser.h"

NodeList::NodeList()
{
    head = NULL;
    ChangeOfVoltage = 0;
}

NodeList::~NodeList()
{
    deleteNodeList ();
}

Node *NodeList::insertNode (int ID, bool isSetV_)
{
    if(head == NULL)
    {
        newNode = new Node(ID, isSetV_);
        
        head = newNode;
        return head;
    }
    
    else
    {
        Node *curr = head;
        Node *prev = NULL;
        
        while(curr != NULL && curr->getNodeID() < ID)
        {  
            prev = curr;
            curr = curr->getNext();
        }
        
        if(curr != NULL && curr->getNodeID() == ID)
            return curr;
        
        else if(curr == NULL && prev->getNodeID() == ID)
            return prev;
        
        else
        {
            newNode = new Node(ID, isSetV_);
            
            if(prev == NULL)
            {
                newNode->setNext(head);
                head = newNode;
                return newNode;
            }

            else if(curr == NULL)
            {
                prev->setNext(newNode);
                return newNode;
            }

            else
            {
                prev->setNext(newNode);
                newNode->setNext(curr);
                return newNode;
            }
        }
    }
}

Node *NodeList::findNode(int ID)
{
    Node *curr = head;
    
    while(curr != NULL && curr->getNodeID() != ID)
        curr = curr->getNext();
    
    return curr;
}

Resistor *NodeList::resistorExists(string label)
{
    Node *curr = head;
    
    while(curr != NULL)
    {
        if(curr->getResList()->getHead() != NULL && curr->getResList()->findResistor(label) != NULL)
            return curr->getResList()->findResistor(label);
        
        curr = curr->getNext();
    }
    
    return NULL;
}

ResistorList *NodeList::findResList(string label)
{
    Node *curr = head;
    
    while(curr != NULL)
    {
        if(curr->getResList()->findResistor(label) != NULL)
            return curr->getResList();
        
        curr = curr->getNext();
    }
    
    return NULL;
}

void NodeList::changeResistance(Resistor *targetResistor, double resistance)
{
    int *endpoints = targetResistor->getEndpoints();
    
    Node *curr = head;
    
    while(curr != NULL)
    {
        if(curr->getNodeID() == *(endpoints + 0) || curr->getNodeID() == *(endpoints + 1))
            curr->getResList()->findResistor(targetResistor->getName())->setResistance(resistance);
        
        curr = curr->getNext();
    }
}

void NodeList::deleteResistor(Resistor *targetResistor)
{
    int *endpoints = targetResistor->getEndpoints();
    
    int nodeIDs[2];
    nodeIDs[0] = *(endpoints + 0);
    nodeIDs[1] = *(endpoints + 1);
    
    Node *curr = head;
    string resName = targetResistor->getName();
    
    while(curr != NULL)
    {
        if(curr->getNodeID() == nodeIDs[0] || curr->getNodeID() == nodeIDs[1])
            curr->getResList()->deleteResistor(resName);
            
        curr = curr->getNext();
    }
}

void NodeList::deleteNode (int ID)
{
    Node *curr = head;
    Node *prev = NULL;
        
    while(curr != NULL && curr->getNodeID() != ID)
    {
        prev = curr;
        curr = curr->getNext();
    }
        
    if(prev == NULL)
        head = curr->getNext();
    
    else
        prev->setNext(curr->getNext());
    
    delete curr->getResList();
    delete curr;
}

void NodeList::deleteNodeList ()
{
    Node *ptr;
    
    while(head != NULL)
    {
        ptr = head;
        ptr->getResList()->deleteResistorList();
        head = ptr->getNext();
 
        delete ptr->getResList();
        delete ptr;
    }
}

void NodeList::printNode (int nodeID)
{
    Node *curr = head;
    
    while(curr->getNodeID() != nodeID)
        curr = curr->getNext();
    
    curr->print(curr->getNodeID(), curr->getResList()->getNumRes());
}

void NodeList::printList ()
{
    Node *curr = head;
    
    while(curr != NULL)
    {
        curr->print(curr->getNodeID(), curr->getResList()->getNumRes());
        curr = curr->getNext();
    }
}

void NodeList::initializeNodeVoltages ()
{
    Node *curr = head;
    
    while(curr != NULL)
    {
        if(!curr->getSetV_status())
            curr->setNodeVoltage(INITIAL_NODE_VOLTAGE);
        
        else
        {
            if(ChangeOfVoltage < abs(curr->getNodeVoltage()))
                ChangeOfVoltage = abs(curr->getNodeVoltage());
        }
        
        curr = curr->getNext();
    }
}

void NodeList::setChangeOfVoltage (double voltageChange)
{    
    ChangeOfVoltage = voltageChange;
}

double NodeList::getChangeOfVoltage () const
{
    return ChangeOfVoltage;
}

void NodeList::calculateNodeVoltages ()
{
    Node *curr = head;
    double maxVoltageChange = 0;
    
    while(curr != NULL)
    {
        if(!curr->getSetV_status() && curr->getResList()->getHead() != NULL)
        {
            double newVoltage = curr->calculateVoltage (curr->getNodeID(), *this);
            
            if(newVoltage > maxVoltageChange)
                maxVoltageChange = newVoltage;
            
            curr->findSetVoltageChange(newVoltage, *this);
        }
            
        curr = curr->getNext();
    }   
}

void NodeList::printNodeVoltages (bool isAllSet)
{
    Node *curr = head;
    
    cout << "Solve:" << endl;
    
    while(curr != NULL && !isAllSet)
    {
    	if(curr->getResList()->getHead() != NULL)
	        cout << "  Node " << curr->getNodeID() << ": " << curr->getNodeVoltage() << " V" << endl;
    
        curr = curr->getNext();
    }
}

bool NodeList::isAnySet ()
{
    Node *curr = head;
    
    while(curr != NULL)
    {
        if(curr->getSetV_status())
            return true;
        
        curr = curr->getNext();
    }
    
    return false;
}

bool NodeList::isAllSet ()
{
    Node *curr = head;
    
    while(curr != NULL)
    {
        if(!curr->getSetV_status())
            return false;
        
        curr = curr->getNext();
    }
    
    return true;
}

void NodeList::draw () {
    // Iterate over Nodes, calling appropriate draw functions (probably in
    // class Node). See easygl.h for a list of drawing functions, like
    // window.gl_drawline (x1, y1, x2, y2).
    // Iterate over resistors, calling appropriate draw functions (probably in
    // class Resistor).
    // These functions will use new member variables that store drawing coordinates
    // for each Node and resistor.
    
    Node *curr = head;
    
    while(curr != NULL)
    {
        curr->drawNode();
        curr = curr->getNext();
    }
    
    Resistor *resList = curr->getResList()->getHead();
    while (resList != NULL) 
    {    
        resList->drawResistor();
        resList = resList->getNext();
    }
}

void NodeList::set_draw_coords (float& xleft, float& ybottom, float& xright, float& ytop) {
    // Iterate over Nodes and resistors, setting drawing coordinate member variables.
    // Return the minimum and maximum coordinates you will use, so they can be
    // passed to the easygl package via set_world_coordinates().
    
    Node *curr = head;
    int countNode = 0;
    int countRes = 0;
    
    xleft = 0;
    ybottom = 0;
    xright = 1000;
    ytop = 750;
    
    int node_xleft = xleft + 50;
    int node_ybottom = ybottom + 50;
    int node_ytop = node_ybottom + 700;
    
    while(curr != NULL)
    {
        Resistor *resList = curr->getResList()->getHead();
        while (resList != NULL) 
        {    
            resList = resList->getNext();
            countRes++;
        }
        
        curr->setNode_draw_coord(node_xleft, node_ybottom, node_xleft + 20, node_ytop);
        node_xleft += 160;
        
        curr = curr->getNext();
        countNode++;
    } 
    
}

