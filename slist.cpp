
//
//  main.cpp
//  LLTemplate
//
//  Created by James Shockey on 12/6/16.
//  Copyright © 2016 James Shockey. All rights reserved.
//


/*
 *
 *	Linked List lab.
 *	- Build a library for singly linked list.
 *	- Replace the airport array in main with a Linked List.
 *  - sort the array. 
 *	
 */

#include <iostream>
#include <fstream>
#include <cmath> 
#include <cstring>
#include "slist.h"

using namespace std;

void simpleSortTotal(List &temp);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

ostream& operator << (ostream &lhs, List &rhs);

int main() {
  ifstream infile;
    char cNum[10] ;
    List airportList;
    airportList.numNodes = 0;
    infile.open ("airport-codes_US.csv", ifstream::in);
    Airport * farthest = new Airport();
    double austinLong = -97.66989899;
    double austinLat = 30.19449997;
    farthest->longitude = austinLong;
    farthest->latitude = austinLat;
    if (infile.is_open()) {
      int i = 0;
      char temp[100];
      char codeC[10];
      char typeC[100];
      string type;
      string thing;

      float longit;
      float latit;
      while (infile.good()) {
        Airport * current = new Airport();
        infile.getline(codeC, 256, ',');
          thing = codeC;
        infile.getline(typeC, 256, ',');
          type = typeC;
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
          longit = atof(temp);
        infile.getline(temp, 256, ',');
          latit = atof(temp);
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, '\n');
        if ((distanceEarth(30.19449997, -97.6698989, latit, longit) <= 100.0) && (type.find("airport") != string::npos) && (thing.find("KAUS") != 0)) {
          strcpy(current->code, codeC);
          current->longitude = longit;
          current->latitude = latit;
          airportList.add(current);
        }
        if ((distanceEarth(30.19449997, -97.66989899, latit, longit) > distanceEarth(austinLat, austinLong, farthest->latitude, farthest->longitude)) && (type.find("airport") != string::npos) && (thing.find("KAUS") != 0)) {
          strcpy(farthest->code, codeC);
          farthest->longitude = longit;
          farthest->latitude = latit;
        }
      }
      infile.close();
    }
    else {
        cout << "Error opening file";
    }
  simpleSortTotal(airportList);
  cout << airportList.toString() << endl; 
  cout << "farthest airport is: " << farthest->code << ", " << to_string(farthest->latitude) <<", "<< to_string(farthest->longitude) << endl;
}

#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

// This function converts decimal degrees to radians
double deg2rad(double deg) {
  return (deg * pi / 180);
}

//  This function converts radians to decimal degrees
double rad2deg(double rad) {
  return (rad * 180 / pi);
}


/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}


/*
	Provide sort routine on linked list
*/

void simpleSortTotal(List &temp) {
  int size = temp.numNodes;
  double austinLong = -97.66989899;
  double austinLat = 30.19449997;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (distanceEarth(austinLat, austinLong, temp.get(i).latitude, temp.get(i).longitude) < distanceEarth(austinLat, austinLong, temp.get(j).latitude, temp.get(j).longitude)) 
        temp.exchg(i, j);
    }
  }
}


//
//  main.cpp
//  LLTemplate
//
//  Created by James Shockey on 12/6/16.
//  Copyright © 2016 James Shockey. All rights reserved.
//


/*
 *
 *	Linked List lab.
 *	- Build a library for singly linked list.
 *	- Replace the airport array in main with a Linked List.
 *  - sort the array. 
 *	
 */

#include <iostream>
#include <fstream>
#include <cmath> 
#include <cstring>
#include "slist.h"

using namespace std;

void simpleSortTotal(List &temp);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

ostream& operator << (ostream &lhs, List &rhs);

