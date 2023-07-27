#ifndef ANALYSIS_H
#define ANALYSIS_H

class Analysis
{
  private:
    int peak;
    int peakDay;
    int lastDay;
    int totalInfected;
  public:
    Analysis()
    {
      peak = 0;
      peakDay = 0;
      lastDay = 0;
      totalInfected = 0;
    }

    void setPeak (int p)
      { peak = p; }
    int getPeak () const
      { return peak; }
    void setPeakDay (int pd)
      { peakDay = pd; }
    int getPeakDay () const
      { return peakDay; }
    void setLastDay (int p)
      { lastDay = p; }
    int getLastDay () const
      { return lastDay; }
    void setTotalInfected (int p)
      { totalInfected = p; }
    int getTotalInfected () const
      { return totalInfected; }
};
#endif