/*
https://visualgdb.com/tutorials/arm/stm32/timers/
*/

#include "stm32f4_discovery.h"
#include "stm32f4xx_conf.h"

void init_leds(){
  // RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; // enable the clock to GPIOD

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  GPIO_InitTypeDef GPIO_InitDef;
  GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
  GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitDef.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_Init(GPIOD, &GPIO_InitDef);
}

void init_timer(){
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  TIM_TimeBaseInitTypeDef timerInitStructure;
  timerInitStructure.TIM_Prescaler = 40000;
  timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  timerInitStructure.TIM_Period = 500;
  timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  timerInitStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &timerInitStructure);
  TIM_Cmd(TIM2, ENABLE);

}

int main(){

  init_leds();
  init_timer();
  while (1){
    int timerValue = TIM_GetCounter(TIM2);
    if(timerValue == 400){
      // GPIOD->ODR |= (1 << 13); // equivalent below
      GPIO_WriteBit(GPIOD, GPIO_Pin_13, Bit_SET);
    }else if(timerValue == 500){
      // GPIOD->ODR &= ~(1 << 13); // equivalent below
      GPIO_WriteBit(GPIOD, GPIO_Pin_13, Bit_RESET);
    }
  }
}
