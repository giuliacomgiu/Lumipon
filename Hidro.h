
#ifndef HIDRO_H
#define HIDRO_H
#include <iostream>
#include <string>
using namespace std;

typedef struct{
	string name;
	int tempo_ideal;
} Planta;

class Contexto{
private:
	int valorPorta,lampada;
	float tensao;
	Planta planta;
public:
	Contexto();//construtor default
	void medePorta(int);	//duvida getPorta ou efetuar
				//de fato a medição da porta atraves desse metodo.
	void setPlanta(string);
	void setLampada(int);
	
	float getTensãoLDR();	//pode so guardar o valornaporta e fazer
				//o calc aqui quando for pedido
	int getLampada();
	string getPlanta();	//retorna so o nome da strcut da planta
} ctx;

class Controle : public Contexto{
private:
	//talves controle so instanciei contexto
public:
	bool calculaTudo(); //Não sei ao exato como sera essa rotina
	//No entanto a intenção é chamar ela pra definir o tempo ideal
	//Ou não para a planta sendo então o codigo base da parte
	//do hardware
} control;
#endif
