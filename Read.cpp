#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

#include "Read.h"

using namespace std;

//--------------------------------------------------------------------------------------------------
// void main
//  Arguments:
//      adjacency: passed by reference to manipulate and load with adjacency data from region.csv
//      population: passed by reference to manipulate and load with population data from pop.txt
//      infectedArea: passed by reference to set the starting point of the virus from config.txt
//      infectiousPeriod: passed by reference to set the time for how long the infected have the virus 
//                        from config.txt
//      contactRate: passed by reference to set the rate of spread of the virus from config.txt
//      numberOfVaccines: passed by reference to set the total number of vaccines from config.txt
//  Returns:
//      Nothing, manipulating variables by reference
//  Purpose:
//      Reads the three files, config.txt, pop.txt, and region.csv to store all the relevent
//      data to run this pandemic simulation
//---------------------------------------------------------------------------------------------------

void Read::main( vector<vector <int>>& adjacency, vector<int>& population, int& infectedArea, int& infectiousPeriod, int& contactRate, int& numberOfVaccines )
{
  string file;
  string line;
  ifstream inFile; //ifstream object for reading

  cout << "Please enter the name of the configuration file: ";
  getline(cin, file);  //get the name of the configuration file to open

  inFile.open(file); //Opening the file

  if(!inFile) // Makes sure that the name given is actually a file
  {
    cout << "Unable to open the file";
    exit(1);
  }

  getline(inFile, line);  // Get the first line of the text file
  int pos = line.find(":"); // Finds the colon in the first line
  string pop = line.substr(pos + 1); // Stores everything after the colon into the string

  getline(inFile, line); // Gets the second line of the text file
  int pos2 = line.find(":"); // Finds the colon in the second line
  string region = line.substr(pos2 + 1); // Stores everyhthing after the colon into the string

  getline(inFile, line); // Gets the empty line (third)

  getline(inFile, line);  // Gets the fourth line 
  int pos3 = line.find(":");
  string area = line.substr(pos3 + 1); 
  infectedArea = stoi(area); //converts the string to an integer

  getline(inFile, line); //Gets the fifth line
  int pos4 = line.find(":"); 
  string period = line.substr(pos4 + 1); 
  infectiousPeriod = stoi(period);

  getline(inFile, line); //Gets the sixth line
  int pos5 = line.find(":"); 
  string rate = line.substr(pos5 + 1); 
  contactRate = stoi(rate);

  getline(inFile, line); //Gets the seventh line
  int pos6 = line.find(":"); 
  string vaccine = line.substr(pos6 + 1); 
  numberOfVaccines = stoi(vaccine);
  
  loadPopulation(population, pop); // call the loadPopulation function to read the pop.txt file
  loadAdjacency(adjacency, region); // call the loadAdjacency function to read the region.txt file
}

//--------------------------------------------------------------------------------------------------
// void loadPopulation
//  Arguments:
//      population: passed by reference to manipulate and load with population data from pop.txt
//      popFile: Holds the name of the pop.txt file read from the config.txt file
//  Returns:
//      Nothing, manipulating variable by reference
//  Purpose:
//      Reads from the pop.txt file
//---------------------------------------------------------------------------------------------------

void Read::loadPopulation( vector<int>& population, string popFile )
{
  string line;
  ifstream inFile;
  
  inFile.open(popFile); // Opening the pop.txt

  if(!inFile) // Makes sure that the name given is actually a file
  {
    cout << "Unable to open the file";
    exit(1);
  }

  // Does the same thing as the initial read in, just with a while loop because
  // of the repetitive structure of the file and data
  while (getline(inFile, line)) 
  {
    int pos = line.find(":"); 
    string pop = line.substr(pos + 1); 
    population.push_back(stoi(pop));
  }
}

//--------------------------------------------------------------------------------------------------
// void loadAdjacency
//  Arguments:
//      adjacency: passed by reference to manipulate and load with population data from pop.txt
//      regionFile: Holds the name of the region.csv file read from the config.txt file
//  Returns:
//      Nothing, manipulating variable by reference
//  Purpose:
//      Reads from the region.csv file
//---------------------------------------------------------------------------------------------------

void Read::loadAdjacency( vector<vector <int>>& adjacency, string regionFile )
{
  string line;
  ifstream inFile;

  inFile.open(regionFile);

  if(!inFile) // Makes sure that the name given is actually a file
  {
    cout << "Unable to open the file";
    exit(1);
  }

  getline(inFile, line); // Gets the top line
  int count = 1;

  while (getline(inFile, line))
  {
    vector<int> node; //vector to hold the adjacent elements per node

    for (char& c : line) //Getting characters through a for loop
    {
      if (c != ',' && c != ' ') // Don't load anything but characters
        node.push_back((int)(c) - 48); // This converts the character to the actual ASCII value
    }                                  // so subtract 48 to get the integer value
    if (count > 9)
      node.erase(node.begin()); // Create two erases for the double digit region
    node.erase(node.begin()); // Erase the first number, because that is the row number
    
    count++;
    adjacency.push_back(node); // place the vector into the vector
  }
}