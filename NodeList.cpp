#include "NodeList.h"
#include "Node.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>

#define MIN_ITERATION_CHANGE 0.0001

using namespace std;

//constructor initially sets the pointer to node to NULL
NodeList::NodeList()
{
    head = NULL;
}

//function that only returns true if a node exists
bool NodeList::checkNode(int _nodeid)
{
    if(head != NULL){
        for (Node *curr = head; curr != NULL; curr = curr->getNext())
        {
            if (curr->getnodeID() == _nodeid)
                return true;
        }
        return false;
    }
    return false;
}

//function that returns true if a resistor already exists in the network
bool NodeList::checkRes(string name)
{
    bool check = false;
    Node* curr = head;
    ResistorList* curr2 = NULL;
    
    if(curr != NULL){
        for (curr; curr != NULL; curr = curr->getNext()){
            if(curr->getResistorListHead() == NULL){
                //no resistors at node
            }
            else{
                curr2 = curr->getResistorListHead();
                //function in ResistorList that searches for a matching resistor
                check = curr2->checkResExists(name);
                if(check == true)
                    return true;
            }
        }
        return false;
    }
    else
        return false;
    
}

//inserts a node into the linked list in ascending order
void NodeList::insertNode (string _name, double _resistance, int _node1, 
                           int _node2)
{
/******************* case1 node1: node already exist **************************/
    
    //first check if resistor already exists. If it does: ERROR 
    bool resistorExists = false; 
    resistorExists = checkRes(_name); 
    if(resistorExists){
        cout << "Error: resistor " << _name << " already exists" << endl;
        return;
    }

    //determine if node already exists. If it does, add resistor to this node.
    //otherwise create a new node before adding the resistor to it
    bool nodeExists = false;
    nodeExists = checkNode(_node1);
    Node *curr = head;
    Node *prev = NULL;

    if(nodeExists == true){
        //find node
        while(curr->getnodeID() != _node1){
            prev = curr;
            curr = curr->getNext();
        }
        //add new resistor to this node
        curr->modifyNode(_name, _resistance, _node1, _node2);
    }
/***************** case2 node1: node does not yet exist ***********************/
  
    //creates node for _node1 where _node2 is the _othernode
    if(nodeExists == false){
        //create node
        Node *newNode1 = new Node(_name, _resistance, _node1, _node2);
        curr = head;
        prev = NULL;

        //node list is filled: insert node in order
        if(head != NULL){
            while((curr != NULL) && (curr->getnodeID() < _node1)){
                //keep incrementing until end or desired position is reached
                prev = curr;
                curr = curr->getNext();
            }
            if(prev == NULL){
                //insert before the first node
                newNode1->setNext(curr);
                head = newNode1;
            }
            else{
                newNode1->setNext(curr);
                prev->setNext(newNode1);
            }
        }
        //node list is empty: add resistor to head
        else{
            head = newNode1;
            newNode1->setNext(NULL);
        }
    }
    
//-------------------------reinitialize variables-------------------------------

/******************* case1 node2: node already exist **************************/
    
    //first check if resistor already exists. If it does: ERROR 
    nodeExists = false;
    nodeExists = checkNode(_node2);
    curr = head;
    prev = NULL;

    //determine if node already exists. If it does, add resistor to this node.
    //otherwise create a new node before adding the resistor to it
    if(nodeExists == true){
        //find node
        while(curr->getnodeID() != _node2){
            prev = curr;
            curr = curr->getNext();
        }
        //add new resistor to this node
        curr->modifyNode(_name, _resistance, _node1, _node2);
    }
/***************** case2 node2: node does not yet exist ***********************/
    
    //creates node for _node2 where _node1 is the _othernode
    if(nodeExists == false){
        //create node
        //second node calls different constructor specific to this node
        //so that node connections can remain in same order as user input
        Node *newNode2 = new Node(_name, _resistance, _node1, _node2, 2);
        curr = head;
        prev = NULL;

        //node list is filled: insert node in order
        if(head != NULL){
            while((curr != NULL)   && (curr->getnodeID() < _node2)){
                //keep incrementing until end or desired position is reached
                prev = curr;
                curr = curr->getNext();
            }
            if(prev == NULL){
                //insert before the first node
                newNode2->setNext(curr);
                head = newNode2;
            }
            else{
                newNode2->setNext(curr);
                prev->setNext(newNode2);
            }
        }
        //node list is empty: add resistor to head
        else{
            head = newNode2;
            newNode2->setNext(NULL);
        }
    }

    //print outputs to screen
    cout << "Inserted: resistor " << _name << " " << fixed << setprecision(2) 
            << _resistance << " Ohms " << _node1 << " -> " << _node2 << endl;
  
}

