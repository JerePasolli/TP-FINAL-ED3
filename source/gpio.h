void gpioConfig(void);
void gpioIntConfig(void);

void gpioConfig(void){
    //GPIO configurations, replace X
    LPC_PINCON -> PINSELX |= (X);
    LPC_PINCON -> PINMODEX |= (X);
    LPC_GPIOX -> FIODIR |= (X);

    return;
}


void gpioIntConfig(void){
    //GPIO interrupt configurations, replace X
    LPC_GPIOINT -> IOXIntEnR |= (X);
    LPC_GPIOINT -> IOXIntClr |= (X);
    NVIC_Enable(EINTX_IRQn);

    return;
}