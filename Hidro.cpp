//code to compile library 
#include "Hidro.h"
#include <iostream>  

using namespace std;  
Contexto::Contexto(){
	valorPorta = 0;
	tensao = 0;
	lampada = 0;
	//planta = NULL;
};
void Contexto::medePorta(int){
	//A implementar
};
void Contexto::converteTensao(int){
	//A implementar
};
void Contexto::nomePlanta(string recebido){
	 //my_planta (recebido);
	//planta = my_planta;
};
void Contexto::setLampada(int numlamp){
	lampada = numlamp;
};
float Contexto::IndicaTensao(){
	return(tensao);
};
int Contexto::getLampada(){
	return(lampada);
};
string Contexto::getPlanta(){
	return(planta.name);
};

bool Controle::calculaTudo(){
	return(true);//returna true se liga lampada ou false se nao liga
};

