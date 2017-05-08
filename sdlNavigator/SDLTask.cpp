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

SDLTask::SDLTask(ArRobot *r):
  /* Store a pointer to the ArRobot object. */
  robot(r),
  /* Initialize the functor to be given added as an ArRobot user task with this
   * instance and which method to call. */
  SDLTaskFunc(this, &SDLTask::sdlTask)
{
}

int SDLTask::init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
      return -1;

    window = SDL_CreateWindow("SDL Navigator",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      WINDOW_SIZE_X, WINDOW_SIZE_Y,
      SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // add our task functor to the robot object as a user task,
    // to be invoked in every robot task cycle (approx. every 100ms):
    robot->addSensorInterpTask("SDLTask", 50, &SDLTaskFunc);

    running = true;
    return 0;
}

static inline int min4(int a1, int a2, int a3, int a4)
{
  int min = a1;
  if(min > a2) min = a2;
  if(min > a3) min = a3;
  if(min > a4) return a4;
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

void drawGrid(SDL_Renderer* renderer)
{
  if(renderer == NULL)
    return;

  SDL_SetRenderDrawColor(renderer, 240, 240, 240, SDL_ALPHA_OPAQUE);

  int gridStep = WINDOW_SIZE_X / 20;
  while(gridStep < WINDOW_SIZE_X)
  {
    SDL_RenderDrawLine(renderer, gridStep, 0, gridStep, WINDOW_SIZE_X);
    gridStep += WINDOW_SIZE_X / 20;
  }
  gridStep = WINDOW_SIZE_Y / 20;
  while(gridStep < WINDOW_SIZE_Y)
  {
    SDL_RenderDrawLine(renderer, 0, gridStep, WINDOW_SIZE_Y, gridStep);
    gridStep += WINDOW_SIZE_Y / 20;
  }

  /* Draw X and Y central axis. */
  SDL_SetRenderDrawColor(renderer, 220, 220, 220, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(renderer, WINDOW_SIZE_Y/2, 0, WINDOW_SIZE_Y/2, WINDOW_SIZE_X);
  SDL_RenderDrawLine(renderer, 0, WINDOW_SIZE_X/2, WINDOW_SIZE_Y, WINDOW_SIZE_X/2);
//  SDL_RenderPresent(renderer);
}

void drawSonarAxis(ArRobot *robot, SDL_Renderer* renderer)
{
  if(renderer == NULL || robot == NULL)
    return;

  /* Compute robot data just once. */
  int robotX = robot->getX();
  int robotY = robot->getY();
  double cosTheta = cos(ArMath::degToRad(robot->getTh()));
  double sinTheta = sin(ArMath::degToRad(robot->getTh()));
  double cosPlus15 = cos(ArMath::degToRad(robot->getTh()+15));
  double sinPlus15 = sin(ArMath::degToRad(robot->getTh()+15));
  double cosMinus15 = cos(ArMath::degToRad(robot->getTh()-15));
  double sinMinus15 = sin(ArMath::degToRad(robot->getTh()-15));

  /* Go to all sonars around the robot. */
  for(int i = 0; i < 8; i++)
  {
  //  printf("(%.2f,%.2f,%.2f) --> ", robot->getX(), robot->getX(), robot->getTh());
    /* Get information on sonars (not just range reading!). */
    ArSensorReading *sensorReading = robot->getSonarReading(i);

    /* getSensorX() and getSensorY() return X and Y coordinates of the sensor
     * origin. Compute the coordinates of this origin according to the robot
     * heading. */
    double localOriginX = sensorReading->getSensorX()*cosTheta - sensorReading->getSensorY()*sinTheta;
    double localOriginY = sensorReading->getSensorX()*sinTheta + sensorReading->getSensorY()*cosTheta;

    /* Compute the coordinates of the sensor origin with respect to the scaled
     * map. */
    int globalOriginX = (robotX + localOriginX + X_AXIS_LIMIT) / WINDOW_SCALE_DIVIDER;
    int globalOriginY = (Y_AXIS_LIMIT - (robotY + localOriginY)) / WINDOW_SCALE_DIVIDER;

    /* getLocalX() and getLocalY() return X and Y coordinates of the reading
     * point with respect of the sensor origin. Compute the coordinates of the
     * sensor reading according to the robot heading. */
    double localEndX = sensorReading->getLocalX()*cosTheta - sensorReading->getLocalY()*sinTheta;
    double localEndY = sensorReading->getLocalX()*sinTheta + sensorReading->getLocalY()*cosTheta;

    /* Compute the coordinates of the sensor reading with respect to the scaled
     * map. */
    int globalEndX = (robotX + localEndX + X_AXIS_LIMIT) / WINDOW_SCALE_DIVIDER;
    int globalEndY = (Y_AXIS_LIMIT - (robotY + localEndY)) / WINDOW_SCALE_DIVIDER;

    /* Draw a line for the acoustic axis of the sensor. */
    int color = 255 * (5000 - robot->getSonarRange(i)) / 5000;
    /* The color turns yellow to red according to the sensor range. */
    SDL_SetRenderDrawColor(renderer, 255, 255 - color, 0, 127);
    SDL_RenderDrawLine(renderer, globalOriginX, globalOriginY, globalEndX, globalEndY);
    /* Draw a little rectangle centralized in the sensor reading. */
    SDL_Rect rect = {globalEndX - 1, globalEndY - 1, 2, 2};
    SDL_RenderFillRect(renderer, &rect);

    /* Compute the sensor cone. */
    double localConePlusX = sensorReading->getLocalX()*cosPlus15 - sensorReading->getLocalY()*sinPlus15;
    double localConePlusY = sensorReading->getLocalX()*sinPlus15 + sensorReading->getLocalY()*cosPlus15;
    int globalConePlusX = (robotX + localConePlusX + X_AXIS_LIMIT) / WINDOW_SCALE_DIVIDER;
    int globalConePlusY = (Y_AXIS_LIMIT - (robotY + localConePlusY)) / WINDOW_SCALE_DIVIDER;
    //SDL_RenderDrawLine(renderer, globalOriginX, globalOriginY, globalConePlusX, globalConePlusY);

    double localConeMinusX = sensorReading->getLocalX()*cosMinus15 - sensorReading->getLocalY()*sinMinus15;
    double localConeMinusY = sensorReading->getLocalX()*sinMinus15 + sensorReading->getLocalY()*cosMinus15;
    int globalConeMinusX = (robotX + localConeMinusX + X_AXIS_LIMIT) / WINDOW_SCALE_DIVIDER;
    int globalConeMinusY = (Y_AXIS_LIMIT - (robotY + localConeMinusY)) / WINDOW_SCALE_DIVIDER;
    //SDL_RenderDrawLine(renderer, globalOriginX, globalOriginY, globalConeMinusX, globalConeMinusY);

    /* Computes a rectangle around the sensor field of view. This is the area
     * that will be subjected to inspection. */
    int x1 = min4(globalOriginX, globalConePlusX, globalConeMinusX, globalEndX);
    int y1 = min4(globalOriginY, globalConePlusY, globalConeMinusY, globalEndY);
    int w = max4(globalOriginX, globalConePlusX, globalConeMinusX, globalEndX);
    int h = max4(globalOriginY, globalConePlusY, globalConeMinusY, globalEndY);
    x1 *= 0.95; y1 *= 0.95; w = w * 1.05 - x1; h = h * 1.05 - y1;
    SDL_Rect sensorRect = {x1, y1, w, h};
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &sensorRect);
  }
}

SDLTask::~SDLTask()
{
  // it is important to remove our task if this object is destroyed, otherwise
  // ArRobot will hold an invalid ArFunctor pointer in its tasks list, resulting
  // in a crash when it tries to invoke it.
  robot->remSensorInterpTask(&SDLTaskFunc);
  if(renderer) SDL_DestroyRenderer(renderer);
  if(window) SDL_DestroyWindow(window);
  SDL_Quit();
}

// This is the method invoked as the user task
void SDLTask::sdlTask()
{
  //if(running && lastLogTime.mSecSince() >= 200)  // 0.2 second has passed since start or last log
  {
    SDL_Event event;
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT)
    {
      running = false;
      return;
    }

    /* White background, clear the screen and draw the grid. */
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    drawGrid(renderer);

    /* Draw the robot. Change this to a better representation. */
    int x = (robot->getX() + X_AXIS_LIMIT) / WINDOW_SCALE_DIVIDER;
    int y = (Y_AXIS_LIMIT - robot->getY()) / WINDOW_SCALE_DIVIDER;
    SDL_Rect rect = {x-3, y-3, 6, 6};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);
    //printf("(%.2f,%.2f) --> (%d,%d)\n", robot->getX(), robot->getY(),
    //  x, y); //robot->getTh());

    /*for(int i=0;i<16;i++)
      printf("%d ", robot->getSonarRange(i));
    printf("\n");*/


/*    ArSensorReading *sensorReading = robot->getSonarReading(3);
    printf("Sonar 3:\n");
    printf("Local X = %f, Local Y = %f, Range = %d\n",
      sensorReading->getLocalX(), sensorReading->getLocalY(),
      sensorReading->getRange());
    printf("Sensor DX = %f, Sensor DY = %f\n",
      sensorReading->getSensorDX(), sensorReading->getSensorDY());
    printf("Sensor position = (%f, %f, %f)\n",
      sensorReading->getSensorX(), sensorReading->getSensorY(),
      sensorReading->getSensorTh());
*/

    drawSonarAxis(robot, renderer);

//  printf("\n");

    // Get rectangle center
/*    int centerX = x - 12;
    int centerY = y - 12;
    SDL_Rect rect = {centerX, centerY, 24, 24};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &rect);
*/
    /*int gridX = 250 + (x / 250) * 25;
    int gridY = 250 + (y / 250) * 25;
    printf("gridX = %d, gridY = %d\n", gridX, gridY);
    SDL_Rect rect = {gridX, gridY, 25, 25};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &rect); */
    SDL_RenderPresent(renderer);

    lastLogTime.setToNow(); // reset timer
  }
}
