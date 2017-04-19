/*
ActivMedia Robotics Interface for Applications (ARIA)
Copyright (C) 2004,2005 ActivMedia Robotics, LLC


     This program is free software; you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation; either version 2 of the License, or
     (at your option) any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program; if not, write to the Free Software
     Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

If you wish to redistribute ARIA under different terms, contact 
ActivMedia Robotics for information about a commercial version of ARIA at 
robots@activmedia.com or 
ActivMedia Robotics, 19 Columbia Drive, Amherst, NH 03031; 800-639-9481

*/

#ifndef ARIA_H
#define ARIA_H

#include "ariaOSDef.h"
#include "ariaTypedefs.h"
#include "ArSerialConnection.h"
#include "ArTcpConnection.h"
#include "ArSimpleConnector.h"
#include "ArLogFileConnection.h"
#include "ArLog.h"
#include "ArRobotPacket.h"
#include "ArRobotPacketSender.h"
#include "ArRobotPacketReceiver.h"
#include "ArRobotConfigPacketReader.h"
#include "ArRobotTypes.h"
#include "ariaUtil.h"
#include "ArArgumentBuilder.h"
#include "ArArgumentParser.h"
#include "ArFileParser.h"
#include "ArConfig.h"
#include "ArConfigArg.h"
#include "ArConfigGroup.h"
#include "ArRobot.h"
#include "ArCommands.h"
#include "ArJoyHandler.h"
#include "ArSyncTask.h"
#include "ArTaskState.h"
#include "ariaInternal.h"
#include "ArSonarDevice.h"
#include "ArPriorityResolver.h"
#include "ArAction.h"
#include "ArActionGroup.h"
#include "ArActionGroups.h"
#include "ArActionDeceleratingLimiter.h"
#include "ArActionLimiterForwards.h"
#include "ArActionLimiterBackwards.h"
#include "ArActionLimiterTableSensor.h"
#include "ArActionBumpers.h"
#include "ArActionIRs.h"
#include "ArActionStallRecover.h"
#include "ArActionAvoidFront.h"
#include "ArActionAvoidSide.h"
#include "ArActionConstantVelocity.h"
#include "ArActionInput.h"
#include "ArActionRobotJoydrive.h"
#include "ArActionJoydrive.h"
#include "ArActionKeydrive.h"
#include "ArActionTriangleDriveTo.h"
#include "ArActionTurn.h"
#include "ArActionRatioInput.h"
#include "ArActionStop.h"
#include "ArActionGoto.h"
#include "ArModule.h"
#include "ArModuleLoader.h"
#include "ArRecurrentTask.h"
#include "ArInterpolation.h"
#include "ArGripper.h"
#include "ArSonyPTZ.h"
#include "ArAMPTU.h"
#include "ArP2Arm.h"
#include "ArACTS.h"
#include "ArSick.h"
#include "ArSickLogger.h"
#include "ArIrrfDevice.h"
#include "ArKeyHandler.h"
#include "ArDPPTU.h"
#include "ArVCC4.h"
#include "ArMode.h"
#include "ArModes.h"
#include "ArNetServer.h"
#include "ArSignalHandler.h"
#include "ArAnalogGyro.h"
#include "ArMap.h"
#include "ArLineFinder.h"
#include "ArBumpers.h"
#include "ArIRs.h"
#include "ArDrawingData.h"
#include "ArForbiddenRangeDevice.h"
#include "ArTCM2.h"
#if !defined(WIN32) && !defined(SWIG)
#include "ArVersalogicIO.h"
#endif
#include "ArActionGotoStraight.h"
#include "ArDataLogger.h"
#include "ArRobotJoyHandler.h"
#include "ArRatioInputKeydrive.h"
#include "ArRatioInputJoydrive.h"
#include "ArRatioInputRobotJoydrive.h"
#include "ArActionMovementParameters.h"
#include "ArSoundPlayer.h"
#include "ArSoundsQueue.h"

