/*
 * Logger class
 * Taken from http://robots.mobilerobots.com/wiki/ARIA_Example:_Use_a_robot_task_to_log_or_print_robot_pose_or_other_information_periodically
 *   and http://www.eecs.yorku.ca/course_archive/2009-10/W/4421/doc/pioneer/aria/robotSyncTaskExample_8cpp-example.html#a500
 *
 * Felipe Kuhne
 * fkuhne at gmail dot com
 * May, 2017
 */

#include "SDLTask.h"
#include "myGlobals.h"
#include "OccupancyGrid.h"
#include "PotentialFields.h"

using namespace std;

OccupancyGrid grid;
PotentialFields potential;

SDLTask::SDLTask(ArRobot *r, bool _method):
  /* Store a pointer to the ArRobot object. */
  robot(r),
  method(_method)
{
}

static inline int min4(int a1, int a2, int a3, int a4)
{
  int min = a1;
  if(min > a2) min = a2;
  if(min > a3) min = a3;
  if(min > a4) min = a4;
  if(min < 0) min = 0;
  return min;
}

static inline int max4(int a1, int a2, int a3, int a4)
{
  int max = a1;
  if(max < a2) max = a2;
  if(max < a3) max = a3;
  if(max < a4) return a4;
  return max;
}

void computeActivationWindow(ArRobot *robot)
{
  if(robot == NULL)
    return;

  int robotX = robot->getX();
  int robotY = robot->getY();
  double robotTheta = robot->getTh();
  double cosTheta = cos(ArMath::degToRad(robotTheta));
  double sinTheta = sin(ArMath::degToRad(robotTheta));

  ArSensorReading *sensorReading[8] = {NULL};
  struct _coord {int x; int y;} sensorEnd[8];
  int leftX=0xFFFF, rightX=-1, upperY=0xFFFF, bottomY=-1;
  for(int i = 0; i < 8; i++)
  {
    /* Compute the coordinates of the sensor reading with respect to the scaled
     * map. */
    sensorReading[i] = robot->getSonarReading(i);
    double localEndX = sensorReading[i]->getLocalX()*cosTheta - sensorReading[i]->getLocalY()*sinTheta;
    double localEndY = sensorReading[i]->getLocalX()*sinTheta + sensorReading[i]->getLocalY()*cosTheta;
    sensorEnd[i].x = round((robotX + localEndX + X_AXIS_LIMIT) / WINDOW_SCALE_DIVIDER);
    sensorEnd[i].y = round((Y_AXIS_LIMIT - (robotY + localEndY)) / WINDOW_SCALE_DIVIDER);
    if(sensorEnd[i].y < 0) sensorEnd[i].y = 0;

    if(sensorEnd[i].x < leftX) leftX = sensorEnd[i].x;
    if(sensorEnd[i].y < upperY) upperY = sensorEnd[i].y;

    if(sensorEnd[i].x > rightX) rightX = sensorEnd[i].x;
    if(sensorEnd[i].y > bottomY) bottomY = sensorEnd[i].y;
  }

  /* Define activation window. */
  /*int activationWindowSize = (SONAR_MAX_RANGE / WINDOW_SCALE_DIVIDER);
  int leftX = robotX - activationWindowSize;
  if(leftX < 0) leftX = 0;
  int rightX = robotX + activationWindowSize;
  if(rightX > WINDOW_SIZE_X) rightX = WINDOW_SIZE_X;
  int upperY = robotY - activationWindowSize;
  if(upperY < 0) upperY = 0;
  int bottomY = robotY + activationWindowSize;
  if(bottomY > WINDOW_SIZE_Y) bottomY = WINDOW_SIZE_Y;*/

  for(int gridY = upperY; gridY <= bottomY; gridY++)
    for(int gridX = leftX; gridX <= rightX; gridX++)
      if(potential.grid[gridX][gridY].state == _unknown)
        potential.grid[gridX][gridY].state = _free;

  /* Make the region where the robot is free. */
  //for(int gridY = robotY-5; gridY <= robotY+5; gridY++)
  //  for(int gridX = robotX-5; gridX <= robotX+5; gridX++)
  //    if(potential.grid[gridX][gridY].state == _unknown)
  //      potential.grid[gridX][gridY].state = _free;

  //SDL_Rect activationWindowRect = {leftX, upperY, rightX - leftX, bottomY - upperY};
  //SDL_SetRenderDrawColor(renderer, 180, 180, 180, SDL_ALPHA_OPAQUE);
  //SDL_RenderDrawRect(renderer, &activationWindowRect);
}

