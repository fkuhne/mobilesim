/*
 * Copied from Aria/examples/demo.cpp and from
 * http://www.eecs.yorku.ca/course_archive/2010-11/W/4421/doc/pioneer/aria/teleopActionsExample_8cpp-example.html
 *
 * Felipe Kuhne
 * fkuhne at gmail dot com
 * May, 2017
 */

/*
 * To connect with the simulator, pass just "./drawGrid"
 * To connect with the real robot, LATER.
 */

#include "AriaRobot.h"

int main(int argc, char** argv)
{
  AriaRobot r(argc, argv);

/*  ArSensorReading *sensorReading = robot.getSonarReading(0);
  printf("Sonar 0:\n");
  printf("Local X = %f, Local Y = %f, Range = %d\n",
    sensorReading->getLocalX(), sensorReading->getLocalY(),
    sensorReading->getRange());
  printf("Sensor DX = %f, Sensor DY = %f\n",
    sensorReading->getSensorDX(), sensorReading->getSensorDY());
  printf("Sensor position = (%f, %f, %f)\n",
    sensorReading->getSensorX(), sensorReading->getSensorY(),
    sensorReading->getSensorTh());

  for(int i = 0; i < 16; i++)
  {
    ArSensorReading *sensorReading = robot.getSonarReading(i);
    printf("Sensor %d position = (%f, %f, %f)\n", i,
      sensorReading->getSensorX(), sensorReading->getSensorY(),
      sensorReading->getSensorTh());
  } */

  return 0;
}
