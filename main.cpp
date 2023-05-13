#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cmath>
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
//{"danceability": 0.6399, "energy": 0.5976, "loudness": -7.3482, "acousticness": 0.3872, "instrumentalness": 0.0162, "liveness": 0.2271, "valence": 0.448, "tempo": 113.3114}
/*Song tempAverages = {"Averages", 0.6399, 0.5976, -7.3482, 0, 0.3872, 0.0162, 0.2271, 0.448, 0};
*/
struct Song {
  string name;
  double danceability;
  double energy;
  double loudness;
  double speechiness;
  double acousticness;
  double instrumentalness;
  double liveness;
  double valence;
  double distanceToAverage;
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

double distance(Song song1, Song song2)
{
  return sqrt(pow(song1.danceability - song2.danceability, 2) + pow(song1.energy - song2.energy, 2) + pow(song1.loudness - song2.loudness, 2)
 + pow(song1.acousticness - song2.acousticness, 2) + pow(song1.instrumentalness - song2.instrumentalness, 2) + pow(song1.liveness - song2.liveness, 2) + pow(song1.valence - song2.valence, 2));
}

vector<Song> getSongs(ifstream& inputfile, Song average)
{
  vector<Song> songs;
  string line;

  getline(inputfile, line);
  while (getline(inputfile, line))
  {
    Song newSong;
    newSong.danceability = stod(line.substr(0, line.find(",")));
    line = line.substr(line.find(",") + 1);
    newSong.energy = stod(line.substr(0, line.find(",")));
    line = line.substr(line.find(",") + 1);
    line = line.substr(line.find(",") + 1);
    newSong.loudness = stod(line.substr(0, line.find(",")));
    line = line.substr(line.find(",") + 1);
    line = line.substr(line.find(",") + 1);
    newSong.speechiness = stod(line.substr(0, line.find(",")));
    line = line.substr(line.find(",") + 1);
    newSong.acousticness = stod(line.substr(0, line.find(",")));
    line = line.substr(line.find(",") + 1);
    newSong.instrumentalness = stod(line.substr(0, line.find(",")));
    line = line.substr(line.find(",") + 1);
    newSong.liveness = stod(line.substr(0, line.find(",")));
    line = line.substr(line.find(",") + 1);
    newSong.valence = stod(line.substr(0, line.find(",")));
    line = line.substr(0, line.rfind(","));
    line = line.substr(0, line.rfind(","));
    line = line.substr(line.rfind(",") + 1);
    newSong.name = line.substr(0, line.find(","));
    line = line.substr(line.find(",") + 1);

    newSong.distanceToAverage = distance(newSong, average);
    
    songs.push_back(newSong);
  }

  return songs;
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

void printSongs(const vector<Song>& songs)
{
  for (const auto& song : songs) {
        cout << song.name << " (" << song.distanceToAverage << ")" << endl;
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

bool sortByDistance(const Song& song1, const Song& song2) {
    return song1.distanceToAverage > song2.distanceToAverage;
}

/*int getHighestTrait(Song Song)
{
  int highestTrait = 0;
  double highestTraitValue = song.danceability;
  if (song.energy > highestTraitValue)
  {highestTrait = 1; highestTraitValue = song.energy;}
  if (song.loudness > highestTraitValue)
  {highestTrait = 2; highestTraitValue = song.loudness;}
  if (song.speechiness > highestTraitValue)
  {highestTrait = 3; highestTraitValue = song.speechiness;}
  if (song.acousticness > highestTraitValue)
  {highestTrait = 4; highestTraitValue = song.acousticnessg;}
  
  double acousticness;
  double instrumentalness;
  double liveness;
  double valence;
}

string findSimilarity(Song song, Song average)
{
  string similarTrait;
  int differentTrait = 0;
  double difference = abs(song.danceability - average.danceability);
  difference = getDifference(difference, differentTrait, 1, song.energy, average.energy);
  difference = getDifference(difference, differentTrait, 2, song.loudness, average.loudness);
  difference = getDifference(difference, differentTrait, 3, song.speechiness, average.speechiness);
  difference = getDifference(difference, differentTrait, 4,song.acousticness, average.acousticness);
  difference = getDifference(difference, differentTrait, 5,song.instrumentalness, average.instrumentalness);
  difference = getDifference(difference, differentTrait, 6, song.liveness, average.liveness);
  difference = getDifference(difference, differentTrait, 7, song.valence, average.valence);

  switch (differentTrait)
  {
    case 0:
      if (song.danceability < 0.5)
        
      return "";
    case 1:
      return ""
    case 2:
    
  }
}

double getDifference(double currentDifference, int differentTrait&, int newTrait, double one, double two)
{
  double newDifference = abs(two - one);
  if (newDifference < currentDifference)
  {
    differentTrait = newTrait;
    return newDifference;
  }
  return currentDifference;
}*/

void forwardChaining(const vector<Genre>& genres) {
    // Perform forward chaining logic here
}

void recommendGenre(vector<Song> songs)
{
  cout << "Hi! I'm your new virtual music assistant, Joe Sanchit! After careful review of your spotify portfolio, I would recommend you listen to " << songs.at(0).name <<".";
}


int main() {
    ifstream myFile("playlist_genres.txt");
    ifstream csv("genres_v2.csv");
//{"danceability": 0.7178, "energy": 0.5977, "loudness": -7.1991, "acousticness": 0.193, "instrumentalness": 0.0054, "liveness": 0.1981, "valence": 0.4128, "tempo": 123.4271}
  //{"danceability": 0.6399, "energy": 0.5976, "loudness": -7.3482, "acousticness": 0.3872, "instrumentalness": 0.0162, "liveness": 0.2271, "valence": 0.448, "tempo": 113.3114}
  //0.7759999999999999,0.564,5,-7.212999999999999,0,0.044000000000000004,0.28800000000000003,0.0,0.18899999999999997,0.386,113.956
    Song tempAverages = {"Averages", 0.6399, 0.5976, -7.3482, 0, 0.3872, 0.0162, 0.2271, 0.448, 0};

    /*if (!myFile.is_open()) {
        cout << "Failed to open the file." << endl;
        return 1;
    }

    vector<Genre> genres = getGenres(myFile);
    myFile.close();
    */
    vector<Song> songs = getSongs(csv, tempAverages);
    csv.close();

    sort(songs.begin(), songs.end(), sortByDistance);

    recommendGenre(songs);
    /*
    // Sort genres by frequency in descending order
    sort(genres.begin(), genres.end(), sortByFrequency);

    printGenrePercents(genres);
    forwardChaining(genres);
    */

    
    return 0;
}