void SDLTask::computePotentialField(ArRobot *robot, SDL_Renderer* renderer)
{
  if(renderer == NULL || robot == NULL)
    return;

  /* Compute potential. */
  double error = 1.0;
  double min_error = 0.00001;
  while(error > min_error)
  {
    error = 0;

    /* Left to right, top to bottom. */
    for(int gridY = 0; gridY <= WINDOW_SIZE_Y; gridY++)
    {
      for(int gridX = 0; gridX <= WINDOW_SIZE_X; gridX++)
      {
        if(potential.grid[gridX][gridY].state == _free)
        {
          potential.compute(gridX, gridY);
        }
      }
    }

    /* Right to left, top to bottom. */
    for(int gridY = 0; gridY <= WINDOW_SIZE_Y; gridY++)
    {
      for(int gridX = WINDOW_SIZE_X; gridX >= 0; gridX--)
      {
        if(potential.grid[gridX][gridY].state == _free)
        {
          potential.compute(gridX, gridY);
        }
      }
    }

    /* Left to right, bottom to top. */
    for(int gridY = WINDOW_SIZE_Y; gridY >= 0; gridY--)
    {
      for(int gridX = 0; gridX <= WINDOW_SIZE_X; gridX++)
      {
        if(potential.grid[gridX][gridY].state == _free)
        {
          potential.compute(gridX, gridY);
        }
      }
    }

    /* Right to left, bottom to top. */
    for(int gridY = WINDOW_SIZE_Y; gridY >= 0; gridY--)
    {
      for(int gridX = WINDOW_SIZE_X; gridX >= 0; gridX--)
      {
        if(potential.grid[gridX][gridY].state == _free)
        {
          error += potential.compute(gridX, gridY);
        }
      }
    }
  }

  int robotX = (robot->getX() + X_AXIS_LIMIT) / WINDOW_SCALE_DIVIDER;
  int robotY = (Y_AXIS_LIMIT - robot->getY()) / WINDOW_SCALE_DIVIDER;

  /* Define heading angle. */
  double Dx = potential.grid[robotX - 1][robotY].potential - potential.grid[robotX + 1][robotY].potential;
  double Dy = potential.grid[robotX][robotY + 1].potential - potential.grid[robotX][robotY - 1].potential;
  //heading = ArMath::radToDeg(atan2(Dy, Dx));

  setHeading(ArMath::atan2(Dy, Dx));
}