int main() {
  ifstream infile;
    char cNum[10] ;
    List airportList;
    airportList.numNodes = 0;
    infile.open ("airport-codes_US.csv", ifstream::in);
    Airport * farthest = new Airport();
    double austinLong = -97.66989899;
    double austinLat = 30.19449997;
    farthest->longitude = austinLong;
    farthest->latitude = austinLat;
    if (infile.is_open()) {
      int i = 0;
      char temp[100];
      char codeC[10];
      char typeC[100];
      string type;
      string thing;

      float longit;
      float latit;
      while (infile.good()) {
        Airport * current = new Airport();
        infile.getline(codeC, 256, ',');
          thing = codeC;
        infile.getline(typeC, 256, ',');
          type = typeC;
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
          longit = atof(temp);
        infile.getline(temp, 256, ',');
          latit = atof(temp);
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, '\n');
        if ((distanceEarth(30.19449997, -97.6698989, latit, longit) <= 100.0) && (type.find("airport") != string::npos) && (thing.find("KAUS") != 0)) {
          strcpy(current->code, codeC);
          current->longitude = longit;
          current->latitude = latit;
          airportList.add(current);
        }
        if ((distanceEarth(30.19449997, -97.66989899, latit, longit) > distanceEarth(austinLat, austinLong, farthest->latitude, farthest->longitude)) && (type.find("airport") != string::npos) && (thing.find("KAUS") != 0)) {
          strcpy(farthest->code, codeC);
          farthest->longitude = longit;
          farthest->latitude = latit;
        }
      }
      infile.close();
    }
    else {
        cout << "Error opening file";
    }
  simpleSortTotal(airportList);
  cout << airportList.toString() << endl; 
  cout << "farthest airport is: " << farthest->code << ", " << to_string(farthest->latitude) <<", "<< to_string(farthest->longitude) << endl;
}

#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

// This function converts decimal degrees to radians
double deg2rad(double deg) {
  return (deg * pi / 180);
}

//  This function converts radians to decimal degrees
double rad2deg(double rad) {
  return (rad * 180 / pi);
}


/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}


/*
	Provide sort routine on linked list
*/

void simpleSortTotal(List &temp) {
  int size = temp.numNodes;
  double austinLong = -97.66989899;
  double austinLat = 30.19449997;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (distanceEarth(austinLat, austinLong, temp.get(i).latitude, temp.get(i).longitude) < distanceEarth(austinLat, austinLong, temp.get(j).latitude, temp.get(j).longitude)) 
        temp.exchg(i, j);
    }
  }
}


//
//  main.cpp
//  LLTemplate
//
//  Created by James Shockey on 12/6/16.
//  Copyright © 2016 James Shockey. All rights reserved.
//


/*
 *
 *	Linked List lab.
 *	- Build a library for singly linked list.
 *	- Replace the airport array in main with a Linked List.
 *  - sort the array. 
 *	
 */

#include <iostream>
#include <fstream>
#include <cmath> 
#include <cstring>
#include "slist.h"

using namespace std;

void simpleSortTotal(List &temp);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

ostream& operator << (ostream &lhs, List &rhs);

int main() {
  ifstream infile;
    char cNum[10] ;
    List airportList;
    airportList.numNodes = 0;
    infile.open ("airport-codes_US.csv", ifstream::in);
    Airport * farthest = new Airport();
    double austinLong = -97.66989899;
    double austinLat = 30.19449997;
    farthest->longitude = austinLong;
    farthest->latitude = austinLat;
    if (infile.is_open()) {
      int i = 0;
      char temp[100];
      char codeC[10];
      char typeC[100];
      string type;
      string thing;

      float longit;
      float latit;
      while (infile.good()) {
        Airport * current = new Airport();
        infile.getline(codeC, 256, ',');
          thing = codeC;
        infile.getline(typeC, 256, ',');
          type = typeC;
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
          longit = atof(temp);
        infile.getline(temp, 256, ',');
          latit = atof(temp);
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, '\n');
        if ((distanceEarth(30.19449997, -97.6698989, latit, longit) <= 100.0) && (type.find("airport") != string::npos) && (thing.find("KAUS") != 0)) {
          strcpy(current->code, codeC);
          current->longitude = longit;
          current->latitude = latit;
          airportList.add(current);
        }
        if ((distanceEarth(30.19449997, -97.66989899, latit, longit) > distanceEarth(austinLat, austinLong, farthest->latitude, farthest->longitude)) && (type.find("airport") != string::npos) && (thing.find("KAUS") != 0)) {
          strcpy(farthest->code, codeC);
          farthest->longitude = longit;
          farthest->latitude = latit;
        }
      }
      infile.close();
    }
    else {
        cout << "Error opening file";
    }
  simpleSortTotal(airportList);
  cout << airportList.toString() << endl; 
  cout << "farthest airport is: " << farthest->code << ", " << to_string(farthest->latitude) <<", "<< to_string(farthest->longitude) << endl;
}

#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

// This function converts decimal degrees to radians
double deg2rad(double deg) {
  return (deg * pi / 180);
}

//  This function converts radians to decimal degrees
double rad2deg(double rad) {
  return (rad * 180 / pi);
}


/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}


/*
	Provide sort routine on linked list
*/

