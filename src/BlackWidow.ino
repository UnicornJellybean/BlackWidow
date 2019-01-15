//************************ BlackWidow **************************
//This code is for Soilwatch10 3V testing 

// Based on code from:
// Piotr Trembecki
// https://pino-tech.eu/sw10

// The circuit:
// Sensor output (white wire) connected to Analog A0
// VCC (brown wire) connected to 3V3
// GND (green wire) connected to GND
// Catnip connected to SDA/D0 and SCL/D1


// The usual maxADC value will be around 600.

#include "adafruit-sht31.h"
#include "I2CSoilMoistureSensor.h"

 const int analogInPin = A0;            // Sensor output
 int minADC = 1018;                        // replace with min ADC value read in air
 int maxADC = 3486;                      // replace with max ADC value read fully submerged in water 
                                        // (usually 600)
 int moistureValue, mappedValue;


 I2CSoilMoistureSensor sensor(0X20);
 const int analogCatnipPin = SDA;
 int CatminADC = 207;
 int CatmaxADC = 722;                   // 3.3V or 5V

 int CatnipmoistureValue, Catnipmappedvalue;


//************************** SETUP ***************************/
void setup() {
    Wire.begin();
    Serial.begin(9600);                 // initialize serial communications at 9600 bps
    sensor.begin();                     // wake up the Catnip
    delay(100);                         // wait for the sensors to be ready
}


//************************ FUNCTIONS *************************/
void loop() {
    Wire.begin();
    Serial.begin(9600);
    // sensor.begin();
    moistureValue = analogRead(analogInPin);           // read the moisture value:
     
    Serial.print("Soilwatch: ");
    Serial.print("ADC = " );                           // print ADC results to the serial monitor:
    Serial.print(moistureValue);
    Serial.print(", " );
     
    mappedValue = map(moistureValue, minADC, maxADC, 0, 100); 
    
    Serial.print("Mapped = " );                       // print mapped results to the serial monitor:
    Serial.println(mappedValue);


    Serial.print("      Catnip: ");
    CatnipmoistureValue = sensor.getCapacitance();

    // Serial.print(" ADC: ");
    // Serial.print(CatnipmoistureValue);                  // reads analog SDA pin

    Serial.print(" Capacitance: ");
    Serial.print(sensor.getCapacitance());              //read capacitance register

    Catnipmappedvalue = map(CatnipmoistureValue, CatminADC, CatmaxADC, 0, 100);

    Serial.print(" Mapped = ");
    Serial.print(Catnipmappedvalue);
    Serial.println("      ");

    delay(1500);                                        // wait 500 milliseconds and then repeat
    }