#include "SRAM.h"


char DISABLE_PERIPHERALS = 0; //sends 0 to cmd register to disable student design
char START_SRAM_READ = 9; //Pass in 9 so binary values get passed to student design. 0001001
char START_SRAM_WRITE = 17; //Pass 17 to right so binary value, 0010001. 


GPIO A0(P1_29);
GPIO A1(P1_28);
GPIO A2(P1_23);
GPIO A3(P1_22);
GPIO A4(P1_20);
GPIO A5(P1_19);
GPIO A6(P0_30);
GPIO A7(P0_29);
//End of Port A pins being set global

//Set Port B pins as global
GPIO dir_w(P0_0);
GPIO bus_e(P0_1);
GPIO addr_w(P2_1);
GPIO dataOut_w(P2_2);
GPIO dataIn_e(P2_3);
GPIO cmd_w(P2_4);
GPIO clk(P2_6);



//End of Port B pins being set global
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
{ //Sets A pins at Output since 245 is bidirectional
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
{ //Sets A pins as input since 245 is bidirectional. 
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
}