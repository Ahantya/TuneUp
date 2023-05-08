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

genre * getGenres(ifstream * inputfile)
{
  cout << "let me in your world";

	int length = 0;
	string placeholder;
	while (inputfile->good())
	{
		getline(*inputfile, placeholder);
		length++;
	}

	inputfile->clear();
	inputfile->seekg(0);
	
  genre * genres = new genre[10 * length];
  int c = 0;
  
  if (inputfile->is_open())
  {
      for (int j = 0; j < length; j++)
      {
        string line;
        getline(*inputfile, line);

				string * genreName = new string[100];
        int p = 0;

				if (line.find("(") != string::npos)
        {
          string genreNam;
          genreNam = line.substr(line.rfind("("));
          genreNam = genreNam.substr(1, genreNam.length() - 1);
          while (genreNam.find(",") != string::npos)
          {
            genreName[p] = genreNam.substr(0, genreNam.find(","));
            genreNam = genreNam.substr(genreNam.find(","));
            p++;
          }
        }
        	
        for (int o = 0; o < p; o++)
        {
          bool inArray = false;
          for (int i = 0; i < length; i++)
          {
            if (genres[i].name == genreName[o])
            {
              genres[i].frequency++;
              inArray = true;
            } 
          }
  
          if (!inArray)
            genres[c].name = genreName[o];
  
          c++;
        }

        if(inputfile->eof() || !inputfile->good())
          break;
      }

    //Order list by frequency
    
  }

  for (int i = 0; i < length; i++)
  {
    cout << genres[i].name;
  }
  
  return genres;
}

void forwardChaining(genre * genres)
{
  return;
}

int main()
{
  ifstream myFile;
  /*cout << "Through our advanced neural network forward chaining processes, we have determined that you would have a great time listening to Drake!";*/
  myFile.open("playlist_genres.txt");
  genre * genres = getGenres(&myFile);
	cout << "hello" << endl;
	some_function();
    

  return 0;
	
}



genre * recommendGenre(genre * genres)
{
  return NULL;
}
