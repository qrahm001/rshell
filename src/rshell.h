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

class singleCommand;
class multiCommand;

void icheck (string &input);  //input parser helper function
char getUserNameHostName(); //get user name and host name helper function

class rShell {
    
    protected:
    string uinput;

    public:
    rShell() {
        
        cout << " Enter command(s):" << endl;
        getUserNameHostName();
        getline(cin, uinput);
        icheck(uinput);
    }
};

class cmd {
    protected:
    vector<cmd> commands;

    public:
    void print() {}
};

class singleCommand : public cmd {
    private:
    cmd* comm; 

    public:
    singleCommand() {
        cout << "\n qazi single shade \n";
    }
    singleCommand(cmd* command) : comm(command) {} 
    void print() {
        cout << "In addition this should appear" << endl;
    }
};


class multiCommand : public cmd{
    private:
    
    public:
    multiCommand() {
        cout << "\n more than 1 single qazi's (all the single ladies.) \n";
    }
    void print()
    {
        cout << "We need more commands per line.";
    }
};

void icheck (string &input) {  //input parser helper function implementation
    char delim[] = ";,&&,||";                 //3 deliminators
    char semi[] = ";";                  
    char annd[] = "&&";                 
    char orr[] =  "||";                 
    int cmdCtr;
    
    cmdCtr = 0;
    vector<string> vCmdStr;                                     //vector of command string
    
    cout <<"You entered commands: " << input << endl;           //cout whatever was inputted
    
    char* userInput = (char*)input.c_str();                     //taking input as a string of characters and saving it as userinput
 
    char * pnt;                                                 //char pointer is created
    
    pnt=strtok( userInput, delim );         //pointer to the tokenizer which is scanning for the separating characters ||, &&, or ; (all part of the deliminators)
   
    while( pnt!= NULL )                 // while pointer does not equal the null character
    {
        printf( "Tokenized string using delim is:: %s\n", pnt );    //prints out the tokenized string without the delim
        
        vCmdStr.push_back(pnt);                     //pointer is pushed back
        pnt = strtok( NULL, delim );                //t
        cmdCtr++;
    }
    
        cout << "Total Number of commands entered: " << cmdCtr << endl;
        
    if (cmdCtr < 1) {                                //none case for commands
         cout << "No commands entered" << endl;     //cout <<nonecase
         
     }
    
     else if (cmdCtr == 1){                             //singlecommand case
        //cout << "Single command entered" << endl;
        //execute single command here
        system(userInput);
     }
     
     else   {
         cout << "Multi commands entered" << endl;
         //execute multi commands here stored in vCmdStr array
            
            char temp[] = "";
            
              for (int y = 0; y < vCmdStr.size(); ++y){
                  
                //need to put logic execute based on chain operators ; && || 
                if (userInput[y] == semi[0])
                {
                    cout << "semicolon";
                }
                
                
                system(vCmdStr[y].c_str());
              }
            
     }
     
}

char getUserNameHostName () {
    
        //get the hostname 
        char hostname[HOST_NAME_MAX];
        int result;
        result = gethostname(hostname, HOST_NAME_MAX);
        if (result)
            {
            perror("gethostname");
            return EXIT_FAILURE;
            }
        
        //get the user name
        char * user_name = getenv("USER");
        
        //output user name and host name 
            std::cout << user_name << "@" << hostname << "$";

        
        if (result < 0)
        {
            perror("printf");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    
}