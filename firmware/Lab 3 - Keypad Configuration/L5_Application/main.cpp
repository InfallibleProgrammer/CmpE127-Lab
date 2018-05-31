#include <stdio.h>
#include "utilities.h"
#include "io.hpp"
#include "gpio.hpp"
#include "Keypad.hpp"



bool sw1 = SW.getSwitch(1);
bool sw2 = SW.getSwitch(2);
bool sw3 = SW.getSwitch(3);


int main(void) {
    initialize();
    char temp = 0;
    LD.setLeftDigit(temp);
    while (1 == 1) {
        sw1 = SW.getSwitch(1);
        if (sw1) {
            temp = keypadValue();
            LD.setRightDigit(temp);
            delay_ms(2000);
            break;
        }
    }
}