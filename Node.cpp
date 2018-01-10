#include "Node.h"
#include "Resistor.h"
#include "ResistorList.h"
#include <iostream>

//constructor
Node::Node()
:nextNode(NULL), resisHead(NULL), resisListHead(NULL)
{}

//creates new node and adds resistor to it
Node::Node(string _name, double _resistance, int _node, int _othernode)
:nodeID(_node)
{
    //declare resistor linked list
    ResistorList* rlist = new ResistorList;

    //add resistors to linked list
    rlist->addResistor(_name, _resistance, _node, _othernode);
    resisListHead = rlist;
}

//constructor
Node::Node(string _name, double _resistance, int _node, int _othernode, 
        int secondnode)
:nodeID(_othernode)
{
  
    //declare resistor linked list
    ResistorList* rlist = new ResistorList;

    //add resistors to linked list
    rlist->addResistor(_name, _resistance, _node, _othernode);
    resisListHead = rlist;
}

//adds resistor to an existing node
void Node::modifyNode(string _name, double _resistance, int _node, 
        int _othernode)
{
    resisListHead->addResistor(_name, _resistance, _node, _othernode);
}

//modify resistor function
int Node::modifyRes(string _name, double _resistance)
{
    bool a = false;
    a = resisListHead->changeResistor(_name, _resistance);
    if(a == true)
        return 1;
    else return 0;
}

//gets next node
Node* Node::getNext()
{
    return nextNode;
}

//sets the next node
void Node::setNext(Node* _n)
{
    nextNode = _n;
}

//gets the node id
int Node::getnodeID()
{
    return nodeID;
}

//delete all resistors
bool Node::deleteAll()
{
    //this linked list is now empty
    //resisListHead which is an object containing pointer to the linked list
    //is not deleted in case future resistors are added
    //resisListHead should always continue to point to rList (from constructor)
    bool successfulDelete = false;
    ResistorList* curr =  resisListHead;
    successfulDelete = curr->deleteAllResistors();
    return successfulDelete;
}

//delete all resistors: alternate function
bool Node::deleteAll2()
{
    //this linked list is now empty
    //resisListHead which is an object containing pointer to the linked list
    //is not deleted in case future resistors are added
    //resisListHead should always continue to point to rList (from constructor)
    bool successfulDelete = false;
    ResistorList* curr =  resisListHead;
    successfulDelete = curr->deleteAllResistors();
    delete resisListHead;
    resisListHead = NULL;
    return successfulDelete;
}

//delete one resistor
bool Node::deleteOne(string name)
{
    bool successfulDelete = false;
    ResistorList* curr =  resisListHead;
    successfulDelete = curr->deleteOneResistor(name);
    return successfulDelete;
}

//print one resistor
bool Node::printOne(string name)
{
    ResistorList* curr =  resisListHead;
    bool successfulPrint = false;

    successfulPrint  = curr->printOneResistor(name);
    return successfulPrint;
}

//print all resistors at this node
bool Node::printNode()
{
    ResistorList* curr =  resisListHead;
    int n = curr->getResNum();

    if(curr->getrhead() == NULL){
        //no resistors at this node
        return false;
    }
    else{
        //else print all resistors at this node
        cout << "Connections at node " << nodeID << " : " << n 
                << " resistor(s)" << endl;
        //prints resistors attached to this node
        curr->printConnections();
        return true;
    }

}

//set the node voltage
void Node::setVoltage(double voltage)
{
    nodeVoltage = voltage;
    set = 1;
}

//set the node voltage: alternate version for use in solve function
void Node::setVoltage2(double voltage)
{
    nodeVoltage = voltage;
}

//unset the node voltage
void Node::unsetVoltage()
{
    nodeVoltage = 0;
    set = 0;
}

//get the node voltage
double Node::getVoltage()
{
    return nodeVoltage;
}

//get the equilibrium resistance 1/Req = 1/Ra + 1/Rb + 1/Rc 
double Node::getReq()
{
    ResistorList* curr =  resisListHead;
    Resistor* curr2 = curr->getrhead();

    double r = 0;

    //iterates through resistors
    for (curr2; curr2 != NULL; curr2 = curr2->getNext()){
        r = r + 1/(curr2->getResistance());
    }

    return r;
}

//determine if a value has been set or not
int Node::getset()
{
    return set;
}

//set the pointer to resistor//use curr for now
    //deleteOne should return bool
void Node::resistorHead()
{
    resisHead = resisListHead->getrhead();
}

//get the pointer to resistor
Resistor* Node::getResistorHead()
{
    return resisHead;
}

//get the pointer to resistor list
ResistorList* Node::getResistorListHead()
{
    return resisListHead; 
}

//find whether a resistor exists
double Node::findr(string name)
{
    Resistor* curr = resisListHead->getrhead();
    while(curr != NULL){
        if(curr->getName() == name)
            return curr->getResistance();
        curr = curr->getNext(); 
    }
    return 0;
}

