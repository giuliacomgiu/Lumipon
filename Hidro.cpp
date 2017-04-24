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
void Contexto::setPlanta(string recebido){
	namePlant = recebido;
};
void Contexto::setLampada(int recebido){
	codigoLamp = recebido;
};
int Contexto::getLampada(){
	return(codigoLamp);
};
string Contexto::getPlanta(){
	return(namePlant);
};
bool Contexto::getLampStats(){
	return(isAceso);
};
float Controle::getTensaoLDR(){
	return(tensaoLDR);
};

bool Controle::calculaTudo(){
	return(true);//returna true se liga lampada ou false se nao liga
};

