/*
 * Functions: ISR WDT, ISR extINT, LDRVoltageUpdt, PowerDown, utcToSeg
*/

ISR(INT0_vect){
    FSM_wake |= (1 << BUT_PRESS_bit);
    Serial.println("ext int!");
    }

ISR(WDT_vect){
    FSM_wake |= (1 << SEC_INCR_bit);
  }

bool acendeLampada(int* tempoPercorrido, int* tempoIdeal, float* LDRVoltage, float*ThrVoltage){
	bool retorno;
	
	if((*tempoPercorrido <= *tempoIdeal) && (*LDRVoltage > *ThrVoltage)){
		retorno = true;
	} else {
		retorno = false;
	}
	return retorno;
}

/*
 * Update LDR input voltage
 */
void LDRVoltageUpdt(float* LDRVoltage){
	*LDRVoltage = 5.0*analogRead(LDRPin)/1023.0;
}

/*
 * Enable pullup on unused pins
 */
void PowerDown(){
    Serial.println("Going to sleep...");
    Serial.end();
    /* 
     * Power Reduction Register
     * Disable I2C, Timer 2, Timer 1, SPI, USART and ADC
     * See how to reinitialize USART
     */
    noInterrupts();
    PRR = (1 << PRTWI0) | (1 << PRTIM2) | (1 << PRTIM1) | (1 << PRTIM0) | (1 << PRSPI0) | (0 << PRUSART0) | (1 << PRADC);
    interrupts();
    /*
     * Sleep Mode Control Register
     * Set Power Down Mode
     * SE = Sleep Enable 
     * After wake up, program re-starts after __asm__
     */
    SMCR = (0 << SM2) | (1 << SM1) | (0 << SM0);
    SMCR |= 1 << SE;
    __asm__ __volatile__ ( "sleep" "\n\t" :: );
    SMCR &= ~(1 << SE);
    Serial.begin(9600);
    Serial.println("\nWaking up...");
    }

    //(*localTime).ano é igual a localTime->ano
//31557600=365.25 dias no ano.  31536000=365*24*3600.    31622400=366*24*3600

void utcToTime(tm *localTime, unsigned long* utc){

    unsigned long segUtc;
    unsigned long anoTemp; 
    unsigned int diaDoAno;        //Bit 15 é 0 se ano n for bissexto, 1 se ano for bissexto
    byte anoBissexto = 0;
    byte anoNoOffset;
    byte diaDoMes;
    byte mesTeste;
    byte hora;
    byte minu;
    byte seg;
    static const unsigned int diasDesde1Jan[2][13]=
        {
            {0,31,59,90,120,151,181,212,243,273,304,334,365}, 
            {0,31,60,91,121,152,182,213,244,274,305,335,366}  
        };

    //Vendo se o ano é bissexto e dividindo pelo tempo certo.
    //Se a divisão do ano por 4 n for 0, ano não é bissexto
    //Bit 15 é 0 se ano n for bissexto, 1 se ano for bissexto
    anoNoOffset = (*utc / 31557600);

    for(anoTemp = 1970; anoTemp <= (anoNoOffset+1970); anoTemp++){
        if((anoTemp % 4) == 0){
            anoBissexto++;
        }
    }

    if( ((anoNoOffset+1970) % 4) != 0){

        anoNoOffset = (*utc / 31536000);
        segUtc = *utc % 31536000;
        diaDoAno = (segUtc / 86400) - anoBissexto;
        diaDoAno &= ~(1<<15);
    
    } else {

        anoNoOffset = (*utc / 31622400);
        segUtc = *utc % 31622400;
        diaDoAno = (segUtc / 86400) - anoBissexto;
        diaDoAno |= (1<<15);
      
    }

    //Calculando dia do ano, mês e dia do mês
   
    for(mesTeste = 1 ; mesTeste < 13 ; mesTeste++){
        if(diaDoAno < diasDesde1Jan[bitRead(diaDoAno,15)][mesTeste]){
            diaDoMes = (diaDoAno & ~(1<<15)) - diasDesde1Jan[bitRead(diaDoAno,15)][mesTeste - 1] + 1;
            break;
        }
    }
  
    segUtc %= 86400;                       //De segundos para dias
    hora = segUtc / 3600;
    segUtc %= 3600;                        //De dias para horas
    minu = segUtc / 60;
    segUtc %= 60;                          //De horas para minutos
    
    localTime->ano = anoNoOffset - 30;  //Últimos dois dígitos, considerando os primeiros como 
    localTime->mes = mesTeste;
    localTime->diaDoAno = diaDoAno & ~(1<<15);
    localTime->diaDoMes = diaDoMes;
    localTime->hora = hora;
    localTime->minu = minu;
    localTime->seg = segUtc;
}
