#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>  // for transform
#include <cstdlib> 
using namespace std;

// Function to create the level bar
string createLevelBar(double progress, int maxLength) {
    int progressLength = static_cast<int>(progress * maxLength);
    string levelBar(progressLength, '=');
    levelBar.resize(maxLength, ' ');
    return levelBar;
}

int main() {
    ifstream inputFile("HOORAY.txt");
		string username;
    unordered_map<string, string> usernames_passwords;

    ifstream file("userssofar.txt");
    if (file.is_open()) {
        string line;
        string password;
        while (getline(file, line)) {
            if (line.find("Username: ") != string::npos) {
                username = line.substr(line.find("Username: ") + 10);
                usernames_passwords[username] = "";
            } else if (line.find("Password: ") != string::npos) {
                password = line.substr(line.find("Password: ") + 10);
                usernames_passwords[username] = password;
            }
        }
        file.close();
    } else {
        cout << "Failed to open userssofar.txt" << endl;
        return 1;
    }

    bool usernameExists = false;
		cout << "Enter your username: ";
    while (!usernameExists) {
        cin >> username;
        string lowercaseEnter = username;
        transform(lowercaseEnter.begin(), lowercaseEnter.end(), lowercaseEnter.begin(), ::tolower);
        if (usernames_passwords.find(lowercaseEnter) != usernames_passwords.end()) {
            usernameExists = true;
        } else {
            cout << "Enter your username CORRECTLY: ";
        }
    }

    string enterPassword;
    bool passwordCorrect = false;
	  cout << "Enter your password: ";
    while (!passwordCorrect) {
        cin >> enterPassword;
        string lowercaseEnterPassword = enterPassword;
        transform(lowercaseEnterPassword.begin(), lowercaseEnterPassword.end(), lowercaseEnterPassword.begin(), ::tolower);
        if (lowercaseEnterPassword == usernames_passwords[username]) {
            passwordCorrect = true;
        } else {
            cout << "Enter your password CORRECTLY: ";
        }
    }
		
	
    if (inputFile.is_open()) {
        double progress = 0.0;
        int maxLength = 0;
				int level = 0;
        string line;

        while (getline(inputFile, line)) {
            if (line.find("progress:") != string::npos) {
                progress = stod(line.substr(line.find(":") + 1));
            } else if (line.find("maxLength:") != string::npos) {
                maxLength = stoi(line.substr(line.find(":") + 1));
            } else if (line.find("level:") != string::npos) {
                level = stoi(line.substr(line.find(":") + 1));
            }
        }
				

        cout << "          _______" << endl;
        cout << "   \\o/  |         |" << endl;
        cout << "    |   |  HOORAY |" << endl;
        cout << "   / \\  | _______ |" << endl;

        cout << "\n";

        cout << "Current Level Progress: [" << createLevelBar(progress, maxLength) << "]" << endl;
				cout << username;

        inputFile.close();
    } else {
        cout << "Failed to open HOORAY.txt" << endl;
    }
	
    return 0;
}
