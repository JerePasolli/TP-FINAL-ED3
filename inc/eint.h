uint8_t interruptAid;
void extIntConfig(void);
void EINTX_IRQHandler(void);
void EINT3_IRQHandler(void);

//external intererupt setup
void extIntConfig(void){
    LPC_PINCON -> PINSELX |= (X);
    LPC_SC -> EXTMODEX |= (X);
    LPC_SC -> EXTPOLARX |= (X);
    LPC_SC -> EXTINTX |= 1; //clearing flag
    NVIC_Enable(EINTX_IRQn); //enable
    return;
}

//external interrupt on EINTX
void EINTX_IRQHandler(void){
    //insert code
    LPC_GPIOINT -> IOXIntClr |= (X); //clearing flag
    return;
}

//gpio interrupting on EINT3
void EINT3_IRQHandler(void){
    //insert code
    LPC_GPIOINT -> IO0IntClr |= (X); //clearing flag
    return;
}