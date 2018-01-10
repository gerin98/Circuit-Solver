#include <string>
#include <iostream>
#include <iomanip>

#include "ResistorList.h"
#include "Resistor.h"

//constructor
ResistorList::ResistorList()
{}

//add resistor to network
void ResistorList::addResistor(string _name, double _resistance, int _node, 
        int _othernode)
{
    //create resistor object
    Resistor* newResistor = new Resistor(_name, _resistance, _node, _othernode);
    Resistor* temp = rhead;
    //if list is empty
    if(rhead == NULL){
        rhead = newResistor;
    }
    else{
        //loop to find last node in the list
        while(temp->getNext() != NULL){
            temp = temp->getNext();
        }
        temp->setNext(newResistor);
    }
}

//change the value of an existing resistor
bool ResistorList::changeResistor(string _name, double _resistance)
{
    //change resistor object
    Resistor* temp = rhead;
    if(rhead == NULL){
        //error
    }
    while((temp != NULL) && (temp->getName() != _name )){
        temp = temp->getNext();
    }
    if(temp == NULL){
    //return error   
    }
    else{
        temp->setVal(_name, _resistance);
        return true;
    }
    return false;
}

//deletes all resistors
bool ResistorList::deleteAllResistors()
{
    //delete all resistors
    Resistor* curr = rhead;
    while(curr != NULL){
        rhead = curr->getNext();
        delete curr;
        curr = rhead;
    }
    return true;
}

//deletes one resistor
bool ResistorList::deleteOneResistor(string name)
{
    //assume correct node was found till now
    Resistor* curr = rhead;
    Resistor* prev = NULL;

    while((curr != NULL) && (curr->getName() != name)){
        //find resistor if it exists
        prev = curr;
        curr = curr->getNext();
        //return false if not found
    }
    if (curr == NULL) {
        //resistor list is empty or resistor not found attached to this node
        return false;
    }
    if(prev == NULL){
        //match found at first element
        //move head pointer to the right
        rhead = curr->getNext();
    }
    else{
        prev->setNext(curr->getNext());
    }
    delete curr;
    curr = NULL;
    return true;

}

//prints one resistor
bool ResistorList::printOneResistor(string name)
{
    Resistor* curr = rhead;

    //loops through all resistors in the linked list
    for (curr; curr != NULL; curr = curr->getNext())  {
        if(curr->getName() == name){
            cout << "Print:" << endl;
            cout << left;
            cout << setw(20) << name << " ";
            cout << right;
            cout << setw(8) << fixed << setprecision(2) << curr->getResistance() 
                    << " ";
            cout << "Ohms " << curr->getEndPointOne() << " -> " 
                    << curr->getEndPointTwo() << endl;
            return true;
        }
    }
    return false;
}

//get the pointer to resistor
Resistor* ResistorList::getrhead()
{
  return rhead;
}

//print the connections
void ResistorList::printConnections()
{
    Resistor* curr = rhead;

    //prints all resistors at ResistorList
    for (curr; curr != NULL; curr = curr->getNext())  {
        cout << left;
        cout << "  " << setw(20) << curr->getName() << " ";
        cout << right;
        cout << setw(8) << fixed << setprecision(2) << curr->getResistance() 
                << " ";
        cout << "Ohms " << curr->getEndPointOne() << " -> " 
                << curr->getEndPointTwo() << endl;
    }
}

//get the number of resistors
int ResistorList::getResNum()
{
    Resistor* curr = rhead;
    int counter = 0;

    for (curr; curr != NULL; curr = curr->getNext())  {
        counter++;
    }
    return counter;
}

//check if resistor exists
bool ResistorList::checkResExists(string name)
{
    Resistor* curr = rhead;
    if(rhead == NULL)
        return false;
    else{
        for(curr; curr != NULL; curr = curr->getNext()){
            if(curr->getName() == name)
                return true;
        }
        return false;
    }
}


