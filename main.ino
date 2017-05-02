#include "header.h"

volatile byte FSM_wake = 0;

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(EXTpin,INPUT);
    
    noInterrupts();
//Setting External Interrupt INT0 - D2
//If D3 is used, chage bits to ISC11 and ISC10 =0
//    EICRA &= ~((1<<ISC11) | (1<<ISC10) | (1<<ISC01) | (1<<ISC00));
//    EIMSK |= 1 << INT0;

//Configurando Watchdog. Para zerar, usar &. Para setar, usar |
    /* Clear the reset flag. */
    MCUSR   &=  ~(1<<WDRF);
    WDTCSR  |=  (1 << WDCE) | (1<<WDE);
    WDTCSR  =   (0 << WDE) |(0 << WDP3) | (1 << WDP2) | (1 << WDP1) | (0 << WDP0);
    WDTCSR  |=  (1 << WDIE);
    interrupts();

//Teste
    contexto[0].setPlanta("alface");
    contexto[0].setLampada(1);
    contexto[0].setTempoPlanta(2);
}

void loop() {
    static unsigned long utc = 1493313620;
    static byte FSM_sec = 0;
    static bool podeContarTempo = false;
    float LDRVoltage;
    float ThrVoltage = 2.0;
    byte timeCountData;
    byte timeCountLDR;
    tm localTime;
    tm horarioInicial;
    
    /*How was uC woken? Ext int or WDT?*/
    switch(FSM_wake){
        case SEC_INCR:
            utc++;
            utcToTime(&localTime, &utc);
            FSM_wake &= ~(1 << SEC_INCR_bit);
            Serial.print(localTime.hora);Serial.print(":");Serial.print(localTime.minu);
            Serial.print(":");Serial.println(localTime.seg);

            /*Turn on timeCountData and timeCountLDR*/
            if(timeCountData >= UPDT_RATE){
                FSM_sec |= (1 << UPDT_DATA_bit);
                timeCountData = 0;
            }else if(timeCountLDR >= UPDT_LDR){
                FSM_sec |= (1 << UPDT_LDR_bit);
                timeCountLDR = 0;
            }else if(timeCountLDR >= UPDT_LDR && timeCountData >= UPDT_RATE){
                FSM_sec |= (1 << UPDT_DATA_bit);
                FSM_sec |= (1 << UPDT_LDR_bit);
                timeCountLDR = 0;
                timeCountData = 0;
            }

            /*Increment timeCountData and timeCountLDR. Both in mins*/
            if (localTime.seg == 0){
                timeCountData++;
                timeCountLDR++;
            }
            switch(FSM_sec){
                case SEC_INCR_AND_UPDT_DATA_AND_LDR:
                /*
                 * Fall through. First updates data,
                 * on the next interrupt, 1 sec later,
                 * the FSM_sec still wont have a 0 on
                 * the UPDT_LDR_bit, so it will
                 * update the LDR!
                 */
                case SEC_INCR_AND_UPDT_DATA:
                /*
                 * Call utc to time func
                 * Update data
                 */
                    FSM_sec &= ~(1 << UPDT_DATA_bit);

                    //Updates lightbulb status
                    if(podeContarTempo == true){
                        for (int i = 0; i < 2; ++i)
                        {
                            int tempoPercorrido = (localTime.hora*60 + localTime.minu) - (horarioInicial.hora*60 + horarioInicial.minu); 
                            int tempoIdeal = contexto[i].getTempoPlanta();
                            contexto[i].setLampStats(acendeLampada(&tempoPercorrido, &tempoIdeal, &LDRVoltage, &ThrVoltage));
                        }
                        if(localTime.hora == 0){podeContarTempo = false;}
                    }
                break;
                case SEC_INCR_AND_UPDT_LDR:
                    FSM_sec &= ~(1 << UPDT_LDR_bit);
                    LDRVoltageUpdt(&LDRVoltage);

                    //Updates daily initial time
                    if ((podeContarTempo == false && LDRVoltage > ThrVoltage) || (localTime.hora > 10) ){
                        podeContarTempo = true;
                        utcToTime(&horarioInicial, &utc);
                    }

                    //Updates lightbulb status
                    if(podeContarTempo == true){
                        for (int i = 0; i < 2; ++i)
                        {
                            int tempoPercorrido = (localTime.hora*60 + localTime.minu) - (horarioInicial.hora*60 + horarioInicial.minu); 
                            int tempoIdeal = contexto[i].getTempoPlanta();
                            contexto[i].setLampStats(acendeLampada(&tempoPercorrido, &tempoIdeal, &LDRVoltage, &ThrVoltage));
                        }
                        if(localTime.hora == 0){podeContarTempo = false;}
                    }                    
                break;
                default:
                break;
            }
        break; 
        case BUT_PRESS:
            //Clear bit
            //Turn on backlight & set bit
            //Send data foward
        break;
        default:
            PowerDown();
        break;
        PowerDown();
    };
}
