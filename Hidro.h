
#ifndef HIDRO_H
#define HIDRO_H
#include <iostream>
#include <string>
using namespace std;
struct Planta{
	string name;
	int tempo_ideal;
} alface,aipim,cereja;
class Contexto{
	int valorPorta,lampada;
	float tensao;
	Planta planta;
	public:
	Contexto();//construtor default
	void medePorta(int); //duvida getPorta ou efetuar
	//de fato a medição da porta atraves desse metodo.
	void converteTensao(int);//n tenho ctz se sera necessario
	void nomePlanta(string);
	void setLampada(int);
	float IndicaTensao();//pode so guardar o valornaporta e fazer
	//o calc aqui quando for pedido
	int getLampada();
	string getPlanta(); //retorna so o nome da strcut da planta
} ctx;
class Controle : public Contexto{
	//talves controle so instanciei contexto
	public:
	bool calculaTudo(); //Não sei ao exato como sera essa rotina
	//No entanto a intenção é chamar ela pra definir o tempo ideal
	//Ou não para a planta sendo então o codigo base da parte
	//do hardware
} control;
#endif
