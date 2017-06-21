/*
 * Class to do Aria stuff
 *
 * Felipe Kuhne
 * fkuhne at gmail dot com
 * May, 2017
 */

#ifndef __ARIA_ROBOT_H__
#define __ARIA_ROBOT_H__

#include <Aria.h>


class AriaRobot
{
public:
  ArRobot robot;

  AriaRobot(int argc, char** argv);
  bool isConnected();
  ~AriaRobot();
};

#endif /* __ARIA_ROBOT_H__ */
