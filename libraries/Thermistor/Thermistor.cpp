
#include "Arduino.h"
#include "Thermistor.h"

//--------------------------
Thermistor::Thermistor(int pin, int resistor = 10000) {
  _pin = pin;
  _resistor = resistor;
}

//--------------------------
double Thermistor::getTemp(int numSamples = 1) {

  int Vin = 1023;
  double Resistance, TempK, Temp, RawADC;
  long sum = 0;
  float r25 = 10000;   // [ohm]     Valor de NTC a 25ºC
  float beta = 3435;   // [K]      Parámetro Beta de NTC
  float t0 = 298.15;   // [K]       Temperatura de referencia en Kelvin

  for(int i = 0; i < numSamples; i++){
    sum = sum + analogRead(_pin);
  }
  
  RawADC = (double)sum/numSamples;
  
  Resistance = ((double)_resistor / (((double)Vin / RawADC)  - 1));   
   
  TempK = (double)beta/(log((double)Resistance/r25)+((double)beta/t0));
  Temp = TempK-273.15;

  return Temp;  // Return the Temperature
}

/* ======================================================== */
