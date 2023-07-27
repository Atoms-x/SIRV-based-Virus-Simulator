#ifndef PERSON_H
#define PERSON_H

#include <iostream>

using namespace std;

class Person
{
  private:
    int daySick;
    char status;
  public:
    Person()
    {
      daySick = 0;
      status = 'S';
    }

    void setDaySick (int d)
      { daySick = d; }
    int getDaySick () const
      { return daySick; }
    void setStatus (char s)
      { status = s; }
    char getStatus () const
      { return status; }
};
#endif