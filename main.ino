#include "header.h"

volatile byte FSM_wake = 0;

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(EXTpin,INPUT);
    pinMode(LAMP0pin,OUTPUT);
    pinMode(LAMP1pin,OUTPUT);
    
    noInterrupts();
//Setting External Interrupt INT0 - D2
//If D3 is used, chage bits to ISC11 and ISC10 =0
    EICRA &= ~((1<<ISC11) | (1<<ISC10) | (1<<ISC01) | (1<<ISC00));
    EIMSK |= 1 << INT0;

//Configurando Watchdog. Para zerar, usar &. Para setar, usar |
    /* Clear the reset flag. */
    MCUSR   &=  ~(1<<WDRF);
    WDTCSR  |=  (1 << WDCE) | (1<<WDE);
    WDTCSR  =   (0 << WDE) | (0 << WDP3) | (1 << WDP2) | (1 << WDP1) | (0 << WDP0);
    WDTCSR  |=  (1 << WDIE);
    interrupts();


//Teste
    contexto[0].setPlanta("alface");
    contexto[0].setLampada(0);
    contexto[0].setTempoPlanta(3);
    contexto[0].setLampStats(false);
}

void loop() {
    static unsigned long utc = 1493769600;
    static byte FSM_sec = 0;
    static bool podeContarTempo = false;
    float LDRVoltage = 0;
    float ThrVoltage = 2.0;
    static byte timeCountData;
    static byte timeCountLDR;
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

            /*Increment timeCountData and timeCountLDR. Both in mins*/
            if (localTime.seg == 1){
                timeCountData++;
                timeCountLDR++;
                Serial.print("timeCountData=");Serial.print(timeCountData);
                Serial.print("\t timeCountLDR=");Serial.println(timeCountLDR);
            }

            /*Turn on timeCountData and timeCountLDR*/
            if(timeCountData-1 >= UPDT_RATE){
                FSM_sec |= (1 << UPDT_DATA_bit);
                timeCountData = 1;
                Serial.println("Atualizacao dados!");
            }else if(timeCountLDR-1 >= UPDT_LDR){
                FSM_sec |= (1 << UPDT_LDR_bit);
                timeCountLDR = 1;
                Serial.println("Atualizacao LDR!");
            }else if(timeCountLDR-1 >= UPDT_LDR && timeCountData-1 >= UPDT_RATE){
                FSM_sec |= (1 << UPDT_DATA_bit);
                FSM_sec |= (1 << UPDT_LDR_bit);
                timeCountLDR = 1;
                timeCountData = 1;
                Serial.println("Atualizacao de tudOOO!");
            }

      //TO DEBUG:
      //if(localTime.hora == 0 && localTime.minu == 0 && localTime.seg == 3){podeContarTempo = false;}
            if(localTime.hora == 0){podeContarTempo = false;}

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
                    bool lampStateAux[N_OF_LAMPS];

                    for (int i = 0; i < N_OF_LAMPS; ++i)
                    {
                      //Updates lightbulb status
                      if(podeContarTempo == true){
                          int tempoPercorrido = (localTime.hora*60 + localTime.minu) - (horarioInicial.hora*60 + horarioInicial.minu); 
                          int tempoIdeal = contexto[i].getTempoPlanta();
                          contexto[i].setLampStats(acendeLampada(&tempoPercorrido, &tempoIdeal, &LDRVoltage, &ThrVoltage));
                      }

                      lampStateAux[i] = contexto[i].getLampStats();
                      updateData(lampStateAux);
                    }

                break;
                case SEC_INCR_AND_UPDT_LDR:
                    Serial.println("FSM att ldr");
                    FSM_sec &= ~(1 << UPDT_LDR_bit);
                    LDRVoltage = analogRead(A0)*(5.0/1023.0);

                    Serial.println(LDRVoltage);

                    //Updates lightbulb status
                    if(podeContarTempo == true){
                        for (int i = 0; i < N_OF_LAMPS; ++i)
                        {
                            int tempoPercorrido = (localTime.hora*60 + localTime.minu) - (horarioInicial.hora*60 + horarioInicial.minu); 
                            int tempoIdeal = contexto[i].getTempoPlanta();
                            contexto[i].setLampStats(acendeLampada(&tempoPercorrido, &tempoIdeal, &LDRVoltage, &ThrVoltage));
                            Serial.print("A lamp ");Serial.print(i);Serial.print(" esta ");
                            Serial.println(contexto[i].getLampStats(), DEC);
                        }
                    }                    
                break;
                default:
                break;
            }

            //Updates daily initial time
            //UNCOMENT
            if (podeContarTempo == false && (LDRVoltage <= ThrVoltage || localTime.hora >= 10) ){
                podeContarTempo = true;
                utcToTime(&horarioInicial, &utc);
                Serial.println("Tempo contando!\t");
            }

        break; 
        case BUT_PRESS_AND_SEC_INC:
            utc++;
            FSM_wake &= ~(1 << SEC_INCR_bit);
        case BUT_PRESS:
            //Clear bit
            //Turn on backlight & set bit
            //Send data foward
            FSM_wake &= ~(1 << BUT_PRESS_bit);
            
        break;
        default:
            PowerDown();
        break;
        PowerDown();
    };
}
