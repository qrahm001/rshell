#include "cmd.h"

void Parse(string input);
void Hash(string &input);
void Login();

int main(int argc, char* argv[]) {
    Login();
    return 0;
}

void Login() {
    passwd *p;
    uid_t uid;
    char host_arr[HOST_NAME_MAX];
    int host_error = gethostname(host_arr, sizeof(host_arr));
    
    
    if ((p = getpwuid(uid = getuid())) == NULL) { //print error if getpwuid fails
        perror("getpwuid() error");
    }
    
    else if (host_error != 0) {
        perror("gethostname() error");  //print error if gethostname fails
    }
    
    string host = host_arr;           //deletes extra stuff from hostname
    size_t found = host.find('-');
    if (found != string::npos) {
      host.erase(found);
    }  

    string input;
    while (input != "exit") {
      printf("[%s@%s]$ ", p->pw_name, host.c_str());  //%s for formatting, first one outputs first paramter, 2nd one outputs second parameter ...
      
      getline(cin, input);
      
      if (input.empty()) {
        cout << "Enter Commands!" << endl;
      }
      else {
        Hash(input);
        if (input.empty()) {
          cout << endl;
        }
      }
      
      if (input != "exit" && !input.empty()) {
          Parse(input);
      }
    }
    return;
}

void Parse(string input) {
  string command;
  vector<string> cmds;
  vector<string> cnctrs;
  int cmd_cntr = 0; //counter for amnt of entered commands
  singleCmd* sCmd;
  multiCmd* mCmd;
  
  //parses input for "[]" command
    string tmp = input;
    size_t open = tmp.find("[");
    size_t close = tmp.find("]");
    while (open != string::npos && close != string::npos) {
        tmp.replace(open, 1, "test");
        close = tmp.find("]");
        tmp.erase(close, 1);
        open = tmp.find("[");
        close = tmp.find("]");
    }
    
    while (tmp.at(0) == ' ') { //removes spaces from beginning of input
      tmp.erase(0, 1);
    }
    
    for (unsigned i = 0; i < tmp.size(); ++i) {
      if (tmp.at(i) == ';') {
        if (!command.empty()) {
          cmds.push_back(command);
          command.clear();
          ++cmd_cntr;
        }
        cnctrs.push_back(";");
      }
      else if (tmp.at(i) == '&') {
        if (!command.empty()) {
          cmds.push_back(command);
          command.clear();
          ++cmd_cntr;
        }
        cnctrs.push_back("&&");
        ++i;
      }
      else if (tmp.at(i) == '|') {
        if (i + 1 < tmp.size()) {
          if (tmp.at(i + 1) == '|') {
            if (!command.empty()) {
              cmds.push_back(command);
              command.clear();
              ++cmd_cntr;
            }
            cnctrs.push_back("||");
            ++i;
          }
        }
        command.push_back(tmp.at(i));
      }
      else if (tmp.at(i) == '(') {
        if (!command.empty()) {
          cmds.push_back(command);
          command.clear();
          ++cmd_cntr;
        }
        cnctrs.push_back("(");
      }
      else if (tmp.at(i) == ')') {
        if (!command.empty()) {
          cmds.push_back(command);
          command.clear();
          ++cmd_cntr;
        }
        cnctrs.push_back(")");
      }
      else {
        command.push_back(tmp.at(i));
      }
    }
    if (!command.empty()) {
      cmds.push_back(command);
      ++cmd_cntr;
    }
     
    if (cmd_cntr == 1) { 
      sCmd = new singleCmd(cmds.at(0)); //makes a single command
      sCmd->execute();  //runs the command
    }
  
    else if (cmd_cntr > 1) { //multiple commands case
        mCmd = new multiCmd(cmds, cnctrs); //normal multi command case
        mCmd->execute();
    }
    
    else {
      cout << "Error: Invalid amount of commands!" << endl;
    }
    return;
}

  
void Hash(string &input){
    size_t firstHash = input.find_first_of("#");               //erase anything after first hash
    if (firstHash != string::npos)
    {
        input.erase(input.begin() + firstHash, input.end());    //works
    }
}
