#ifndef __POTENTIAL_FIELDS_H__
#define __POTENTIAL_FIELDS_H__

#include "myGlobals.h"

class PotentialFields
{
private:

public:
  PotentialFields();

  void clearGrid();
  void clearVisited();
  void compute(const int robotX, const int robotY);

  struct {
    double field;
    bool visited;
  } grid[WINDOW_SIZE_X+1][WINDOW_SIZE_Y+1];
};

#endif
