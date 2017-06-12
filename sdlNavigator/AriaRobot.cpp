/*
 * Class to do Aria stuff
 *
 * Felipe Kuhne
 * fkuhne at gmail dot com
 * May, 2017
 */

#include "AriaRobot.h"
#include "SDLTask.h"

AriaRobot::AriaRobot(int argc, char** argv)
{
  Aria::init();

  bool method = false; // defaut: bayes
  if(!strncmp(argv[argc-1], "bayes", strlen("bayes")))
    method = false;
  else if(!strncmp(argv[argc-1], "himm", strlen("himm")))
    method = true;

  ArArgumentParser parser(&argc, argv);
  //parser.addDefaultArgument("-rh 192.168.1.11");
  //parser.loadDefaultArguments();

  ArRobotConnector robotConnector(&parser, &robot);
  if (!robotConnector.connectRobot())
  {
    ArLog::log(ArLog::Terse, "Error, could not connect to robot.");
    Aria::exit(1);
  }

  ArSonarDevice sonarDev;
  robot.addRangeDevice(&sonarDev);

  // set the robots maximum velocity (sonar don't work at all well if you're
  // going faster)
  robot.setAbsoluteMaxTransVel(200); // mm/sec
  robot.enableMotors();

  // limiter for close obstacles
  ArActionLimiterForwards limiter("speed limiter near", 50, 600, 250);
  robot.addAction(&limiter, 95);
  // limiter for far away obstacles
  ArActionLimiterForwards limiterFar("speed limiter far", 50, 1100, 400);
  robot.addAction(&limiterFar, 90);

  // limiter that checks IR sensors (like Peoplebot has)
  ArActionLimiterTableSensor tableLimiter;
  robot.addAction(&tableLimiter, 100);

  // limiter so we don't bump things backwards
  ArActionLimiterBackwards backwardsLimiter;
  robot.addAction(&backwardsLimiter, 85);

  // the keydrive action
  ArActionKeydrive keydriveAct;
  robot.addAction(&keydriveAct, 45);

  SDLTask sdlTask(&robot, method);
  sdlTask.init();

  // run the robot, true means that the run will exit if connection lost
  robot.run(true);

  // Start the robot task loop running in a new background thread. The 'true'
  // argument means if it loses connection the task loop stops and the thread
  // exits.
  //robot.runAsync(true);
  //while(1){}
}

AriaRobot::~AriaRobot()
{
  robot.stopRunning(true);
  Aria::shutdown();
}

bool AriaRobot::isConnected()
{
  return robot.isConnected();
}
