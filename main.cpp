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

string convertToString(char* a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

genre * getGenres(ifstream * inputfile)
{
  cout << "let me in your world";
  genre * genres = new genre[1000];
  int c = 0;
  
  if (inputfile->is_open())
  {
      //for (int j = 0; j < 1000; j++)
      //{
        char * lineChar;
        inputfile->getline(lineChar, 256);
        
        string line;
        line = convertToString(lineChar,256);
        
        string genreName = line.substr(line.find("("),line.find(")")-line.find("("));

        bool inArray = false;
        for (int i = 0; i < 1000; i++)
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

        if(inputfile->eof())
          break;
      //}

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
	some_function();
    

  return 0;
	
}



void recommendGenre(string genres[])
{
  
}
