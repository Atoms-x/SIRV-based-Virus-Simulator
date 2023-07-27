#ifndef READ_H
#define READ_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Read
{
  public:
    void main(vector<vector <int>>&, vector<int>&, int&, int&, int&, int&);
    void loadPopulation(vector<int>&, string);
    void loadAdjacency(vector<vector <int>>&, string);
};
#endif