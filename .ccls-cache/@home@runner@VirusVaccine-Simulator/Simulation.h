#ifndef SIMULATION_H
#define SIMULATION_H

#include "PopulationNode.h"
#include "Analysis.h"
#include <queue>

class Simulation
{
  public:
    void main(vector<PopulationNode> &, int, int&, int, int, int, Analysis&);
    int getInfectedTotal(vector<PopulationNode>);
    int getRecoveredTotal(vector<PopulationNode>);
    bool search(vector<int>, int) const;
    bool searchQueue(queue<int>, int) const;
};
#endif