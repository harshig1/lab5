// StepperMotorController.c starter file EE319K Lab 5
// Runs on TM4C123
// Finite state machine to operate a stepper motor.  
// Jonathan Valvano
// January 18, 2019

// Hardware connections (External: two input buttons and four outputs to stepper motor)
//  PA5 is Wash input  (1 means pressed, 0 means not pressed)
//  PA4 is Wiper input  (1 means pressed, 0 means not pressed)
//  PE5 is Water pump output (toggle means washing)
//  PE4-0 are stepper motor outputs 
//  PF1 PF2 or PF3 control the LED on Launchpad used as a heartbeat
//  PB6 is LED output (1 activates external LED on protoboard)

#include "SysTick.h"
#include "TExaS.h"
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

void EnableInterrupts(void);
// edit the following only if you need to move pins from PA4, PE3-0      
// logic analyzer on the real board
#define PA4       (*((volatile unsigned long *)0x40004040))
#define PE50      (*((volatile unsigned long *)0x400240FC))
void SendDataToLogicAnalyzer(void){
  UART0_DR_R = 0x80|(PA4<<2)|PE50;
}
struct State{
	uint8_t out;
	uint8_t next[4];
};

typedef struct State SType_t;


int main(void){ 
  
// you initialize your system here
	
	
	
	SType_t FSM[38] = {
	
	{0x01, {0,1,20,20}},
	{0x02, {2,2,21,21}},
	{0x04, {3,3,22,22}},
	{0x08, {4,4,23,23}},
	{0x10, {5,5,24,24}},
	{0x01, {6,6,25,25}},
	{0x02, {7,7,26,26}},
	{0x04, {8,8,27,27}},
	{0x08, {9,9,28,28}},
	{0x10, {10,10,29,29}},
	{0x08, {11,11,30,30}},
	{0x04, {12,12,31,31}},
	{0x02, {13,13,32,32}},
	{0x01, {14,14,33,33}},
	{0x10, {15,15,34,34}},
	{0x08, {16,16,35,35}},
	{0x04, {17,17,36,36}},
	{0x02, {18,18,37,37}},
	{0x01, {0,0,19,19}},
	{0x21, {1,1,20,20}},
	{0x22, {2,2,21,21}},
	{0x24, {3,3,22,22}},
	{0x28, {4,4,23,23}},
	{0x30, {5,5,24,24}},
	{0x21, {6,6,25,25}},
	{0x22, {7,7,26,26}},
	{0x24, {8,8,27,27}},
	{0x28, {9,9,28,28}},
	{0x30, {10,10,29,29}},
	{0x28, {11,11,30,30}},
	{0x24, {12,12,31,31}},
	{0x22, {13,13,32,32}},
	{0x21, {14,14,33,33}},
	{0x30, {15,15,34,34}},
	{0x28, {16,16,35,35}},
	{0x24, {17,17,36,36}},
	{0x22, {18,18,37,37}},
	{0x21, {0,0,19,19}}
	};
	
	
	int8_t N = 0;
	int8_t input;
	
	volatile int delay;
	
	SYSCTL_RCGCGPIO_R |= 0x11;
	delay = 0;
	GPIO_PORTA_DEN_R |= 0x30;
	GPIO_PORTA_DIR_R &= 0xCF;
	GPIO_PORTE_DEN_R |= 0x3F;
	GPIO_PORTE_DIR_R |= 0x3F;
	
	TExaS_Init(&SendDataToLogicAnalyzer);    // activate logic analyzer and set system clock to 80 MHz
  SysTick_Init(); 
  EnableInterrupts();   
  while(1){
		GPIO_PORTE_DATA_R = FSM[N].out;
		SysTick_Wait1ms(50);
		input = (GPIO_PORTA_DATA_R & 0x30) >> 4;
		N = FSM[N].next[input];
  }
}


