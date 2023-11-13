#include <../inc/timers.h>
#include "LPC17xx.h"
#include "lpc17xx_timer.h"

#define PRESCALER 1000000
#define MATCHER 4
#define MATCHER2 5

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

	TIM_MATCHCFG_Type matchCfg;
		matchCfg.ExtMatchOutputType = TIM_EXTMATCH_TOGGLE;
		matchCfg.IntOnMatch = DISABLE;
		matchCfg.MatchChannel = 1;
		matchCfg.MatchValue = MATCHER-1;
		matchCfg.ResetOnMatch = ENABLE;
		matchCfg.StopOnMatch = DISABLE;

	TIM_Init(LPC_TIM0, TIM_TIMER_MODE, (void*) &timCfg);
	TIM_ConfigMatch(LPC_TIM0, &matchCfg);
	TIM_Cmd(LPC_TIM0, ENABLE);

	TIM_TIMERCFG_Type timCfg2;
		timCfg2.PrescaleOption = TIM_PRESCALE_USVAL;
		timCfg2.PrescaleValue = PRESCALER;

	TIM_MATCHCFG_Type matchCfg2;
		matchCfg2.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
		matchCfg2.IntOnMatch = ENABLE;
		matchCfg2.MatchChannel = 1;
		matchCfg2.MatchValue = MATCHER2-1;
		matchCfg2.ResetOnMatch = ENABLE;
		matchCfg2.StopOnMatch = DISABLE;

		TIM_Init(LPC_TIM1, TIM_TIMER_MODE, &timCfg2);
		TIM_ConfigMatch(LPC_TIM1, &matchCfg2);
		TIM_Cmd(LPC_TIM1, ENABLE);
		TIM_ClearIntPending(LPC_TIM1, TIM_MR1_INT);
		//NVIC_SetPriority(TIMER1_IRQn,5);
		NVIC_EnableIRQ(TIMER1_IRQn);


    return;
}
