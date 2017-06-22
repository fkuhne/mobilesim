#include "OccupancyGrid.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

OccupancyGrid::OccupancyGrid()
{
  for(int i = 0; i <= WINDOW_SIZE_X; i++) {
    for(int j = 0; j <= WINDOW_SIZE_Y; j++) {
      grid[i][j].bayes = 0.5;
      grid[i][j].himm = 0;
      grid[i][j].visited = false;
      grid[i][j].alpha = SONAR_BETA;
      grid[i][j].distance = SONAR_MAX_RANGE / WINDOW_SCALE_DIVIDER;
  }}
}

void OccupancyGrid::clearBayes()
{
  for(int i = 0; i <= WINDOW_SIZE_X; i++) {
    for(int j = 0; j <= WINDOW_SIZE_Y; j++) {
      grid[i][j].bayes = 0.5;
  }}
}

void OccupancyGrid::clearVisited()
{
  for(int i = 0; i <= WINDOW_SIZE_X; i++) {
    for(int j = 0; j <= WINDOW_SIZE_Y; j++) {
      grid[i][j].visited = false;
  }}
}

void OccupancyGrid::computeBayes(const int gridX, const int gridY, const int s, const int r, const double alpha)
{
  int R = 2*SONAR_MAX_RANGE / WINDOW_SCALE_DIVIDER;
  double beta = SONAR_BETA;
  double pso = 0.0, pse = 0.0;

  double _1t = (R - r) / R;
  double _2t = (beta - fabs(alpha)) / beta;
  double t = _1t + _2t;

  if(r < (s - S_TOLERANCE))
  {
    // Region II
    //printf("II:\t");
    //pse = ((double((R - r) / R) + double((beta - abs(alpha)) / beta))) / 2;
    pse = t / 2;
    pse = (pse < 0.7) ? 0.7 : pse;
    pso = 1.0 - pse;
  }
  else
  {
    // Region I
    //printf("I:\t");
    //pso = ((double((R - r) / R) + double((beta - abs(alpha)) / beta))*0.98) / 2;
    pso = (t * 0.8) / 2;
    pse = 1.0 - pso;
  }

  //printf("s=%.2f\tR=%d\tr=%.2f\t1t=%.2f\tbeta=%.2f\talpha=%.2f\t2t=%.2f\tpso=%.2f\tpse=%.2f",
  //  s, R, r, _1t, beta, alpha, _2t, pso, pse);

  double po = grid[gridX][gridY].bayes;
  double pe = 1.0 - po;
  /* Computes the new value. */
  grid[gridX][gridY].bayes = (pso * po) / (pso * po + pse * pe);

  /* Have to protect against absolute zero. */
  if(grid[gridX][gridY].bayes == 0)
    grid[gridX][gridY].bayes = 0.2;

  //printf("\t> %.2f\n", grid[gridX][gridY].bayes);

}

void OccupancyGrid::computeHIMM(int region, const int gridX, const int gridY)
{
  if(grid[gridX][gridY].himm < HIMM_MAX_VALUE && region == 1) /* Maybe put a little tolerance here? */
  {
    grid[gridX][gridY].himm += 3;

    if(gridX > 0) grid[gridX - 1][gridY].himm += 1;
    if(gridX < WINDOW_SIZE_X) grid[gridX + 1][gridY].himm += 1;
    if(gridY > 0) grid[gridX][gridY - 1].himm += 1;
    if(gridY < WINDOW_SIZE_X) grid[gridX][gridY - 1].himm += 1;

    gro(gridX, gridY);
  }
  else if(grid[gridX][gridY].himm > 0 && region == 2)
  {
    grid[gridX][gridY].himm -= 1;
    if(grid[gridX][gridY].himm < 0)
      grid[gridX][gridY].himm = 0;
  }
}

void OccupancyGrid::gro(int gridX, int gridY)
{
  double newValue = (double)grid[gridX][gridY].himm;

  /* First row. */
  if((gridX > 0) && (gridY > 0)) newValue += grid[gridX - 1][gridY - 1].himm * 0.5;
  if(gridY > 0) newValue += grid[gridX][gridY - 1].himm * 0.5;
  if((gridX < WINDOW_SIZE_X) && (gridY > 0)) newValue += grid[gridX + 1][gridY - 1].himm * 0.5;

  /* Second row. */
  if(gridX > 0) newValue += grid[gridX - 1][gridY].himm * 0.5;
  if(gridX < WINDOW_SIZE_X) newValue += grid[gridX + 1][gridY].himm * 0.5;

  /* Third row. */
  if((gridX > 0) && (gridY < WINDOW_SIZE_Y)) newValue += grid[gridX - 1][gridY + 1].himm * 0.5;
  if(gridY < WINDOW_SIZE_Y) newValue += grid[gridX][gridY + 1].himm * 0.5;
  if((gridX < WINDOW_SIZE_X) && (gridY < WINDOW_SIZE_Y)) newValue += grid[gridX + 1][gridY + 1].himm * 0.5;

  if(newValue < HIMM_MAX_VALUE)
    grid[gridX][gridY].himm = (int)(round(newValue));
  else
    grid[gridX][gridY].himm = HIMM_MAX_VALUE;
}
