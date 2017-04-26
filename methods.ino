//Methods to Contexto e Controle
#include "header.h"

using namespace std;  
Contexto::Contexto(){
    codigoLamp = tempo_ideal = 0;
    isAceso = false;
    namePlant = "";
};
void Contexto::setPlanta(String recebido){
	namePlant = recebido;
};
void Contexto::setLampada(int recebido){
	codigoLamp = recebido;
};
void Contexto::setLampStats(bool recebido){
    isAceso = recebido;
};
void Contexto::setTempoPlanta(int recebido){
    tempo_ideal = recebido;
};
void Contexto::setTempoPercorrido(){
//    utcToTime(&tempoPercorrido);
};
tm Contexto::getTempoPercorrido(){
    return(tempoPercorrido);
};
int Contexto::getTempoPlanta(){
    return(tempo_ideal);
};
int Contexto::getLampada(){
	return(codigoLamp);
};
String Contexto::getPlanta(){
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
