#include "header.h"

volatile byte FSM_wake = 0;

void setup() {
    Serial.begin(115200);
    Serial.println("Begin");
    Serial.flush();
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(EXTpin,INPUT);
    pinMode(LAMP0pin,OUTPUT);
    pinMode(LAMP1pin,OUTPUT);

//Teste
    contexto[0].setPlanta("alface");
    contexto[0].setLampada(1);
    contexto[0].setTempoPlanta(6);
    contexto[0].setLampStats(false);
}

void loop() {
    static unsigned long utc = 1493769600;
    static bool podeContarTempo = false;
    static float LDRVoltage;
    float ThrVoltage = 2.0;
    static byte timeCountData;
    static byte timeCountLDR;
    tm localTime;
    tm horarioInicial;
    
    /*How was uC woken? Ext int or WDT?*/

    if(localTime.hora == 0 && localTime.minu == 0 && localTime.seg == 3){podeContarTempo = false;}

    Serial.print("updata");
    Serial.flush();
    bool lampStateAux[N_OF_LAMPS];

    for (int i = 0; i < N_OF_LAMPS; ++i)
    {
      //Updates lightbulb status
      if(podeContarTempo == true){
          int tempoPercorrido = (localTime.minu) - (horarioInicial.minu); 
            int tempoIdeal = contexto[i].getTempoPlanta();
            contexto[i].setLampStats(acendeLampada(&tempoPercorrido, &tempoIdeal, &LDRVoltage, &ThrVoltage));
      }

      lampStateAux[i] = contexto[i].getLampStats();
      updateData(lampStateAux);
    }

    //Serial.println("FSM att ldr");
    LDRVoltage = analogRead(A0)*(5.0/1023.0);

    //Serial.println(LDRVoltage);

    //Updates lightbulb status
    if(podeContarTempo == true){
        for (int i = 0; i < 2; ++i)
        {
            int tempoPercorrido = (localTime.minu) - (horarioInicial.minu); 
            int tempoIdeal = contexto[i].getTempoPlanta();
            contexto[i].setLampStats(acendeLampada(&tempoPercorrido, &tempoIdeal, &LDRVoltage, &ThrVoltage));
            //Serial.print("A lamp ");Serial.print(i);Serial.print(" esta ");
            //Serial.println(contexto[i].getLampStats(), DEC);
        }
    } 

    //Updates daily initial time
    //UNCOMENT
    if (podeContarTempo == false && (LDRVoltage <= ThrVoltage || (localTime.minu == 0 && localTime.seg > 9) ) ){
    podeContarTempo = true;
    utcToTime(&horarioInicial, &utc);
    //Serial.println("Tempo contando!\t");
    }
        PowerDown();
    };
}
