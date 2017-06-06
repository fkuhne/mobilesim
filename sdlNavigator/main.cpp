/*
 * Copied from Aria/examples/demo.cpp and from
 * http://www.eecs.yorku.ca/course_archive/2010-11/W/4421/doc/pioneer/aria/teleopActionsExample_8cpp-example.html
 *
 * Felipe Kuhne
 * fkuhne at gmail dot com
 * May, 2017
 */

/*
 * To connect with the simulator, pass just "./sdlNavigator"
 * To connect with the real robot, "./sdlNavigator -rh 192.168.1.11"
 */

#include "AriaRobot.h"

int main(int argc, char** argv)
{
  AriaRobot r(argc, argv);

  return 0;
}