void computeOccupancyGrid(ArRobot *robot, bool _method, SDL_Renderer* renderer)
{
  if(robot == NULL)
    return;

  /* Get information on sonars (not just range reading!). */
  double sonarRange[8] = {0};
  ArSensorReading *sensorReading[8] = {NULL};
  for(int i = 0; i < 8; i++)
  {
    sonarRange[i] = robot->getSonarRange(i);
    sensorReading[i] = robot->getSonarReading(i);
  }

  /* Compute robot data just once. */
  int robotX = robot->getX();
  int robotY = robot->getY();
  double robotTheta = robot->getTh();
  double cosTheta = cos(ArMath::degToRad(robotTheta));
  double sinTheta = sin(ArMath::degToRad(robotTheta));
  double cosPlus15 = cos(ArMath::degToRad(robotTheta + SONAR_BETA));
  double sinPlus15 = sin(ArMath::degToRad(robotTheta + SONAR_BETA));
  double cosMinus15 = cos(ArMath::degToRad(robotTheta - SONAR_BETA));
  double sinMinus15 = sin(ArMath::degToRad(robotTheta - SONAR_BETA));

  /* Go to all sonars around the robot. */
  for(int i = 0; i < 8; i++)
  {
    if((_method == true) && (sonarRange[i] >= SONAR_MAX_RANGE))
      continue;

//printf("sensor=(%.2f,%.2f,%.2f) range=%.2f(%.2f,%.2f), reading=(%.2f,%.2f)\n",
//  sensorReading[i]->getSensorX(), sensorReading[i]->getSensorY(), sensorReading[i]->getSensorTh(),
//  sonarRange[i], sensorReading[i]->getLocalX(), sensorReading[i]->getLocalY(),
//  sensorReading[i]->getX(), sensorReading[i]->getY());
//continue;

    /* getSensorX() and getSensorY() return X and Y coordinates of the sensor
     * origin. Compute the coordinates of this origin according to the robot
     * heading. */
    double localOriginX = sensorReading[i]->getSensorX()*cosTheta - sensorReading[i]->getSensorY()*sinTheta;
    double localOriginY = sensorReading[i]->getSensorX()*sinTheta + sensorReading[i]->getSensorY()*cosTheta;

    /* Compute the coordinates of the sensor origin with respect to the scaled
     * map. */
    int globalOriginX = round((robotX + localOriginX + X_AXIS_LIMIT) / WINDOW_SCALE_DIVIDER);
    int globalOriginY = round((Y_AXIS_LIMIT - (robotY + localOriginY)) / WINDOW_SCALE_DIVIDER);

    //printf("robot=(%d,%d) sensor local=(%.2f,%.2f) global=(%d,%d)",
    //  robotX, robotY, localOriginX, localOriginY, globalOriginX, globalOriginY);

    /* getLocalX() and getLocalY() return X and Y coordinates of the reading
     * point with respect of the sensor origin. Compute the coordinates of the
     * sensor reading according to the robot heading. */
    double localEndX = sensorReading[i]->getLocalX()*cosTheta - sensorReading[i]->getLocalY()*sinTheta;
    double localEndY = sensorReading[i]->getLocalX()*sinTheta + sensorReading[i]->getLocalY()*cosTheta;

    /* Compute the coordinates of the sensor reading with respect to the scaled
     * map. */
    int globalEndX = round((robotX + localEndX + X_AXIS_LIMIT) / WINDOW_SCALE_DIVIDER);
    int globalEndY = round((Y_AXIS_LIMIT - (robotY + localEndY)) / WINDOW_SCALE_DIVIDER);
    if(globalEndY < 0) globalEndY = 0;

    int u[2] = {globalEndX - globalOriginX, globalEndY - globalOriginY};
    //double s = sqrt(u[0]*u[0]+u[1]*u[1]);
    double s = sonarRange[i] / WINDOW_SCALE_DIVIDER;

    /* Unit length vector. It is the gradient vector, which gives us the
     * direction of the vector. */
    double v[2] = {u[0]/s, u[1]/s};

    /* Draw a line for the acoustic axis of the sensor. The color turns yellow
     * to red according to the sensor range. */
    //int color = 255 * (5000 - robot->getSonarRange(i)) / 5000;
    //SDL_SetRenderDrawColor(renderer, 255, 255 - color, 0, 127);
    //SDL_RenderDrawLine(renderer, globalOriginX, globalOriginY, globalEndX, globalEndY);

    /* Implement bayes method. */
    if(_method == true)
    {
      /* Compute the sensor cone. */
      int localConePlusX = sensorReading[i]->getLocalX()*cosPlus15 - sensorReading[i]->getLocalY()*sinPlus15;
      int localConePlusY = sensorReading[i]->getLocalX()*sinPlus15 + sensorReading[i]->getLocalY()*cosPlus15;
      int globalConePlusX = (robotX + localConePlusX + X_AXIS_LIMIT) / WINDOW_SCALE_DIVIDER;
      int globalConePlusY = (Y_AXIS_LIMIT - (robotY + localConePlusY)) / WINDOW_SCALE_DIVIDER;
      if(globalConePlusY < 0) globalConePlusY = 0;
      //SDL_RenderDrawLine(renderer, globalOriginX, globalOriginY, globalConePlusX, globalConePlusY);

      int localConeMinusX = sensorReading[i]->getLocalX()*cosMinus15 - sensorReading[i]->getLocalY()*sinMinus15;
      int localConeMinusY = sensorReading[i]->getLocalX()*sinMinus15 + sensorReading[i]->getLocalY()*cosMinus15;
      int globalConeMinusX = (robotX + localConeMinusX + X_AXIS_LIMIT) / WINDOW_SCALE_DIVIDER;
      int globalConeMinusY = (Y_AXIS_LIMIT - (robotY + localConeMinusY)) / WINDOW_SCALE_DIVIDER;
      if(globalConeMinusY < 0) globalConeMinusY = 0;
      //SDL_RenderDrawLine(renderer, globalOriginX, globalOriginY, globalConeMinusX, globalConeMinusY);

      /* Computes a rectangle around the sensor field of view. This is the area
      * that will be subjected to inspection (region of interest). */
      int x1 = min4(globalOriginX, globalConePlusX, globalConeMinusX, globalEndX) - 5;
      int y1 = min4(globalOriginY, globalConePlusY, globalConeMinusY, globalEndY) - 5;
      int x2 = max4(globalOriginX, globalConePlusX, globalConeMinusX, globalEndX) + 5;
      int y2 = max4(globalOriginY, globalConePlusY, globalConeMinusY, globalEndY) + 5;
      if(x1 > WINDOW_SIZE_X) {x1 = WINDOW_SIZE_X;} if(x1 < 0) {x1 = 0;}
      if(y1 > WINDOW_SIZE_X) {y1 = WINDOW_SIZE_X;} if(y1 < 0) {y1 = 0;}
      if(x2 > WINDOW_SIZE_X) {x2 = WINDOW_SIZE_X;}
      if(y2 > WINDOW_SIZE_X) {y2 = WINDOW_SIZE_X;}

      //printf("rect = (%d,%d,%d,%d)", x1, y1, x2, y2);
      /* Draw the rectangle for the region of interest of the sensor. */
      //SDL_Rect sensorROIRect = {x1, y1, x2 - x1, y2 - y1};
      //SDL_SetRenderDrawColor(renderer, 180, 180, 180, SDL_ALPHA_OPAQUE);
      //SDL_RenderDrawRect(renderer, &sensorROIRect);

      for(int gridY = y1; gridY <= y2; gridY++)
      {
        for(int gridX = x1; gridX <= x2; gridX++)
        {
          if(grid.grid[gridX][gridY].visited == true)
            continue;

          /* This is the vector from the sensor origin to the grid element. */
          int v[2] = {(gridX - globalOriginX), (gridY - globalOriginY)};
          /* This is the size of this vector. */
          int r = round(sqrt(v[0]*v[0]+v[1]*v[1]));
          /* This is the angle between the acoustic asix and the gris element vector. */
          double alpha = ArMath::atan2((v[0] * u[1] - v[1] * u[0]), (v[0] * u[0] + v[1] * u[1]));

          //printf(" origin=(%d,%d), grid=(%d,%d), r = %.2f, alpha = %.2f\n",
          //  globalOriginX, globalOriginY, gridX, gridY, r, alpha);

          /* Skip this grid element if it is outside the sensor cone or above the
          * Region I. */
          if((fabs(alpha) > SONAR_BETA) || (r > (s + S_TOLERANCE)))
            continue;

          /* Note that the regions of interest for the several sensors overlap. So
          * there will be cases a grid element will be inspected more than once.
          * If the current values for angle and distance are better than this,
          * leave the best values there. */
          if(alpha > grid.grid[gridX][gridY].alpha || r > grid.grid[gridX][gridY].distance)
            continue;

          if(grid.grid[gridX][gridY].bayes > 0.8)
          {
            grid.grid[gridX][gridY].visited = true;
            continue;
          }

          if(sonarRange[i] >= SONAR_MAX_RANGE || grid.grid[gridX][gridY].bayes < 0.5)
          {
            /* Paint with white */
            if(renderer)
            {
              SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
              SDL_RenderDrawPoint(renderer, gridX, gridY);
            }
            continue;
          }

          grid.computeBayes(gridX, gridY, s, r, alpha);
          //grid.grid[gridX][gridY].visited = true;

          grid.grid[gridX][gridY].distance = r;
          grid.grid[gridX][gridY].alpha = alpha;

          //int color = 255;
          //if(grid.bayes[gridX][gridY] <= 0.3) color = 255; /* White */
          //else if(grid.bayes[gridX][gridY] <= 0.5) color = 230; /* Light gray */
          //else if(grid.bayes[gridX][gridY] > 0.7) color = 127; /* Medium gray */
          //else color = 5; /* Black */
          //printf("bayes[%d][%d]=%.2f, color=%d\n", gridX, gridY, grid.bayes[gridX][gridY], color);
          if(renderer)
          {
            int color = (1.0 - grid.grid[gridX][gridY].bayes) * 255;
            SDL_SetRenderDrawColor(renderer, color, color, color, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawPoint(renderer, gridX, gridY);
          }
        }
      }
    }

    /* Implement HIMM. */
    else
    {
      int posX = globalOriginX;
      int posY = globalOriginY;
      //s = int(round(s));

      int cont = 0;
      /* This is a loop that gos through the pixels of sensor axis. */
      while(true)
      {
        double partialX = cont * v[0];
        double partialY = cont * v[1];

        posX = globalOriginX + partialX;
        posY = globalOriginY + partialY;

        if(posX > WINDOW_SIZE_X) {posX = WINDOW_SIZE_X;} if(posX < 0) {posX = 0;}
        if(posY > WINDOW_SIZE_X) {posY = WINDOW_SIZE_X;} if(posY < 0) {posY = 0;}

        /* This is the size of the vector going from the sensor to the obstacle.
         * Its total length is equal to s. So let us test it and define the last
         * coordinate on it to be the obstacle itself. So we can paint it red
         * and break the loop. */
        double q = sqrt(partialX * partialX + partialY * partialY);
        if((s < SONAR_MAX_RANGE/WINDOW_SCALE_DIVIDER) && (q >= s*0.99))
        {
          /* Here we are in region 1. */
          grid.computeHIMM(1, posX, posY);
          /* Set state of the cells according to the certainty values given by HIMM. */
          potential.updateState(posX, posY, grid.grid[posX][posY].himm);

          if(renderer)
          {
            int color = (15 - grid.grid[posX][posY].himm) * (255 / HIMM_MAX_VALUE);
            SDL_SetRenderDrawColor(renderer, color, color, color, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawPoint(renderer, posX, posY);
          }
        }

        else
          /* Region II. */
          grid.computeHIMM(2, posX, posY);

        if(q >= s) break;

        cont++;
      } // loop for axis points
    } // loop for mapping method
  } // loop for all sensors
}

void drawPotentialField(SDL_Renderer *renderer)
{
  for(int gridY = 0; gridY <= WINDOW_SIZE_Y; gridY++) {
    for(int gridX = 0; gridX <= WINDOW_SIZE_X; gridX++) {
      if(potential.grid[gridX][gridY].state != _unknown) //else
      {
        if(potential.grid[gridX][gridY].potential == 1 && potential.grid[gridX][gridY].state == _occupied)
          SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        else
        {
          int color = round(255.0 * (1.0 - potential.grid[gridX][gridY].potential));
          SDL_SetRenderDrawColor(renderer, 255-color, color, 0, SDL_ALPHA_OPAQUE);
        }
        SDL_RenderDrawPoint(renderer, gridX, gridY);
      }
    }
  }
}
// This is the method invoked as the user task
void SDLTask::sdlTask()
{
  SDL_Event event;

  /* This is an infinite loop, because is running on a different thread. */
  while(true)
  {
    SDL_PollEvent(&event);
    if(running && sdlTimer.mSecSince() >= 0)  // 1.0 second has passed since start or last log
    {
      /*if(event.type == SDL_QUIT)
      {
        running = false;
        return;
      }*/
      /*else if(event.type == SDL_KEYDOWN)
      {
        printf("%c\n", event.key.keysym.scancode);
      }*/

      /* Draw the robot. */
      //int x = (robot->getX() + X_AXIS_LIMIT) / WINDOW_SCALE_DIVIDER;
      //int y = (Y_AXIS_LIMIT - robot->getY()) / WINDOW_SCALE_DIVIDER;
      //SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
      //SDL_RenderDrawPoint(renderer, x, y);
      //SDL_SetRenderDrawColor(potentialRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
      //SDL_RenderDrawPoint(potentialRenderer, x, y);

      computeOccupancyGrid(robot, method, NULL);

      computeActivationWindow(robot);

      computePotentialField(robot, potentialRenderer);

      drawPotentialField(potentialRenderer);

      /* Redraw the screen. */
      //SDL_RenderPresent(renderer);
      SDL_RenderPresent(potentialRenderer);
      SDL_Delay(700);

      sdlTimer.setToNow(); // reset timer
    }
  }
}

int SDLTask::init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
      return -1;

    /*window = SDL_CreateWindow("Occupancy Grid",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      WINDOW_SIZE_X, WINDOW_SIZE_Y,
      0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //SDL_RenderSetLogicalSize(renderer, WINDOW_SIZE_X, WINDOW_SIZE_Y);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);*/

    potentialWindow = SDL_CreateWindow("Potential Field",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      WINDOW_SIZE_X, WINDOW_SIZE_Y,
      0);
    potentialRenderer = SDL_CreateRenderer(potentialWindow, -1, SDL_RENDERER_ACCELERATED);
    //SDL_RenderSetLogicalSize(renderer, WINDOW_SIZE_X, WINDOW_SIZE_Y);
    SDL_SetRenderDrawColor(potentialRenderer, 210, 210, 210, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(potentialRenderer);
    SDL_RenderPresent(potentialRenderer);

    sdlThread = thread(&SDLTask::sdlTask, this);

    setHeading(0);

    running = true;
    return 0;
}

void SDLTask::setHeading(double _heading)
{
  heading = _heading;
}

double SDLTask::getHeading()
{
  return heading;
}

SDLTask::~SDLTask()
{
  sdlThread.join();

  if(renderer) SDL_DestroyRenderer(renderer);
  if(window) SDL_DestroyWindow(window);
  if(potentialRenderer) SDL_DestroyRenderer(potentialRenderer);
  if(potentialWindow) SDL_DestroyWindow(potentialWindow);

  SDL_Quit();
}
