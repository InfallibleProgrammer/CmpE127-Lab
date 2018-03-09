#include <stdio.h>
#include "utilities.h"
#include "io.hpp"
#include "gpio.hpp"
#include "SRAM.h"


//Set Port A pins as global so each variable can use them
// GPIO A0(P1_29);
// GPIO A1(P1_28);
// GPIO A2(P1_23);
// GPIO A3(P1_22);
// GPIO A4(P1_20);
// GPIO A5(P1_19);
// GPIO A6(P0_30);
// GPIO A7(P0_29);
// //End of Port A pins being set global

// //Set Port B pins as global
// GPIO dir_w(P0_0);
// GPIO bus_e(P0_1);
// GPIO addr_w(P2_1);
// GPIO dataOut_w(P2_2);
// GPIO dataIn_e(P2_3);
// GPIO cmd_w(P2_4);
// GPIO clk(P2_6);
//End of Port B pins being set global



// char DISABLE_PERIPHERALS = 0; //sends 0 to cmd register to disable student design
// char START_SRAM_READ = 9; //Pass in 9 so binary values get passed to student design. 0001001
// char START_SRAM_WRITE = 17; //Pass 17 to right so binary value, 0010001. 

//typedef char mem_t; //char is a data type
//typedef char reg_t; //char is a data type


// void toggleClock(void); //Function includes 5 clock cycles
// void setAPinsOutput(void); //Refers to Port A pins from 1758, refer to circuit diagram
// void setAPinsIntput(void); //Refers to Port A pins from 1758, refer to circuit diagram
// void setBPinsOutput(void); //refers to Port B pins from 1758, refer to circuit diagram 

// void write(char); //write function inputs char. What to write
// char read(void); //Read function is void because it reads the value 
// void setAddr(char); //Setaddr takes in char to know what address to set
// void setDataOut(char); //DataOut takes in char so you know what value you need to write
// char getDataIn(void); //What take is passed into 245. Void
// void setCmd(char); //What to set the cmd as
// void initialize(void); //Initalize function disables every IC used.

// //main write function
// void mov(char, char);

// //main read function
// char mov(char);

/*
MAIN FUNCTION
*/


/*char DISABLE_PERIPHERALS = 0; //sends 0 to cmd register to disable student design
char START_SRAM_READ = 9; //Pass in 9 so binary values get passed to student design. 0001001
char START_SRAM_WRITE = 17; //Pass 17 to right so binary value, 0010001. */


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


// int main(void)
// {
//     initialize();
//     int choice = 2;
//     delay_ms(3000);
//  /*   printf("%i \n", START_SRAM_WRITE);
//     printf("%i \n", START_SRAM_WRITE);*/

//     while(1)
//     {
//         initialize();
//         while((choice != 0) && (choice != 1))
//         {
//             printf("Press 1 to write and 0 to read\n");
//             delay_ms(300);
//             if(choice != 0 && choice != 1){
//                 scanf("%d", &choice);
//             }
//             delay_ms(300);

//         }
//         switch (choice)
//         {
//             //read
//             case 0:
//             {
//                 char mem_location;
//                 char data;
//                 printf("Which memory location do you want to read from?\n");
//                 getchar();
//                 getchar();
//                 scanf("%d", &mem_location);
//                 data = mov(mem_location);
//                 int i_data = data;
//                 LD.setNumber(i_data);

//                 printf("This is shit: %i", i_data);
//                 break;
//             }

//             //write
//             case 1:
//             {
//                 printf("%d\n", choice);
//                 getchar();
//                 getchar();
//                 char mem_location;
//                 char data;
//                 printf("Which memory location do you want to write to?\n");
//                 scanf("%d", &mem_location);
//                 printf("This is mem location: %d\n", mem_location);
//                 printf("What data do you want to write?\n");
//                 getchar();
//                 scanf("%d", &data);
//                 printf("This is data: %d", data);
//                 mov(mem_location, data);
//                 break;
//             }
//             default:
//             {
//                 //shouldn't get here
//             }
//         }

//         choice = 2;
//     }

