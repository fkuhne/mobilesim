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
#include <thread>

class SDLTask
{
private:

  std::thread sdlThread;
  bool running;
  bool method; // false = bayes, true = himm

  /* This is the main window. */
  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;

  /* Separate window to plot the potential field. */
  SDL_Window* potentialWindow = NULL;
  SDL_Renderer* potentialRenderer = NULL;

  void sdlTask();

  ArRobot *robot = NULL;
  ArTime sdlTimer;

  double heading;

public:
  SDLTask(ArRobot *r, bool method);
  void computePotentialField(ArRobot *robot, SDL_Renderer* renderer);
  int init();
  void setHeading(double _heading);
  double getHeading();
  ~SDLTask();
};
