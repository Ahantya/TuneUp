#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int main() {
    string username, password;
		
    // Get user input
    cout << "Create a User Account\n";
    cout << "Username: ";
    getline(cin, username);
    cout << "Password: ";
    getline(cin, password);


    // Open the file in append mode
    ofstream file("userssofar.txt", ios::app);
    
    if (!file.is_open()) {
        cerr << "Failed to open the file.\n";
        return 1;
    }
    
    // Write the account information to the file
    file << "Username: " << username << "\n";
    file << "Password: " << password << "\n\n";

	
    file.close();
    
    cout << "User account created successfully!\n";
    
    return 0;
}
