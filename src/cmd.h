#include "tests.h"

class cmd {
    protected:
    vector<string> commands;
    vector<string> connectors;
    
    public:
    virtual void execute() = 0;
};

class singleCmd : public cmd {
    public:
    singleCmd(string command) { //constructs the command, separates commands with paramater into command and parameters
        size_t found = command.find(" ");
        if (found == string::npos) { //if there are no paramters, just add the command
            commands.push_back(command);
            return;
        }
        char input_ch[128]; //separates commands and paramteters
        strcpy(input_ch, command.c_str());
        char* pch = strtok(input_ch, " ");
        while (pch != NULL) {
            commands.push_back(pch);
            pch = strtok(NULL, " ");
        }
        return;
    }
    void execute() {  //runs the stored command
        //char* tests = (char*)"test";
        pid_t PID = fork();
        
        if (PID < 0) {
            perror("fork() has failed");
            exit(-1);
        }
        
        else if (PID == 0) {
            char* args[128];
            unsigned i = 0; 
        
            for (i = 0; i < commands.size(); ++i) { //stores commands into array 
                args [i] = (char*)commands.at(i).c_str();
            }
            
            args [i] = NULL; //null so execvp knows where to stop
            
            if (commands.at(0) == "test") {
                if (commands.size() != 3 && commands.size() != 2) { //test argument # check
                    cout << "Invalid amount of test arguments!" << endl;
                    exit(-1);
                }
                tests begTest(commands);
                bool testRes = begTest.run();
                if (testRes == 1) {
                    cout << "(TRUE)" << endl;
                    exit(0);
                }
                cout << "(FALSE)" << endl;
                exit(-1);
            }
            
            else if ((execvp(args[0], args)) == -1) { 
                perror("execvp has failed:");
                exit(-1);
            }
        }
        
        else {
            int status; // passed into waitpid
            if (waitpid(PID, &status, 0) == -1) { //wait for child processes to end
                perror("wait() has failed");
            }
        }
        return;
    }
};

class multiCmd : public cmd {
    private:
    vector<string> tmp;
    vector<vector<string> > par_cmds; //commands with parameters
    
    public:
    multiCmd(vector<string> &cmds, vector<string> &cnctrs) { //constructs the command, separates commands with paramater into command and parameters
        commands = cmds;
        connectors = cnctrs;
        
        for (unsigned i = 0; i < commands.size(); ++i) {
            size_t found = commands.at(i).find(" ");
            if (found == string::npos) {  //command doesnt have parameters case
                tmp.push_back(commands.at(i));
                tmp.push_back("NULL");
                par_cmds.push_back(tmp);
                tmp.clear();
            }
            else {
                char input_ch[128];
                strcpy(input_ch, commands.at(i).c_str()); //tokenizes string
                char* pch = strtok(input_ch, " ");
                
                while (pch != NULL) {
                    tmp.push_back(pch);
                    pch = strtok(NULL, " ");
                }
                tmp.push_back("NULL");
                par_cmds.push_back(tmp);
                tmp.clear();
            }
        }
        return;
    }
    
    
    void execute() { 
        int success;
        bool group = false;
        bool groupCheck = false;
        while (par_cmds.size() > 0) { 
                if (par_cmds.at(0).at(0) == "exit") { //exit function
                    exit(0);
                }
                pid_t PID = fork(); 
                
                if (PID < 0) { //case if fork failed
                    perror("MultiCmd Fork() Failed:");
                    exit(EXIT_FAILURE);
                }
                
                else if (PID == 0) { //child process, runs commands
                    char* args[128];
                    unsigned k = 0; 
        
                    for (k = 0; k < par_cmds.at(0).size(); ++k) {
                        args [k] = (char*)par_cmds.at(0).at(k).c_str();
                    }
                    args [k - 1] = NULL;
                
                    if (par_cmds.at(0).at(0) == "test") { //if command is "test" case
                        if (commands.size() > 3 || commands.size() < 2) { //test argument # check
                            cout << "Invalid amount of test arguments!" << endl;
                            exit(EXIT_FAILURE);
                        }
                        tests begTest(par_cmds.at(0));
                        bool testRes = begTest.run();
                        if (testRes == true) {
                            cout << "(TRUE)" << endl;
                            exit(0);
                        }
                        cout << "(FALSE)" << endl;
                        exit(EXIT_FAILURE);
                    }
                    
                    if ((execvp(args[0], args)) == -1) { //executes command
                        perror("command has failed:");
                        exit(EXIT_FAILURE);
                    }
                    exit(0);
                }
                
                else { //parent
                    int status; // passed into waitpid
                    if (waitpid(PID, &status, 0) == -1) { //wait for child processes to end
                        perror("wait() has failed");
                    }
                    
                    success =  WEXITSTATUS(status); //checks whether child process was succesful or failed
                    par_cmds.erase(par_cmds.begin());
                    while (par_cmds.size() > 0 && par_cmds.at(0).at(0) == "NULL") {
                        par_cmds.erase(par_cmds.begin());
                    }
                    
                    if (connectors.size() > 0) { // logic commands
                        if (connectors.at(0) == "(") { //opening parenthesis means next few commands are grouped
                            group = true;
                            connectors.erase(connectors.begin());
                        }
                        else if (connectors.at(0) == ")") { //closing parenthesis means grouped commands over
                            connectors.erase(connectors.begin());
                            if (group == true) { //sets success value to overall group success
                                if (groupCheck == true) {
                                    success = 0;
                                }
                                else {
                                    success = 1;
                                }
                                groupCheck = false;
                            }
                        }
                        
                        if (connectors.size() > 0) { //decides whether next command(s) are skipped or run
                            if (par_cmds.size() > 0) {
                                if ((connectors.at(0) == "&&" && success != 0) || (connectors.at(0) == "||" && success == 0)) { //case where a command would be skipped
                                    if (connectors.size() > 1) {
                                        if (connectors.at(1) == "(") { //case where if following commands are grouped and need to be skipped
                                            group = true;
                                        }
                                    }
                                    if (group == true) { //if current command is part of a group of commands, skip all commands up to the close parthenthesis
                                        group = false;
                                        while (connectors.size() > 0 && par_cmds.size() > 0 && connectors.at(0) != ")") {
                                            if (connectors.at(0) != "&&") {
                                                par_cmds.erase(par_cmds.begin());
                                                connectors.erase(connectors.begin());
                                            }
                                            else {
                                                break;
                                            }
                                        }
                                    }
                                    else {
                                        par_cmds.erase(par_cmds.begin());
                                        connectors.erase(connectors.begin());
                                    }
                                }
                                else { //command ran
                                    groupCheck = true;
                                }
                            }
                            if (connectors.size() > 0) { //erase connector that was just used
                                connectors.erase(connectors.begin());
                            }
                        }
                    }
                }
            }
        }
};
