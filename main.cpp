#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cmath>
#include "other_file.cpp"
#include "help.cpp"
#include <algorithm>
#include <queue>
 
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
  return sqrt(pow(song1.danceability - song2.danceability, 2) + pow(song1.energy - song2.energy, 2) + pow((song1.loudness - song2.loudness)/10, 2)
 + pow(song1.acousticness - song2.acousticness, 2) + pow(song1.instrumentalness - song2.instrumentalness, 2) + pow(song1.liveness - song2.liveness, 2) + pow(song1.valence - song2.valence, 2));
}

bool sortByFrequency(const Genre& genre1, const Genre& genre2) {
    return genre1.frequency > genre2.frequency;
}

//< is correct
bool sortByDistance(const Song& song1, const Song& song2) {
    return song1.distanceToAverage < song2.distanceToAverage;
}

Song generateCluster(vector<Song> songs)
{
  int random = rand() % songs.size();
  return songs.at(random);
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

    if (newSong.name != "")
      songs.push_back(newSong);
  }

  return songs;
}

Song operator -(Song& one, Song& two)
{
  Song newSong = {"", one.danceability - two.danceability, one.energy - two.energy, one.loudness - two.loudness, 0, one.acousticness - two.acousticness, one.instrumentalness - two.instrumentalness, one.liveness - two.liveness, one.valence - two.valence};
  return newSong;
}

Song operator+(const Song& one, const Song& two)
{
  Song newSong = {"", one.danceability + two.danceability, one.energy + two.energy, one.loudness + two.loudness, 0, one.acousticness + two.acousticness, one.instrumentalness + two.instrumentalness, one.liveness + two.liveness, one.valence + two.valence};
  return newSong;
}

Song operator *(double& multi, Song& song)
{
  Song newSong = {"", multi * song.danceability, multi * song.energy, multi * song.loudness, 0, multi * song.acousticness, multi * song.instrumentalness, multi * song.liveness, multi * song.valence};
  return newSong;
}

Song operator /(const Song& song, const double& div)
{
  Song newSong = {"", song.danceability / div, song.energy / div, song.loudness / div, 0, song.acousticness / div, song.instrumentalness / div, song.liveness / div, song.valence / div};
  return newSong;
}

void printSongs(const vector<Song>& songs)
{
  for (const auto& song : songs) {
        cout << song.name << " (" << song.danceability << ", " << song.energy << ", " << song.loudness << ", " << song.distanceToAverage << ")" << endl;
    }
}

vector<Song> weightLiftClustering(vector<Song> songs)
{
  Song clusterOne = generateCluster(songs);
  Song clusterTwo = generateCluster(songs);

  for (int i = 0; i < 100; i++)
  {
    vector<Song> clusterDataOne, clusterDataTwo;
    for (const Song& song : songs)
    {
      if (pow(distance(song, clusterOne), 2) < pow(distance(song, clusterTwo), 2))
        clusterDataOne.push_back(song);
      else
        clusterDataTwo.push_back(song);
    }

    Song meanOne = {"", 0, 0, 0, 0, 0, 0, 0, 0, 0};
    Song meanTwo = {"", 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (const Song& song: clusterDataOne)
    {
      meanOne = meanOne + song;
    }

   
  
    meanOne = meanOne / clusterDataOne.size();
    //cout << meanOne.danceability << '\n';

    for (const Song& song: clusterDataTwo)
    {
      meanTwo = meanTwo + song;
    }
  
    meanTwo = meanTwo / clusterDataTwo.size();
    //cout << meanTwo.danceability << '\n';

    clusterOne = meanOne;
    clusterTwo = meanTwo;
  }

  vector<Song> clusterDataOne, clusterDataTwo;  
  for (const Song& song : songs)
  {
    Song newSong = song;
    if (pow(distance(song, clusterOne), 2) < pow(distance(song, clusterTwo), 2))
    {
      newSong.distanceToAverage = distance(song, clusterOne);
      clusterDataOne.push_back(newSong);
    }
    else
    {
      newSong.distanceToAverage = distance(song, clusterTwo);
      clusterDataTwo.push_back(newSong);
    }
  }

  sort(clusterDataOne.begin(), clusterDataOne.end(), sortByDistance);
  sort(clusterDataTwo.begin(), clusterDataTwo.end(), sortByDistance);

  vector<Song> clusterPoints;
  clusterPoints.push_back(clusterOne);
  clusterPoints.push_back(clusterTwo);

  //printSongs(clusterDataOne);
  //cout << '\n';
  //printSongs(clusterDataTwo);
  
  //cout << "If you would like suggestions more in line with specific genres you may listen to, try " << clusterDataOne.at(0).name << " or " << clusterDataTwo.at(0).name << ".\n";

  return clusterPoints;
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

Song getAverages(ifstream& file)
{
  Song newSong;
  string line;
  getline(file, line);
  getline(file, line);
  newSong.name = "Averages";
  line = line.substr(line.find("danceability:") + 13);
  newSong.danceability = stod(line.substr(0, line.find("e")));
  line = line.substr(line.find("energy:") + 7);
  newSong.energy = stod(line.substr(0, line.find("l")));
  line = line.substr(line.find("loudness:") + 9);
  newSong.loudness = stod(line.substr(0, line.find("a")));
  line = line.substr(line.find("acousticness:") + 13);
  newSong.acousticness = stod(line.substr(0, line.find("i")));
  line = line.substr(line.find("instrumentalness:") + 17);
  newSong.instrumentalness = stod(line.substr(0, line.find("l")));
  line = line.substr(line.find("liveness:") + 9);
  newSong.liveness = stod(line.substr(0, line.find("v")));
  line = line.substr(line.find("valence:") + 8);
  newSong.valence = stod(line.substr(0, line.find("t")));

  return newSong;
}

queue<Song> convertToQueue(vector<Song> sortedList)
{
  queue<Song> queue;
  for (const Song& song : sortedList)
  {
    queue.push(song);
  }

  return queue;
}

void printNextSong(queue<Song>& queue)
{
  cout << "A great song for you to listen to would be \"" << queue.front().name << "\".\n";
  queue.pop();
}

int main() {
    ifstream myFile("playlist_genres.txt");
    ifstream csv("genres_v2.csv");
    ifstream averageFile("playlist_average_features.txt");
    ifstream playlist("playlist_all_features.txt");

    Song averages = getAverages(averageFile);

    vector<Song> playlistSongs = getSongs(playlist, averages);
    playlist.close();
  
    vector<Song> averageVector = weightLiftClustering(playlistSongs);
    //printSongs(averageVector);

    /*if (!myFile.is_open()) {
        cout << "Failed to open the file." << endl;
        return 1;
    }

    vector<Genre> genres = getGenres(myFile);
    myFile.close();
    */
    vector<Song> songsOne = getSongs(csv, averageVector.at(0));
    csv.close();

    ifstream csv2("genres_v2.csv");
    vector<Song> songsTwo = getSongs(csv2, averageVector.at(1));
    csv2.close();

    sort(songsOne.begin(), songsOne.end(), sortByDistance);
    sort(songsTwo.begin(), songsTwo.end(), sortByDistance);

    queue<Song> queueOne = convertToQueue(songsOne);
    queue<Song> queueTwo = convertToQueue(songsTwo);


    printNextSong(queueOne);
    printNextSong(queueTwo);
    //printSongs(songs);


    /*
    // Sort genres by frequency in descending order
    sort(genres.begin(), genres.end(), sortByFrequency);

    printGenrePercents(genres);
    forwardChaining(genres);
    */

    
    return 0;
}


