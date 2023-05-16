#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>  // for transform
#include <cstdlib> 
using namespace std;

// Function to create the level bar
string createLevelBar(double progress, int maxLength) {
    int progressLength = (progress * maxLength);
    string levelBar(progressLength, '=');
    levelBar.resize(maxLength, ' ');
    return levelBar;
}

int main(int argc, char* argv[]) {
		int level = 0;
    ifstream inputFile("userssofar.txt");
		string username = argv[1];
		string hehe;

    ifstream file("userssofar.txt");
	
    if (inputFile.is_open()) {
        double progress = 0.0;
        int maxLength = 0;
        string line;

while (getline(inputFile, line)) {
	     if (line.find("Username: " + username) != string::npos) {
				while (getline(inputFile, line) && line != "") {
		    	if (line.find("Progress: ") != string::npos) {
		        progress = stod(line.substr(line.find(":") + 1));
		    } 
					else if (line.find("maxLength: ") != string::npos) {
		        maxLength = stoi(line.substr(line.find(":") + 1));
		    } 
					else if (line.find("Level: ") != string::npos) {
		        level = stoi(line.substr(line.find(":") + 1));
		    }
				}
}
				 
}

				
        cout << "          _______" << endl;
        cout << "   \\o/  |         |" << endl;
        cout << "    |   |  HOORAY |" << endl;
        cout << "   / \\  | _______ |" << endl;

        cout << "\n";

        cout << "Current Level " << level << " Progress: [" << createLevelBar(progress, maxLength) << "]" << endl;

        inputFile.close();
    } else {
        cout << "Failed to open HOORAY.txt" << endl;
    }
	
    return 0;
}
