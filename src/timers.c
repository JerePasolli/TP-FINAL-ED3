#include "../inc/timers.h"
#include "LPC17xx.h"
#include "lpc17xx_timer.h"

#define PRESCALER_TIM_0 1000000
#define MATCHER_TIM_0 4
#define PRESCALER_TIM_1 75000
#define MATCHER_TIM_1 2
#define PRESCALER_TIM_2 1000000
#define MATCHER_TIM_2 4

void timerConfig(void){
	TIM_TIMERCFG_Type timCfg0;								//timer configuration structure
	timCfg0.PrescaleOption = TIM_PRESCALE_USVAL;			//prescale in microseconds
	timCfg0.PrescaleValue = PRESCALER_TIM_0;					//value in microseconds

	TIM_MATCHCFG_Type matchCfg0;								//match channel configuration structure
	matchCfg0.ExtMatchOutputType = TIM_EXTMATCH_TOGGLE;	//toggle pin on match
	matchCfg0.MatchChannel = 1;							//choose match channel 1
	matchCfg0.MatchValue = MATCHER_TIM_0-1;					//match value
	matchCfg0.IntOnMatch = DISABLE;						//disable interrupt on match
	matchCfg0.ResetOnMatch = ENABLE;						//enable timer reset on match
	matchCfg0.StopOnMatch = DISABLE;						//disable timer stop on match

	TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &timCfg0);			//initialize timer 0
	TIM_ConfigMatch(LPC_TIM0, &matchCfg0);					//configure match channel 1
	TIM_Cmd(LPC_TIM0, ENABLE);

	TIM_TIMERCFG_Type timCfg1;
	timCfg1.PrescaleOption = TIM_PRESCALE_USVAL;
	timCfg1.PrescaleValue = PRESCALER_TIM_1;

	TIM_MATCHCFG_Type matchCfg1;
	matchCfg1.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
	matchCfg1.MatchChannel = 1;
	matchCfg1.MatchValue = MATCHER_TIM_1-1;
	matchCfg1.IntOnMatch = ENABLE;
	matchCfg1.ResetOnMatch = ENABLE;
	matchCfg1.StopOnMatch = DISABLE;

	TIM_Init(LPC_TIM1, TIM_TIMER_MODE, &timCfg1);
	TIM_ConfigMatch(LPC_TIM1, &matchCfg1);
	NVIC_SetPriority(TIMER1_IRQn,1);
	NVIC_EnableIRQ(TIMER1_IRQn);

	TIM_TIMERCFG_Type timCfg2;
	timCfg2.PrescaleOption = TIM_PRESCALE_USVAL;
	timCfg2.PrescaleValue = PRESCALER_TIM_2;

	TIM_MATCHCFG_Type matchCfg2;
	matchCfg2.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
	matchCfg2.MatchChannel = 1;
	matchCfg2.MatchValue = MATCHER_TIM_2-1;
	matchCfg2.IntOnMatch = ENABLE;
	matchCfg2.ResetOnMatch = ENABLE;
	matchCfg2.StopOnMatch = DISABLE;

	TIM_Init(LPC_TIM2, TIM_TIMER_MODE, &timCfg2);
	TIM_ConfigMatch(LPC_TIM2, &matchCfg2);
	NVIC_SetPriority(TIMER2_IRQn,1);
	NVIC_EnableIRQ(TIMER2_IRQn);

    return;
}
