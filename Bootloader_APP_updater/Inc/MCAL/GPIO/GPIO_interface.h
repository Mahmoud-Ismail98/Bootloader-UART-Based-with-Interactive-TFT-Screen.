/*********************************************************/
/********** Author 		: Mahmoud Korayem ****************/
/********** Date        : 19 AUG 2020     ****************/
/********** version     : V 01			  ****************/
/********** Description : GPIO_interface.c***************/
/*********************************************************/

#ifndef  GPIO_INTERFACE_H
#define  GPIO_INTERFACE_H

#define     GPIO_HIGH  1
#define     GPIO_LOW   0

#define    PULLUP_SELECT   1
#define    PULLDOWN_SELECT 0

#define     GPIOA      0 
#define     GPIOB      1 
#define     GPIOC      2 

#define     PIN0       0 
#define     PIN1       1 
#define     PIN2       2 
#define     PIN3       3 
#define     PIN4       4 
#define     PIN5       5 
#define     PIN6       6 
#define     PIN7       7 
#define     PIN8       8 
#define     PIN9       9 
#define     PIN10      10
#define     PIN11      11
#define     PIN12      12
#define     PIN13      13
#define     PIN14      14
#define     PIN15      15

#define     INPUT_ANALOG_               0b0000  
#define     INPUT_FLOAT                 0b0100 
#define     INPUT_PULL_UP_DOWEN         0b1000
									    
#define     OUTPUT_SPEED_10MHZ_PP       0b0001  
#define     OUTPUT_SPEED_10MHZ_OD       0b0101 
#define     OUTPUT_SPEED_10MHZ_AFPP     0b1001
#define     OUTPUT_SPEED_10MHZ_AFOD     0b1101
									    
#define     OUTPUT_SPEED_2MHZ_PP        0b0010  
#define     OUTPUT_SPEED_2MHZ_OD        0b0110 
#define     OUTPUT_SPEED_2MHZ_AFPP      0b1010
#define     OUTPUT_SPEED_2MHZ_AFOD      0b1110
									    
#define     OUTPUT_SPEED_50MHZ_PP       0b0011
#define     OUTPUT_SPEED_50MHZ_OD       0b0111
#define     OUTPUT_SPEED_50MHZ_AFPP     0b1011
#define     OUTPUT_SPEED_50MHZ_AFOD     0b1111




void MGPIO_voidSetPinDirection(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Mode);
void MGPIO_voidSetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Value);
u8   MGPIO_u8GetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin);













#endif
