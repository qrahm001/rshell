#ifndef TESTS_H
#define TESTS_H

#include <iostream>
#include <vector>
#include <string>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <pwd.h>

using namespace std;

class tests {
    protected:
    string file;
    string flag;
    struct stat fileAttr;
    
    public:
    tests(vector<string> &cmds) { //sets the flag as well as the target file
        if (cmds.size() == 2 || cmds.at(2) == "NULL") { // sets default case
            file = cmds.at(1);
            flag = "-e";
        }    
    
        else { //sets other cases
            
            if ((cmds.at(1) != "-f" && cmds.at(1) != "-d")) { 
                file = cmds.at(1);
                flag = "-e";
            }
            
            if (cmds.at(1) == "-e") {
                file = cmds.at(2);
                flag = "-e";
            }
            
            else {
                file = cmds.at(2);
                flag = cmds.at(1);
            }
        }
    }
    
    bool run() {
        if (flag == "-e") { //case where flag is -e
            char* cFile = (char*)file.c_str();
            if (stat(cFile, &fileAttr) != 0) { //case where stat fails
                perror("File not Found");
                return false;
            }
            if (S_ISREG(fileAttr.st_mode) || S_ISDIR(fileAttr.st_mode)) { //checks if file is either a file or directory
                return true;
            }
            return false;
        }
        else if (flag == "-f") { //case where flag is -f
            char* cFile = (char*)file.c_str();
            if (stat(cFile, &fileAttr) != 0) {
                perror("File not Found");
                return false;
            }
            return S_ISREG(fileAttr.st_mode); //checks if file is a file
        }
        else if (flag == "-d") { //case where flag is -d
            char* cFile = (char*)file.c_str();
            if (stat(cFile, &fileAttr) != 0) {
                perror("File not Found");
                return false;
            }
            return S_ISDIR(fileAttr.st_mode); //checks if file is a directory
        }
        return false;
    }
};

#endif
