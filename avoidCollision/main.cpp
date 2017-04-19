/*
 * My first program for ARIA/MobileSim
 *
 * Class CMP545 - PPGC INF UFRGS
 * Prof. Edson Prestes
 *
 * Felipe Kuhne - April, 2017
 * fkuhne at gmail dot com
 *
 */

#include "ClassRobo.h"

int main(int argc, char** argv)
{
  int returnStatus = -1;

  PioneerRobot robot(ConexaoSimulacao, "", &returnStatus);

  if(!returnStatus)
  {
    fprintf(stderr, "Error while creating robot object.\n");
    ArLog::log(ArLog::Terse, "Error while creating robot object.");
    exit(-1);
  }

  /*while(true)
  {
    int s[8];
    robot.getAllSonar(s);
  }*/
}
