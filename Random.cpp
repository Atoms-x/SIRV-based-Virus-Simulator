#include <iostream>
#include <string>
#include <vector>
#include "Random.h"
#include "PopulationNode.h"
#include <set>

using namespace std;

//-----------------------------------------------------------------------------------
// void main
//  Arguments:
//      random: passed by reference to adjust the vaccinated and susceptible
//      numberOfVaccines: max amount of vaccines that can be distributed
//      numNodes: gives the number of population nodes to sort through
//  Returns:
//      Nothing, manipulating variables by reference
//  Purpose:
//      Steps through the random vector to distribute vaccines according to
//      ascending label value (least to greatest)
//      Also adjusts susceptible because of direct relation to vaccinated.
//------------------------------------------------------------------------------------

void Random::main(vector<PopulationNode> &random, int numberOfVaccines, int numNodes)
{
  // This for loop steps through each populationNode, sets the label value to +1 the index
  // to match with its displayed number (and for later priority math).
  for (int i = 0; i < numNodes; i++)
    random[i].setLabelValue(i+1); 
  

  // A while loop with nested a for loop and conditional statements to distribute vaccines properly.
  // The while checks to see if there are any vaccines left, the for loop steps 
  // through each of the PopulationNodes. The if statment checks if the population can be 
  // fully vaccinated and then sets the vaccinated equal to the population, subtracts that 
  // number from the total vaccines left and then sets the suscueptible equal to 
  // population - vaccinated. The else covers when there aren't enough vaccines, just 
  // setting vaccinated equal to whats left and zero'ing out total vaccines
  while (numberOfVaccines > 0)
  {
    for (int i = 0; i < numNodes; i++)
    {   
      if (numberOfVaccines - random[i].getPopulation() > 0)
      {
        random[i].setVaccinated(random[i].getPopulation());
        numberOfVaccines -= random[i].getPopulation();
        random[i].setSusceptible(random[i].getPopulation() - random[i].getVaccinated());
      }
      else
      {
        random[i].setVaccinated(numberOfVaccines);
        numberOfVaccines -= numberOfVaccines;
        random[i].setSusceptible(random[i].getPopulation() - random[i].getVaccinated());
      }   
    }
  }
}
