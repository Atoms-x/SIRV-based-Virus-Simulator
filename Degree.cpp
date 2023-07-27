#include <iostream>
#include <string>
#include <vector>
#include "Degree.h"
#include "PopulationNode.h"
#include <set>

using namespace std;

//----------------------------------------------------------------------------------------
// void main
//  Arguments:
//      degree: passed by reference to adjust the vaccinated and susceptible
//      numberOfVaccines: max amount of vaccines that can be distributed
//      numNodes: gives the number of population nodes to sort through
//  Returns:
//      Nothing, manipulating variables by reference
//  Purpose:
//      Steps through the degree vector to calculate the degree centrality and 
//      distribute vaccines according to that calculation (pValue is the normalized score).
//      Also adjusts susceptible because of direct relation to vaccinated.
//-----------------------------------------------------------------------------------------

void Degree::main(vector<PopulationNode> &degree, int numberOfVaccines, int numNodes)
{
  set<int> grow; //Set for making pValue checks to grow in the right order
  
  // This for loop steps through each populationNode, sets the label value to +1 the index
  // to match with its displayed number (and for later priority math), sets the degree centrality
  // score equal to the number of degrees adjacent, sets the pValue by calling the determinePriority 
  // function, and then inserts that pValue into the growth set to later make order checks
  for (int i = 0; i < numNodes; i++)
  {
    degree[i].setLabelValue(i+1); 
    degree[i].setDegreeScore(degree[i].adjacentNodes.size()); 
    degree[i].setPriorityValue(determinePriority(degree, i, numNodes)); 
    grow.insert(degree[i].getPriorityValue()); 
  }

  // A while loop with nested for loops and conditional statements to distribute vaccines properly.
  // The while checks to see if there are any vaccines left, the first for steps through each pValue
  // in descending order in the set to grow the vaccinated properly. The second for loop steps 
  // through each of the PopulationNodes. The first if statement checks for a pValue match; the 
  // second if statment checks if the population can be fully vaccinated and then sets the 
  // vaccinated equal to the population, subtracts that number from the total vaccines left and 
  // then sets the suscueptible equal to population - vaccinated. The else covers when there
  // aren't enough vaccines, just setting vaccinated equal to whats left and zero'ing out total vaccines
  while (numberOfVaccines > 0)
  {
    for (auto it = grow.rbegin(); it != grow.rend(); it++)
    {
      for (int i = 0; i < numNodes; i++)
      {
        if (degree[i].getPriorityValue() == (*it))
        {
          if (numberOfVaccines - degree[i].getPopulation() > 0)
          {
            degree[i].setVaccinated(degree[i].getPopulation());
            numberOfVaccines -= degree[i].getPopulation();
            degree[i].setSusceptible(degree[i].getPopulation() - degree[i].getVaccinated());
          }
          else
          {
            degree[i].setVaccinated(numberOfVaccines);
            numberOfVaccines -= numberOfVaccines;
            degree[i].setSusceptible(degree[i].getPopulation() - degree[i].getVaccinated());
          }
        }
      }
    }
  }
}

//--------------------------------------------------------------------------------------------
// int determinePriority
//  Arguments:
//      degree: passed by value to make checks into the vector of nodes 
//      i: provides the current index point
//      numNodes: provides a max number to subtract from for pValue
//  Returns:
//      pValue: A unique number derived from the differing levels of priority, each 
//              level adding a dispraportionate amount of value to the variable,creating
//              non-overlapping ranges of priority for each node
//  Purpose:
//      Creates a number that can be placed into a list of some kind (this program uses a set)
//      to linearly grow nodes in proper order, based upon a set of well defined rules, until
//      the conditions for growth are no longer met.
//---------------------------------------------------------------------------------------------

int Degree::determinePriority(vector<PopulationNode> degree, int i, int numNodes)
{
  int pValue = 0;

  pValue += degree[i].getDegreeScore() * 10000;
  pValue += (numNodes - degree[i].getLabelValue());

  return pValue;
}