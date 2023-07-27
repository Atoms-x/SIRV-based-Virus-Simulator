#ifndef DEGREE_H
#define DEGREE_H

#include <iostream>
#include <string>
#include <vector>
#include "PopulationNode.h"

using namespace std;

class Degree
{
  public:
    void main(vector<PopulationNode>&, int, int);
    int determinePriority(vector<PopulationNode>, int, int);
};
#endif