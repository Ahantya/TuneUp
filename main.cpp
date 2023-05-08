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

genre * getGenres(ifstream * inputfile)
{

	int length = 0;
	string placeholder;
	while (inputfile->good())
	{
		getline(*inputfile, placeholder);
		length++;
	}

	inputfile->clear();
	inputfile->seekg(0);
	
  genre * genres = new genre[length];
  int c = 0;
  
  if (inputfile->is_open())
  {
      for (int j = 0; j < length; j++)
      {
        string line;
        getline(*inputfile, line);

				string genreName;
				if (line.find("(") != string::npos)
        	genreName = line.substr(line.find("("));

        bool inArray = false;
        for (int i = 0; i < length; i++)
        {
          if (genres[i].name == genreName)
          {
            genres[i].frequency++;
            inArray = true;
          } 
        }

        if (!inArray)
          genres[c].name = genreName;

        c++;

        if(inputfile->eof() || !inputfile->good())
          break;
      }

    //Order list by frequency
    
  }

  return genres;
}

void forwardChaining(string username)
{
  return;
}

int main()
{
  ifstream myFile;
  myFile.open("playlist_genres.txt");
  genre * genres = getGenres(&myFile);
	cout << "hello" << endl;
	//bugs_and_more();
    

  return 0;
	
}



void recommendGenre(string genres[])
{
  
}
