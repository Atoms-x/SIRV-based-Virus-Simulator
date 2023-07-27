#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <queue>

#include "Simulation.h"
#include "PopulationNode.h"
#include "Person.h"

using namespace std;

//--------------------------------------------------------------------------------------------
// void main
//  Arguments:
//      sim: Passed by refernce to display stored data and eventually manipulate in the simualation
//      numNodes: number of nodes/population areas
//      simCount: passed by reference to keep track of which sim run this is
//      infectedArea: gives the designated area for the start of the infection
//      infectiousPeriod: gives the period of time an infected is sick till recovery
//      contactRate: gives the amount of people that get infected per infected person
//      analysis: Passed by reference to log the peak infected, peak day, final day, and total infected
//  Returns:
//      Nothing explicitly, displaying and modifying the sim vectors PopulationNodes
//  Purpose:
//      Runs the simulation. Creates the agents, distributes the vaccine among them
//      spreads the infection through them, logs the data and displays the status each day
//---------------------------------------------------------------------------------------------

void Simulation::main(vector<PopulationNode> &sim, int numNodes, int &simCount, int infectedArea, int infectiousPeriod, int contactRate, Analysis &analysis)
{
  int num = 1;
  vector<vector <Person>> population; // The agent based sim set up
  vector<int> checked; // Used to reference against to not spread the infection again
  queue<int> nextArea; // Specifies the areas to spread to

  // AGENT SET-UP ********************************************************************************
  //Adding vectors of persons to the population vector at the correct amount
  for (int i = 0; i < numNodes; i++)
  {
    population.push_back(vector <Person>(sim[i].getPopulation()));
  }

  //Setting the right number of persons per vector/area to vaccinated (the rest are susceptible)
  for (int y = 0; y < numNodes; y++)
  {
    int distributeVaccine = sim[y].getVaccinated();

    if (distributeVaccine > 0)
    {
      for (auto it = population[y].begin(); it != population[y].end(); it++)
      {
        if (distributeVaccine > 0)
        {
          (*it).setStatus('V');
          distributeVaccine--;
        }
      }
    }
  }

  // Set the first non-vaccinated person to infected, if possible
  if (sim[infectedArea-1].getSusceptible() > 0)
  {
    int count = 1;
    for (auto it = population[infectedArea-1].begin(); it != population[infectedArea-1].end(); it++)
    {
      if((*it).getStatus() == 'S' && count > 0 && (*it).getStatus() != 'V')
      {
        (*it).setStatus('I');
        (*it).setDaySick(1);
        sim[infectedArea-1].setInfected(1);
        sim[infectedArea-1].setSusceptible(sim[infectedArea-1].getSusceptible()-1);
        count--;
      }
    }
  }
  // END OF AGENT SET-UP **************************************************************************

  // INITIAL DISPLAY ******************************************************************************
  string whichOne[4] = {"CLOSENESS DISTRIBUTION", "DEGREE DISTRIBUTION", "RANDOM DISTRIBUTION", "EQUAL DISTRIBUTION"};
  
  //Simple conditional to only output the starting info (regional population and adjacency list) once
  if (simCount == 1)
  {  
    cout << "Regional Population\n";
    
    // Simple for loop to pull population data, with some light formatting REGIONAL POPULATION
    for (int i = 0; i < numNodes; i++)
    {
      cout << num << " " << sim[i].getPopulation() << endl;
      num++;
    }

    cout << "\nAdjacency List\n";
    num = 1; //Reset the num count for proper display

    // Nested for loop for displaying adjacent nodes. The first loop is to step through the 
    // vector of PopulationNodes, the second vector is to step through the vector inside
    // of PopulationNode, called adjacentNodes, to output an adjacency list
    for (int i = 0; i < numNodes; i++)
    {
      cout << num << ": "; 

      for (int y = 0; y < sim[i].adjacentNodes.size(); y++)
        cout << sim[i].adjacentNodes[y] << " ";

      cout << endl;  
      num++;
    }
  }

  //Display of the zero day and correct model type
  cout << "\n" << whichOne[simCount - 1] << "\n";
  cout << "Day 0\n";
  num = 1;

  for (int i = 0; i < numNodes; i++)
  {
    cout <<  num << "\tPOP: " << setw(5) << left << sim[i].getPopulation();
    cout <<  "\tS: " << setw(7) << sim[i].getSusceptible();
    cout << " I: " << setw(7) <<  sim[i].getInfected();
    cout << " R: " << setw(7) <<  sim[i].getRecovered();
    cout << " V: " << setw(7) <<  sim[i].getVaccinated() << endl;
    num++;
  }
  //END OF INITIAL DISPLAY ***************************************************************************
  
  //SIMULATION ***************************************************************************************
  // The simulation works by creating a while loop condition until nobody is sick anymore, meaning
  // the infection has run it's course. Each day consists of stepping through each PopulationNode once.
  // At each corresponding index point is a population of persons (agents). These are then stepped
  // through individually and manipulated appropriately as they interact with the infection,
  // each other, and adjacent populations. At the end of each PopulationNode/Agent check, a check
  // is made against a queue that is only loaded if it hasn't been before or already is. If a match
  // occurs, then the area is "infected", but only on the first susceptible, if any. This occurs
  // in a 1-day delayed fashion because the loading of the queue only occurs after the day that 
  // the condition for spread is reached. The current day is displayed and the peak infection
  // is logged if the current total infection is greater than what is in the variable. Day number
  // the peak was reached is also stored. After the while loop ends, the total infection and length
  // of the infection is stored
  int day = 1; // Zeroth day already displayed, really starts on day 1
  
  while (getInfectedTotal(sim) > 0)
  {
    cout << "\nDay " << day << endl;
    //Spread Virus ******************************************************************
    for (int y = 0; y < numNodes; y++)
    {
      if (sim[y].getInfected() > 0)
      {
        int newlyInfected = (sim[y].getInfected()*contactRate); // Count to spread for given area/day

        for (auto it = population[y].begin(); it != population[y].end(); it++)
        {
          // Increments an agents days of sickness
          if ((*it).getStatus() == 'I' && (*it).getDaySick() <= infectiousPeriod) 
          {
            (*it).setDaySick((*it).getDaySick()+1);
          }
          // If they've been sick for long enough, they recover
          if ((*it).getStatus() == 'I' && (*it).getDaySick() > infectiousPeriod)
          {
            (*it).setStatus('R');
            sim[y].setInfected(sim[y].getInfected()-1);
            sim[y].setRecovered(sim[y].getRecovered()+1);
          }
          // Spreads the sickenss if they are susceptible to it or there is any left
          if ((*it).getStatus() == 'S' && newlyInfected > 0)
          {
            (*it).setStatus('I');
            (*it).setDaySick((*it).getDaySick()+1);
            sim[y].setInfected(sim[y].getInfected()+1);
            sim[y].setSusceptible(sim[y].getSusceptible()-1);
            newlyInfected--;
          }
        }
      }

      //Infect new area ***********************************
      if (searchQueue(nextArea, sim[y].getLabelValue()))
      {
        if (sim[nextArea.front()-1].getSusceptible() > 0)
        {
          int count = 1;
          for (auto it = population[nextArea.front()-1].begin(); it != population[nextArea.front()-1].end(); it++)
          {
            if((*it).getStatus() == 'S' && count > 0 && (*it).getStatus() != 'V')
            {
              (*it).setStatus('I');
              (*it).setDaySick(1);
              sim[nextArea.front()-1].setInfected(1);
              sim[nextArea.front()-1].setSusceptible(sim[nextArea.front()-1].getSusceptible()-1);
              count--;
            }
          }
        }
        nextArea.pop();
      }  
    } // END OF TURN ******************************************************

    // Check for conditions to spread to other areas and load the other areas
    for (int y = 0; y < numNodes; y++)
    {
      if (sim[y].getInfected() > (sim[y].getPopulation() / 2) )
      {
        for (auto it = sim[y].adjacentNodes.begin(); it != sim[y].adjacentNodes.end(); it++)
        {
          if(!search(checked, *it) && !searchQueue(nextArea, *it))
          {
            nextArea.push(*it);
            checked.push_back(*it);
          }
        }
      }
    }

    num = 1;
    for (int i = 0; i < numNodes; i++)
    {
      cout <<  num << "\tPOP: " << setw(5) << left << sim[i].getPopulation();
      cout <<  "\tS: " << setw(7) << sim[i].getSusceptible();
      cout << " I: " << setw(7) <<  sim[i].getInfected();
      cout << " R: " << setw(7) <<  sim[i].getRecovered();
      cout << " V: " << setw(7) <<  sim[i].getVaccinated() << endl;
      num++;
    }
  
    // Tracking the max infected and day
    if (analysis.getPeak() < getInfectedTotal(sim))
    {
      analysis.setPeak(getInfectedTotal(sim));
      analysis.setPeakDay(day);
    }

    day++;
  } // END OF WHILE LOOP
  analysis.setTotalInfected(getRecoveredTotal(sim));
  analysis.setLastDay(day-1);

  simCount++;
  cout << endl;
} // END OF SIMULATION ****************************************************************************

