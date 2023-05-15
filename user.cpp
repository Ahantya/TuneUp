#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool isUsernameTaken(const string& username) {
    ifstream file("userssofar.txt");
    string line;
    
    while (std::getline(file, line)) {
        if (line.find("Username: " + username) != string::npos) {
            return true;
        }
    }
    
   return false;
}



int main() {
    string username, password, spotifyuser;
		
    // Get user input
    cout << "Create a User Account\n";
    cout << "Username: ";
    getline(cin, username);
	  while (isUsernameTaken(username)) {
			cout << "Enter a Unique Username: ";
    	getline(cin, username);
		}
    cout << "Password: ";
    getline(cin, password);


    // Open the file in append mode
    ofstream file("userssofar.txt", ios::app);
    
    if (!file.is_open()) {
        cerr << "Failed to open the file.\n";
        return 1;
    }
    
    // Write the account information to the file
    file << "Username: " << username << endl;
    file << "Password: " << password << endl;
		file << "Level: " << "1" << endl;
		file << "Progress: " << "0" << endl;
	  file << "maxLength: " << "10" << '\n';
		file << "\n";
		

	
    file.close();
    
    cout << "User account created successfully!\n";
    
    return 0;
}
