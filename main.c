#include "stm32l1xx.h"

int main(void){
    unsigned int i, output;
	  
	  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	
    RCC->APB1ENR |= RCC_APB1ENR_DACEN;

    GPIOA->MODER &= ~(0x0F << (2*4));
    GPIOA->MODER |= 0x0F << (2*4);
	
    DAC->CR |= DAC_CR_BOFF1 | DAC_CR_BOFF2;

    DAC->CR |= DAC_CR_TEN1 | DAC_CR_TEN2;
	
	  DAC->CR |= DAC_CR_TSEL1 | DAC_CR_TSEL2;
	
	  DAC->CR |= DAC_CR_EN1 | DAC_CR_EN2;
	
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
	
	  return 0;
}
