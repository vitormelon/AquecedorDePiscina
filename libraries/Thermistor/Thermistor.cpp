/**************************************************************/
/*				max mayfield								  */
/*				mm systems									  */
/*				max.mayfield@hotmail.com					  */
/*															  */
/*	code based from code on Arduino playground found here:	  */
/*	http://www.arduino.cc/playground/ComponentLib/Thermistor2 */
/**************************************************************/

/* ======================================================== */

#include "Arduino.h"
#include "Thermistor.h"

//--------------------------
Thermistor::Thermistor(int pin, int resistor = 10000) {
  _pin = pin;
  _resistor = resistor;
}

//--------------------------
double Thermistor::getTemp(int numSamples = 1) {
  // Inputs ADC Value from Thermistor and outputs Temperature in Celsius

  int i;
  long Resistance;
  double Temp;
  long sum = 0;
  for(i = 0; i < numSamples; i++){
    sum = sum + 1023 - analogRead(_pin);
    delay(100);
  }
  
  int RawADC = sum/numSamples;
  

  // Usin the resistor resistence.  Calculation is actually: Resistance = (1024/ADC)
  Resistance=((10240000/RawADC) - _resistor);

  /******************************************************************/
  /* Utilizes the Steinhart-Hart Thermistor Equation:				*/
  /*    Temperature in Kelvin = 1 / {A + B[ln(R)] + C[ln(R)]^3}		*/
  /*    where A = 0.001129148, B = 0.000234125 and C = 8.76741E-08	*/
  /******************************************************************/
  Temp = log(Resistance);
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;  // Convert Kelvin to Celsius

  // - TESTING OUTPUT - remove lines with * to get serial print of data
  Serial.print("ADC: "); Serial.print(RawADC); Serial.print("/1024");  // Print out RAW ADC Number
  Serial.print(", Volts: "); Serial.print(((RawADC*4.960)/1024.0),3);   // 4.860 volts is what my USB Port outputs.
  Serial.print(", Resistance: "); Serial.print(Resistance); Serial.println("ohms");
  //

  // Uncomment this line for the function to return Fahrenheit instead.
  //Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert to Fahrenheit

  return Temp;  // Return the Temperature
}

/* ======================================================== */