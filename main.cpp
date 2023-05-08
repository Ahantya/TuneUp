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

genre* getGenres(ifstream* inputfile)
{
    int length = 0;
    string placeholder;
    while (getline(*inputfile, placeholder))
    {
        length++;
    }

    inputfile->clear();
    inputfile->seekg(0);

    genre* genres = new genre[length];
    int c = 0;

    if (inputfile->is_open())
    {
        for (int j = 0; j < length; j++)
        {
            string line;
            getline(*inputfile, line);

            int p = 0;
            if (line.find("(") != string::npos)
            {
                string genreNam;
                genreNam = line.substr(line.rfind("("));
                genreNam = genreNam.substr(1, genreNam.length() - 1);
                cout << genreNam;
                while (genreNam.find(",") != string::npos)
                {
                    genres[c].name = genreNam.substr(0, genreNam.find(","));
                    genreNam = genreNam.substr(genreNam.find(",") + 1);
                    genres[c].frequency++;
                    c++;
                    p++;
                }
            }

            //cout << p;

            if (inputfile->eof() || !inputfile->good())
                break;
        }

        // Order list by frequency
    }

    for (int i = 0; i < length; i++)
    {
        cout << genres[i].name << endl;
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
	//bugs_and_more();
    

  return 0;
	
}



genre * recommendGenre(genre * genres)
{
  return NULL;
}
