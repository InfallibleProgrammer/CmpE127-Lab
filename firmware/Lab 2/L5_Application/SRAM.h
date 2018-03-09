#ifndef SRAM_H
#define SRAM_H

#include "io.hpp"
#include "gpio.hpp"
#include <stdio.h>
#include "utilities.h"



void toggleClock(void); //Function includes 5 clock cycles
void setAPinsOutput(void); //Refers to Port A pins from 1758, refer to circuit diagram
void setAPinsIntput(void); //Refers to Port A pins from 1758, refer to circuit diagram
void setBPinsOutput(void); //refers to Port B pins from 1758, refer to circuit diagram 

void write(char); //write function inputs char. What to write
char read(void); //Read function is void because it reads the value 
void setAddr(char); //Setaddr takes in char to know what address to set
void setDataOut(char); //DataOut takes in char so you know what value you need to write
char getDataIn(void); //What take is passed into 245. Void
void setCmd(char); //What to set the cmd as
void initialize(void); //Initalize function disables every IC used.

//main write function
void mov(char, char);

//main read function
char mov(char);

#endif