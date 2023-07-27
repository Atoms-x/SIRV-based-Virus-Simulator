#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Closeness.h"
#include "PopulationNode.h"
#include <set>
#include <queue>

using namespace std;

//-----------------------------------------------------------------------------------
// void main
//  Arguments:
//      closeness: passed by reference to adjust the vaccinated and susceptible
//      numberOfVaccines: max amount of vaccines that can be distributed
//      numNodes: gives the number of population nodes to sort through
//  Returns:
//      Nothing, manipulating variables by reference
//  Purpose:
//      Steps through the closeness vector to calculate the closeness centrality and 
//      distribute vaccines according to that calculation (pValue is the normalized score).
//      Also adjusts susceptible because of direct relation to vaccinated.
//------------------------------------------------------------------------------------

void Closeness::main(vector<PopulationNode> &closeness, int numberOfVaccines, int numNodes)
{
  set<int> grow; //Set for making pValue checks to grow in the right order
  queue<int> next; //queue for breadth first search of nodes
  vector<int> checked; //Vector to hold checked node label values
  int countDown = 0; //integer to count down dequeue'ing elements till the next level (distance)
  int currentLevel = 1; //Current distance of nodes from the central node
  double sumDistance = 0; //Holds the sum of all distances to all nodes
  
  // This for loop steps through each populationNode, sets the label value to +1 the index
  // to match with its displayed number (and for later priority math).
  for (int i = 0; i < numNodes; i++)
    closeness[i].setLabelValue(i+1); 
 
  //CLOSENESS CALCULATION ***********************************************************************************
  // For loop to ensure stepping through all the nodes to eventually set pValue (encapsulates the calculation)
  for (int i = 0; i < numNodes; i++)
  {
    sumDistance = 0; //reset of the value
    currentLevel = 1; //reset of the value
    //sets the currently checking node to checked, since its distance is 0 from itself
    checked.push_back(closeness[i].getLabelValue()); 
                                                    
    // For loop that steps through the nodes adjacent to the currently checked node
    for (auto it = closeness[i].adjacentNodes.begin(); it != closeness[i].adjacentNodes.end(); it++)
      next.push(*it);
    
    countDown = next.size(); // sets a counter that keeps track of what level groups of nodes are part of

    // While loop that keeps the closeness algorithm going until all nodes have been checked
    // and their distances summed 
    while (!next.empty()) 
    {
      int n = 0;
      n = next.front(); // places the next adjacent node into a variable
      checked.push_back(n); // pushes that node into the checked vector
      next.pop(); // pops that node off the queue

      // This for loop checkes to ensure the node passed hasn't already been checked or
      // hasn't already been loaded into the queue (at its shortest distance) before placing
      // the node into the queue
      for (auto it = closeness[n-1].adjacentNodes.begin(); it != closeness[n-1].adjacentNodes.end(); it++)
      { 
        if(!search(checked, *it) && !searchQueue(next, *it))
          next.push(*it);
      }
      
      countDown--; // decrement the count down till the next level (distance)
      sumDistance += currentLevel; // add to the distance sum based on the current level of the node

      if(countDown == 0) // if the countdown has hit 0, all nodes after will be part of the next level
      {
        countDown = next.size();
        currentLevel++;
      }
    }
    
    checked.clear(); // clear the check vector for the next node
    closeness[i].setClosenessScore(numNodes/sumDistance); // take the average of the sum for the closeness
  }
  //END OF CLOSENESS CALCULATION ***************************************************************************

  // This for loop steps through each populationNode sets the pValue by 
  // calling the determinePriority function, and then inserts that pValue 
  // into the growth set to later make order checks
  for (int i = 0; i < numNodes; i++)
  { 
    closeness[i].setPriorityValue(determinePriority(closeness, i, numNodes)); 
    grow.insert(closeness[i].getPriorityValue()); 
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
        if (closeness[i].getPriorityValue() == (*it))
        {
          if (numberOfVaccines - closeness[i].getPopulation() > 0)
          {
            closeness[i].setVaccinated(closeness[i].getPopulation());
            numberOfVaccines -= closeness[i].getPopulation();
            closeness[i].setSusceptible(closeness[i].getPopulation() - closeness[i].getVaccinated());
          }
          else
          {
            closeness[i].setVaccinated(numberOfVaccines);
            numberOfVaccines -= numberOfVaccines;
            closeness[i].setSusceptible(closeness[i].getPopulation() - closeness[i].getVaccinated());
          }
        }
      }
    }
  }
}

//---------------------------------------------------------------------------------------------
// int determinePriority
//  Arguments:
//      closeness: passed by value to make checks into the vector of nodes 
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
//----------------------------------------------------------------------------------------------

int Closeness::determinePriority(vector<PopulationNode> closeness, int i, int numNodes)
{
  // Because matching double values can be haphazard, this multiplies it by a very
  // large number to derive some precision, and then converts it to an integer
  // to get rid of the issues associated with after the decimal
  int pValue = 0;
  double y = closeness[i].getClosenessScore() * 10000;
  int x = y;
  
  pValue += x;
  pValue += (numNodes - closeness[i].getLabelValue());

  return pValue;
}

//-----------------------------------------------------------------------------------------
// bool search
//  Arguments:
//      checked: passed by value to make checks into the vector of node values
//      val: The value checked against to ensure the node hasn't already been checked
//  Returns:
//      true: if the value passed is equal to any value inside of the vector
//      false: if the value passed is not equal to any value inside of the queue
//  Purpose:
//      Checks the checked vector for any already checked nodes so that it doesn'that
//      end up in an infinite loop or skewing the shortest distance to node measurement
//-----------------------------------------------------------------------------------------

bool Closeness::search(vector<int> checked, int val) const
{
  for (auto it = checked.begin(); it != checked.end(); it++)
    if ((*it) == val)
      return true;
  
  return false;
}

//---------------------------------------------------------------------------------------
// bool searchQueue
//  Arguments:
//      next: passed by value to make checks into the queue of node values 
//      val: The value checked against to ensure the node isn't already queue'd
//  Returns:
//      true: if the value passed is equal to any value inside of the queue
//      false: if the value passed is not equal to any value inside of the queue
//  Purpose:
//      Checks the current queue for any already loaded nodes so that it doesn'that
//      end up in an infinite loop or skewing the shortest distance to node measurement
//----------------------------------------------------------------------------------------

bool Closeness::searchQueue(queue<int> next, int val) const
{
  while (!next.empty())
  {
    int c = 0;
    c = next.front();

    if (c == val)
      return true;

    next.pop();
  }
  return false;
}