void simpleSortTotal(List &temp) {
  int size = temp.numNodes;
  double austinLong = -97.66989899;
  double austinLat = 30.19449997;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (distanceEarth(austinLat, austinLong, temp.get(i).latitude, temp.get(i).longitude) < distanceEarth(austinLat, austinLong, temp.get(j).latitude, temp.get(j).longitude)) 
        temp.exchg(i, j);
    }
  }
}


//
//  main.cpp
//  LLTemplate
//
//  Created by James Shockey on 12/6/16.
//  Copyright © 2016 James Shockey. All rights reserved.
//


/*
 *
 *	Linked List lab.
 *	- Build a library for singly linked list.
 *	- Replace the airport array in main with a Linked List.
 *  - sort the array. 
 *	
 */

#include <iostream>
#include <fstream>
#include <cmath> 
#include <cstring>
#include "slist.h"

using namespace std;

void simpleSortTotal(List &temp);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

ostream& operator << (ostream &lhs, List &rhs);

int main() {
  ifstream infile;
    char cNum[10] ;
    List airportList;
    airportList.numNodes = 0;
    infile.open ("airport-codes_US.csv", ifstream::in);
    Airport * farthest = new Airport();
    double austinLong = -97.66989899;
    double austinLat = 30.19449997;
    farthest->longitude = austinLong;
    farthest->latitude = austinLat;
    if (infile.is_open()) {
      int i = 0;
      char temp[100];
      char codeC[10];
      char typeC[100];
      string type;
      string thing;

      float longit;
      float latit;
      while (infile.good()) {
        Airport * current = new Airport();
        infile.getline(codeC, 256, ',');
          thing = codeC;
        infile.getline(typeC, 256, ',');
          type = typeC;
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
          longit = atof(temp);
        infile.getline(temp, 256, ',');
          latit = atof(temp);
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, '\n');
        if ((distanceEarth(30.19449997, -97.6698989, latit, longit) <= 100.0) && (type.find("airport") != string::npos) && (thing.find("KAUS") != 0)) {
          strcpy(current->code, codeC);
          current->longitude = longit;
          current->latitude = latit;
          airportList.add(current);
        }
        if ((distanceEarth(30.19449997, -97.66989899, latit, longit) > distanceEarth(austinLat, austinLong, farthest->latitude, farthest->longitude)) && (type.find("airport") != string::npos) && (thing.find("KAUS") != 0)) {
          strcpy(farthest->code, codeC);
          farthest->longitude = longit;
          farthest->latitude = latit;
        }
      }
      infile.close();
    }
    else {
        cout << "Error opening file";
    }
  simpleSortTotal(airportList);
  cout << airportList.toString() << endl; 
  cout << "farthest airport is: " << farthest->code << ", " << to_string(farthest->latitude) <<", "<< to_string(farthest->longitude) << endl;
}

#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

// This function converts decimal degrees to radians
double deg2rad(double deg) {
  return (deg * pi / 180);
}

//  This function converts radians to decimal degrees
double rad2deg(double rad) {
  return (rad * 180 / pi);
}


/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}


/*
	Provide sort routine on linked list
*/

void simpleSortTotal(List &temp) {
  int size = temp.numNodes;
  double austinLong = -97.66989899;
  double austinLat = 30.19449997;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (distanceEarth(austinLat, austinLong, temp.get(i).latitude, temp.get(i).longitude) < distanceEarth(austinLat, austinLong, temp.get(j).latitude, temp.get(j).longitude)) 
        temp.exchg(i, j);
    }
  }
}


//
//  main.cpp
//  LLTemplate
//
//  Created by James Shockey on 12/6/16.
//  Copyright © 2016 James Shockey. All rights reserved.
//


/*
 *
 *	Linked List lab.
 *	- Build a library for singly linked list.
 *	- Replace the airport array in main with a Linked List.
 *  - sort the array. 
 *	
 */

#include <iostream>
#include <fstream>
#include <cmath> 
#include <cstring>
#include "slist.h"

using namespace std;

void simpleSortTotal(List &temp);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

ostream& operator << (ostream &lhs, List &rhs);

