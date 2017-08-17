
#include "Rparser.h"

ResistorList::ResistorList()
{
    numRes = 0;
    head = NULL;
}

ResistorList::~ResistorList()
{
    ;
}

Resistor *ResistorList::getHead() const
{
    return head;
}

void ResistorList::insertResistor(string label, double resistance, int endpoints[])
{
    newResistor = new Resistor(label, resistance, endpoints);
    
    if(head == NULL)
        head = newResistor;
    
    else
    {
        Resistor *current = head;
        while(current->getNext() != NULL)
            current = current->getNext();
        
        current->setNext(newResistor);
    }
    
    numRes++;
}

Resistor *ResistorList::findResistor(string label)
{
    Resistor *curr = head;
    
    while(curr != NULL && curr->getName().compare(label) != 0)
        curr = curr->getNext();
    
    return curr;
}

void ResistorList::deleteResistor(string label)
{
    Resistor *curr = head;
    Resistor *prev = NULL;
        
    while(curr != NULL && curr->getName().compare(label) != 0)
    {
        prev = curr;
        curr = curr->getNext();
    }
        
    if(prev == NULL)
        head = curr->getNext();
    
    else
        prev->setNext(curr->getNext());
    
    delete curr;
    numRes--;
}

void ResistorList::deleteResistorList()
{
    Resistor *ptr;
    
    while(head != NULL)
    {
        ptr = head;
        head = ptr->getNext();
        delete ptr;
    }
}

int ResistorList::getNumRes () const
{
    return numRes;
}

void ResistorList::print ()
{
    Resistor *curr = head;
    
    while(curr != NULL)
    {
        curr->print();
        curr = curr->getNext();
    }
}