//modify resistor function
void NodeList::modifyResistor(string _name, double _resistance)
{
    Node *curr = head;
    Resistor* curr2;
    bool check = false;
    double a = 0;
    double b = 0;

    //find the node
    if(curr == NULL){
        cout << "Error: resistor " << _name << " not found" << endl;
        return;
    }
    while(curr != NULL){
        a = curr->findr(_name);
        if(a != 0)
            b = a;
        curr = curr->getNext();
    }
    curr = head;
    //modify the resistor if found
    //b is a counter to determine if a resistor exists
    if(b != 0){
        cout << "Modified: resistor " << _name << " from " << fixed 
                << setprecision(2) << b << " Ohms to " << fixed 
                << setprecision(2) << _resistance << " Ohms" <<endl;

        while(curr != NULL){
            a = curr->modifyRes(_name, _resistance);
            b = b + a;
            if(b == 2){
                //
            }
            curr = curr->getNext();
        }
    }
    //print error message
    else{
        cout << "Error: resistor " << _name << " not found" << endl;
        return;
    }

}

//delete function for 1 resistor
void NodeList::deleteNL(string name)
{
    //need to search for all nodes containing the resistor
    Node *curr = head;
    bool successfulDelete = false;
    int counter = 0;

    //deleteOne function called for every node in linked list until all 
    //resistors of matching names are deleted
    for (curr; curr != NULL; curr = curr->getNext()){
        successfulDelete = curr->deleteOne(name);
        if(successfulDelete){
            counter++;
        }
        if(counter == 2){
            break;
        }
    }
    if(successfulDelete){
        cout << "Deleted: resistor " << name << endl;
    }
    if(!successfulDelete){
        cout << "Error: resistor " << name << " not found" << endl;
    }
}

//delete function for all resistors
void NodeList::deleteNLAll()
{
  //need to search for all nodes containing the resistor
  Node *curr = head;
  bool successfulDelete = false;

  //delete All function called for every node in linked list
  for (curr; curr != NULL; curr = curr->getNext()){
    successfulDelete = curr->deleteAll();
  }
  cout << "Deleted: all resistors" << endl;
}

//delete function to be called at the end of the program to prevent memory leaks
void NodeList::deleteNLAll2()
{
    Node *curr = head;
    bool successfulDelete = false;
    for (curr; curr != NULL; curr = curr->getNext()){
        successfulDelete = curr->deleteAll2();
    }
    curr = head;
    
    while(curr != NULL){
        head = curr->getNext();
        delete curr;
        curr = head;
    }
    head = NULL;   
}

//print resistor function
void NodeList::printr(string name)
{
    Node *curr = head;
    bool successfulPrint = false;
    //loop through all nodes
    //until successfulPrint == true or NULL is reached
    if(curr != NULL){
        for (curr; curr != NULL; curr = curr->getNext()){
            successfulPrint = curr->printOne(name);
            if(successfulPrint)
                break;
        }
    }
    if(successfulPrint == false){
        //error message
        cout << "Error: resistor " << name << " not found" << endl;
    }
}

//function to print all nodes
void NodeList::print()
{
    Node *curr = head;
    bool successfulPrint = false;
    //loop through all nodes
    if(curr == NULL){
        cout << "Print: " << endl;
        return;
    }
    else
        cout << "Print: " << endl;
    //loop through nodes
    for (curr; curr != NULL; curr = curr->getNext()){
        successfulPrint = curr->printNode();
    }
}

