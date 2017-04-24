
#ifndef HIDRO_H
#define HIDRO_H
#include <iostream>
#include <string>
using namespace std;

class Planta{
protected:
	string namePlant;
	int tempo_ideal;
}

class Lampada{
protected:
	int codigoLamp;
	bool isAceso;
}

class Contexto: public Lampada, public Planta{
public:
	Contexto();//construtor default
	void setPlanta(string);
	void setLampada(int);
	
	void medePorta(int);	//a lampada ta acesa?
	int getLampada();	//numero da lampada
	bool getLampStats();
	string getPlanta();	//retorna so o nome da strcut da planta
}

class Controle : public Contexto{
private:
	float tensaoLDR;
public:
	float getTensãoLDR();
	bool calculaTudo(); //Não sei ao exato como sera essa rotina
	//No entanto a intenção é chamar ela pra definir o tempo ideal
	//Ou não para a planta sendo então o codigo base da parte
	//do hardware
} control;
#endif
