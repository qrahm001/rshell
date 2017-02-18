#include <iostream>
#include <vector>
#include <string>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>

using namespace std;
using std::vector ;

int fail = 0;

void exitFnctn() {
    cout << "\n Exiting rShell \n";
    return;
}

class cmd {
    protected:
    vector<string> commands;

    public:
    virtual void evaluate() = 0;
};

class singleCommand : public cmd {
    private:
    
    public:
    singleCommand(string command) 
    {
        commands.push_back(command);
    } 
    void evaluate() 
    {
        if (commands.size() < 1 || commands.size() > 1) {
            cout << "Error, Command not found! \n";
        }
        
        else {
            fail = system(commands.at(0).c_str());
            
            if (fail != 0) {
                cout << "Error: Command is not Correct!" << endl;
                fail = 0;
            }
        }
        
    }
};


class multiCommand : public cmd{
    private:
    
    public:
    multiCommand(vector<string> command) {
        commands = command;
    }
    void evaluate() {
        unsigned cmdctr = 0;
        while (cmdctr < commands.size() && fail == 0) {
            fail = system(commands.at(cmdctr).c_str());
                
            if (fail != 0) {
                cout << "Error: Command is not Correct!" << endl;
            }
            
            ++cmdctr;
        }    
    }
};
