
#ifndef HIDRO_H
#define HIDRO_H
#include <iostream>
#include <string>
/*struct Planta{
	string planta_name;
	int tempo_ideal;
} ;//exemplos de nome so */
class Contexto{
	int valorPorta,lampada;
	float tensao;
	string planta;
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
	int calculaTudo(); //Não sei ao exato como sera essa rotina
	//No entanto a intenção é chamar ela pra definir o tempo ideal
	//Ou não para a planta sendo então o codigo base da parte
	//do hardware
} control;
void Contexto::Contexto{
	Contexto::valorPorta = 0;
	Contexto::tensao = 0;
	Contexto::lampada = 0;
	Contexto::planta = NULL;
}
void Contexto::medePorta(int){
	//A implementar
}
void Contexto::converteTensao(int){
	//A implementar
}
void Contexto::nomePlanta(string recebido){
//	 my_planta (recebido);
	//planta = my_planta;
}
void Contexto::setLampada(int numlamp){
	lampada = numlamp;
}
float Contexto::IndicaTensao(){
	return(tensao);
}
int Contexto::getLampada(){
	return(lampada);
}
string Contexto::getPlanta(){
	return(planta.nome)
}

int Controle::calculaTudo(){
	
}



#endif