#include <iostream>
#include <string>
using namespace std;
void isUsernameTaken(const string& username) {
    ifstream file("userssofar.txt");
    string line;
    bool isTaken = false;
    
    while (std::getline(file, line)) {
        if (line.find("Username: " + username) != string::npos) {
            isTaken = true;
            break;
        }
    }
    
    // Write the result to a new file
    ofstream resultFile("result.txt");
    if (resultFile.is_open()) {
        resultFile << boolalpha << isTaken;
        resultFile.close();
    } else {
        cerr << "Unable to open result file." << endl;
    }
}
