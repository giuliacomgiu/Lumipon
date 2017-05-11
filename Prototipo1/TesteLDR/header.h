#ifndef HEADER_H
#define HEADER_H

#define LDRPin A1
#define EXTpin 2
#define LAMP0pin 5
#define LAMP1pin 6

#define SEC_INCR_bit 0
#define BUT_PRESS_bit 1
#define UPDT_DATA_bit 0
#define UPDT_LDR_bit 1
#define KEEP_LCD_bit 2

#define BUT_PRESS_AND_SEC_INC B11
#define BUT_PRESS B10
#define SEC_INCR 1
#define SEC_INCR_AND_UPDT_DATA B1
#define SEC_INCR_AND_UPDT_LDR B10
#define SEC_INCR_AND_UPDT_DATA_AND_LDR B11
#define UPDT_RATE 6
#define UPDT_LDR 1
#define KEEP_LCD 30

#define PRTWI0 7
#define PRTIM2 6
#define PRTIM0 5
#define PRTIM1 3
#define PRSPI0 2
#define PRUSART0 1
#define PRADC 0
#define WDP3 5
#define WDP2 2
#define WDP1 1
#define WDP0 0

//#define CA22 2
//#define CA21 1
//#define CA20 0

//#define OCIEA 1

typedef struct {
    byte seg;
    byte minu;
    byte hora;
    byte dia;   //Dia da semana
    byte diaDoMes;
    unsigned int diaDoAno;
    byte mes;
    byte ano;   //overflow em 2038
    }   tm;

class Planta{
protected:
	String namePlant;
	int tempo_ideal;
};

class Lampada{
protected:
	int codigoLamp;
	bool isAceso;
};

class Contexto: public Lampada, public Planta{
private:
//    tm tempoPercorrido;
public:
	Contexto();//construtor default
    void setTempoPlanta(int);
//    void setTempoPercorrido();
	void setPlanta(String);
	void setLampada(int);
    void setLampStats(bool);

//    tm getTempoPercorrido();
    int getTempoPlanta();
	int getLampada();	//numero da lampada
	bool getLampStats();
	String getPlanta();	//retorna so o nome da strcut da planta
} contexto[2];

class Controle : public Contexto{
private:
	float tensaoLDR;
	float tensaoThreshold;
public:
	bool jaTeveLuz;

	void setTensaoThreshold(byte porcentagem);
	float getTensaoLDR();
};
    
#endif
