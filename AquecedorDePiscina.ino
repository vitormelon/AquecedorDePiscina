

#include <EEPROM.h>

/* ==== Defines ==== */

//Pinos
#define SENSOR_TEMPERATURA_CIMA         1 
#define SENSOR_TEMPERATURA_BAIXO        1 
#define RELE_BOMBA                      1
#define BOTAO_MAIS                      1 
#define BOTAO_MENOS                     1
#define BOTAO_MENU                      1

//Constantes
#define SERIAL_BAUD                     9600

#define EEPROM_TEMPERATURA_DESEJADA     10
#define EEPROM_TOLERANCIA_TEMPERATURA   20
#define EEPROM_TOLERANCIA_DIFERENCA     30



/* ==== END Defines ==== */

/* ==== Global Variables ==== */
int temperaturaDesejada = 30; //ºC
int toleranciaTemperaturaDesejada = 1; //ºC

int toleranciaDiferenca = 3;

float temperaturaCima = 0;
float temperaturaBaixo = 0;

bool bombaLigada = false;

/* ==== END Global Variables ==== */


void setup() {
  Serial.begin(SERIAL_BAUD);
  buttonToLow();
  desligarBomba();
  lerTemperaturas();
}

void loop() {
  
}
/* ==== Functions ==== */


void printStatusOnSerial(){
  
  Serial.print("Temp desejada: ");
  Serial.print(temperaturaDesejada);
  
  Serial.print(" Tolerancia temp desejada: ");
  Serial.print(toleranciaTemperaturaDesejada);
  
  Serial.print(" Tolerancia dif: ");
  Serial.print(toleranciaDiferenca;
  
  
}

void readFromEprom(){
  temperaturaDesejada = EEPROM.read(EEPROM_TEMPERATURA_DESEJADA);
  toleranciaTemperaturaDesejada = EEPROM.read(EEPROM_TOLERANCIA_TEMPERATURA);
  toleranciaDiferenca = EEPROM.read(EEPROM_TOLERANCIA_DIFERENCA);  
}

void writeOnEprom(){
  EEPROM.put(EEPROM_TEMPERATURA_DESEJADA, temperaturaDesejada);
  EEPROM.put(EEPROM_TOLERANCIA_TEMPERATURA, toleranciaTemperaturaDesejada);
  EEPROM.put(EEPROM_TOLERANCIA_DIFERENCA, toleranciaDiferenca);
}

bool validaTemperaturaDesejada(){
  if(!bombaLigada){
    if(temperaturaBaixo + toleranciaTemperaturaDesejada <= temperaturaDesejada){
      return true;
    }
    return false;
  }else{
    if(temperaturaBaixo - toleranciaTemperaturaDesejada >= temperaturaDesejada){
      return true;
    }
    return false;
  }
}


bool validaDiferencaTemperatura(){
  if(!bombaLigada){
    if((temperaturaCima - toleranciaDiferenca) > temperaturaBaixo){
      return true;
    }else{
      return false;
    }
  }else{
    if(temperaturaCima > temperaturaBaixo){
      return true;
    }else{
      return false;
    }
  }
}

void lerTemperaturas(){
  temperaturaCima = lerTemperaturaDe(SENSOR_TEMPERATURA_CIMA);
  temperaturaBaixo = lerTemperaturaDe(SENSOR_TEMPERATURA_BAIXO);
}

float lerTemperaturaDe(int sensor){
  return 0.0;
}

void ligarBomba(){
  digitalWrite(RELE_BOMBA, HIGH);
  bombaLigada = true;
}

void desligarBomba(){
  digitalWrite(RELE_BOMBA, LOW);
  bombaLigada = false;
}

void buttonToLow(){
  digitalWrite(BOTAO_MAIS, LOW);
  digitalWrite(BOTAO_MENOS, LOW);
  digitalWrite(BOTAO_MENU, LOW);
}

/* ==== END Functions ==== */