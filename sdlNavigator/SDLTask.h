/*
 * Logger class
 * Taken from http://robots.mobilerobots.com/wiki/ARIA_Example:_Use_a_robot_task_to_log_or_print_robot_pose_or_other_information_periodically
 *   and http://www.eecs.yorku.ca/course_archive/2009-10/W/4421/doc/pioneer/aria/robotSyncTaskExample_8cpp-example.html#a500
 *
 * Felipe Kuhne
 * fkuhne at gmail dot com
 * May, 2017
 */

#include <Aria.h>
#include <SDL.h>

class SDLTask
{
private:
  bool running = false;

  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  SDL_Surface* surface = NULL;
  void sdlTask();

  ArRobot *robot = NULL;
  ArTime lastLogTime;
  ArFunctorC<SDLTask> SDLTaskFunc;

public:
  SDLTask(ArRobot *r);
  int init();
  ~SDLTask();
};
