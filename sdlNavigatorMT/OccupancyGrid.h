#ifndef __OCCUPANCY_GRID_H__
#define __OCCUPANCY_GRID_H__

#include "myGlobals.h"

class OccupancyGrid
{
private:

public:
  OccupancyGrid();

  void clearBayes();
  void clearVisited();
  void computeBayes(const int gridX, const int gridY, const int s, const int r, const double alpha);
  void computeHIMM(int region, const int gridX, const int gridY);
  void gro(int gridX, int gridY);

  struct {
    double bayes;
    int himm;
    bool visited;
    double alpha;
    double distance;
  } grid[WINDOW_SIZE_X+1][WINDOW_SIZE_Y+1];
};

#endif
