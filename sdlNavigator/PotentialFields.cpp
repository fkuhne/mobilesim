#include "PotentialFields.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

PotentialFields::PotentialFields()
{
  for(int i = 0; i <= WINDOW_SIZE_X; i++) {
    for(int j = 0; j <= WINDOW_SIZE_Y; j++) {
      grid[i][j].potential = 0;
      grid[i][j].state = _unknown;
      grid[i][j].visited = false;
  }}
}

void PotentialFields::clearVisited()
{
  for(int i = 0; i <= WINDOW_SIZE_X; i++) {
    for(int j = 0; j <= WINDOW_SIZE_Y; j++) {
      grid[i][j].visited = false;
  }}
}

void PotentialFields::compute(const int robotX, const int robotY)
{
  /* I don't have to care about separate old and new values, as long as I follow
   * the natural order to go through the matrix of points. That is, points above
   * and to the left of (robotX, robotY) are new values, and points below and
   * to the right are old values, exactly how the Gauss-Seidel relaxation rule. */

  /* If some coordinate goes out of the map, its value is considered to be 1. */

  double partial = 1;

  if(robotX > 0) partial = grid[robotX-1][robotY].potential;

  if(robotY > 0) partial += grid[robotX][robotY-1].potential;
  else partial += 1;

  if(robotX < WINDOW_SIZE_X) partial += grid[robotX+1][robotY].potential;
  else partial += 1;

  if(robotY < WINDOW_SIZE_Y) partial += grid[robotX][robotY+1].potential;
  else partial += 1;

  grid[robotX][robotY].potential = 0.25*partial;
}
