#include <queue>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
  ifstream infile;
  queue<string> sotd;
  infile.open ("sotd.txt", ifstream::in);
  if(infile.is_open()) {
    while(infile.good()) {
      string line;
      getline(infile, line);
      sotd.push(line);
    }
  }
  cout << "The song of the day is: " << sotd.front() << endl;
}