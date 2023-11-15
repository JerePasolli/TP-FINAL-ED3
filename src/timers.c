#include "../inc/timers.h"
#include "LPC17xx.h"
#include "lpc17xx_timer.h"

#define PRESCALER 1000000
#define MATCHER 4

void timerConfig(void){
	TIM_TIMERCFG_Type timCfg;								//timer configuration structure
		timCfg.PrescaleOption = TIM_PRESCALE_USVAL;			//prescale in microseconds
		timCfg.PrescaleValue = PRESCALER;					//value in microseconds

	TIM_MATCHCFG_Type matchCfg;								//match channel configuration structure
		matchCfg.ExtMatchOutputType = TIM_EXTMATCH_TOGGLE;	//toggle pin on match
		matchCfg.MatchChannel = 1;							//choose match channel 1
		matchCfg.MatchValue = MATCHER-1;					//match value
		matchCfg.IntOnMatch = DISABLE;						//disable interrupt on match
		matchCfg.ResetOnMatch = ENABLE;						//enable timer reset on match
		matchCfg.StopOnMatch = DISABLE;						//disable timer stop on match

	TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &timCfg);			//initialize timer 0
	TIM_ConfigMatch(LPC_TIM0, &matchCfg);					//configure match channel 1
	TIM_Cmd(LPC_TIM0, ENABLE);								//enable timer 0
    return;
}