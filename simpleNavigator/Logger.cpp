/*
 * Logger class
 * Taken from http://robots.mobilerobots.com/wiki/ARIA_Example:_Use_a_robot_task_to_log_or_print_robot_pose_or_other_information_periodically
 *
 * Felipe Kuhne
 * fkuhne at gmail dot com
 * May, 2017
 */

#include "Logger.h"

Logger::Logger(ArRobot *r) :
  robot(r),                              // store a pointer to the ArRobot object
  robotTaskFunc(this, &Logger::logTask)  // initialize the functor to be given added as an ArRobot
                                         // user task with this instance and which method to  call
{
  // add our task functor to the robot object as a user task,
  // to be invoked in every robot task cycle (approx. every 100ms):
  robot->addSensorInterpTask("Logger", 50, &robotTaskFunc);
}

Logger::~Logger()
{
  // it is important to remove our task if this object is destroyed, otherwise
  // ArRobot will hold an invalid ArFunctor pointer in its tasks list, resulting
  // in a crash when it tries to invoke it.
  robot->remSensorInterpTask(&robotTaskFunc);
}

// This is the method invoked as the user task
void Logger::logTask()
{
  if(lastLogTime.mSecSince() >= 1000)  // 1 second has passed since start or last log
  {
     printf("%.2f %.2f %.2f\n", robot->getX(), robot->getY(), robot->getTh());
     lastLogTime.setToNow(); // reset timer
  }
}
