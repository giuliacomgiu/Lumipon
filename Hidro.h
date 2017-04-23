
#ifndef HIDRO_H
#define HIDRO_H
#include <iostream>
#include <string>
using namespace std;

class Planta{
private:
	string name;
	int tempo_ideal;
}

class Lampada{
private:
	int codigo;
	int isAceso;
}

class Contexto{
private:
	
	Planta planta;
public:
	Contexto();//construtor default
	void setPlanta(string);
	void setLampada(int);
	
	void medePorta(int);	//a lampada ta acesa?
	int getLampada();	//numero da lampada
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
