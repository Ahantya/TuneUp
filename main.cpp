#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "other_file.cpp"
#include "help.cpp"
#include <algorithm>
 
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


const string WHITESPACE = " \n\r\t\f\v";
 
string ltrim(const string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == string::npos) ? "" : s.substr(start);
}
 
string rtrim(const string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == string::npos) ? "" : s.substr(0, end + 1);
}

string trim(const string &s) {
    return rtrim(ltrim(s));
}

vector<Genre> getGenres(ifstream& inputFile) {
    vector<Genre> genres;
    string line;

    while (getline(inputFile, line)) {
        size_t pos = line.rfind("(");

        if (pos != string::npos) {
            string genreNames = line.substr(pos + 1);
            size_t commaPos = genreNames.find(",");

            if (commaPos == string::npos)
            {
              string genreName = genreNames.substr(0, genreNames.length() - 1);
              bool inVector = false;
              for (int i = 0; i < genres.size(); i++)
              {
                if (genres.at(i).name == genreName)
                {
                  inVector = true;
                  genres.at(i).frequency++;
                  break;
                }
              }
              
              if (!inVector) genres.push_back({ genreName, 1 });
            }
            
            while (commaPos != string::npos) {
              string genreName = genreNames.substr(0, commaPos);
              genreName = trim(genreName);
              bool inVector = false;
              for (int i = 0; i < genres.size(); i++)
              {
                if (genres.at(i).name == genreName)
                {
                  inVector = true;
                  genres.at(i).frequency++;
                  break;
                }
              }

              if (!inVector) genres.push_back({ genreName, 1 });
              genreNames = genreNames.substr(commaPos + 2);
              commaPos = genreNames.find(",");
            }

            // Extract the last genre name (no trailing comma)
            string lastGenreName = genreNames.substr(0, genreNames.length() - 1);
            bool inVector = false;
              for (int i = 0; i < genres.size(); i++)
              {
                if (genres.at(i).name == lastGenreName)
                {
                  inVector = true;
                  genres.at(i).frequency++;
                  break;
                }
              }
            if (!inVector) genres.push_back({ lastGenreName, 1 });
        }
    }

    return genres;
}

void printGenres(const vector<Genre>& genres) {
    for (const auto& genre : genres) {
        cout << genre.name << " (" << genre.frequency << ")" << endl;
    }
}

void printGenrePercents(const vector<Genre>& genres)
{
  for (const auto& genre : genres) {
        cout << genre.name << " (" << ((double)genre.frequency)/genres.size() * 100 << "%)" << endl;
    }
}

bool sortByFrequency(const Genre& genre1, const Genre& genre2) {
    return genre1.frequency > genre2.frequency;
}

void forwardChaining(const vector<Genre>& genres) {
    // Perform forward chaining logic here
}

int main() {
    /*ifstream myFile("playlist_genres.txt");

    if (!myFile.is_open()) {
        cout << "Failed to open the file." << endl;
        return 1;
    }

    vector<Genre> genres = getGenres(myFile);
    myFile.close();

    // Sort genres by frequency in descending order
    sort(genres.begin(), genres.end(), sortByFrequency);

    printGenrePercents(genres);
    forwardChaining(genres);
    */
    return 0;
}




genre * recommendGenre(genre * genres)
{
  return NULL;
}
