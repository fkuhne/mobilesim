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

void PotentialFields::updateState(const int gridX, const int gridY, const int himmValue)
{
  if(himmValue > 5)
  {
    grid[gridX][gridY].potential = 1.0;
    grid[gridX][gridY].state = _occupied;
  }
  else if(himmValue == 0)
  {
    grid[gridX][gridY].potential = 0.0;
    grid[gridX][gridY].state = _free;
  }
}
void PotentialFields::compute(const int gridX, const int gridY)
{
  /* I don't have to care about separate old and new values, as long as I follow
   * the natural order to go through the matrix of points. That is, points above
   * and to the left of (robotX, robotY) are new values, and points below and
   * to the right are old values, exactly how the Gauss-Seidel relaxation rule. */

  /* If some coordinate goes out of the map, its value is considered to be 1. */

  double partial = 1;

  if(gridX > 0) partial = grid[gridX - 1][gridY].potential;

  if(gridY > 0) partial += grid[gridX][gridY - 1].potential;
  else partial += 1;

  if(gridX < WINDOW_SIZE_X) partial += grid[gridX + 1][gridY].potential;
  else partial += 1;

  if(gridY < WINDOW_SIZE_Y) partial += grid[gridX][gridY + 1].potential;
  else partial += 1;

  grid[gridX][gridY].potential = 0.25*partial;
}
