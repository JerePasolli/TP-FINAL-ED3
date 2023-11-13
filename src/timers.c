#include <../inc/timers.h>
#include "LPC17xx.h"
#include "lpc17xx_timer.h"

#define PRESCALER 1000000
#define MATCHER 4
#define MATCHER2 3

void timerConfig(void){

	TIM_TIMERCFG_Type timCfg;
		timCfg.PrescaleOption = TIM_PRESCALE_USVAL;
		timCfg.PrescaleValue = PRESCALER;

	TIM_MATCHCFG_Type matchCfg;
		matchCfg.ExtMatchOutputType = TIM_EXTMATCH_TOGGLE;
		matchCfg.IntOnMatch = DISABLE;
		matchCfg.MatchChannel = 1;
		matchCfg.MatchValue = MATCHER-1;
		matchCfg.ResetOnMatch = ENABLE;
		matchCfg.StopOnMatch = DISABLE;

	TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &timCfg);
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
		NVIC_SetPriority(TIMER1_IRQn, 0);
		NVIC_EnableIRQ(TIMER1_IRQn);


    return;
}
