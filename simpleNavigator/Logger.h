/*
 * Logger class
 * Taken from http://robots.mobilerobots.com/wiki/ARIA_Example:_Use_a_robot_task_to_log_or_print_robot_pose_or_other_information_periodically
 *
 * Felipe Kuhne
 * fkuhne at gmail dot com
 * May, 2017
 */

#include <Aria.h>

/** This class creates a robot sensor task that prints the robot pose
   every second. It adds the new task to the given ArRobot object
   (on class instantiation), and removes it when destroyed.
*/
class Logger {
private:
  ArRobot *robot;
  ArTime lastLogTime;
  ArFunctorC<Logger> robotTaskFunc;
  void logTask();
public:
  Logger(ArRobot *r);
  ~Logger();
};
