#include <iostream>
#include <string>
#include <vector>
#include "Equal.h"
#include "PopulationNode.h"
#include <set>

using namespace std;

//-----------------------------------------------------------------------------------
// void main
//  Arguments:
//      equal: passed by reference to adjust the vaccinated and susceptible
//      numberOfVaccines: max amount of vaccines that can be distributed
//      numNodes: gives the number of population nodes to sort through
//  Returns:
//      Nothing, manipulating variables by reference
//  Purpose:
//      Steps through the equal vector to distribute vaccines according to
//      ascending label value (least to greatest)
//      Also adjusts susceptible because of direct relation to vaccinated.
//------------------------------------------------------------------------------------

void Equal::main(vector<PopulationNode> &equal, int numberOfVaccines, int numNodes)
{
  // This for loop steps through each populationNode, sets the label value to +1 the index
  // to match with its displayed number.
  for (int i = 0; i < numNodes; i++)
    equal[i].setLabelValue(i+1); 
  

  // A while loop with nested a for loop and a conditional statement to distribute vaccines properly.
  // The while checks to see if there are any vaccines left, the for loop steps 
  // through each of the PopulationNodes. The if statment checks if the population is
  // fully vaccinated and if not, adds one vaccine to it then subtracts that 
  // number from the total vaccines left. After the vaccines are full distributed a for loop 
  // sets the suscueptible equal to population - vaccinated. This loads the vaccines one at a time
  // in order, ensuring an equal distribution with the lower label values keeping priority for the leftover
  while (numberOfVaccines > 0)
  {
    for (int i = 0; i < numNodes; i++)
    {   
      if (equal[i].getPopulation() != equal[i].getVaccinated() && numberOfVaccines > 0)
      {
        equal[i].setVaccinated(equal[i].getVaccinated() + 1);
        numberOfVaccines--;
      } 
    }
  }
  for (int i = 0; i < numNodes; i++)
    equal[i].setSusceptible(equal[i].getPopulation() - equal[i].getVaccinated());
}

  