int main() {
  ifstream infile;
    char cNum[10] ;
    List airportList;
    airportList.numNodes = 0;
    infile.open ("airport-codes_US.csv", ifstream::in);
    Airport * farthest = new Airport();
    double austinLong = -97.66989899;
    double austinLat = 30.19449997;
    farthest->longitude = austinLong;
    farthest->latitude = austinLat;
    if (infile.is_open()) {
      int i = 0;
      char temp[100];
      char codeC[10];
      char typeC[100];
      string type;
      string thing;

      float longit;
      float latit;
      while (infile.good()) {
        Airport * current = new Airport();
        infile.getline(codeC, 256, ',');
          thing = codeC;
        infile.getline(typeC, 256, ',');
          type = typeC;
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
          longit = atof(temp);
        infile.getline(temp, 256, ',');
          latit = atof(temp);
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, ',');
        infile.getline(temp, 256, '\n');
        if ((distanceEarth(30.19449997, -97.6698989, latit, longit) <= 100.0) && (type.find("airport") != string::npos) && (thing.find("KAUS") != 0)) {
          strcpy(current->code, codeC);
          current->longitude = longit;
          current->latitude = latit;
          airportList.add(current);
        }
        if ((distanceEarth(30.19449997, -97.66989899, latit, longit) > distanceEarth(austinLat, austinLong, farthest->latitude, farthest->longitude)) && (type.find("airport") != string::npos) && (thing.find("KAUS") != 0)) {
          strcpy(farthest->code, codeC);
          farthest->longitude = longit;
          farthest->latitude = latit;
        }
      }
      infile.close();
    }
    else {
        cout << "Error opening file";
    }
  simpleSortTotal(airportList);
  cout << airportList.toString() << endl; 
  cout << "farthest airport is: " << farthest->code << ", " << to_string(farthest->latitude) <<", "<< to_string(farthest->longitude) << endl;
}

#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

// This function converts decimal degrees to radians
double deg2rad(double deg) {
  return (deg * pi / 180);
}

//  This function converts radians to decimal degrees
double rad2deg(double rad) {
  return (rad * 180 / pi);
}


/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}


/*
	Provide sort routine on linked list
*/

void simpleSortTotal(List &temp) {
  int size = temp.numNodes;
  double austinLong = -97.66989899;
  double austinLat = 30.19449997;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (distanceEarth(austinLat, austinLong, temp.get(i).latitude, temp.get(i).longitude) < distanceEarth(austinLat, austinLong, temp.get(j).latitude, temp.get(j).longitude)) 
        temp.exchg(i, j);
    }
  }
}

/*
 * LALLOC Main test
 * 
 * Choose test by using macro SIMPLETEST1 or SIMPLETEST2
 * 
 * Do not change anything else in this file
 */ 
#define SIMPLETEST1



#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include"LASAalloc.h"



#ifdef SIMPLETEST1
int main(int argc, char *argv[])
{
	
	LASAalloc	lasa;

	
	char *array;
	int i;

	array = (char *)lasa.lalloc(10);
	if(array == NULL)
	{
		fprintf(stderr,"call to lasa.lalloc() failed\n");
		fflush(stderr);
		exit(1);
	}

	for(i=0; i < 9; i++)
	{
		array[i] = 'a' + i;
	}
	array[9] = 0;

	printf("here is my nifty new string: %s\n",array);

	lasa.lfree(array);

	return(0);
}

	
#endif //SIMPLETEST1

#ifdef SIMPLETEST2

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include"LASAalloc.h"

int main(int argc, char *argv[])
{
	char *a1;
	char *a2;
	char *a3;
	char *a4;

	
	LASAalloc	lasa;



	a1 = (char *)lasa.lalloc(128);
	if(a1 == NULL)
	{
		fprintf(stderr,"call to lasa.lalloc(128) failed\n");
		fflush(stderr);
		exit(1);
	}

	printf("FREE LIST after malloc(128)\n");
	lasa.display(NULL);

	a2 = (char *)lasa.lalloc(32);
	if(a2 == NULL)
	{
		fprintf(stderr,"first call to lasa.lalloc(32) failed\n");
		fflush(stderr);
		exit(1);
	}

	printf("FREE LIST after malloc(32)\n");
	lasa.display(NULL);

	lasa.lfree(a1);

	printf("FREE LIST after free of first 128 malloc()\n");
	lasa.display(NULL);

	a3 = (char *)lasa.lalloc(104);
	if(a3 == NULL)
	{
		fprintf(stderr,"call to lasa.lalloc(104) failed\n");
		fflush(stderr);
		exit(1);
	}

	printf("FREE LIST after malloc(104)\n");
	lasa.display(NULL);

	a4 = (char *)lasa.lalloc(8);
	if(a4 == NULL)
	{
		fprintf(stderr,"call to lasa.lalloc(8) failed\n");
		fflush(stderr);
		exit(1);
	}
	printf("FREE LIST after malloc(8)\n");
	lasa.display(NULL);

	/*
	 * free it all -- notice that a1 is already free
	 */
	lasa.lfree(a2);
	lasa.lfree(a3);
	lasa.lfree(a4);
	printf("FREE LIST after all free\n");
	lasa.display(NULL);


	return(0);
}

	

