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

  bool method = false; // defaut: himm
  if(!strncmp(argv[argc-1], "bayes", strlen("bayes")))
    method = true;
  else if(!strncmp(argv[argc-1], "himm", strlen("himm")))
    method = false;

  ArArgumentParser parser(&argc, argv);
  //parser.addDefaultArgument("-rh 192.168.1.11");
  //parser.loadDefaultArguments();

  ArRobotConnector robotConnector(&parser, &robot);
  if (!robotConnector.connectRobot())
  {
    ArLog::log(ArLog::Terse, "Error, could not connect to robot.");
    Aria::exit(1);
  }

  // limiter for close obstacles
  ArActionLimiterForwards limiter("speed limiter near", 50, 600, 250);
  robot.addAction(&limiter, 95);
  // limiter for far away obstacles
  //ArActionLimiterForwards limiterFar("speed limiter far", 50, 1100, 400);
  //robot.addAction(&limiterFar, 90);

  // limiter that checks IR sensors (like Peoplebot has)
  //ArActionLimiterTableSensor tableLimiter;
  //robot.addAction(&tableLimiter, 100);

  // limiter so we don't bump things backwards
  //ArActionLimiterBackwards backwardsLimiter;
  //robot.addAction(&backwardsLimiter, 85);

  // the keydrive action
  //ArActionKeydrive keydriveAct;
  //robot.addAction(&keydriveAct, 45);

  ArSonarDevice sonarDev;
  robot.addRangeDevice(&sonarDev);

  // set the robots maximum velocity (sonar don't work at all well if you're
  // going faster)
  //robot.setAbsoluteMaxTransVel(100); // mm/sec
  robot.setHeading(0);
  robot.setVel(0);
  robot.enableMotors();

  /* The robot starts moving right away, without keyboard commands. */
  //robot.setVel(50);

  /* This creates a posix thread which will compute everything on the map (Bayes,
   * HIMM and Potential fields). */
  SDLTask sdlTask(&robot, method);
  sdlTask.init();

  // run the robot, true means that the run will exit if connection lost
  //robot.run(true);

  // Start the robot task loop running in a new background thread. The 'true'
  // argument means if it loses connection the task loop stops and the thread
  // exits.
  robot.runAsync(true);

  while(1)
  {
    //robot.lock();
    double diffTh = sdlTask.getHeading() - robot.getTh();

printf("heading = %.2f, robot = %.2f", sdlTask.getHeading(), robot.getTh());

    diffTh = fmod((diffTh+180+360), 360) - 180;

printf(", diffTh = %.2f\n", diffTh);

    if(diffTh <= 90)
      robot.setVel2(50+50*ArMath::sin(diffTh), 50-50*ArMath::sin(diffTh));
    else
      robot.setVel2(10+20*ArMath::sin(diffTh), 10-20*ArMath::sin(diffTh));

    //if(diffTh <= 90)
    //  robot.setVel(70);
    //else
    //  robot.setVel(20);

    //robot.setVel(10);
    //robot.setHeading(sdlTask.getHeading());
    //while(true)
    //{
    //  if(robot.isHeadingDone()) break;
    //  ArUtil::sleep(100);
    //}
    //robot.setVel(50);
    //robot.unlock();

    ArUtil::sleep(500);
  }
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
