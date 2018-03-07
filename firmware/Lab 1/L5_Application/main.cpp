/*
 *     SocialLedge.com - Copyright (C) 2013
 *
 *     This file is part of free software framework for embedded processors.
 *     You can use it and/or distribute it as long as this copyright header
 *     remains unmodified.  The code is free for personal use and requires
 *     permission to use in a commercial product.
 *
 *      THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 *      OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 *      MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 *      I SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 *      CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *     You can reach the author of this software at :
 *          p r e e t . w i k i @ g m a i l . c o m
 */

/**
 * @file
 * @brief This is the application entry point.
 */

#include <stdio.h>
#include "utilities.h"
#include "io.hpp"
#include <string.h>

inline bool CHECK_BIT(int var, int pos)
{
  return (bool)(var & (1 << pos));
}

int getLED(int x);

int main (void)
{
// Use typedef to create a new variable type called myStateType
  typedef enum {start, HelloWorld, switches, end} myStateType;
  myStateType currentState = start;
  char S1[25];
  int SV;
  int led;
  int x;
  while (1) {
    delay_ms(100);

    switch (currentState)
    {
    case start:
      printf("Enter \"1\" to print out Hello World or \"2\" to get switch input or \"end\" to end program \n");
      scanf("%s", &S1);
      if (strcmp(S1, "1") == 0)
      {
        currentState = HelloWorld;
      }
      else if (strcmp(S1, "2") == 0)
      {
        currentState = switches;
      }
      else if (strcmp(S1, "end") == 0) {
        currentState = end;
      }
      break;

    case HelloWorld:
      printf("\nHello World\n");
      currentState = start;
      break;
    case switches:
      printf("Press the LED u want on \n \n");
      x = SW.getSwitchValues();
      delay_ms(100);
      if (x == 1 || x == 2 || x == 4 || x == 8) {
        led = getLED(x);
        LE.on(led);
        printf("LED %i is turned on \n", led);
        delay_ms(500);
        LE.off(led);
        currentState = start;
      }
      else {
        continue;
      }
      break;
    case end:
      return (1);

    default:
      printf("State machine ERROR!\n");
    }

  } // end while()
}

int getLED(int x) {
  int y;
  if (x == 1) {
    y = 1;
  }
  if (x == 2) {
    y = 2;
  }
  if (x == 4) {
    y = 3;
  }
  if (x == 8) {
    y = 4;
  }
  return y;
}