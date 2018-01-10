#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <iomanip>

#include <algorithm>
#include <cctype>
#include <cmath>

#include "Node.h"
#include "NodeList.h"
#include "Resistor.h"
#include "ResistorList.h"

#define MIN_ITERATION_CHANGE 0.0001

using namespace std;

/*
    > NodeList should be an object containing a linked list of Nodes
    > Nodes should be objects each connecting to each other in increasing order
    > Node should also point to an object ResistorList
    > ResistorList should be an object containing a linked list of Resistors
    > Resistor objects should point to each other in order of insertion

*/


int main(int argc, char const *argv[]) {

    //listNode Nodehead;
    NodeList nlist;
    string command = "", name = "";
    double voltage = 0;
    int id;

    string line = "", node1 = "", node2 = "", resis = "";
    int node1num = 0, node2num = 0;
    char arg = '\0';
    double resisNum = 0.0;
    int rID = 0;

    cout << "> ";
    getline(cin,line);


    while(!cin.eof()){
        
        //get to command from user
        stringstream lineStream (line);
        lineStream >> command;

        //insert resistor command
        if(command == "insertR"){
          lineStream >> name >> resis >> node1 >> node2 >> arg;
          stringstream lineStream2 (node1);
          lineStream2 >> node1num;
          stringstream lineStream3 (node2);
          lineStream3 >> node2num;
          stringstream lineStream4 (resis);
          lineStream4 >> resisNum;

          nlist.insertNode(name,resisNum,node1num,node2num);
        }
        //modify resistor command
        else if(command == "modifyR"){
          lineStream >> name >> resis >> arg;
          stringstream lineStream4 (resis);
          lineStream4 >> resisNum;

          //need to find nodes which the resistor attaches to
          nlist.modifyResistor(name,resisNum);
        }
        //delete resistor command
        else if(command == "deleteR"){
          lineStream >> name >> arg;

          if(name == "all")
            nlist.deleteNLAll();
          else
            nlist.deleteNL(name);
        }
        //print resistor command
        else if(command == "printR"){
          lineStream >> name >> arg;

          nlist.printr(name);
        }
        //print node command
        else if(command == "printNode"){
          lineStream >> node1 >> arg;
          stringstream lineStream2 (node1);
          lineStream2 >> node1num;

          if(node1 == "all")
            nlist.print();
          else
            nlist.printn(node1num);
        }
        //set voltage command
        else if(command == "setV"){
          lineStream >> node1 >> voltage;  
          stringstream lineStream2 (node1);
          lineStream2 >> node1num;

          nlist.setV(node1num, voltage);
        }
        //unset voltage commmand
        else if(command == "unsetV"){
          lineStream >> node1 >> arg;
          stringstream lineStream2 (node1);
          lineStream2 >> node1num;  

          nlist.unsetV(node1num);
        }
        //solve command
        else if(command == "solve"){
            nlist.solve();
        }
        //otherwise say "invalid argument"
        else
          cout << "Invalid argument" << endl;

        //reinitialize variables and receive next line of input
        cout << "> ";
        line = "";
        command = "";
        getline (cin, line);

        //reinitialize all variables coming from stringstream
        arg = '\0';
        name = "", node1 = "", node2 = "", resis = "";
        node1num = 0, node2num = 0, resisNum = 0.0;     

    }

    /*function deletes all resistors in ResistorList, ResistorList object in 
    nodes as well as all nodes*/
    nlist.deleteNLAll2();


    return 0;
}


