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

int i, j, k;                                   // allows for output to be recorded every 5 and 30 seconds
// int Soilw1, Soilw2, Soilw3, Soilw4, Soilw5;     // 5 moisture values
// int Cat1, Cat2, Cat3, Cat4, Cat5;               // 5 moisture values

 const int analogInPin = A0;                // Sensor output
 int minADC = 1018;                         // replace with min ADC value read in air
 int maxADC = 3486;                         // replace with max ADC value read fully submerged in water 
                                            // (usually 600)
 int moistureValue, mappedValue;


 I2CSoilMoistureSensor sensor(0X20);
 const int analogCatnipPin = SDA;
 int CatminADC = 207;
 int CatmaxADC = 722;                       // 3.3V or 5V

 int CatnipmoistureValue, Catnipmappedvalue;


//************************** SETUP ***************************/
void setup() {
    Wire.begin();
    Serial.begin(9600);                 // initialize serial communications at 9600 bps
    sensor.begin();                     // wake up the Catnip
    delay(100);                         // wait for the sensors to be ready

    i=0;                                            // start at 0 seconds
    j=0;                                            // start at 0 minutes
}


//************************ FUNCTIONS *************************/
void loop() {
    Wire.begin();
    Serial.begin(9600);
    // sensor.begin();

    Serial.print(F("i: "));                             // shows how many 5second loops have gone by
    Serial.print(i);

    Serial.print(F(" j: "));                             // shows how many 60second loops have gone by
    Serial.print(j);


    moistureValue = analogRead(analogInPin);            // read the moisture value:
     
    Serial.print(F("    Soilwatch: "));
    Serial.print(F("ADC = " ));                         // print ADC results to the serial monitor:
    Serial.print(moistureValue);
    Serial.print(F(", " ));
     
    mappedValue = map(moistureValue, minADC, maxADC, 0, 100); 
    
    Serial.print(F("Mapped = " ));                       // print mapped results to the serial monitor:
    Serial.print(mappedValue);


    Serial.print(F("      Catnip: "));
    CatnipmoistureValue = sensor.getCapacitance();

    Serial.print(" Capacitance: ");
    Serial.print(sensor.getCapacitance());              //read capacitance register

    Catnipmappedvalue = map(CatnipmoistureValue, CatminADC, CatmaxADC, 0, 100);

    Serial.print(" Mapped = ");
    Serial.print(Catnipmappedvalue);
    Serial.print("      ");

    
    delay(5000);                                        // wait 5 seconds and then repeat

    i++;

    if (i%6 == 0){
        Serial.print(i*5);
        Serial.print(F("s reading"));
    }

  

    if (i%12 == 0){
        j++;
        Serial.print(F(" , "));
        Serial.print(j);
        Serial.print(F("min reading"));
    }


    Serial.println("");
}