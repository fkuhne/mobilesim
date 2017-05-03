/*
 * Copied from Aria/examples/demo.cpp and from
 * http://www.eecs.yorku.ca/course_archive/2010-11/W/4421/doc/pioneer/aria/teleopActionsExample_8cpp-example.html
 *
 * Need to add grid drawing functionality.
 *
 * Felipe Kuhne
 * fkuhne at gmail dot com
 * May, 2017
 */

/*
 * To connect with the simulator, pass just "./drawGrid"
 * To connect with the real robot, LATER.
 */

#include <Aria.h>
#include "Logger.h"

int main(int argc, char** argv)
{
  Aria::init();

  // This object parses program options from the command line
  ArArgumentParser parser(&argc, argv);
  // Load some default values for command line arguments from /etc/Aria.args
  // (Linux) or the ARIAARGS environment variable.
  parser.loadDefaultArguments();

  // Central object that is an interface to the robot and its integrated
  // devices, and which manages control of the robot by the rest of the program.
  ArRobot robot;
  // Object that connects to the robot or simulator using program options
  ArRobotConnector robotConnector(&parser, &robot);

  // Connect to the robot, get some initial data from it such as type and name,
  // and then load parameter files for this robot.
  if (!robotConnector.connectRobot())
  {
    ArLog::log(ArLog::Terse, "Error, could not connect to robot.");
    Aria::logOptions();
    Aria::exit(1);
  }

  if(!robot.isConnected())
  {
    ArLog::log(ArLog::Terse, "Internal error: robot connector succeeded but ArRobot::isConnected() is false!");
  }

  // Parse the command line options. Fail and print the help message if the parsing fails
  // or if the help was requested with the -help option
  if (!Aria::parseArgs() || !parser.checkHelpAndWarnUnparsed())
  {
    Aria::logOptions();
    Aria::exit(1);
    return 1;
  }

  // Used to access and process sonar range data
  ArSonarDevice sonarDev;
  // Attach sonarDev to the robot so it gets data from it.
  robot.addRangeDevice(&sonarDev);

  // set the robots maximum velocity (sonar don't work at all well if you're
  // going faster)
  robot.setAbsoluteMaxTransVel(400);

  // enable the motor
  robot.enableMotors();

  // limiter for close obstacles
  ArActionLimiterForwards limiter("speed limiter near", 300, 600, 250);
  // limiter for far away obstacles
  ArActionLimiterForwards limiterFar("speed limiter far", 300, 1100, 400);
  // limiter that checks IR sensors (like Peoplebot has)
  ArActionLimiterTableSensor tableLimiter;
  // limiter so we don't bump things backwards
  ArActionLimiterBackwards backwardsLimiter;
  // the keydrive action
  ArActionKeydrive keydriveAct;

  // Add the actions, with the limiters as highest priority, then the teleop.
  // actions.  This will keep the teleop. actions from being able to drive too
  // fast and hit something
  robot.addAction(&tableLimiter, 100);
  robot.addAction(&limiter, 95);
  robot.addAction(&limiterFar, 90);
  robot.addAction(&backwardsLimiter, 85);
  robot.addAction(&keydriveAct, 45);

  // This adds an action to print out the robot pose
  Logger logger(&robot);

  // run the robot, true means that the run will exit if connection lost
  robot.run(true);

  // Start the robot task loop running in a new background thread. The 'true'
  // argument means if it loses connection the task loop stops and the thread
  // exits.
  //robot.runAsync(true);

  Aria::shutdown();

  Aria::exit(0);
  return 0;
}
