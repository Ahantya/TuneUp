#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "other_file.cpp"

using namespace std; 

struct genre {
  string name;
  int frequency = 0;
};

void forwardChaining(string username)
{
  for (a)
}

int main()
{
  ifstream myFile;
  myFile.open("playlist_genres.txt");
  genre * genres = getGenres(myFile);
	cout << "hello" << endl;
	some_function();
    

    return 0;
	
}

genre * getGenres(ifstream inputfile)
{
  genre * genres = new genre[1000];
  int i = 0;
  if (inputfile.is_open())
  {
      while (inputfile.is_good())
      {
        string line = inputfile.getline();
        string genreName = inputfile.substr(line.find("("),line.find(")")-line.find("("));

        bool inArray = false;
        for (i = 0; i < 1000; i++)
        {
          if (genres[i].name == genreName)
          {
            genres[i]->frequency++;
            inArray = true;
          } 
        }

        if (!inArray)
          genres[i].name = genre;

        i++;
      }

    //Order list by frequency
  }
}

void recommendGenre(string genres[])
{
  
}