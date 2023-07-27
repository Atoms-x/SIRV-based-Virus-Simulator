#ifndef CLOSENESS_H
#define CLOSENESS_H

#include <iostream>
#include <string>
#include <vector>
#include "PopulationNode.h"
#include <queue>

using namespace std;

class Closeness
{
  public:
    void main(vector<PopulationNode>&, int, int);
    int determinePriority(vector<PopulationNode>, int, int);
    bool search(vector<int>, int) const;
    bool searchQueue(queue<int>, int) const;
};
#endif