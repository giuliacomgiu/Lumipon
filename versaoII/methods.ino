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
    switch(recebido){
        case 0:
            codigoLamp = LAMP0pin;
        break;
        case 1:
            codigoLamp = LAMP1pin;
        break;
    }
};
void Contexto::setLampStats(bool recebido){
    isAceso = recebido;
    digitalWrite(codigoLamp,recebido);
};
void Contexto::setTempoPlanta(int recebido){
    tempo_ideal = recebido;
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
