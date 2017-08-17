#include "Rparser.h"

//extern easygl window;

Node::Node(int ID, bool isSetV_)
{
    nodeID = ID;
    isSetV = isSetV_;
    
    ResList = new ResistorList;
    next = NULL;
}

Node::~Node ()
{
    ;
}

void Node::print (int nodeIndex, int numRes)
{
    if(numRes > 0)
    {
        cout << "Connections at node " << nodeIndex << ": " << numRes << " resistor(s)" << endl;
        ResList->print ();
    }
}

ResistorList *Node::getResList () const
{
    return ResList;
}

Node *Node::getNext () const
{
    return next;
}

int Node::getNodeID() const
{
    return nodeID;
}

double Node::getNodeVoltage () const
{
    return nodeVoltage;
}

bool Node::getSetV_status () const
{
    return isSetV;
}

void Node::setNext(Node* nodePtr)
{
    next = nodePtr;
}

void Node::initNodeVoltage ()
{
    nodeVoltage = INITIAL_NODE_VOLTAGE;
}

void Node::setNodeVoltage (double newVoltage)//, NodeList &list)
{
    nodeVoltage = newVoltage;
}

void Node::findSetVoltageChange (double newVoltage, NodeList &list)
{
    double voltageChange = abs(newVoltage - nodeVoltage);
    
    list.setChangeOfVoltage(voltageChange);
    nodeVoltage = newVoltage;
}

void Node::setV_status (bool isSetV_)
{
    isSetV = isSetV_;
}

double Node::calculateVoltage (int nodeid, NodeList &list)
{
    double leftPart = 0;
    double rightPart = 0;
    double nodeV;
    
    Resistor *curr = ResList->getHead();
    
    while(curr != NULL)
    {
        leftPart += pow(curr->getResistance(), -1.0);
        
        int neighbourID = (curr->getEndpoints()[0] == nodeid) ? curr->getEndpoints()[1] : curr->getEndpoints()[0];
        double V_x = (list.findNode(neighbourID))->getNodeVoltage();
        
        rightPart += V_x / curr->getResistance();
        curr = curr->getNext();
    }
        
    nodeV = pow(leftPart, -1.0) * rightPart;
    
    return nodeV;
}

void Node::drawNode() {
    
	double xCen = xLeft + ((xRight - xLeft) / 2.0);
	double yCen = 30.0;
	
	stringstream ss;
	ss << nodeID;
	string id = ss.str();

	string text = "Node " + id;

    window.gl_setcolor (CORAL);
    window.gl_fillrect (xLeft, yBottom, xRight, yTop);

	window.gl_setcolor (BLACK);
	window.gl_drawtext (xCen, yCen, text);
}


void Node::setNode_draw_coord (double xLeft_, double yBottom_, double xRight_, double yTop_)
{
    xLeft = xLeft_;
    yBottom = yBottom_;
    xRight = xRight_;
    yTop = yTop_;
}

double Node::getNode_xLeft_coord () const
{
	return xLeft;
}

double Node::getNode_yBottom_coord () const
{
	return yBottom;
}

double Node::getNode_xRight_coord () const
{
	return xRight;
}

double Node::getNode_yTop_coord () const
{
	return yTop;
}

