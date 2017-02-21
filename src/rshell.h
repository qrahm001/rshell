#include <iostream>
#include <vector>
#include <string>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>

using namespace std;
using std::vector;

class singleCommand;
class multiCommand;

void icheck (string &input);  //input parser helper function
char getUserNameHostName(); //get user name and host name helper function
int runCmdCall(string &cmdString); //run the command and return exit code

class rShell {
    
    protected:
    string uinput;

    public:
    rShell() {
        while(uinput != "exit")
        {
       // cout << " Enter command(s):" << endl;
        getUserNameHostName();
        getline(cin, uinput);
        icheck(uinput);
        }
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
    }
    singleCommand(cmd* command) : comm(command) {} 
    void print() {
        //cout << "In addition this should appear" << endl;
    }
};


class multiCommand : public cmd{
    private:
    
    public:
    multiCommand() {
    }
    void print()
    {
        //cout << "We need more commands per line.";
    }
};

void icheck (string &input) {//input parser helper function implementation
    char delim[] = ";,&&,||";//3 delimiters
    char semi[] = ";";
    char annd[] = "&&";                 
    char orr[] =  "||";                 
    int cmdCtr;
    int runCmdResultExitCode = 0;
    
    cmdCtr = 0;
    vector<string> vCmdStr;                                     //vector of command string
    vector<string> vDelimStr;
    
    
    size_t firstHash = input.find_first_of("#");               //erase anything after first hash
    if (firstHash != string::npos)
    {
        input.erase(input.begin() + firstHash, input.end());    //works
    }
    
    char * userInput = (char*)input.c_str();                     //taking input as a string of characters and saving it as userinput
    char *userInputcopy = strdup(input.c_str());
    char * pnt;                                                 //char pointer is created
    
    //std::cout << userInputcopy << std::endl;
    
    pnt=strtok( userInput, delim );         //pointer to the tokenizer which is scanning for the separating characters ||, &&, or ; (all part of the deliminators)
   
    while( pnt!= NULL )                 // while pointer does not equal the null character
    {
        //printf( "Tokenized string using delim is:: %s\n", pnt );    //prints out the tokenized string without the delim
        
        
        if (userInputcopy[pnt-userInput+strlen(pnt)] == ';'){
            
         vDelimStr.push_back(semi);
            
        }
        else if (userInputcopy[pnt-userInput+strlen(pnt)] == '&') {
            vDelimStr.push_back(annd);
        }
        else if (userInputcopy[pnt-userInput+strlen(pnt)] == '|'){
            
         vDelimStr.push_back(orr);
            
        }
        
        vCmdStr.push_back(pnt);                     //pointer is pushed back
        pnt = strtok( NULL, delim );                //t
        cmdCtr++;
    }
    
      //  cout << "Total Number of commands entered: " << cmdCtr << endl;
        
    if (cmdCtr < 1) {                                //none case for commands
         cout << "No commands entered" << endl;     //cout <<nonecase
         
     }
    
     else if (cmdCtr == 1){                             //singlecommand case
        
            //printf ("Checking if processor is available...");
        //if (system(NULL)) puts ("Ok");  //Checkingif process is available.....
          //    else exit (EXIT_FAILURE);
        runCmdResultExitCode = system(userInput); //run single command
        
     }
     
     else   {
         //cout << "Multi commands entered" << endl;
         //execute multi commands here stored in vCmdStr array
     
                if (system(NULL)) puts ("");  //Checkingif process is available.....
                  else exit (EXIT_FAILURE);
                runCmdResultExitCode = system(vCmdStr[0].c_str()); //execute first command 
         
     
                //system(vCmdStr[0].c_str());  //execute first command
              for (unsigned y = 0; y < vDelimStr.size(); ++y){
                  
                  //cout << "this is in vDelimStr string " << vDelimStr[y] << endl;
                  
                  if (vDelimStr[y] == ";")
                  {
                    //  cout << "semicolon case found";
                        if (system(NULL)) puts ("");  //Checking if process is available.....
                          else exit (EXIT_FAILURE);
                        runCmdResultExitCode = system(vCmdStr[y+1].c_str()); //execute next command 
                  }
                  else if(vDelimStr[y] == "&&")
                  {
                      //cout << "&& case found. execute next command only if first command succeeds" << endl;
                      if (runCmdResultExitCode == 0) {
                        if (system(NULL)) puts ("");  //Checking if process is available.....
                          else exit (EXIT_FAILURE);
                        runCmdResultExitCode = system(vCmdStr[y+1].c_str()); //execute next command 
                      }
                  }
                  else if(vDelimStr[y] == "||")
                  {
           //           cout << "|| found. execute next command only if first command fails" << endl;
                      if (runCmdResultExitCode != 0) {
                        if (system(NULL)) puts ("");  //Checking if process is available.....
                          else exit (EXIT_FAILURE);
                        runCmdResultExitCode = system(vCmdStr[y+1].c_str()); //execute next command 
                      }
                  }
                  else
                  {
             //         cout << "execute this command." << endl;
                        if (system(NULL)) puts ("");  //Checking if process is available.....
                        else exit (EXIT_FAILURE);
                        runCmdResultExitCode = system(vCmdStr[0].c_str()); //execute next command 
                  }
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
