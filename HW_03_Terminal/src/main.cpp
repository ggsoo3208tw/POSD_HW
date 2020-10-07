#include <string>//string must include
#include <iostream>// cout,endl must include
#include <fstream>
using namespace std;

#include "terminal.h"

int main(int argc, char *argv[]){
  string input = string(argv[1]);
  string output = string(argv[2]);
  string featur = string(argv[3]);
  string order = string(argv[4]);
  fstream file;
  char ch, buffer[200];
  int chCount = 0;
  string result;
  file.open(input, ios::in);
  if(!file){
     cout << "Can't open file" << endl;
  }else{
    while(file.get(ch)){
      if(ch == '\r' || ch == '\n'){
        buffer[chCount++] = ' ';
        continue;
      }
      buffer[chCount++] = ch;
    }
    buffer[chCount]='\0';
    result = string(buffer) + ' ' + featur + ' ' + order;
    file.close();
  }
  Terminal terminal(result);
  cout << "------------" << endl;
  string a = terminal.showResult();
  file.open(output, ios::out | ios::trunc);
  if(file.fail()){
    cout << "Can't open file";
  }else{
    file.write(a.c_str(), sizeof(char)*a.size());
    file.close();
  }
  return 0;
}
