// #include <stdio.h>
// #include "utilities.h"
// #include "io.hpp"
// #include "gpio.hpp"
// #include "SRAM.h"

// bool sw1 = SW.getSwitch(1);
// bool sw2 = SW.getSwitch(2);
// bool sw3 = SW.getSwitch(3);


// int main(void){
// 	printf("Lab 2: SRAM Read/Write \n");
// 	printf("By: Akash Vachhani");
// 	printf("... Program initializing");
// 	delay_ms(2000);
// 	initialize();
// 	int choice = 5;
// 	while(1){
// 		initialize();
// 		printf("******* Menu ********\n");
// 		printf("1) Write\n");
// 		printf("2) Read\n");
// 		printf("3) Exit");
// 		while(choice!= 1 && choice != 2 && choice != 3){
// 			sw1 = SW.getSwitch(1);
// 			sw2 = SW.getSwitch(2);
// 			sw3 = SW.getSwitch(3);
// 			if(sw1){
// 				choice = 1;
// 			}
// 			if(sw2){
// 				choice = 2;
// 			}
// 			if(sw3){
// 				choice = 3;
// 			}

// 		}
// 		if(choice == 1){
// 		    char mem_location;
//             char data;
//             printf("Which memory location do you want to read from?\n");
//             getchar();
//             getchar();
//             scanf("%d", &mem_location);
//             data = mov(mem_location);
//             int i_data = data;
//             LD.setNumber(i_data);

//             printf("This is shit: %i", i_data);
//            	choice = 5;
// 		}
// 		if(choice == 2){
// 	        char mem_location;
//             char data;
//             printf("Which memory location do you want to read from?\n");
//             getchar();
//             getchar();
//             scanf("%d", &mem_location);
//             data = mov(mem_location);
//             int i_data = data;
//             LD.setNumber(i_data);

//             printf("This is shit: %i", i_data);
//           	choice = 5;
// 		}
// 		if(choice == 3){
// 			return 0;
// 		}

// 	}
// }