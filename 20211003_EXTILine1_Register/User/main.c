#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
void GPIO_Configure(){
	//Cap enable port A
	RCC -> APB2ENR |= 0x04; 
	//Chan PA0 duoc keo xuyong thap 
	GPIOA -> CRL  |= 0xFF0FFFFF;
	//Cau hinh cho Mode va Toc do 
	GPIOA -> CRL  |= 0x00300000;
}
void EXTI_Configure(){
	//cap clock cho AFIO hoat dong
	RCC -> APB2ENR |= 0x01;
	//Port haot dong la port nao 
	AFIO -> EXTICR[0] = 0x10;
	//clear Co ngat trong thanh ghi PR 
	EXTI -> PR    = 0x02;
	// Cau hinh cho canh xuong xung clk = 1
	EXTI -> FTSR  |= 0x02;
	//Canh len = 0 
	EXTI -> RTSR  = 0x00;
	//Cau hinh cho Sortware event interrupt
	EXTI -> SWIER = 0x00;
	//Cau hinh cho Interrupt mask register
	EXTI -> IMR  |= 0x02;
	// cau hinh cho Event mask registr =-0 
	EXTI -> EMR  = 0x00;
	//cau hinh ngat trong core
	NVIC -> ISER[0] = 0x80;
}
void delay(int time){
	for(int i = 0; i< time; i++){
		for(int j = 0; j< 0x2AFF; j++);
	}
}
void EXTI1_IRQHandler(){
	if((EXTI -> PR) == 0x02 && (EXTI -> IMR) == 0x02){
		EXTI -> PR = 0x02;
		GPIOA -> ODR  |= 0x0020;
		delay(100);
		GPIOA -> ODR  &= ~(0x0020);
		delay(100);		
	}
}
int main(){
	GPIO_Configure();
	EXTI_Configure();
	while(1){
	}
}