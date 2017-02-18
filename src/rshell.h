#include "cmd.h"

void icheck (string &input);  //input parser helper function
char getUserNameHostName(); //get user name and host name helper function

class rShell {
    
    protected:
    string uinput;

    public:
    rShell() {
        while (uinput != "exit") {
            getUserNameHostName();
            getline(cin, uinput);
            icheck(uinput);
        }
    }
};

void icheck (string &input) {  //input parser helper function implementation
    char delim[] = ";,&&,||";                 //3 deliminators
    // char semi[] = ";";                  
    // char annd[] = "&&";                 
    // char orr[] =  "||";                 
    int cmdCtr;
    
    cmdCtr = 0;
    vector<string> vCmdStr;                                     //vector of command string
    vector<string> vCnctrStr;                                   //vector of connectors
    
    
    char* userInput = (char*)input.c_str();                     //taking input as a string of characters and saving it as userinput
 
    char * pnt;                                                 //char pointer is created
    
    pnt=strtok( userInput, delim );         //pointer to the tokenizer which is scanning for the separating characters ||, &&, or ; (all part of the deliminators)
   
    while( pnt!= NULL ) {                 // while pointer does not equal the null character
        vCmdStr.push_back(pnt);                     //pointer is pushed back
        pnt = strtok( NULL, delim );                //pointer is updated to next command location
        cmdCtr++;                                   //command counter updates
    }
        
    if (cmdCtr < 1) {                                //none case for commands
         cout << "No commands entered" << endl;     //cout <<nonecase
         
     }
    
     else if (cmdCtr == 1) {                             //singlecommand case
        //cout << "Single command entered" << endl;
        //execute single command here
        singleCommand* one = new singleCommand(vCmdStr.at(0));
        one->evaluate();
     }
     
     else {
         //execute multi commands here stored in vCmdStr array
        multiCommand* multi = new multiCommand(vCmdStr);
        multi->evaluate();    
     }
     
}

char getUserNameHostName () {
    
        //get the hostname 
        char hostname[HOST_NAME_MAX];
        int result;
        result = gethostname(hostname, HOST_NAME_MAX);
        if (result) {
            perror("gethostname");
            return EXIT_FAILURE;
            }
        
        //get the user name
        char * user_name = getenv("USER");
        
        //output user name and host name 
            std::cout << "[" << user_name << "@" << hostname << "]" << "$ ";

        
        if (result < 0) {
            perror("printf");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    
}
