#include "PotentialFields.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

PotentialFields::PotentialFields()
{
  for(int i = 0; i <= WINDOW_SIZE_X; i++) {
    for(int j = 0; j <= WINDOW_SIZE_Y; j++) {
      grid[i][j].field = 0;
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

}
