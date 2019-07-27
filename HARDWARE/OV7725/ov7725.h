#ifndef _OV7725_H
#define _OV7725_H
#include "sys.h"
#include "sccb.h"


#define OV7725_MID				0X7FA2    
#define OV7725_PID				0X7721
 
#define OV7725_VSYNC  	PAin(8)			//ͬ���źż��IO
#define OV7725_WRST		PBout(7)		//дָ�븴λ
#define OV7725_WREN		PGout(9)		//д��FIFOʹ��
#define OV7725_RCK_H	GPIOA->BSRRL=1<<6//���ö�����ʱ�Ӹߵ�ƽ
#define OV7725_RCK_L	GPIOA->BSRRH=1<<6	//���ö�����ʱ�ӵ͵�ƽ
#define OV7725_RRST		PAout(4)  		//��ָ�븴λ
#define OV7725_CS		PGout(15)  		//Ƭѡ�ź�(OE)

			  /*bit 6789->bit 0123*/         /*bit 11->bit 4*/
#define OV7725_DATA   ((GPIOC->IDR&0x03C0)>>6) | ((GPIOC->IDR&0x0800)>>7)| \
		       ((GPIOB->IDR&0x0040)>>1 | ((GPIOE->IDR&0x0060)<<1))					//��������˿�
			/*bit 6->bit 5*/            /*bit 56->bit 67*/

	    				 
u8   OV7725_Init(void);	
void EXTI8_Init(void);
void OV7725_Contrast(u8 contrast);
void OV7725_Special_Effects(u8 eft);
void OV7725_Color_Saturation(u8 sat);
void OV7725_Window_Set(u16 width,u16 height,u8 mode);

#endif




















