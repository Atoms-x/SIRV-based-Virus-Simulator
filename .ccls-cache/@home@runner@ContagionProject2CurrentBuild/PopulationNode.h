#ifndef POPULATIONNODE_H
#define POPULATIONNODE_H

#include <iostream>
#include <vector>

using namespace std;

class PopulationNode
{
  private:
    int population;
    int susceptible;
    int infected;
    int recovered;
    int vaccinated;
    double closenessScore;
    int degreeScore;
    int labelValue;
    int priorityValue;
  public:
    PopulationNode()
    {
      population = 0;
      susceptible = 0;
      infected = 0;
      recovered = 0;
      vaccinated = 0;
      closenessScore = 0.0;
      degreeScore = 0.0;
      labelValue = 0;
      priorityValue = 0;
    }

    vector<int> adjacentNodes; // Prevents writing functions just for the vectors

    void setPopulation (int p)
      { population = p; }
    int getPopulation () const
      { return population; }
    void setSusceptible (int s)
      { susceptible = s; }
    int getSusceptible () const
      { return susceptible; }
    void setInfected (int i)
      { infected = i; }
    int getInfected () const
      { return infected; }
    void setRecovered (int r)
      { recovered = r; }
    int getRecovered () const
      { return recovered; }
    void setVaccinated (int v)
      { vaccinated = v; }
    int getVaccinated () const
      { return vaccinated; }
    void setClosenessScore (double c)
      { closenessScore = c; }
    double getClosenessScore () const
      { return closenessScore; }
    void setDegreeScore (double d)
      { degreeScore = d; }
    double getDegreeScore () const
      { return degreeScore; }
    void setLabelValue (int l)
      { labelValue = l; }
    int getLabelValue () const
      { return labelValue; }
    void setPriorityValue (double pv)
      { priorityValue = pv; }
    double getPriorityValue () const
      { return priorityValue; }

    //Overloaded < operator to do priority comparisons for vaccine distribution to place into a set
    bool operator< (const PopulationNode &right)
      { return priorityValue < right.priorityValue; }
    
};
#endif