#endif	//ACTIVE

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
	 * 		LASAalloc.h
	 * 		LASAalloc class declaration.  
	 * 
	 * 		Do not change this file other than to add local varaibles and Functions.
	 *    Make any changes only in the provided block.
	 * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include<iostream>
#include<stdlib.h>
#include "LASAalloc.h"

// Defines for LASAalloc buffer simulation.  
// Keep it simple, no changes to program break
#define INITIAL_MALLOC_SIZE 100000
#define MAX_MALLOC_SIZE 100000


using namespace std;

//typedef unsigned char BYTE_t;

LASAalloc::LASAalloc()
{
	brk(INITIAL_MALLOC_SIZE);
	
	// Point to where first node will be located.
	block* firstBlock = (block*)bufferBase;
	freeList = firstBlock;
	
	// Configure first node on freeList
	firstBlock->size = (int)(bufferSize);
	firstBlock->prev_block = nullptr;
	firstBlock->next_block = nullptr; 
	firstBlock->this_block_data = (void*)((long long int)bufferBase+(long long int)sizeof(block)); 
	firstBlock->freeFlag = true; 
	
	// Show initial statistics
	cout<<"buffer Allocation: "<< bufferBase << " - " << brk(0) << endl;
	cout<<"freeList: "<< freeList << " - " << brk(0) << endl;
	cout<<"Block header size " << sizeof(block) << endl;
	cout<<"integer size " << sizeof(int) << endl;
	
	display_node(freeList);

}

LASAalloc::~LASAalloc()
{
}

 

void LASAalloc::display_node(struct block *p)
{
		cout << "Prev: " << p->prev_block;
		cout << "\tNext: " << p->next_block;
		cout << "\tFree: " << p->freeFlag;
		cout << "\tSize: " << p->size;
		cout << "\tThis: " << p->this_block_data << endl;
		cout << endl;	
}

void LASAalloc::display(struct block *begin)
{
	struct block *p;
	if(begin==NULL)
	{
		begin = freeList;
	}
	p=begin;
	cout<<"List is :\n";
	while(p!=NULL)
	{
		display_node(p);
		p=p->next_block;
	}
	cout<<"\n";
}




void* LASAalloc::lalloc(int size)
{
	//cout << "lalloc start " << size << endl;
	block * newBlock = (block*)(findFit(size));
	if(newBlock == NULL){
		return NULL;
	}
	//cout << "lalloc end" << endl;
	return split(newBlock, size);
}


void* LASAalloc::lfree(void* userBlock)
{
	//cout << "lfree start" << endl;
	block * freedBlock = (block*)userBlock;
	block * cycle = freeList;
	while(cycle != freedBlock){
    if (cycle->next_block == NULL)
      return NULL;
    cycle = cycle->next_block;
	}
	cycle->freeFlag = true;
	//cycle->this_block_data = NULL;
	//cout << "lfree end" << endl;
	return cycle;
}

void* LASAalloc::findFit(int size)
{
	//cout << "findFit start" << endl;
	block * cycle = freeList;
	bool found = false;

	while(cycle != NULL){
    if ((cycle->freeFlag == true ) && (cycle->size > (size + 32))){
			found = true;
			break;
		}
		cycle = cycle->next_block;
	}
	//cout << "findFit end" << endl;
	if(found){
		return (void*)(cycle);
	}
	else{
		return NULL;
	}
}

void* LASAalloc::split(block* target, int size)
{
	//cout << "split start" << endl;
	block * newBlock = (block*)(target + size);
	newBlock->size = target->size - size - 32;
	target->size =size;
	newBlock->next_block = target->next_block;
	newBlock->prev_block = target;
	target->next_block = newBlock;
	newBlock->freeFlag = true;
	target->freeFlag = false;
	// newBlock->this_block_data = target->this_block_data;
	// target->this_block_data = NULL;
	//cout << "split end" << endl;
	return target;
}
 


/*
 *   >>>>>>  DO NOT CHANGE THIS SECTION  <<<<<<<
 * 
 * brk()
 * Function to simulate the libc brk() function to allocate memory for a buffer
 * 
 */

void * LASAalloc::brk(int size)
{
	
	if (size !=0)
	{
		if (bufferBase == 0)
		{
			bufferBase = malloc(size);
			bufferSize = size;
		}
		else
		{
			cout<<"buffer already locked/n";
			return 0;
		}
		
	}
  int *temp = (int*)(bufferBase);
  int *sum = temp + bufferSize;
	return (void*) (sum);
}