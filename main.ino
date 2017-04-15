#include "header.h"

unsigned long utc = 1483228800;
volatile byte FSM_wake = 0;
byte minPassed = 0;

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
}

void loop() {
    tm localTime;
    
    PowerDown();
    switch(FSM_wake){
        case SEC_INCR:
            /*
             * Call utc to time func
             * If 5 min passed, update data
             * Else, do nothing. For now
            */
            utcToTime(&localTime);
            FSM_wake &= ~(1 << SEC_INCR_bit);
            if(localTime.minu - minPassed >= UPDT_RATE){
                //Get data
                Serial.print(UPDT_RATE); Serial.println(" minute(s) passed.");
                minPassed = localTime.minu;
                }
        break;
        };
}
