#ifndef __POTENTIAL_FIELDS_H__
#define __POTENTIAL_FIELDS_H__

#include "myGlobals.h"

enum cellState {_unknown = 0, _free, _occupied};

class PotentialFields
{
private:

public:
  PotentialFields();

  void clearGrid();
  void clearVisited();
  void updateState(int gridX, int gridY, int himmValue);
  double compute(int robotX, int robotY);

  struct {
    double potential;
    cellState state;
    bool visited;
  } grid[WINDOW_SIZE_X+1][WINDOW_SIZE_Y+1];

  int numberOfCells = WINDOW_SIZE_X * WINDOW_SIZE_Y;
};

#endif
