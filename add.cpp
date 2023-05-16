#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm> // for trim

using namespace std;

// Function to trim leading and trailing whitespaces
void trim(string& str) {
    str.erase(str.begin(), find_if(str.begin(), str.end(), [](int ch) {
        return !isspace(ch);
    }));

    str.erase(find_if(str.rbegin(), str.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), str.end());
}

int main(int argc, char* argv[]) {
    string username = argv[1];
    ifstream inputFile("userssofar.txt");
    ofstream outputFile("temp.txt");
    double progress = 0.0;
    int maxLength = 0;
    int level = 0;
    string password;  // Add password variable
    string line;
    bool userFound = false;

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            if (line.find("Username: " + username) != string::npos) {
                userFound = true;
                while (getline(inputFile, line) && line != "") {
                    if (line.find("Progress: ") != string::npos) {
                        progress = stod(line.substr(line.find(":") + 1));
                    } else if (line.find("maxLength: ") != string::npos) {
                        maxLength = stoi(line.substr(line.find(":") + 1));
                    } else if (line.find("Level: ") != string::npos) {
                        level = stoi(line.substr(line.find(":") + 1));
                    } else if (line.find("Password: ") != string::npos) {
                        password = line.substr(line.find(":") + 1);
                        trim(password);  // Trim leading and trailing whitespaces
                    }
                }
            }
        }

        inputFile.close();
        inputFile.open("userssofar.txt");

        if (userFound) {
            progress += 0.05;
            if (progress >= 1) {
                progress = progress - 1;
                level++;
                maxLength += 5;
								cout << endl << "LEVEL UP!" << endl;
            }
        }

        if (inputFile.is_open()) {
            while (getline(inputFile, line)) {
                if (line.find("Username: " + username) != string::npos) {
                    userFound = true;
                    outputFile << line << endl;
                    outputFile << "Password: " << password << endl;
                    outputFile << "Progress: " << progress << endl;
                    outputFile << "maxLength: " << maxLength << endl;
                    outputFile << "Level: " << level << endl;
                    outputFile << '\n';
                    while (getline(inputFile, line) && line != "") {
                        // Skip the old info
                    }
                } else {
                    outputFile << line << endl;
                }
            }

            if (!userFound) {
                cout << "Username not found." << endl;
            }

            inputFile.close();
            outputFile.close();
        } else {
            cout << "Failed to open file." << endl;
        }
    } else {
        cout << "Failed to open file." << endl;
    }

    // Rename the temp file to the original file
    if (rename("temp.txt", "userssofar.txt") != 0) {
        cout << "Failed to rename file." << endl;
    }

    return 0;
}
