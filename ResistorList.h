#ifndef RESISTOR_LIST_H
#define RESISTOR_LIST_H

#include <string>
#include "Resistor.h"

class ResistorList
{
    public:
        //constructor
        ResistorList();
        
        //insert function
        void addResistor(string _name, double _resistance, int _node, int _othernode);
        
        //modify function
        bool changeResistor(string _name, double _resistance);
        
        //delete functions
        bool deleteAllResistors();
        bool deleteOneResistor(string name);
        
        //print functions
        bool printOneResistor(string name);
        void printConnections();
        
        //get functions
        Resistor* getrhead();
        int getResNum();
        
        //check function 
        bool checkResExists(string name);

    private:
        //ResistorList object contains a pointer to the first resistor
        Resistor* rhead;
};

#endif