/**
  \mainpage ARIA overview

ActivMedia Robotics Interface for Application (ARIA)
Copyright 2002,2003,2004,2005 ActivMedia Robotics, LLC. All rights reserved.


\section toc Contents
<ul>
 <li>\ref intro
   <ul>
     <li>\ref javapython</li>
   </ul>
 </li>
 <li>\ref licensing</li>
 <li>\ref AriaPackage
    <ul>
      <li>\ref arpack</li>
      <li>\ref arpackother</li>
    </ul>
 </li>
 <li>\ref codingConventions</li>
 <li>\ref arCliServ</li>
 <li>\ref commClasses
  <ul>
    <li>\ref connectRobot</li>
  </ul>
 </li>
 <li>\ref robot
  <ul>
    <li>\ref commands</li>
    <li>\ref packetHandlers</li>
    <li>\ref CommandPackets</li>
    <li>\ref syncRobot</li>
    <li>\ref stateReflection</li>
  </ul>
 </li>
 <li>\ref rangeDevices</li>
 <li>\ref ClientCommands
  <ul>
    <li>\ref DirectCommands</li>
    <li>\ref directMotionCommands</li>
    <li>\ref actions</li>
    <li>\ref actionDesired</li>
    <li>\ref resolvers</li>
    <li>\ref specialActions</li>
    <li>\ref actionInteractions</li>
  </ul>
 </li>
 <li>\ref callback</li>
 <li>\ref functors</li>
 <li>\ref userInput</li>
 <li>\ref threading
  <ul>
    <li>\ref syncObject</li>
    <li>\ref asynctasks</li>
  </ul>
 </li>
 <li>\ref aria</li>
</ul>

\subsection tocAdv Advanced Usage:
<ul>
 <li>\ref pieceMealUse</li>
 <li>\ref params
  <ul>
    <li>\ref paramMechanisms</li>
  </ul>
 </li>
 <li>\ref hardConnectRobot
  <ul>
    <li>\ref openDevice</li>
    <li>\ref devConnect</li>
    <li>\ref connrw</li>
  </ul>
 </li>
</ul>

\subsection tocToolbox Additional tools in the ARIA toolbox:
<ul>
 <li>\ref utility</li>
 <li>\ref arconfig</li>
 <li>\ref sockets</li>
 <li>\ref ArNetworking</li>
 <li>\ref sound</li>
</ul>

\subsection tocDevHelp Helpful information about development with ARIA:
<ul>
 <li>\ref emacs</li>
 <li>\ref noneverydayC
  <ul>
    <li>\ref stl</li>
    <li>\ref defaultArgs</li>
    <li>\ref constructorChaining</li>
    <li>\ref charsAndStrings</li>
    <li>\ref arexport</li>
  </ul>
 </li>
</ul>
  

  \section intro Introduction

Welcome to ARIA, an object-oriented, robot control
applications-programming interface for ActivMedia Robotics' line of
intelligent mobile robots.

Written in the C++ language, ARIA is client-side software for easy,
high-performance access to and management of the robot server, as well
as to the many accessory robot sensors and effectors. Its versatility
and flexibility makes ARIA an excellent foundation for higher-level
robotics applications.
   
ARIA can be run multi- or single-threaded, using its own wrapper
around Linux pthreads and WIN32 threads.  Use ARIA in many different
ways, from simple command-control of the robot server for direct-drive
navigation, to development of higher-level intelligent actions (aka
behaviors). For a description of how to integrate parts of ARIA with
your other code, see \ref pieceMealUse.

This document contains an overview of ARIA. If you are browsing it in
HTML, click a class or function link to view its detail pages. New
users should view this document along with the ARIA examples.

You can download new versions of ARIA from http://robots.activmedia.com/ARIA

 \subsection whouses	How Should I Use ARIA?

Who is ARIA for? How does ARIA fit in with other ActivMedia software? 

ARIA is a programming library (SDK) for C++ object-oriented programmers 
who want to have close control of their robot.  ARIA also is for those 
who have prepared robot-control software and want to quickly and easily 
deploy it on one or more ActivMedia Robotics mobile robot platforms. 
ARIA also provides various tools useful for robot programming.

For creating applications with built-in advanced navigation routines
consider using our ARNL or SONARNL libraries in addition to ARIA.

For a GUI, you can use ArNetworking to create a server program, and connect to it with
MobileEyes.  See the ArNetworking library documentation for more information.

Browse ActivMedia Robotics' support webpages http://www.activrobots.com and
http://robots.activmedia.com for these and many other mobile robotics 
resources, including the MobileSim simulator which can be used used for
programming and debugging before driving an actual robot.

Read on for information about the key pieces of ARIA and how to get started.
See the README.txt file for a brief practical overview of ARIA software development
on Linux and Windows.  Many example programs are available as well.

 \subsection javapython Java and Python

ARIA and ArNetworking now work in Java and Python!  Each library has a 
Java wrapper and a Python
wrapper included with the base release.  This means that you can write
ARIA programs in Java or Python almost as if ARIA itself was written in these
languages.  This wrapper is automatically generated by SWIG
(http://www.swig.org) at each release, meaning that unlike three
different implementations its consistent between languages, all three
languages get new features and are maintained, and the many examples
written for C++ ARIA are valid in the other languages.  

There are a couple of more complicated/advanced features that don't work yet in
these languages (you can use the classes in C++ that use the features,
but you can't reimplement these features in the other languages).  The
main unimplemented feature in the wrappers is virtual function overloading
which means that you will not be able to make your own ArActions in
Java or Python, but you can always add them to the C++ library and use
them in Java or Python.  
You also will not be able to make your own ArFunctors for callbacks, but again
you can make objects in the C++ library and use
them in Java or Python.  For this deficiency language specific
workarounds could likely be written by users, which I could
incorporate or if there are large numbers of people using these
wrappers we may develop these on our own.  

Look in the javaExamples/README.txt file for directions on how to use
the Java wrapper and in the pythonExamples/README.txt for directions
on how to use the Python wrapper, and likewise see ArNetworking/javaExamples
and ArNetworking/pythonExamples.

 \section licensing License and Sharing

ARIA is released under the GNU Public License, which means that if you
distribute any work which uses ARIA, you must distribute the entire
source code to that work.  Read the included LICENSE text for
details. We open-sourced ARIA under GPL not only for your convenience,
but also so that you will share your enhancements to the software.  If
you wish your enhancements to make it into the ARIA baseline, you will
need to assign the copyright on those changes to ActivMedia, contact
aria-support@activmedia.com with these changes or with questions about
this.

Accordingly, please do share your work, and please sign up for the
exclusive ARIA-users@activmedia.com newslist so that you can benefit
from others' work, too.

ARIA may be licensed for proprietary, closed-source applications.
Contact sales@activmedia.com for details.

 \section AriaPackage The ARIA Package

 \subsection arpack ARIA/

<pre>
  LICENSE.txt     GPL license; agree to this to use ARIA	      	   
  INSTALL.txt     Step-wise instructions for installing ARIA
  README.txt      Getting started with ARIA.  Also see the README files in advanced/, examples/, and tests/
  Changes.txt     Summary of changes featured in each version of ARIA
  docs/           Extensive library documentation in HTML and PDF format (this manual).
  examples/       ARIA examples -- a good place to start; see examples README
  bin/            Win32 binaries and DLLs
  include/        Header files
  lib/            Win32 DLL export library (.lib) files and Linux shared library (.so) files
  params/         Robot definition (parameter) files (p3dx.p, for example)
  src/            ARIA source (*.cpp) files
</pre>

 \subsection arpackother Other ARIA Files of Note

<pre>
  Aria.sln        MS Visual C++ workspace for building ARIA libraries and examples
  Aria.vcproj     MSVC++ project file used in Aria.sln for the ARIA library.
  Makefile        Linux makefile for building ARIA and examples
  Makefile.dep    Linux dependency
  ArNetworking/   Networking infrastructure library, included with ARIA, but a seperate library
  run             Linux only; builds and executes your ARIA applcation
  tests/          Test files, somewhat esoteric but useful during ARIA development
  utils/          Utility commands, not generally needed
  advanced/       Advanced demos, not for the faint of heart (or ARIA novice)
  pythonExamples/ Information and examples using ARIA via Python
  javaExamples/   Information and examples using ARIA via Java
  python/         Contains ARIA Python module and other files
  java/           Contains ARIA Java package and other files
</pre>

 \section codingConventions Documentation and Coding Convention

For clarity while you read this technical document and ARIA's source code,
we  follow the following coding conventions:

<ol>
  <li>Class names begin with a capital letter.</li>
  <li>Enums either begin with a capital letter or are all in caps.</li>
  <li>Avoid #defines whenever possible.</li>
  <li>Member variables in classes are prefixed with 'my'.</li> 
  <li>Static variables in classes are prefixed with 'our'.</li>
  <li>Member function names start with a lower case.</li>
  <li>Capitalize each word except the first one in a variable or method name; <code>likeThisForExample</code></li>
  <li>Write all code so that it can be used threaded</li>
</ol>

@sa @ref emacs

 \section arCliServ ARIA-Robot Client-Server Relationship

For those of you who are familiar with SRI International's Saphira
software and ActivMedia Robotics' mobile robots and their related
technologies, the underlying client-server control architecture for
the mobile platform, sensors, and accessories hasn't changed much in
ARIA. It's just gotten a lot better and more accessible.

The mobile robot servers, embodied in the Pioneer and AmigoBot Operating
System software (ARCOS, AROS, P2OS, AmigOS, etc.) and found embedded 
on the robot's microcontroller,
manage the low-level tasks of robot control and operation, including
motion, heading and odometry, as well as acquiring sensor information
(sonar and compass, for example) and driving accessory components like
the PTZ camera, TCM2 compass/inclinometer, and the Pioneer 5-DOF
Arm. The robot servers do not, however, perform any high-level robotic tasks.

Rather, it is the job of an intelligent client running on a connected
PC to perform the full gamut of robotics control strategies and tasks,
such as obstacle detection and avoidance, sensor fusion, localization,
features recognition, mapping, intelligent navigation, PTZ camera
control, Arm motion, and much more. ARIA's role is on that intelligent
client side.

Nearest the robot, ARIA's ArDeviceConnection class, at the behest of
your application code, establishes and maintains a communication
channel with the robot server, packaging commands to
(ArRobotPacketSender) and decoding responses (ArRobotPacketReceiver)
from the robot in safe and reliable packet formats (ArRobotPacket)
prescribed by the client-server protocols.

At its heart, ARIA's ArRobot class collects and organizes the robot's
operating states, and provides clear and convenient interface for
other ARIA components, as well as upper-level applications, to access
that robot state-reflection information for assessment, planning, and
ultimately, intelligent, purposeful control of the platform and its
accessories.

ArRobot's heart metaphor is particularly apt, too, since one of its
important jobs is to maintain the clockwork cycles and multi-threaded
rhythms of the robot-control system. Keyed to the robot's main
information-packet cycle (hence, no longer a fixed timing cycle),
ArRobot's syncronous tasks (ArSyncTask) include the robot
server-information packet handlers, sensor interpreters, action
handlers, state reflectors, user tasks, and more. And your software
may expand, replace, remove, and rearrange the list of synchronized
tasks through ArRobot's convenient sensor interp
(ArRobot::addSensorInterpTask) and user task (ArRobot::addUserTask)
related methods.

Through its Action class, ARIA provides a flexible, programmable
mechanism for behavior-level control of the robot server. An
associated Resolver class lets you organize and combine actions, for
coordinated motion control and intelligent guidance. With ARIA
actions, you easily develop integrated guarded-teleoperation and
color-blob tracking applications, for example.

ARIA also includes clear and convenient interface for applications to
access and control ActivMedia Robotics accessory sensors and devices,
including operation and state reflection for sonar and laser range
finders, pan-tilt units, arms, inertial navigation devices, and many
others.

The versatility and ease of access to ARIA code (sources included!)
makes it the ideal platform for robotics client applications
development.
  
 \section commClasses Robot Communication

One of the most important functions of ARIA, and one of the first and
necessary things that your application must do, is to establish and
manage client-server communications between your ARIA-based software
client and the robot's onboard servers and devices.

Do note that some accessories, such as the P2 Gripper, PTZ camera, P2
Arm, compass, and others, which attach to the robot's microcontroller
AUX serial port, are controlled through the client-side device
connection with the robot. Use different methods and procedures other
than ArDeviceConnection to communicate with and manage those devices
through ARIA.


 \subsection connectRobot Connecting with a Robot or the Simulator the easy way

You can use a convenience class called ArSimpleConnector to do
the connection for you, this is used in examples/demo,
examples/wander, examples/teleop to name a few.  ArSimpleConnector can also
parse command line arguments so that you don't need to recompile
to change where you want to connect.  Among other benefits, an
ArSimpleConnector will first try to connect to a simulator if one is running,
otherwise it'll connect to a serial port... so you don't have to
recompile your program for either mode, just don't have a simulator
running, or have one running.  If you want to have more control over how you connect with the robot or learn about how the pieces that make up a robot connection see \ref hardConnectRobot.


 \section robot ArRobot

As mentioned earlier, ArRobot is the heart of ARIA, acting as
client-server communications gateway, central database for collection
and distribution of state-reflection information, and systems
synchronization manager. ArRobot is also the gathering point for many
other robot tasks, including syncTasks, callbacks, range-finding
sensor and Actions classes. 

 \subsection commands Client Commands and Server Information Packets

Client-server communications between applications software and an
ActivMedia robot or the Simulator must adhere to strict packet-based
protocols. (In this context, the <i>client</i> is the software using
ARIA to operate a robot, and the <i>server</i> is the robot's microcontroller.)
The gory details can be found in several other ActivMedia
Robotics publications, including the Pioneer 3 Operations Manual and
the AmigoBot Technical Manual. Suffice it to say here that ArRobot
handles the low-level details of constructing and sending a
client-command packets to the robot as well as receiving and decoding
the various Server Information Packets from the robot.

 \subsection packetHandlers Packet Handlers

Server Information Packets (SIPs) come from the robot over the
robot-device connection and contain operating information about the
robot and its accessories. Currently, there are two types of SIPs: the
standard SIP and extended SIPs. The standard SIP gets sent by the
robot to a connected client automatically every 100 (default) or 50
milliseconds. It contains the robot's current position, heading,
translational and rotational speeds, freshly accumulated sonar
readings, and much more. These data ultimately are stored and
distributed by ArRobot's State Reflection (see \ref stateReflection
below).

Extended SIPs use the same communication-packet protocols as the
standard SIP, but with a different "type" specification and, of
course, containing different operating information, such as I/O port
readings or accessory device states like for the Gripper. And, whereas
the standard SIP gets sent automatically once per cycle, your client
controls extended packet communications by explicitly requesting that
the server send one or more extended SIPs.

ArRobot's standard SIP handler automatically runs as an ArRobot
synchronized task. Other SIP handlers are built in, but your client
must add each to the connected robot object, and hence to the SIP
handler sync task list, for it to take effect. See
examples/gripperDemo.cpp for a good example.

You also may add your own SIP handler with
ArRobot::addPacketHandler. ArListPos keeps track of the order by which
ArRobot calls each handler. When run, your packet handler must test
the SIP type (ArRobotPacket::getID) and return true after decoding
your own packet type or return false, leaving the packet untouched
for other handlers.

 \subsection CommandPackets Command Packets

From the client side going to the robot server, your ARIA program may
send commands directly, or more commonly, use ARIA's convenience
methods (Motion Commands and others) as well as engage Actions which
ARIA ultimately converts into Direct Commands to the robot. See \ref
ClientCommands for details. At the ARIA-robot interface, there is no
difference between Action- or other ARIA convenience-generated
commands and Direct Commands. However, upper-level processes aren't
necessarily aware of extraneous Direct or Motion Commands your client
may send to the robot. Motion Commands in particular need special
attention when mixing with Actions. See \ref ClientCommands below for
more details.

Once connected, your ARIA client may send commands to the robot server
nearly at will, only limited by communication speeds and other
temporal processes and delays. Similarly, the server responds nearly
immediately with a requested SIP, such as a GRIPPERpac or IOpac which
describe the P2 Gripper or Input/Output port states, respectively.

However, general information from the robot server about its odometry,
current sonar readings, and the many other details which comprise its
"standard" SIP automatically get sent to the ARIA client on a constant
100 or 50 millisecond cycle. This requires some synchronization with
ArRobot.

 \subsection syncRobot Robot-ARIA Synchronization

ArRobot runs a processing cycle: a series of synchronized tasks,
including SIP handling, sensor interpretation, action handling and
resolution, state reflection, and user tasks, in that order. By
default, ArRobot performs these sequenced tasks each time it receives
a standard SIP from the robot. Its cycle is thereby triggered by the
robot so that the tasks get the freshest information from the robot
upon which to act. 

To begin ArRobot's processing cycle, call ArRobot::run() to enter
the cycle synchronously, or ArRobot::runAsync() to run the cycle
in a new background thread. ArRobot::stopRunning() stops the 
processing cycle.

Of course, syncTasks runs without a connection with a robot, too. It
has its own default cycle time of 100 milliseconds which you may
examine and reset with ArRobot::getCycleTime and
ArRobot::setCycleTime, respectively. ArRobot waits up to twice that
cycle time for a standard SIP before cycling automatically.

ArRobot's synchronization task list is actually a tree, with five
major branches. If a particular task is not running, none of its
children will be called. Each task has an associated state value and a
pointer to an ArTaskState::State variable, which can be used to
control the process, by turning it on or off, or to see if it
succeeded or failed. If the pointer is NULL, then it is assumed that
the task does not care about its state, and a local variable will be
used in the task structure to keep track of that tasks state.

For each branch, tasks get executed in descending order of
priority. 

ARIA provides convenient methods to add your own sensor-interpretation
and user tasks. Create an ARIA function pointer (\ref functors) and
then add your sensor interpreter (ArRobot::addSensorInterpTask ) or
user task (ArRobot::addUserTask) to the list of syncTasks. These tasks
can be removed; use ArRobot::remSensorInterpTask or
ArRobot::remUserTask to remove sensor interpreter or user tasks,
respectively, by name or by functor.

The intrepid ARIA programmer can add or prune branches from the
ArRobot task list, as well as leaves on the branches.  Do these things
by getting the root of the tree with ArRobot::getSyncTaskRoot, and
then using the ArSyncTask class to do the desired manipulation.

You may disassociate ArRobot's syncTask from firing when the standard
SIP is received, through ArRobot::setCycleChained. But in doing so,
you may degrade robot performance, as the robot's cycle will simply be
run once every ArRobot::getCycleTime milliseconds.

 \subsection stateReflection State Reflection

State reflection in the ArRobot class is the way ARIA maintains and
distributes a snapshot of the robot's operating conditions and values,
as extracted from the latest standard SIP. ArRobot methods for
examining these values include ArRobot::getPose, ArRobot::getX,
ArRobot::getY, ArRobot::getTh, ArRobot::getVel, ArRobot::getRotVel,
ArRobot::getBatteryVoltage, ArRobot::isLeftMotorStalled,
ArRobot::isRightMotorStalled, ArRobot::getCompass,
ArRobot::getAnalogPortSelected, ArRobot::getAnalog, ArRobot::getDigIn,
ArRobot::getDigOut.

The standard SIP also contains low-level sonar readings, which are
reflected in ArRobot and examined with the methods:
ArRobot::getNumSonar, ArRobot::getSonarRange, ArRobot::isSonarNew,
ArRobot::getSonarReading, ArRobot::getClosestSonarRange,
ArRobot::getClosestSonarNumber.  This information is more useful when
applied to a range device; see \ref rangeDevices for details. And read
the link pages for ArRobot state reflection method details.

ARIA's ArRobot also, by default, reflects in the State Reflection \ref
syncRobot syncTask the latest client Motion Command to the robot
server at a rate set by ArRobot::setStateReflectionRefreshTime. If no
command is in effect, the ArCommands::PULSE Direct Command gets
sent. State reflection of the motion command ensures that the
client-server communication watchdog on the robot won't time out and
disable the robot.

You may turn the motion-control state reflector off in the
ArRobot::ArRobot constructor (set doStateReflection parameter to
false).  This will cause Motion Commands to be sent directly to the
robot whenever they are called.  State Reflection will send a PULSE
command to the robot at ArRobot::getStateReflectionRefreshTime
milliseconds to prevent the watchdog from timing out.

 \section rangeDevices Range Devices

Range devices (ArRangeDevice) are abstractions of sensors for which
there are histories of relevant readings.  Currently, there are two ARIA
RangeDevices: sonar (ArSonarDevice) and the SICK laser (ArSick). All 
range devices are range-finding devices that periodically collect 2-D 
data at specific global coordinates, so the RangeDevice class should 
work for any type of two-dimensional sensor.


Attach a RangeDevice to your robot with ArRobot::addRangeDevice and
remove it with ArRobot::remRangeDevice. Query for RangeDevices with
ArRobot::findRangeDevice.  ArRobot::hasRangeDevice will check to see
if a particular range device (the given instance) is attached to the
robot.  A list of range devices can be obtained with
ArRobot::getRangeDeviceList.

Note that sonar are integrated with the robot controller and that
their readings automatically come included with the standard SIP and
so are handled by the standard ArRobot packet handler. Nonetheless,
you must explicitly add the sonar RangeDevice with your robot object
to use the sonar readings for control tasks. ARIA's design gives the
programmer ultimate control over their code, even though that means
making you do nearly everything explicitly. Besides, not every program
needs to track sonar data and there are some robots don't even have
sonar.

Each RangeDevice has two sets of buffers (ArRangeBuffer): current and
cumulative, and each support two different reading formats: box and
polar (ArRangeDevice::currentReadingPolar,
ArRangeDevice::currentReadingBox,
ArRangeDevice::cumulativeReadingPolar,
ArRangeDevice::cumulativeReadingBox).  The current buffer contains the
most recent reading; the cumulative buffer contains several readings
over time, limited by ArRangeBuffer::setSize.

Useful for collision avoidance and other object detection tasks, apply
the checkRangeDevices methods to conveniently scan a related buffer on
all range devices attached to the robot for readings that fall within
a specified range, including ArRobot::checkRangeDevicesCurrentPolar,
ArRobot::checkRangeDevicesCurrentBox,
ArRobot::checkRangesDevicesCumulativePolar,
ArRobot::checkRangeDevicesCumulativeBox.

Note that each range device also has a threading mutex
(ArRangeDevice::lockDevice and ArRangeDevice::unlockDevice) associated
with it, so that sensors can be used in a thread-safe manner. For
example, if a laser device gets added that runs in its own thread, the
checkRangeDevice functions on the robot lock the device so it can poke
at the laser device without running into any issues, unlocking the
device when it is done.  If you want to understand why this locking is
good, see \ref threading.

 \section ClientCommands Commands and Actions

Your ARIA client drives the robot and runs its various accessories
through Direct and Motion Commands, as well as through Actions.

 \subsection DirectCommands Direct Commands

At the very lowest level, you may send commands directly to the robot
server through ArRobot. Direct commands consist of a 1-byte command
number followed by none or more arguments, as defined by the robot's
operating system (ARCOS, AROS, P2OS, AmigOS, etc.). For example, the command
number 4, aka ENABLE, enables the robot's motors if accompanied by the
argument 1, and disables the motors with the argument 0.

Direct commands to the robot come in five flavors, each defined by its
command argument type and length: Use ArRobot::com for commands that
have no argument, such as PULSE; ArRobot::comInt for a 2-byte integer
argument, signed or unsigned, such as the motors ENABLE command;
ArRobot::com2Bytes for when you want to define each of the two bytes
in the argument, such as the VEL2 command; and ArRobot::comStr or
ArRobot::comStrN for a null-terminated or defined-length (N extra
argument) string argument, respectively, such as the sonar POLLING
sequencing command.

The ArCommands class contains an enum with all the direct commands;
ArCommands::ENABLE, for example. Although identical in syntax and
effect when supported, not all Direct Commands are included with every
ActivMedia robot. Fortunately, unrecognized or otherwise malformed
client commands are benign since they get ignored by the
server. Please consult your robot's technical manual for details, such
as the Chapter 6 in the Pioneer 3
Operations Manual, for client command numbers and syntax.

 \subsection directMotionCommands Motion Commands

At a level just above ArRobot's Direct Commands are the Motion
Commands. These are explicit movement commands. Some have identical
Direct Command analogues and act to immediately control the mobility
of your robot, either to set individual-wheel, or coordinated
translational and rotational velocities (ArRobot::setVel2,
ArRobot::setVel, ArRobot::setRotVel, respectively); change the robot's
absolute or relative heading (ArRobot::setHeading or
ArRobot::setDeltaHeading, respectively); move a prescribed distance
(ArRobot::move); or just stop (ArRobot::stop).

Examine the directMotionDemo.cpp example file to to see Motion
Commands at work.

Be aware that a Direct or a Motion Command may conflict with controls
from Actions or other upper-level processes and lead to unexpected
consequences. Use ArRobot::clearDirectMotion to cancel the overriding
effect of a Motion Command so that your Action is able to regain
control the robot. Or limit the time a Motion Command prevents other
motion actions with ArRobot::setDirectMotionPrecedenceTime. Otherwise,
the Motion Command will prevent actions forever.  Use
ArRobot::getDirectMotionPrecedenceTime to see how long a Motion
Command takes precedence.

 \subsection actions Actions

The best way to do non-trivial motion from ARIA is with its higher-level
"Actions" mechanism.  Actions are individual objects that independently 
provide motion requests which are evaluated and then combined each cycle 
to produce a final desired movement. This allows you to build complex
behavior from simple building blocks.

Actions are defined by creating a subclass of the ArAction the base class. 
ArAction::fire is the only function that needs to be overloaded
for an action to work. ARIA includes a number of premade action classes:
look for them in the ARIA sources (the inheritance diagram on the
ArAction page will show you which they are as well). See the
<code>actionExample</code> program to for an example of how to create your own actions.

Actions are added to robots with ArRobot::addAction, including a
priority which determines its position in the action list.
ArAction::setRobot is called on an action when it is added to a robot.
You can override this. For example, this would be useful to add a
connection callback, if there were some calculations you wished to do
upon connection to the robot.

Actions are evaluated by the resolver in descending order of priority
(lowest priority goes last) in each ArRobot syncTask cycle just prior
to State Reflection.  An action resolver goes through the actions to find a
single end actionDesired (an ArActionDesired object).  Depending on its current
state, each action contributes particular actionDesired movement values
and strengths to the final action desired.  After this final action
desired has been calculated, it is stored and later gets passed to the
State Reflector and on to the robot as motion commands. 

As the resolver is evaluating each action it passes in
the current action desired of the higher priority actions, this is the
currentDesired.  For example, a stall-recovery action could
be programmed not to exert its motion effects if it has been
pre-empted by a stop action, so this stall-recovery action would check
and see if either the "strength" is "used up" or if there is a maximum
velocity, and if so it can reset its state. However, there is no need
for an action to pay attention to the currentDesired if not neccesary.  
(A resolver could also simply pass a ArActionDesired.reset() to the actions if it
did not want the actions to know about its state.)

 \subsection actionDesired Action Desired

ArActionDesired is the meat of actions. ArActionDesired objects should be
reset (ArActionDesired::reset()) before they are used or reused.

There are six action channels: velocity
(ArActionDesired::setVel), relative heading
(ArActionDesired::setDeltaHeading), absolute heading
(ArActionDesired::setHeading), maximum forward translational velocity
(ArActionDesired::setMaxVel), maximum reverse translational velocity
(ArActionDesired::setMaxNegVel), and maximum rotational velocity
(ArActionDesired::setMaxRotVel).

Your action gives each channel a strength between 0.0, the lowest, and 1.0,
the highest. Strengths are used by the resolver to compute the
relative effect the actionDesired channel setting will have on the
current translational velocity and heading of the robot, as well as
the speed limits for those movements. (Note that deltaHeading and
heading are treated as the same channel for strength purposes, and
that these are simply alternate ways of accessing the same channel.)

The maximum velocity, maximum negative velocity, and maximum
rotational velocity channels simply impose speed limits and thereby
indirectly control the robot.

For more advanced usage, desired actions can be merged
(ArActionDesired::merge) and averaged (ArActionDesired::startAverage,
ArActionDesired::addAverage, ArActionDesired::endAverage).

 \subsection resolvers Resolvers

ArResolver is the base action-resolver class.  ArPriorityResolver is
the default resolver. ArResolver::resolve is the function that ArRobot
calls with the action list (actually ArResolver::ActionMap) in order
to combine and thereby resolve the actionDesired movement controls
into State Reflection motion commands to the robot server.

There may only be one resolver per robot, which is set with
ArRobot::setResolver.  (However, a resolver could be created to contain
within it multiple resolvers of its own.)  Note that although a robot has
one particular resolver bound to it, a resolver instance is not tied to
any robot.  Thus, if you define a custom resolver, you could use one instance
to work for all robots in a program.

The resolver works by setting each of the currentDesired channels to
the contributing actionDesired values in proportion to their
respective strenghts and priority, adjusting each movement channel's
currentDesired value until the individual strength becomes 1.0 or the
list is exhausted. Same-priority actions get averaged together (if
they are competing) before being resolved with higher-priority
results.

The following table illustrates the steps and currentDesired setVel
results when the resolver combines four fictional actionDesired setVel
channel values and their relative strengths:

<pre>
  step #  action  priority  Desired::setVel  strength  currentDesired  strength
    1       4        4           -400         0.25       -400            0.25
    2       3        3           -100         1.0     (combine to 2&3) 
    3       2        3            200         0.50    (combine to 2&3)
    4      2&3       3              0         0.75        -100            1.0
    5       1        1            500         0.50        -100            1.0
</pre>

Notice in the example that the same-priority actions 2 and 3 are
combined before being resolved with the higher priority action 4. Also
notice that action 1 has no effect since the currentDesired channel
strength reaches 1.0 before that lowest-priority action gets
considered by the resolver.

 \subsection specialActions Predefined Movement and Limiting Actions

For programming convenience, ARIA has defined two useful types of
actions: Movement and Limiting. There are no classes for limiting or
movement actions.

Built in movement actions have an %ArAction prefix and act to set
either or both the translational velocity (setVel) and heading
(setDeltaHeading and setHeading) channels. Built in limiting actions
are prefixed with %ArActionLimiter and act to set one or more of the
maximum translational and rotational velocity channels.

 \subsection actionInteractions Mixing Actions

Actions are most useful when mixed. The <code>teleop</code> example program is a good
example of mixing limiting and movement actions. In the code, there
are many limiting actions, including Limiter, LimiterFar, and so
on. And there are two movement actions, joydriveAct and
keydriveAct. The limiting actions have higher priority than the
movement ones, thereby making sure the way is safe before allowing the
robot to drive.

The example also illustrates fundamental, yet very powerful features
of ARIA actions and how they contribute to the overall behavior of the
mobile robot. Because they are individuals, contributing discretely to
the movements of the robot, actions are easily reusable. The limiting
action in the <code>teleop</code> example that prevents the robot from crashing
into a wall when translating forward, can be copied, as is, into
another ARIA program and have the identical effect, except that
instead of driving the robot with a joystick, the new program's
lower-priority movement action might use color-tracking to have the
robot follow a rolling ball. The ball-following action doesn't needs
to know anything about the finer arts of safe navigation--the
higher-priority limiting actions take care of that.

Another ARIA example program called <code>wander</code> demonstrates how
different movement actions can be used and how they interact. The
stall-recover action in wander (ArActionStallRecover) influences the
robot's movements only when the motors are stalled, disabling the
lower priority actions by using up all translational and rotational
strength until the robot has extracted from the stall. You should also
examine ArActionStallRecover.cpp in the src/ directory for
actionDesired details on how the action changes its motion control
influences based on the stall state.

Also note how ArActionAvoidFront and ArActionConstantVelocity
interact.

 \section callback Robot Callbacks

There are a number of useful callbacks in the ARIA system, including
ArRobot::addConnectCB, ArRobot::remConnectCB,
ArRobot::addFailedConnectCB, ArRobot::remFailedConnectCB,
ArRobot::addDisconnectNormallyCB, ArRobot::remDisconnectNormallyCB,
ArRobot::addDisconnectOnErrorCB, ArRobot::remDisconnectOnErrorCB,
ArRobot::addRunExitCB, ArRobot::remRunExitCB.  Read their individual
documentation pages for details.

Examples of callbacks are in the directMotionDemo and in
joydriveThreaded.  Also, ArGripper uses a connectCB as a way to find
out when to poll the robot -- a good use of callbacks.  Just make sure
that any modular code you have removes callbacks if you use them.

 \section functors Functors

Functors are used throughout ARIA.
Functor is short for function pointer. A Functor lets you call a
function without knowing the declaration of the function. Instead, the
compiler and linker figure out how to properly call the function.

Function pointers are fully supported by the C language. C++ treats
function pointers like C, but adds in the concept of member functions
and the 'this' pointer. C++ does not include the 'this' pointer in the
function pointer, which can cause all sorts of problems in an
object-oriented program. Hence, we created functors. Functors contain
both the function pointer and the pointer to the object which contains
the function, or what the function uses as its 'this' pointer.

ARIA makes use of functors as callback functions. In most cases, you
will only need to instantiate callback functors and pass them off to
various parts of ARIA. To instantiate a functor, you first need to
identify how many parameters the function needs and if it returns a
value. Most ARIA functions take a pointer to ArFunctor.  This is the
base class for all the different functors. Its for a function that has
no parameters and no return value.

But you can not create an ArFunctor, because it is an abstract base
class.  Rather, you need to instantiate one of these classes:

ArFunctorC, ArFunctor1C, ArFunctor2C, ArRetFunctorC, ArRetFunctor1C,
ArRetFunctor2C

The 'C' in the name means that it's an instance of the functor that
knows about the class of a member function. These are templatized
classes so need to be instantiated. For example:
<pre>
     ExampleClass obj;
     ArFunctorC<ExampleClass> functor(obj, &ExampleClass::aFunction);
</pre>
ExampleClass is a class which contains a function called
aFunction. Once the functor is created in this fashion, it can now be
passed off to an ARIA function that wants a callback functor. And the
function ExampleClass::aFunction will be called when the functor is
invoked.

The code that uses the callback functor only needs to know about these
templatized classes: ArFunctor, ArFunctor1, ArFunctor2,
ArRetFunctor, ArRetFunctor1, and ArRetFunctor2. When invoked, these functors pass 
0-2 parameters to the target function. The plain ArFunctor functors have no
return value; the ArRetFunctor functors may return a value. 

To invoke a functor, simply call the invoke function
on the functor. If it takes parameters, call invoke with those
parameters. If the functor has a return value, call invokeR. The
return value of the function will be passed back through the invokeR
function.

 \section userInput User Input

There are two different ways to get user input into ARIA, from a
joystick and from a keyboard.  With a joystick is most useful for
driving the robot around.  There is a class set up that interfaces to
the OS for joystick controls, this is ArJoyHandler, the important
functions are ArJoyHandler::getButtons, ArJoyHandler::getAdjusted,
ArJoyHandler::setSpeeds, and ArJoyHandler::getDoubles.  With a
keyboard is most useful for setting and changing modes, and exiting
the program, but it it can also be used to drive the robot as well
(with the arrow keys and the space bar typically), ArKeyHandler is the
class which deals with interfacing to the keyboard.  ArKeyhandler is
directed towards capturing single key presses, not towards reading in
sets of text, you can use the normal OS functions to do this.  The
important functions in ArKeyHandler is ArKeyHandler::addKeyHandler,
which binds a specific key to a given functor, also look at the enum
ArKeyHandler::KEY for values to pass in for special keys.  You also
need to attach a key handler to some robot with
ArRobot::attachKeyHandler.  ArActionJoydrive will use the joystick to
drive the robot around, while ArActionKeydrive will use the arrow keys
and spacebar to drive the robot around, both of these are employed in
the <code>teleop</code> example.  The keyboard control is also a nice way to exit
cleanly in Windows since control C or just clicking on the program box
won't cleanly disconnect from the robot, by default if you connect an
ArKeyHandler to a robot, escape will exit the program, however you can
chage this behavior when you attach the key handler to the robot if
you wish.
 
 \section threading Threading

ARIA is highly multi-threaded. This section presents some of the
critical concepts behind writing threaded ARIA code.

ARIA provides a number of support classes to make it easier to write
object-oriented threaded code. They are: ArASyncTask, ArCondition,
ArMutex, and ArThread.

Thread-safe code mostly means proper coordination between threads when
handling the same data. You want to avoid the obvious problem of one
or more threads reading the data at the same time others write the
data. To prevent this problem from happening, the data needs to be
protected with synchronization objects.

 \subsection syncObject Synchronous Objects

In ARIA, the synchronization objects are ArMutex and ArCondition.
ArMutex is the most useful one. Mutex is short for mutual
exclusion. It guarantees that only one thread will use its data at a
time.  The proper way to use a mutex is to attempt to lock it right
before accessing its shared data.  If the mutex is not in use, ARIA
then grants exclusive access by the requesting thread. If the mutex is
locked, the access request gets blocked, and the thread must wait
until the mutex gets free.  When the thread that has access to the
mutex is finished with the data, it must unlock the mutex and thereby
make the data available to other threads. If it is not unlocked, the
program will become deadlocked and hang. See the mutex example in the
ARIA distribution for more details.

ArCondition is useful for delaying the execution of a thread. A thread
suspends execution while waiting on an ArCondition until another
thread wakes it up. For instance, use ArCondition while waiting for a
mutex to become free. Performance is better, too.  ArCondition puts
the thread to sleep. The processing expensive alternative is to have
the thread continously check for a change in condition. ArCondition
notifies only those threads that are currently waiting on it at the
time the condition changes.

See the ARIA condition example.

 \subsection asynctasks Asynchronous Tasks

Unlike the cyclical tasks in the syncTask list, asynchronous tasks run
in their own threads. And an ARIA ArASyncTask needs to have a thread
under its control for the full lifetime of the program.

To create an ansynchronous task, derive a class from ArASyncTask and
override the ArASyncTask::runThread() function. (The function
automatically is called within the new thread, when the ArASyncTask
gets created.) To create and start the thread, call
ArASyncTask::create(). When the ArASyncTask::runThread() function
exits, the thread will exit and be destroyed.

This class is mainly a convenience wrapper around ArThread so that you
can easily create your own object that encapsulates the concept of a
thread.

 \section aria Global Data

ARIA contains a list of all the ArRobot instances. Use the
Aria::findRobot() to find a robot by name, or use Aria::getRobotList()
to get a list of the robots.

Use Aria::getDirectory() to find ARIA's top-level path (C:\\Program Files\\ActivMedia Robotics\\%Aria on Windows, or
/usr/local/Aria on Linux, typically, but not always). This is useful, 
for instance, to locate
robot parameter files for individual operational details. Use
Aria::setDirectory() to change this path for the run of the program if
you feel the need to override what ARIA has decided.

Call Aria::init() at program start to perform global initialization, and use 
Aria::exit() to exit all Aria threads before exiting your program. :w


 \section pieceMealUse Piecemeal Use of ARIA

The most basic layer of ARIA is ArDeviceConnection and subclasses, which
handle low-level communication with the robot server.  On top of the
connection layer, we have a packet layer--ArBasePacket and
ArRobotPacket--the basic algorithms for constructing command packets
and decoding server information packets.

Above the packet layer is the packet handler classes,
ArRobotPacketReceiver and ArRobotPacketSender, when send and receive
packets to and from the robot.  Finally, on top of all these lowest
layers is ArRobot, which is a gathering point for all things, but can
be used in a quite basic format without all of the bells and whistles.
ArRobot has builtin tasks, actions, state reflection and so forth, all
of which can be disabled from the constructor (ArRobot::ArRobot) and
ignored or reimplemented.

Also note that if all you do is turn off state reflection, which only
affects sending ArRobot-mediated motion commands to the robot, not
receiving SIPs from the robot, none of the other activities which
ArRobot engages on its loop will take up hardly any time, so it
probably isn't worth building your own set of tasks, but the power to
do so is there for the intrepid.

One other thing worth noting is that you can call ArRobot::loopOnce
and it will run through its loop a single time and return.  This is so
that you can use ARIA from your own control structure.  If you are
using loopOnce you may also find it beneficial to call
ArRobot::incCounter, so that the loop counter will be updated.  You
could also just call ArRobot::packetHandler, ArRobot::actionHandler,
or ArRobot::stateReflector on your own, as these are the most
important internal functions, though if you make your own loop you
should probably call ArRobot::incCounter any way that you do it, as
this is how sonar are known to be new or not, and such.

We recommend that whatever you do you use the same type of strict
threading/locking that ARIA observes.

 \section params Robot Parameter Files
 
Found in the <code>Aria/params</code> directory, generic, as well as individually
named robot parameter files contain default and name-specific robot
information that ARIA uses to characterize the robot and correctly
interpret the server information that a robot sends back to the
client.

Every robot has a type and subtype (e.g. "Pioneer" and "p3dx-sh") as well
as a user-modifiable name, embedded in its FLASH parameters (see your
robot operations manual for information about the robot's FLASH). 
These parameters get sent to the ARIA client right after establishment of
the client-server connection, which ARIA prints to output (watch as 
<code>demo</code> connects, for example). ARIA first loads parameters from the subtype
parameter file, then from a name parameter file--setting and resetting global variables
based on the contents of each file. Accordingly, subtype may add or
change the settings derived from the default, and a named parameter
file has the very last say over things.

ARIA has robot subtype parameter
files in its <code>params</code> directory.  Example of parameter files are 
<code>p3dx.p</code> (old H8 Pioneer 3 DX), <code>p3dx-sh.p</code> 
(new SH Pioneer 3 DX), <code>p3at-sh.p</code>
(new SH Pioneer 3 AT), <code>p2de.p</code> (Pioneer 2 DE), 
  <code>peoplebot-sh.p</code> (for new 
SH PeopleBot).  Parameter files are also available from ActivMedia
technical support (http://robots.activmedia.com). 

To override a subtype parameter file, copy it to a new file named for your 
robot's name as specified in the FLASH parameter, adding the ".p" 
suffix, and change any parameters neccesary for that specific robot.
For example, ARIA uses <code>RobotRadius</code> to determine the robot's turn
limits in most of the obstacle avoidance routines. The default for the
P2AT robot doesn't account for bumper accessories. Accordingly, you
might create a new parameter file that redefines <code>RobotRadius</code> for that
specific robot.

ARIA uses the values in the conversion factors section of a parameter
file to transform the robot-dependent server information data into
normal dimensions and rates. For example, the <code>DistConvFactor</code> converts
the robot's position data, measured in encoder ticks, into
millimeters.

ARIA consults the accessories section of a robot's parameter file to
determine what accessories a robot might have that cannot be told by
other means.  For example, the P2 bumper values appear in the standard
SIP stall values, but if a bump ring isn't connected, these values
float and vacillate between on and off. An accessory definition in the
parameter file clues ARIA to use or not use the bumper values.

Finally, the sonar section of the parameter file contains information
about the sonar number and geometry so that ARIA can relate sonar
readings with position relative to the center of the robot.

 \subsection paramMechanisms How the parameter file works

The parameter file is very much like a Windows INI file in format. It
contains sections and keyword/data pairs. Comments start with a
semi-colon. A section identifier is a bracketed keyword, such as:

<pre>
     [ConvFactors]
</pre>

Keywords and data are separated by one or more spaces on a single
line, and may include several defining data values. Each keyword has
its own behavior with how it parses the data. For example:

<pre>
     KeyWord data1 data2 data3 ...
</pre>

Case doesn't matter for either section identifiers and keyword names.  Some
parameters can have multiple instances in the file. <code>SonarUnit</code> is a
good example of this. For example:

<pre>
     SonarUnit 0 73 105 90 
     SonarUnit 1 130 78 41 
</pre>

See ArConfig or ArRobotParams for additional details.  ArConfig (and the
same file format) may also be used by ARIA applications for other config
files as well.

@sa @ref arconfig

 \section hardConnectRobot Connecting with a Robot or the Simulator the hard way

ArDeviceConnection is ARIA's communications object; ArSerialConnection
and ArTcpConnection are its built-in children most commonly used to
manage communication between an ActivMedia robot or the robot
simulator, respectively. These classes are not device-specific,
however, so use ArSerialConnection, for instance, to also configure a
serial port and establish a connection with a robot accessory, such as
with the SICK laser range finder.


 \subsection openDevice Opening the Connection

After creating and opening a device connection, associate it with its
ARIA device handlers, most commonly with ArRobot::setDeviceConnection
for the robot or the simulator.

For example, early in an ARIA program, specify the connection device and 
associate it with the robot:

<pre>
  ArTcpConnection con;
  ArRobot robot;
</pre>

Later in the program, after initializing the ARIA system
(Aria::init(); is mandatory), set the Connection port to its default
values (for TCP, host is "localhost" and port number is 8101), and
then open the port:

<pre>
 con.setPort();
 if (!con.openSimple())
  {
    printf("Open failed.");
    Aria::shutdown();
    return 1;
  }
</pre>

TCP and Serial connections have their own implementation of open which
is not inherited, but has default arguments that make the generic open
work for the all default cases.  And open returns a status integer
which can be passed to the re-implemented and inherited
ArDeviceConnection::getOpenMessage in order to retrieve related status
string, which is useful in reporting errors to the user without having
to know about the underlying device.

 \subsection devConnect Robot Client-Server Connection

After associating the device with the robot, now connect with the
robot's servers, ArRobot::blockingConnect or ArRobot::asyncConnect, for
example, to establish the client-server connection between ARIA
ArRobot and the ActivMedia robot microcontroller or robot
simulator. The blockingConnect method doesn't return from the call until
a connection succeeds or fails:

<pre>
  robot.setDeviceConnection(&con);
  if (!robot.blockingConnect())
  {
    printf("Could not connect to robot... Exiting.");
    Aria::shutdown();
    return 1;
  }
</pre>

The previous examples connect with the simulator through a TCP
socket on your PC. Use <code>tcpConn.setPort(host, port)</code> to set the TCP
hostname or IP address and related socket number to another machine on
the network. For instance, use <code>tcpConn.setPort("bill", 8101);</code> to
connect to the simulator which is running on the networked computer
"bill" through port 8101.

Replace <code>ArTcpConnection con;</code> with <code>ArSerialConnection con;</code>
to connect with a robot through the default serial port (<code>/dev/ttyS0</code> 
or <code>COM1</code>), or another you specify with ArSerialConnection::setPort(), 
 such as <code>con.setPort("COM3");</code>.

At some point, you may want to open the port with the more
verbose <code>con.open()</code>.

 \subsection connrw Connection Read, Write, Close and Timestamping

The two main functions of a device connection are
ArDeviceConnection::read and ArDeviceConnection::write. Simple
enough. ArDeviceConnection::close also is inherited and important. You
probably won't use direct read or write to the robot device, although
you could. Rather, ArRobot provides a host of convenient methods that
package your robot commands, and gather and distribute the various
robot information packets, so that you don't have to attend those
mundane details. See the next section for details.

All ArDeviceConnection subclasses have support for timestamping
(ArDeviceConnection::getTimeRead). With the robot connection,
timestamping merely says what time a robot SIP came in, which can be
useful for interpolating the robot's location more precisely.

 \section utility Utility Classes

Some of the utility classes are ArMath, ArUtil, ArTime, ArPose, ArLog, 
ArSectors, ArRingQueue.

 \section arconfig ArConfig

ArConfig is a mechanism for storing configuration parameters for different
modules in a text configuration file.  The global Aria class
maintains a global ArConfig pointer which program modules may access.
Use ArConfig::addParam to register a new parameter with ArConfig, and use
ArConfig::addProcessFileCB to register a callback functor called when the 
configuration changes (by loading the file with ArConfig::parseFile, or other 
means such as an update from a remote client via ArNetworking).

 \section sockets Sockets

The ArSocket class is a wrapper around the socket network
communication layer of your operating system. ARIA mostly uses
ArSocket to open a server port and to connect to another server port.

To connect to a port, simply construct a socket containing the
hostname or IP address of the host, a port number, and the ARIA socket
type (TCP or UDP). For example:

<pre>
     ArSocket sock("host.name.com", 4040, ArSocket::TCP);
</pre>

Or call the ArSocket::connect() function, such as:

<pre>
ArSocket sock;
     sock.connect("host.name.com", 4040, ArSocket::TCP);
</pre>

To open a server port, simple construct a socket:

<pre>
     ArSocket sock(4040, true, ArSocket::TCP);
</pre>

Or call:

<pre>
     ArSocket::open(4040, ArSocket::TCP);
</pre>

 \section ArNetworking ArNetworking

    For a more advanced networking infrastructure, see the ArNetworking companion library, 
    distributed with ARIA.  ArNetworking provides an extensible system of
    data requests and updates between client and server applications via TCP or
    UDP, using the same base "packet" concept as robot communication.  
    For example, use ArNetworking to connect multiple robots working together, 
    offboard user interfaces to onboard control servers, or robot control programs to 
    offboard data resources.

 \section sound Sound and Speech

 
    ARIA provides foundation sound support, and seperate libraries use this
    for speech and network audio.
 
    <ol>
 
     <li>ARIA's ArSoundsQueue provides a method for handling sound output 
     generated by various components of a large ARIA application in sequence 
     and in loops. 
     It is a sound playback and speech synthesis manager, which 
     uses a thread-safe queue of sound and speech synthesis requests, and runs
     a background processing thread for it. Use this for most of your non-trivial
     audio playback and voice synthesis needs.
     The speech synthesis libraries, the voice recognition library, and the NetAudio
     library are designed to be used in conjuction with this class to coordinate their 
     usage of the sound device.
    </li>

    <li>ARIA's ArSoundPlayer provides a basic cross-platform sound-file playback 
    capability.
    Sound files are in WAV (Windows RIFF) format. This class provides static methods
    that can be used by ArSoundsQueue for sound file playback.
    </li>

     <li>Seperate libraries provide wrappers around some 
      speech synthesis (Text-to-speech) and recognition products:
     <ul>
       <li>The ArSpeechSynth_Festival library  uses the free Festival system from the 
         University of Edinburgh to perform speech synthesis. It provides
         the ArFestival class as a wrapper around Festival.
       </li>
       <li>The ArSpeechSynth_Cepstral library uses the Swift library from
         Cepstral, Inc. to perform speech synthesis. It provides the ArCepstral
         class for this. ArCepstral offers a few extra features over
         ArFestival, and Cepstral, Inc. provides high quality voices for use with Swift.
       </li>
       <li>The ArSpeechRec_Sphinx library uses Sphinx from Carnegie Mellon
         University to perform speech recognition. ArSphinx provides an interface to this.
       </li>
      </ul>
     </li>

     <p>Functions common to both of the speech synthesis libraries are included in a base
        class, ArSpeechSynth. 
      </p>

     <li>The separate ArNetAudio library provides network voice audio recording, transmission and playback:
     <ul>
       <li>ArNetAudioServer automatically decodes and plays or records and
     encodes audio for a network server (typically running on a robot's onboard
     computer) and sends and recieves the encoded audio to/from a client.</li>
       <li>ArNetAudioClient automatically decodes and plays or records and
     encodes audio for a network client, sending and recieving the encoded
     audio to/from a server (i.e. a robot's onboard computer).</li>
       <li>ArNetAudioIO is the common class performing cross-platform Audio I/O 
       (via the free PortAudio library), and voice encoding/decoding (via the free Speex codec).
       It is used by ArNetAudioClient and ArNetAudioServer, but is also available for 
       standalone use.
       </li>
     </ul>
     </li>
 

 </ol>    
 
 \section emacs Emacs

Here is the configuration specification the developers at ActivMedia
Robotics use in their .emacs files, in case you want to modify the
code using emacs and not deal with differences in indentation and
such.

<pre>
    (setq c-default-style '((other . "user")))
    (c-set-offset 'substatement-open 0)
    (c-set-offset 'defun-block-intro 2)
    (c-set-offset 'statement-block-intro 2)
    (c-set-offset 'substatement 2)
    (c-set-offset 'topmost-intro -2)
    (c-set-offset 'arglist-intro '++)
    (c-set-offset 'statement-case-intro '*)
    (c-set-offset 'member-init-intro 2)
    (c-set-offset 'inline-open 0)
    (c-set-offset 'brace-list-intro 2)
    (c-set-offset 'statement-cont 0)
    (defvar c-mode-hook 'c++-mode)
</pre>

 \section noneverydayC Non-everyday use of C++

ARIA uses some features of C++ that some programmers may not be aware of yet,
and includes some workarounds for platform differences.

 \subsection stl Standard Template Library

ARIA makes heavy use of the C++ standard template library.  So you
should understand the STL in order to get the best use from some of
the more advanced parts of ARIA.  A reference many developers have
found useful is http://www.sgi.com/tech/stl/, this is documentation to
SGI's implementation, but other than the SGI specific templates which
are explicitly stated as being SGI only, the documentation is quite
helpful.

 \subsection defaultArgs Default Arguments 

Default arguments work like the following, in the function delcaration
a parameter is specified, and given a default value at the same time.
If the function is then used the parameters which have been given a
value do not need to be given values when the function is used.

For example, after defining foo, it can be used in two differnt manners:
<pre>
     void foo(int number = 3);
     // ...later
     foo();
     // or
     foo(int);   
</pre>
This behavior is quite useful for having defaults that most people
will not need to change, but allowing people to change them if they
desire.

Also note that the function definition must not have the assignment in
it, only the declaration, otherwise Windows compilers will not work
and will report a not entirely useful error message.

 \subsection constructorChaining Constructor Chaining

Constructor chaining is quite simple though little used.  Each
contructor can give arguments to the constructors of the member
variables it contains and to the constructors which it inherits.  For
example if you have:
<pre>
     class BaseClass
     {
     public:
       BaseClass(int someNumber);
     };
</pre>
and 
<pre>
     class SubClass : public BaseClass
     {
     public:
       SubClass(void);
       int anotherNumber;
     };
</pre>
When you write your constructor for SubClass you can intialize both
baseClass and anotherNumber:
<pre>
     SubClass::SubClass(void) : BaseClass(3), anotherNumber(37)
     {
         // ...
     }
</pre>
Note how the constructors to be initialized must follow a colon (:) after the
constructor, and be separated by commas.  Member variables 
must  be initialized in the order they are in the class.  Note
that intializing integers is not all that unique or useful, but using
this to initialize callback \ref functors is quite useful.

Constructor chaining is used in many many places by ARIA, thus it must
be understood in order to understand ARIA, but the above is all that
really needs to be known.

 \subsection charsAndStrings Chars and Strings, Win workaround

During development problems were encountered with Windows if
a <code>std::string</code> was passed into a DLL.  Thus for all input to ARIA 
<code>const char *</code> is used, but for all internal storage and all reporting
<code>std::string</code>s are passed back out of ARIA.

 \subsection arexport AREXPORT

Because of the Windows set up for using DLLs, this macro is used
to take care of the required declaration attributes for DLLs.  Largely 
users do not need to worry about <code>AREXPORT</code>, but only functions which have 
<code>AREXPORT</code> and inline functions are usable with DLLs in Windows (all of the 
ARIA functions which are documented in this manual are usable).

*/


#endif // ARIA_H
