#include <iostream>
#include <string>

using namespace std;

int main() {
    string userResponse;
do {
    cout << "What help do you need? (Levels & Progress, Data Security, Algorithm for Music, Login and Passwords, or exit)" << endl;
    getline(cin, userResponse);
	
    if (userResponse == "Levels & Progress") {
        cout << "Our app uses levels and progress to allow users to get a certain amount of chances to find new songs that they will love. By running our app, your progress in a level increaes. When you level up, you earn more(2 * the new level) amount of songs. As you level up though, it's becomes harder to level up. Note: You start with 5 free songs." << endl;
    } else if (userResponse == "Data Security") {
        cout << "As Tuneup, our old company, Groovehub wasn't very careful with data security, however, we are new and renovated and we make sure that your music data is kept safe as we only access your tracks and PUBLIC playlists." << endl;
    } else if (userResponse == "Algorithm for Music") {
        cout << "Our app uses K-means of clustering of groups in order to pick and find new music that you may like based on the energy, danceability, loudness, acousticness, instrumentalness, liveness, valence, and tempo of the songs that you enjoy" << endl;
    } else if (userResponse == "Login and Passwords") {
        cout << "We have created a login account system in order to validate spotify usernames. This means that if you enter in a username that doesn't exist on Spotify, you will be prompted with an 401 error on Spotify's behalf because your account may not exist. In order to create any disrutption or spamming, we included passwords for the logins." << endl;
    }
		else if (userResponse == "exit") {
        break; 
		}
	else {
		cout << "If you got this, this means that you either misspelled your help request, or we're still working on more responses. If you want help quickly, email us at tuneupgroovehub@gmail.com" << endl;
	}
	} while (true);
    return 0;
}
