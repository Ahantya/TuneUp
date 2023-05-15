#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int main() {
    string username, password, spotifyuser;
		
    // Get user input
    cout << "Create a User Account\n";
    cout << "Username: ";
    getline(cin, username);
    cout << "Password: ";
    getline(cin, password);
    cout << "Spotify UserName: ";
    getline(cin, spotifyuser);


    // Open the file in append mode
    ofstream file("userssofar.txt", ios::app);
    
    if (!file.is_open()) {
        cerr << "Failed to open the file.\n";
        return 1;
    }
    
    // Write the account information to the file
    file << "\n\nUsername: " << username;
    file << " , Password: " << password;
    file << " , Spotify Username: " << spotifyuser;

	
    file.close();
    
    cout << "User account created successfully!\n";
    
    return 0;
}
