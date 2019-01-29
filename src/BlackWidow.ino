//************************ BlackWidow **************************
// This code is for Soilwatch10 3V testing 

// Based on code from:
// Piotr Trembecki
// https://pino-tech.eu/sw10

// The circuit:
// Sensor output (white wire) connected to Analog A0
// VCC (brown wire) connected to 3V3
// GND (green wire) connected to GND
// Catnip connected to SDA/D0 and SCL/D1


#include "adafruit-sht31.h"
#include "I2CSoilMoistureSensor.h"
#include "QuickStats.h"

// timer variables
int i, j, h, k;                                 // second, minute, and hour record, median array value

QuickStats stats;                               // used to calculate median
const int vals = 6;                             // number of values for median

float SW_med[vals] = {};                        // Soilwatch median array
float Cat_med[vals] = {};                       // Catnip median array

int medSW, medCat;                              // calculated median


// Soilwatch
 const int analogInPin = A0;                    // Sensor output
 int minADC = 1018;                             // replace with min ADC value read in air
 int maxADC = 3486;                             // replace with max ADC value read fully submerged in water 
                                                // usually 600
 unsigned int moistureValue, mappedValue;       // mapping variables


// Catnip
 I2CSoilMoistureSensor sensor(0X20);            // currently testing the shallow sensors at 0X20
                                                // change to 0X25 for medium
                                                // or 0X30 for deep

 const int analogCatnipPin = SDA;
 int CatminADC = 207;
 int CatmaxADC = 722;                           // 3.3V or 5V

// mapping
 int CatnipmoistureValue, Catnipmappedvalue;    // maps raw values to values chosen in above min/max ranges



//************************** SETUP ***************************/
void setup(){
    Wire.begin();
    Serial.begin(9600);                 // initialize serial communications at 9600 bps

    while(!Serial.isConnected()){
        sensor.begin();                     // wake up the Catnip
        delay(1000);                        // wait for the sensors to be ready
        
        i=0;                                // start at 0 seconds
        j=0;                                // start at 0 minutes
        h=0;                                // start at 0 hours
        k=0;                                // starts at 0 to eventually find median of values stored in median array



// uncomment this block of code if you have doubts about your Catnip sensor address
/*
        byte error, address;
        int nDevices = 0;
    
        for(address = 1; address < 127; address++ ){
            Wire.beginTransmission(address);
            error = Wire.endTransmission();
    
            if (error == 0){
                Serial.print("I2C device found at address 0x");
                if (address<16)
                Serial.print("0");
                Serial.print(address,HEX);
                Serial.println("  !");
                nDevices++;
            }
        }
*/


    }
}



//********************* REPEATED CODE ************************/
void loop() {
    Wire.begin();
    Serial.begin(9600);
    // sensor.begin();


// uncomment this block of code to print 5 second, minute, and hour values
/*
    Serial.print(F("i: "));                             // shows how many 5second loops have gone by
    Serial.print(i);

    Serial.print(F(" j: "));                             // shows how many 60second loops have gone by
    Serial.print(j);

    Serial.print(F(" h: "));                             // shows how many 60minute loops have gone by
    Serial.print(h);

    Serial.print(F(" k: "));                             // shows what moisture reading is being saved into median array
    Serial.print(k);
*/


// Soilwatch analog moisture reading

    Serial.print(F("    Soilwatch: "));
    moistureValue = analogRead(analogInPin);            // read the moisture value
     
    Serial.print(F("ADC = " ));                         // print ADC results to the serial monitor:
    Serial.print(moistureValue);
    Serial.print(F(" " ));
     
    mappedValue = map(moistureValue, minADC, maxADC, 0, 100); 
    
    Serial.print(F("Mapped = " ));                       // print mapped results to the serial monitor:
    Serial.print(mappedValue);



// Catnip capacitance reading
    
    Serial.print(F("      Catnip: "));
    CatnipmoistureValue = sensor.getCapacitance();

    Serial.print(F(" Capacitance: "));
    Serial.print(sensor.getCapacitance());              // read capacitance register

    Catnipmappedvalue = map(CatnipmoistureValue, CatminADC, CatmaxADC, 0, 100);

    Serial.print(F(" Mapped = "));
    Serial.print(Catnipmappedvalue);

    Serial.print(F("      "));



// Median code
    
        SW_med[k] = moistureValue;                      // median array assignment
        Cat_med[k] = CatnipmoistureValue;               // median array assignment

        k++;                                            // increment k to go through array values

        if (k %6 == 0){
            k=0;                                        // reset k to fill median array again
        }

    medSW = stats.median(SW_med, vals);
    medCat = stats.median(Cat_med, vals);

    i++;                                                // increment timer



// Timer code

    if (i%6 == 0){                                      // keeps track every 5 seconds
        Serial.print(F(" medSW "));                     // displays median every 30 seconds, for previous 30 seconds
        Serial.print(medSW);

        Serial.print(F(" medCat "));
        Serial.print(medCat);

        Serial.print(F("   "));
        Serial.print(i*5);
        Serial.print(F(" s "));
    }

    if (i%12 == 0){                                     // increment minute number every 60 seconds
        j++;
        Serial.print(j);
        Serial.print(F(" min "));
    }

    if (i%60 == 0){                                     // increment hour number every 60 minutes
        h++;
        Serial.print(h);
        Serial.print(F(" hr "));
    }


    Serial.println(F(""));
    delay(5000);                                        // wait 5 seconds and then repeat
    
}