#include <../inc/timers.h>
#include "LPC17xx.h"
#include "lpc17xx_timer.h"

#define PRESCALER 1000000
#define MATCHER 4

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

	TIM_Init(LPC_TIM0, TIM_TIMER_MODE, (void*) &timCfg);
		TIM_ConfigMatch(LPC_TIM0, &matchCfg);
		TIM_Cmd(LPC_TIM0, ENABLE);

    return;
}
