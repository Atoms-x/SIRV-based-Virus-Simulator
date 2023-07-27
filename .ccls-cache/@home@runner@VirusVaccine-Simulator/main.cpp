//***************************************************************
// Chet Lockwood
// Last Update: 28 JUL 2020
// Description: Virus and Vaccine Spread Simulator
//***************************************************************

#include <iostream>
#include <string>
#include <vector>
#include "PopulationNode.h"
#include "Read.h"
#include "Simulation.h"
#include "Degree.h"
#include "Closeness.h"
#include "Random.h"
#include "Equal.h"
#include "Analysis.h"

using namespace std;

void load (vector<PopulationNode> &, vector<vector <int>>, vector<int>);
void finalOutput (Analysis, int&);

// MAIN FUNCTION --------------------------------------------------------------------------------
int main() 
{
  vector<vector <int>> adjacency;
  vector<int> population;
  int infectedArea = 0;
  int infectiousPeriod = 0;
  int contactRate = 0;
  int numberOfVaccines = 0; 
  int simCount = 1;

  Read read; //Instantiate the read in class

  // Call the Read classes main function to get all the data from the three files
  read.main(adjacency, population, infectedArea, infectiousPeriod, contactRate, numberOfVaccines);

  int numNodes = population.size(); // define the number of nodes

  // Define the four simulation vectors
  vector<PopulationNode> closeness(adjacency.size());
  vector<PopulationNode> degree(adjacency.size());
  vector<PopulationNode> random(adjacency.size());
  vector<PopulationNode> equal(adjacency.size());

  // Load the four vectors with the read in data
  load(closeness, adjacency, population);
  load(degree, adjacency, population);
  load(random, adjacency, population);
  load(equal, adjacency, population);

  // Instantiate the four vaccine loading classes
  Closeness cVaccine;
  Degree dVaccine;
  Random rVaccine;
  Equal eVaccine;

  // Call the main function of the four vaccine loading classes
  cVaccine.main(closeness, numberOfVaccines, numNodes);
  dVaccine.main(degree, numberOfVaccines, numNodes);
  rVaccine.main(random, numberOfVaccines, numNodes);
  eVaccine.main(equal, numberOfVaccines, numNodes);

  // Instantiate the four analysis classes
  Analysis cAnalysis;
  Analysis dAnalysis;
  Analysis rAnalysis;
  Analysis eAnalysis;

  Simulation sim; //Instantiate the sim class to start the sim

  // Call the sim classes main function for the four sims to start each sim
  sim.main(closeness, numNodes, simCount, infectedArea, infectiousPeriod, contactRate, cAnalysis);
  sim.main(degree, numNodes, simCount, infectedArea, infectiousPeriod, contactRate, dAnalysis); 
  sim.main(random, numNodes, simCount, infectedArea, infectiousPeriod, contactRate, rAnalysis);
  sim.main(equal, numNodes, simCount, infectedArea, infectiousPeriod, contactRate, eAnalysis);

  // Output the final analysis information
  int finalCounter = 0;
  finalOutput(cAnalysis, finalCounter);
  finalOutput(dAnalysis, finalCounter);
  finalOutput(rAnalysis, finalCounter);
  finalOutput(eAnalysis, finalCounter);

  return 0;
}

//FUNCTIONS -------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
// void load
//  Arguments:
//      sim: Passed by reference to manipulate the PopulationNodes inside
//      adjacency: Holds the adjacency data 
//      population: Holds the population data
//  Returns:
//      Nothing explicitly, modifying the area/sim vectors to load file data
//  Purpose:
//      Loads the vectors used for the simulation with the data from the files that were read
//---------------------------------------------------------------------------------------------

void load (vector<PopulationNode> &sim, vector<vector <int>> adjacency, vector<int> population)
{
  // Nested for loop to step through the 2D vector of adjacency and then by using
  // the x value of the current y vector, the number of the node that is connected 
  // can be determined and loaded into the adjacentNodes vector inside of the PopulationNodes 
  // objects inside of the sim vector
  for(int y = 0; y < adjacency.size(); y++)
  {
    for(int x = 0; x < adjacency[y].size(); x++)
    {
      if (adjacency[y][x] == 1)
        sim[y].adjacentNodes.push_back(x + 1);
    }
  }

  // Simple for loop that loads the population data into their respective nodes
  // inside of the sim vector (the vector inside of the vector matches up to the 
  // index of the population vector)
  for (int i = 0; i < population.size(); i++)
  {
    sim[i].setPopulation(population[i]);
  }
}

//-------------------------------------------------------------------------------------------
// void finalOutput
//  Arguments:
//      analysis: Passed by value to get the required analysis data that was logged
//      count: Passed by reference to display the right experiment name
//  Returns:
//      Nothing explicitly, displays the analysis information
//  Purpose:
//      Displays all the analysis information in the appropriate format, prevents repeat code
//---------------------------------------------------------------------------------------------

void finalOutput (Analysis analysis, int &count)
{
  string whichOne[4] = {"closeness centrality", "degree centrality", "random", "equal"};

  cout << endl << "Using the " << whichOne[count] << " distribution method, the peak number of "; 
  cout << "infected was " << analysis.getPeak() << " on day " << analysis.getPeakDay() << ". ";
  cout << "The outbreak ended on day " << analysis.getLastDay() << " and the total number of ";
  cout << "infected individuals was " << analysis.getTotalInfected() << "." << endl;

  count++;
}