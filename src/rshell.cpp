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
        
      getline(cin, input);  //gets userinput
      Hash(input);
      if (input != "exit") {
          Parse(input);
      }
    }
    return;
}

void Parse(string input) {
  vector<string> cmds;
  vector<string> cnctrs;
  int cmd_cntr = 0; //counter for amnt of entered commands
  singleCmd* sCmd;
  multiCmd* mCmd;
  
  for (unsigned i = 0; i < input.size(); ++i) { //pushes connectors into  a vector
      if (input.at(i) == ';') {
          cnctrs.push_back(";");
      }
      else if (input.at(i) == '&') {
          cnctrs.push_back("&&");
          if (i + 1 < input.size()) {
              ++i;
          }
      }
      else if (input.at(i) == '|') {
          cnctrs.push_back("||");
          if (i + 1 < input.size()) {
              ++i;
          }
      }
  }
  
  char input_ch[128];
  strcpy(input_ch, input.c_str());
  char* pch = strtok(input_ch, ";|&");
  
  while(pch != NULL) {
      cmds.push_back(pch);
      pch = strtok(NULL, ";|&");
      ++cmd_cntr;
  }
     
    if (cmd_cntr == 1) { 
      sCmd = new singleCmd(cmds.at(0)); //makes a single command
      sCmd->execute();  //runs the command
    }
  
    else if (cmd_cntr > 1) { //multiple commands case
      mCmd = new multiCmd(cmds, cnctrs);
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