//--------------------------------------------------------------------------------------------
// void getInfectedTotal
//  Arguments:
//      sim: Passed by value to step through and get the total count of infected
//  Returns:
//      returns an integer called infectedTotal (its the sum of all infected)
//  Purpose:
//      Determines whether the simulation will go for another turn by returning a 
//      current total infected
//---------------------------------------------------------------------------------------------

int Simulation::getInfectedTotal(vector<PopulationNode> sim)
{
  int infectedTotal = 0;

  for (auto it = sim.begin(); it != sim.end(); it++)
  {
    infectedTotal += (*it).getInfected();
  }

  return infectedTotal;
}

//--------------------------------------------------------------------------------------------
// void getRecoveredTotal
//  Arguments:
//      sim: Passed by value to step through and get the total count of recovered
//  Returns:
//      returns an integer called recoveredTotal (its the sum of all recovered)
//  Purpose:
//      Returns a count for the total recovered, which is also the total number infected
//---------------------------------------------------------------------------------------------

int Simulation::getRecoveredTotal(vector<PopulationNode> sim)
{
  int recoveredTotal = 0;

  for (auto it = sim.begin(); it != sim.end(); it++)
  {
    recoveredTotal += (*it).getRecovered();
  }

  return recoveredTotal;
}

//-----------------------------------------------------------------------------------
// bool search
//  Arguments:
//      checked: passed by value to make checks into the vector of node values
//      val: The value checked against to ensure the node hasn't already been checked
//  Returns:
//      true: if the value passed is equal to any value inside of the vector
//      false: if the value passed is not equal to any value inside of the queue
//  Purpose:
//      Checks the checked vector for any already checked nodes so that it doesn'that
//      end up in an infinite loop or create anomolous behaviour with infected
//------------------------------------------------------------------------------------

bool Simulation::search(vector<int> checked, int val) const
{
  for (auto it = checked.begin(); it != checked.end(); it++)
    if ((*it) == val)
      return true;
  
  return false;
}

//-----------------------------------------------------------------------------------
// bool searchQueue
//  Arguments:
//      next: passed by value to make checks into the queue of node values 
//      val: The value checked against to ensure the node isn't already queue'd
//  Returns:
//      true: if the value passed is equal to any value inside of the queue
//      false: if the value passed is not equal to any value inside of the queue
//  Purpose:
//      Checks the current queue for any already loaded nodes so that it doesn'that
//      end up in an infinite loop or create anomolous behaviour with infected
//------------------------------------------------------------------------------------

bool Simulation::searchQueue(queue<int> next, int val) const
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