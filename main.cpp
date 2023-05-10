#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "other_file.cpp"
#include "help.cpp"

using namespace std; 

struct genre {
  string name;
  int frequency = 0;
};

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Genre {
    string name;
    int frequency = 0;
};

vector<Genre> getGenres(ifstream& inputFile) {
    vector<Genre> genres;
    string line;

    while (getline(inputFile, line)) {
        size_t pos = line.find("(");

        if (pos != string::npos) {
            string genreNames = line.substr(pos + 1);
            size_t commaPos = genreNames.find(",");
            
            while (commaPos != string::npos) {
                string genreName = genreNames.substr(0, commaPos);
                genres.push_back({ genreName, 1 });
                genreNames = genreNames.substr(commaPos + 1);
                commaPos = genreNames.find(",");
            }

            // Extract the last genre name (no trailing comma)
            string lastGenreName = genreNames.substr(0, genreNames.length() - 1);
            genres.push_back({ lastGenreName, 1 });
        }
    }

    return genres;
}

void printGenres(const vector<Genre>& genres) {
    for (const auto& genre : genres) {
        cout << genre.name << " (" << genre.frequency << ")" << endl;
    }
}

bool sortByFrequency(const Genre& genre1, const Genre& genre2) {
    return genre1.frequency > genre2.frequency;
}

void forwardChaining(const vector<Genre>& genres) {
    // Perform forward chaining logic here
}

int main() {
    ifstream myFile("playlist_genres.txt");

    if (!myFile.is_open()) {
        cout << "Failed to open the file." << endl;
        return 1;
    }

    vector<Genre> genres = getGenres(myFile);
    myFile.close();

    // Sort genres by frequency in descending order
    sort(genres.begin(), genres.end(), sortByFrequency);

    printGenres(genres);
    forwardChaining(genres);

    return 0;
}




genre * recommendGenre(genre * genres)
{
  return NULL;
}