//     return 0;
// }
/*
void initialize(void)
{
    setBPinsOutput(); //Set B pins as GPIO output
    dir_w.setHigh(); //Disable 245
    bus_e.setHigh(); //Direction for 245 set from A to B
    addr_w.setLow(); //Disable 373 Address
    dataOut_w.setLow(); //Disable 373 from writing data to SRAM
    dataIn_e.setHigh(); //Disable 373 from reading data from SRAM
    cmd_w.setLow(); //Disable the State Machine
    clk.setLow(); //Set clk(GPIO pin) to low
}

void setAPinsOutput(void)
{
    A0.setAsOutput();
    A1.setAsOutput();
    A2.setAsOutput();
    A3.setAsOutput();
    A4.setAsOutput();
    A5.setAsOutput();
    A6.setAsOutput();
    A7.setAsOutput();
}

void setAPinsInput(void)
{
    A0.setAsInput();
    A1.setAsInput();
    A2.setAsInput();
    A3.setAsInput();
    A4.setAsInput();
    A5.setAsInput();
    A6.setAsInput();
    A7.setAsInput();

}

void setBPinsOutput(void)
{
    dir_w.setAsOutput();
    bus_e.setAsOutput();
    addr_w.setAsOutput();
    dataOut_w.setAsOutput();
    dataIn_e.setAsOutput();
    cmd_w.setAsOutput();
    clk.setAsOutput();
    }

void toggleClock(void)
{
    for(int i = 0; i <5; i++){
    clk.setHigh();
    delay_ms(1);
    clk.setLow();
    delay_ms(1);
    }
}

void write(char byte)
{
    printf("This is byte: %d\n\n\n", byte);
    bus_e.setHigh();

    //A-->B
    dir_w.setHigh();

    //set GPIOs as output
    setAPinsOutput();

    if (byte & (1 << 7)) A7.setHigh();
    else A7.setLow();

    if (byte & (1 << 6)) A6.setHigh();
    else A6.setLow();

    if (byte & (1 << 5)) A5.setHigh();
    else A5.setLow();

    if (byte & (1 << 4)) A4.setHigh();
    else A4.setLow();

    if (byte & (1 << 3)) A3.setHigh();
    else A3.setLow();

    if (byte & (1 << 2)) A2.setHigh();
    else A2.setLow();

    if (byte & (1 << 1)) A1.setHigh();
    else A1.setLow();

    if (byte & (1 << 0)) A0.setHigh();
    else A0.setLow();  

    bus_e.setLow();  
}

char read(void)
{
    bus_e.setHigh(); //disable device from beginning
    setAPinsInput(); //Set the A pins as output for GPIO;
    dir_w.setLow(); //set direction flowing from B to A in 245.
    bus_e.setLow(); //Enable deivce


    char byte; //delcare the byte

    byte = A0.read(); //begin to read the memory location and set value to byte
    byte = byte | (A1.read() << 1); //Shifting information to byte
    byte = byte | (A2.read() << 2);
    byte = byte | (A3.read() << 3);
    byte = byte | (A4.read() << 4);
    byte = byte | (A5.read() << 5);
    byte = byte | (A6.read() << 6);
    byte = byte | (A7.read() << 7); //Last shifting for info into byte

    bus_e.setHigh(); //Disable the device
    return byte; //return the byte 
}

void setAddr(char byte)
{
    bus_e.setHigh();
    dataOut_w.setLow();
    dataIn_e.setHigh();
    cmd_w.setLow();
    addr_w.setHigh();
    printf("I hate this class: %d", byte);
    write(byte);

    addr_w.setLow();
}

void setDataOut(char byte)
{
    bus_e.setHigh();
    addr_w.setLow();
    dataIn_e.setHigh();
    cmd_w.setLow();

    dataOut_w.setHigh();

    write(byte);

    dataOut_w.setLow();
}

void setCmd(char byte)
{
    bus_e.setHigh();
    addr_w.setLow();
    dataOut_w.setLow();
    dataIn_e.setHigh();
    cmd_w.setHigh();
    printf("CMD: %d", byte);
    write(byte);

    cmd_w.setLow();
}

char getDataIn(void)
{
    char byte;
    bus_e.setHigh();
    addr_w.setLow();
    dataOut_w.setLow();
    cmd_w.setLow();
    dataIn_e.setLow();

    byte = read();

    dataIn_e.setHigh();

    return byte;
}

//main write function
void mov(char destination, char source)
{
    setCmd(DISABLE_PERIPHERALS);
    printf("This is the destination %d\n", destination);
    setAddr(destination);
    setDataOut(source);
    setCmd(START_SRAM_WRITE);
    bus_e.setHigh();
    toggleClock();
    //data has now been moved
}

//main read function
char mov(char destination)
{
    setCmd(DISABLE_PERIPHERALS);
    printf("This is the destination %d", destination);
    setAddr(destination);
    setCmd(START_SRAM_READ);
    bus_e.setHigh();
    toggleClock();
    char byte = getDataIn();
    return byte;   
}*/