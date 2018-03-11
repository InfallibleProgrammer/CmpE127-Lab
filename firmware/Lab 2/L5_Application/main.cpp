#include <stdio.h>
#include "utilities.h"
#include "io.hpp"
#include "gpio.hpp"
#include "SRAM.h"



bool sw1 = SW.getSwitch(1);
bool sw2 = SW.getSwitch(2);
bool sw3 = SW.getSwitch(3);


int main(void){
    printf("Lab 2: SRAM Read/Write \n");
    printf("By: Akash Vachhani");
    printf("... Program initializing");
    delay_ms(2000);
    initialize();
    int choice = 0;
    while(1){
        initialize();
        printf("******* Menu ********\n");
        printf("1) Write\n");
        printf("2) Read\n");
        printf("3) Exit");
        while(choice == 0){
            sw1 = SW.getSwitch(1);
            sw2 = SW.getSwitch(2);
            sw3 = SW.getSwitch(3);
            if(sw1){
                choice = 1;
            }
            if(sw2){
                choice = 2;
            }
            if(sw3){
                choice = 3;
            }

        }
        if(choice == 1){ // write
            char mem_location;
            char data;
            printf("\nWhich memory location do you want to write to?\n");
            scanf("%d", &mem_location);
            printf("This is mem location: %d\n", mem_location);
            printf("What data do you want to write?\n");
            getchar();
            getchar();
            scanf("%d", &data);
            printf("\nThis is data being written: %d", data);
            mov(mem_location, data);
            choice = 0;
        }
        if(choice == 2){ //read
            char mem_location;
            char data;
            printf("\nWhich memory location do you want to read from?\n");
            getchar();
            getchar();
            scanf("%d", &mem_location);
            data = mov(mem_location);
            int i_data = data;
            printf("\nThis is data being read: %i \n", i_data);
            choice = 0;
        }
        if(choice == 3){
            return 0;
        }

    }
}