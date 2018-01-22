

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
#define EEPROM_TOLERANCIA_DIF_LIGAR     30
#define EEPROM_TOLERANCIA_DIF_DESLIGAR  40


/* ==== END Defines ==== */

/* ==== Global Variables ==== */
int temperaturaDesejada = 30; //ºC
int toleranciaTemperaturaDesejada = 1; //ºC

int toleranciaDiferencaLigarBomba = 3;
int toleranciaDiferencaDesligarBomba = 3;

/* ==== END Global Variables ==== */


void setup() {
  Serial.begin(SERIAL_BAUD);
  buttonToLow();

}

void loop() {
  
}
/* ==== Functions ==== */


void printStatusOnSerial(){
  
  Serial.print("Temp desejada: ");
  Serial.print(temperaturaDesejada);
  
  Serial.print(" Tolerancia temp desejada: ");
  Serial.print(toleranciaTemperaturaDesejada);
  
  Serial.print(" Tolerancia dif ligar: ");
  Serial.print(toleranciaDiferencaLigarBomba;
  
  Serial.print(" Tolerancia dif desligar: ");
  Serial.print(toleranciaDiferencaDesligarBomba);
  
}

void readFromEprom(){
  temperaturaDesejada = EEPROM.read(EEPROM_TEMPERATURA_DESEJADA);
  toleranciaTemperaturaDesejada = EEPROM.read(EEPROM_TOLERANCIA_TEMPERATURA);
  toleranciaDiferencaLigarBomba = EEPROM.read(EEPROM_TOLERANCIA_DIF_LIGAR);
  toleranciaDiferencaDesligarBomba = EEPROM.read(EEPROM_TOLERANCIA_DIF_DESLIGAR);  
}

void writeOnEprom(){
  EEPROM.put(EEPROM_TEMPERATURA_DESEJADA, temperaturaDesejada);
  EEPROM.put(EEPROM_TOLERANCIA_TEMPERATURA, toleranciaTemperaturaDesejada);
  EEPROM.put(EEPROM_TOLERANCIA_DIF_LIGAR, toleranciaDiferencaLigarBomba);
  EEPROM.put(EEPROM_TOLERANCIA_DIF_DESLIGAR, toleranciaDiferencaDesligarBomba);
}



void buttonToLow(){
  digitalWrite(BOTAO_MAIS, LOW);
  digitalWrite(BOTAO_MENOS, LOW);
  digitalWrite(BOTAO_MENU, LOW);
}

/* ==== END Functions ==== */