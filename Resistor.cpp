#include "Resistor.h"
#include <iomanip>

//constructor
Resistor::Resistor()
{}

//constructor
// _node represents the the node in which the ResistorList is part of while
// _othernode represents the resistor's other connecting node
Resistor::Resistor(string _name, double _resistance, int _node, int _othernode)
:label(_name), resistance(_resistance)
{
  endpoints[0] = _node;
  endpoints[1] = _othernode;
  nextResistor = NULL;
}

//get the next resistor
Resistor* Resistor::getNext()
{
  return nextResistor;
}

//get the resistor's name
string Resistor::getName()
{
  return label;
}

//set the pointer to the next resistor
void Resistor::setNext(Resistor* _r)
{
  nextResistor = _r;
}

//set the value of the resistor
void Resistor::setVal(string _name, double _resistance)
{
  resistance = _resistance;
}

//return the resistance
double Resistor::getResistance()
{
  return resistance;
}

//obtain the first endpoint
int Resistor::getEndPointOne()
{
  return endpoints[0];
}

//return the second endpoint
int Resistor::getEndPointTwo()
{
  return endpoints[1];
}


