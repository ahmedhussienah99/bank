#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#include "stdint.h"
void SystemInit(){}
void initportb(void){
uint32_t delay;
SYSCTL_RCGCGPIO_R |= 0x02;
while((SYSCTL_PRGPIO_R&0X02)==0){}
GPIO_PORTB_DIR_R = 0xFF;
GPIO_PORTB_AMSEL_R =0;
GPIO_PORTB_PCTL_R =0;
GPIO_PORTB_AFSEL_R =0;
GPIO_PORTB_PUR_R = 0xFF;
GPIO_PORTB_DEN_R = 0XFF;
//GPIO_PORTA_CR_R
//GPIO_PORTA_LOCK_R	}
void initportf(void){
uint32_t delay;
SYSCTL_RCGCGPIO_R |= 0x20;
delay=5;
GPIO_PORTF_LOCK_R =0x4C4F434B;
GPIO_PORTF_CR_R =0x1F;
GPIO_PORTF_AMSEL_R =0;
GPIO_PORTF_AFSEL_R =0;
GPIO_PORTF_PCTL_R =0;
GPIO_PORTF_DIR_R = 0x0E;
GPIO_PORTF_DEN_R = 0x1F;
GPIO_PORTF_PUR_R = 0x11;	}
void inituart(void){
uint32_t delay;
SYSCTL_RCGCGPIO_R |= 0x00000001;
delay=5;
SYSCTL_RCGCUART_R |= 0x00000001;
UART1_CTL_R&= ~0X0001;
UART1_IBRD_R=27;
UART1_FBRD_R=8;
UART1_LCRH_R =0x0070;
UART1_CTL_R=0X0301;
GPIO_PORTA_AMSEL_R =0X03;
GPIO_PORTA_PCTL_R =(GPIO_PORTA_PCTL_R&0XFFFFFF00)+0X00000011;
GPIO_PORTA_AFSEL_R |=0X03;
GPIO_PORTA_DEN_R = 0X03;}
char uartin(void){
while((UART1_FR_R&0X0010)==0){};
return ((char)(UART1_DR_R&0XFF));}
void uartout(char data){
while((UART1_FR_R&0X0010)==0){};
UART1_DR_R=data;}
int main()
{
char NumOfRoom,status;
char keypassword[5];
char currentpassword[5]={1,2,3,4};
int col =5,row=5;
int i=0,j,flag=0;
/*	inituart();
uartout(1);
NumOfRoom=uartin();
inituart();
//uartout(0); it will be on pc to put status
status=uartin();*/
while(1){
NumOfRoom=1;
//status=1; //for check code
if(status==0){
initportf();
GPIO_PORTF_DATA_R=0x02;}
else if (status==1){
initportb();
//GPIO_PORTF_DATA_R=0x02;
GPIO_PORTB_DATA_R=0x00000001;
if((GPIO_PORTB_DATA_R & 0x00010000)==1&&i<5){keypassword[i]='1';}
else	if((GPIO_PORTB_DATA_R & 0x00100000)==1&&i<5){keypassword[i]='2';}
else	if((GPIO_PORTB_DATA_R & 0x01000000)==1&&i<5){keypassword[i]='3';}
else	if((GPIO_PORTB_DATA_R & 0x10000000)==1&&i<5){keypassword[i]='A';}
GPIO_PORTB_DATA_R=0x00000010;
if((GPIO_PORTB_DATA_R & 0x00010000)==1&&i<5){	keypassword[i]='4';}
else	if((GPIO_PORTB_DATA_R & 0x00100000)==1&&i<5){keypassword[i]='5';}
else	if((GPIO_PORTB_DATA_R & 0x01000000)==1&&i<5){keypassword[i]='6';}
else	if((GPIO_PORTB_DATA_R & 0x10000000)==1&&i<5){keypassword[i]='B';}
GPIO_PORTB_DATA_R=0x00000100;
if((GPIO_PORTB_DATA_R & 0x00010000)==1){	keypassword[i]='7';}
else	if((GPIO_PORTB_DATA_R & 0x00100000)==1&&i<5){keypassword[i]='8';}
else	if((GPIO_PORTB_DATA_R & 0x01000000)==1&&i<5){keypassword[i]='9';}
else	if((GPIO_PORTB_DATA_R & 0x10000000)==1&&i<5){keypassword[i]='C';}
GPIO_PORTB_DATA_R=0x00001000;
if((GPIO_PORTB_DATA_R & 0x00001000)==1&&i<5){	keypassword[i]='*';}
else	if((GPIO_PORTB_DATA_R & 0x00100000)==1&&i<5){keypassword[i]='0';}
else	if((GPIO_PORTB_DATA_R & 0x01000000)==1&&i<5){keypassword[i]='#';}
else	if((GPIO_PORTB_DATA_R & 0x10000000)==1&&i<5){keypassword[i]='D';}
i++;}
else if(status==2){
initportf();
GPIO_PORTF_DATA_R=0x00;}
if(status==1 && i>4){
for(j=0;j<4;j++){
if(currentpassword[j]==keypassword[j]){
flag++;}
}
}
if(flag==4){
//door open
flag=0; i=0; //reset for another opening door}
}
}
