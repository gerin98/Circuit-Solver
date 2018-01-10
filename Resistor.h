#ifndef RESISTOR_H
#define RESISTOR_H

#include <string>
#include <iostream>

using namespace std;

class Resistor
{
    public:
        //constructors
        Resistor();
        Resistor(string _name, double _resistance, int _node, int _othernode);
        
        //get functions
        Resistor* getNext();
        string getName();
        double getResistance();
        int getEndPointOne();
        int getEndPointTwo();
        
        //set functions
        void setNext(Resistor* _r);
        void setVal(string _name, double _resistance);

    private:
//resistor object contains its name, resistance, endpoints and pointer to next
        string label;
        double resistance;
        int endpoints[2] = {0};
        Resistor* nextResistor = NULL;
};

#endif	/* RESISTOR_H */


