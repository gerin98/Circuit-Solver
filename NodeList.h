#ifndef NODE_LIST_H
#define NODE_LIST_H

#include <iostream>
#include "Node.h"

using namespace std;

class NodeList
{
  public:
    //default constructor
    NodeList();
    
    //check functions
    bool checkNode(int _nodeid);
    bool checkRes(string name);
    
    //insert function
    void insertNode(string _name, double _resistance, int _node1, int _node2);
    
    //modify function
    void modifyResistor(string _name, double _resistance);
    
    //delete functions
    void deleteNL(string name);
    void deleteNLAll();
    void deleteNLAll2();
    
    //print functions
    void printr(string name);
    void print();
    void printn(int id);
    
    //set and solve functions
    void setV(int id, double voltage);
    void unsetV(int id);
    void solve();

  private:
    //NodeList object contains a pointer to the first node
    Node* head;   
};

#endif


