#ifndef _NSC_MAIN_H
#define _NSC_MAIN_H

#include "stm32l1xx.h"
#include "nc_defines.h"
#endif

void init_GPIO(void);
void init_DAC(void);

int main(void){
    unsigned int i, output;
	  
		init_GPIO();
		init_DAC();
	
	  output = 0;
	
	  while(1){
		    DAC->DHR12R1 = output;             /* Channel 1 12-bit right-aligned data. Check that "=" isn't "|=". */
        DAC->DHR12R2 = output;             /* Channel 2 12-bit right-aligned data. Check that "=" isn't "|=". */

			  /* Set software flags. Hardware clears the flags once DAC_DHRx is copied to DAC_DORx. */
        DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG1 | DAC_SWTRIGR_SWTRIG2;

        for(i = 0; i <= 10; i++);           /* Software delay */

        output++;                           /* Increment the DAC analog output voltage */

        if(output >= 0xFFF) output = 0;		
		}
}

void init_GPIO(){
	  RCC->AHBENR |= RCC_AHBENR_GPIOAEN; /* Enable GPIOA clock. */

    GPIOA->MODER &= ~(0x0F << (2*4));  /* Clear MODER4 mode for bits 4 and 5. */ 
    GPIOA->MODER |= 0x0F << (2*4);     /* Set 11: Analog mode. */
}

void init_DAC(){                             /* DAC_OUT1 = PA.4, DAC_OUT2 = PA.5 */
    RCC->APB1ENR |= RCC_APB1ENR_DACEN;       /* Enable DAC clock. */

    DAC->CR |= DAC_CR_BOFF1 | DAC_CR_BOFF2;  /* Enable DAC output buffers BOFF1 and BOFF2. */

    DAC->CR |= DAC_CR_TEN1 | DAC_CR_TEN2;    /* Enable DAC triggers for channels 1 and 2. */
	
	  DAC->CR |= DAC_CR_TSEL1 | DAC_CR_TSEL2;  /* Select 101: Timer 4 TRGO event. */
	
	  DAC->CR |= DAC_CR_EN1 | DAC_CR_EN2;      /* Enable DAC converters 1 and 2. */
}
