#include <Wire.h> 
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include </home/vitormelon/dev/AquecedorDePiscina/libraries/Thermistor/Thermistor.cpp>

/* ==== Defines ==== */

//Pinos
#define SENSOR_TEMPERATURA_CIMA         1 
#define SENSOR_TEMPERATURA_BAIXO        2 
#define RELE_BOMBA                      4
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
int temperaturaDesejada = 35; //ºC
int toleranciaTemperaturaDesejada = 1; //ºC

int toleranciaDiferenca = 2;

float temperaturaCima = 0;
float temperaturaBaixo = 0;

bool bombaLigada = false;

Thermistor sensorCima(SENSOR_TEMPERATURA_CIMA, 9740);
Thermistor sensorBaixo(SENSOR_TEMPERATURA_BAIXO, 9740);

LiquidCrystal_I2C lcd(0x3F, 20, 4);
/* ==== END Global Variables ==== */


void setup() {
  Serial.begin(SERIAL_BAUD);
  lcd.begin();
  pinMode(RELE_BOMBA, OUTPUT);
  buttonToLow();
  desligarBomba();
  lerTemperaturas();
}

void loop() {
  getTemperaturas();
  if(LigarBombaPelaDiferencaDeTemperatura()){
    ligarBomba();
  }else{
    desligarBomba();
  }
  printDisplay();
  delay(2000);
}
/* ==== Functions ==== */

void printDisplay(){
  String bomba = "Desligada";
  if(bombaLigada){bomba = "Ligada    ";}
  lcd.setCursor(0,0);
  lcd.print("Melon's Pool Heater");
  lcd.setCursor(0,1);
  lcd.print("   Placa: ");
  lcd.print(temperaturaCima,1);
  lcd.print("*C");
  lcd.setCursor(0,2);
  lcd.print(" Piscina: ");
  lcd.print(temperaturaBaixo,1);
  lcd.print("*C");
  lcd.setCursor(0,3);
  lcd.print("   Bomba: ");
  lcd.print(bomba);
}

void getTemperaturas(){
  temperaturaCima = arredonda(sensorCima.getTemp(2000));
  temperaturaBaixo = arredonda(sensorBaixo.getTemp(2000));
}

float arredonda(float numero){
  return ((int)(numero * 10))/10.0;
}

void printStatusOnSerial(){
  
  Serial.print("Temp desejada: ");
  Serial.print(temperaturaDesejada);
  
  Serial.print(" Tolerancia temp desejada: ");
  Serial.print(toleranciaTemperaturaDesejada);
  
  Serial.print(" Tolerancia dif: ");
  Serial.print(toleranciaDiferenca);
  
  
}

void readFromEprom(){
  temperaturaDesejada = EEPROM.read(EEPROM_TEMPERATURA_DESEJADA);
  toleranciaTemperaturaDesejada = EEPROM.read(EEPROM_TOLERANCIA_TEMPERATURA);
  toleranciaDiferenca = EEPROM.read(EEPROM_TOLERANCIA_DIFERENCA);  
}

void writeOnEprom(){
  writeIfChange(EEPROM_TEMPERATURA_DESEJADA, temperaturaDesejada);
  writeIfChange(EEPROM_TOLERANCIA_TEMPERATURA, toleranciaTemperaturaDesejada);
  writeIfChange(EEPROM_TOLERANCIA_DIFERENCA, toleranciaDiferenca);
}

void writeIfChange(int address, int value){
  int eepromValue = EEPROM.read(address);
  if(eepromValue != value){
    EEPROM.write(address, value);  
  }
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


bool LigarBombaPelaDiferencaDeTemperatura(){
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
