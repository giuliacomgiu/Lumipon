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
//void Contexto::setTempoPercorrido(int auxiliar){
//    tempoPercorrido = auxiliar;
//};
//tm Contexto::getTempoPercorrido(){
//    return(tempoPercorrido);
//};
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