//function to print one node
void NodeList::printn(int id)
{
    Node *curr = head;
    bool successfulPrint = false;
    int n = 0;

    //loop through all nodes and check for nodeid match
    for (curr; curr != NULL; curr = curr->getNext()){
        n = curr->getnodeID();
        if(n == id){
            //print node
            cout << "Print: " << endl;
            successfulPrint = curr->printNode();
            break;
        }
    }
    if(!successfulPrint){
        cout << "Error: node " << id << " not found" << endl;
    }

}

//function to set voltage. this value cannot be changed unless it's unset
void NodeList::setV(int id, double voltage)
{
    Node *curr = head;
    int n = 0;

    //loop through nodes until match is found
    for (curr; curr != NULL; curr = curr->getNext()){
        n = curr->getnodeID();
        if(n == id){
            curr->setVoltage(voltage);
            cout << "Set: node " << id << " to " << voltage << " Volts" << endl;
            return;
        }
    }
    cout << "Error: node " << id << " not found" << endl;
}

//function to unset the voltage. voltages will be determined by solve
void NodeList::unsetV(int id)
{
    Node *curr = head;
    int n = 0;
    
    //loop through nodes until match is found
    for (curr; curr != NULL; curr = curr->getNext()){
        n = curr->getnodeID();
        if(n == id){
            curr->unsetVoltage();
            cout << "Unset: the solver will determine the voltage of node " 
                    << id << endl;
            return;
        }
    }
    cout << "Error: node " << id << " not found" << endl;
}

//solve function
void NodeList::solve()
{
    Node *curr;
    Node *curr3;
    curr = head;
    curr3 = head;
    int numNode = 0;
    int dummy = 0;
    double marker = 1;
    double marker2 = 0;
    //first need to determine how many nodes
    for (curr; curr != NULL; curr = curr->getNext()){
      numNode++;
    }
  
    curr = head;
    double voltageArray[numNode][3];
    for(int i = 0; i < numNode; i++){
          voltageArray[i][0] = curr->getnodeID();
          voltageArray[i][1] = curr->getVoltage();
          voltageArray[i][2] = curr->getset();
          curr = curr->getNext();
    }
  
    for(int i = 0; i < numNode; i++){
        dummy = dummy + voltageArray[i][2] ;
    }
    if(dummy == 0){
        cout << "Error: no nodes have their voltage set" << endl;
        return;
    }
    else{
        do{
        curr = head;

        int p = 0;
        int res = 0;
        double volt = 0.0;
        double _VOLTAGE = 0.0;
        double Veq = 0.0;
        double Req = 0;

        Resistor* curr2 = NULL;

        int i = 0;
        curr = head;
        curr3 = head;

              for (curr; curr != NULL; curr = curr->getNext()){
                if(curr->getset() == 0){    //only update if not set 

                    
                    curr2 = curr->getResistorListHead()->getrhead();
                    

                    Req = 1/(curr->getReq());

                    while(curr2 != NULL){
                          //OBTAIN CONNECTING NODE
                        p = curr2->getEndPointTwo();
                        if(p == curr->getnodeID()){
                            p = curr2->getEndPointOne();
                        }
                        for(curr3;curr3 != NULL; curr3 = curr3->getNext()){
                            if(p == curr3->getnodeID()){
                                volt = curr3->getVoltage();
                                break;
                            }
                        }
                        
                        res = curr2->getResistance(); 
                        Veq = Veq + volt/res;
                        curr2 = curr2->getNext();
                        curr3 = head;
                    }

                    

                    _VOLTAGE = Req * Veq;

                    marker = fabs(curr->getVoltage() - _VOLTAGE);
                    if(marker > marker2)
                        marker2 = marker;

                    //voltageArray[i][1] = _VOLTAGE;
                    curr->setVoltage2(_VOLTAGE);
                    i++;
                    Veq = 0;
                    Req = 0;
                    res = 0;
                    volt = 0;
                    _VOLTAGE;
                }
                else
                    i++;
              }
          
        }while(marker > MIN_ITERATION_CHANGE);
    }
    curr = head;
    cout << "Solve:" << endl;
    for(curr; curr != NULL; curr = curr->getNext()){
        cout << "Node " << curr->getnodeID() << ": " << curr->getVoltage() 
                << " V" << endl;
    }
}


