#define OCIEA 1
#define secIncreased 0x00

unsigned long utc = 1483228800;
volatile byte aux = 0;

ISR(TIMER2_COMPA_vect){
    utc++;
    aux |= (1 << secIncreased);
    }

void setup() {
    //VETOR -> TIMER2_COMPA
    //TIFR2.OCFA É 1 se interrupção habilitada e cmp
    //ASSR.OCR2AUB - OCR2A Update Busy - Vai ser fixo. N se preocupar
    //ASSR.TCR2AUB - TCCR2A Update Busy - Deve estar setado! - N se preocupar
    noInterrupts();
    TCCR2A  |= (1 << WGM21) | (1 << COM2A1) | (1 << COM2A0);   //WGM2[2:0] = 2 //CTC Mode
    TCCR2B  |= (1 << CS20);  //No prescaling
    TIMSK2  |= (1 << OCIEA); //Interrupt Enable
    OCR2A   |= 0x7FFF;       //Compare Register
    ASSR    |= 1 << AS2;     //Usa XTAL de 32kHz
    interrupts();
}

void loop() {
    if(bitRead(aux,secIncreased)){
        Serial.println(utc);
        }
  // put your main code here, to run repeatedly:

}
