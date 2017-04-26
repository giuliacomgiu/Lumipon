#include "header.h"

volatile byte FSM_wake = 0;
static byte FSM_sec = 0;

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    
    noInterrupts();
    //Configurando Watchdog. Para zerar, usar &. Para setar, usar |
    /* Clear the reset flag. */
    MCUSR   &=  ~(1<<WDRF);
    WDTCSR  |=  (1 << WDCE) | (1<<WDE);
    WDTCSR  =   (0 << WDE) |(0 << WDP3) | (1 << WDP2) | (1 << WDP1) | (0 << WDP0);
    WDTCSR  |=  (1 << WDIE);
    interrupts();
    l1.setPlanta("alface");
    l1.setLampada(1);
    l1.setTempoPlanta(2);
    l1.setTempoPercorrido();
    l1.setTempoPercorrido();
}

void loop() {
    static unsigned long utc = 1483228800;
    float LDRVoltage;
    byte timeCountData;
    byte timeCountLDR;
    tm localTime;
    
    /*How was uC woken? Ext int or WDT?*/
    switch(FSM_wake){
        case SEC_INCR:
            utc++;
            Serial.println(localTime.seg);
            utcToTime(&localTime, &utc);
            FSM_wake &= ~(1 << SEC_INCR_bit);

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
        break;
        switch(FSM_sec){
            case SEC_INCR_AND_UPDT_DATA:
            /*
             * Call utc to time func
             * Update data
             */
                FSM_sec &= ~(1 << UPDT_DATA_bit);
                utcToTime(&localTime, &utc);
            break;
            case SEC_INCR_AND_UPDT_LDR:
                FSM_sec &= ~(1 << UPDT_LDR_bit);
                LDRVoltageUpdt(&LDRVoltage);
            break;
            case SEC_INCR_AND_UPDT_DATA_AND_LDR:
                FSM_sec &= ~((1 << UPDT_LDR_bit) | (1 << UPDT_DATA_bit));
                LDRVoltageUpdt(&LDRVoltage);
            break;
            default:
            break;
        } 
        default:
            PowerDown();
        break;
        PowerDown();
    };
}
