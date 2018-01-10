#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "ResistorList.h"
#include "Resistor.h"
using namespace std;

class Node
{
    public:
        //constructors
        Node();
        Node(string _name, double _resistance, int _node, int _othernode);
        Node(string _name, double _resistance, int _node, int _othernode, int secondnode);
                
        //modify functions
        void modifyNode(string _name, double _resistance, int _node, int _othernode);
        int modifyRes(string _name, double _resistance);
        
        //delete functions
        bool deleteAll();
        bool deleteAll2();
        bool deleteOne(string name);
        
        //print functions
        bool printOne(string name);
        bool printNode();
        
        //set and unset functions
        void setVoltage(double voltage);
        void setVoltage2(double voltage);
        void unsetVoltage();
        
        //get functions
        int getnodeID();
        Node* getNext();
        double getVoltage();
        double getReq();
        int getset();
        Resistor* getResistorHead();
        ResistorList* getResistorListHead();
        
        //set functions
        void resistorHead();
        void setNext(Node* _n);
        
        //find function
        double findr(string name);

      private:
        //node elements
        int nodeID;
        Node* nextNode = NULL;
        double nodeVoltage = 0;
        
        //resistor elements
        string name; 
        ResistorList* resisListHead = NULL;
        Resistor* resisHead = NULL; //no use
        
        //set variable is 0 when voltage is unset and 1 when voltage is set
        int set = 0;
};

#endif	/* NODE_H */


