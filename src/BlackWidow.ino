/************************ BlackWidow **************************
This code is for Soilwatch10 3V testing 

Based on code from:
Piotr Trembecki
https://pino-tech.eu/sw10

The circuit:
Sensor output (white wire) connected to Analog A0
VCC (brown wire) connected to 3V3
GND (green wire) connected to GND
*/

// The usual maxADC value will be around 600.

const int analogInPin = A0;         // Sensor output
int minADC = 0;                     // replace with min ADC value read in air
int maxADC = 600;                   // replace with max ADC value read fully submerged in water 
                                    // (usually 600)

int moistureValue, mappedValue;


/************************ SETUP *************************/
void setup() {
    Serial.begin(9600);                         // initialize serial communications at 9600 bps
}


/************************ FUNCTIONS *************************/
void loop() {
    moistureValue = analogRead(analogInPin);    // read the moisture value:
     
    Serial.print("ADC = " );                    // print ADC results to the serial monitor:
    Serial.print(moistureValue);
    Serial.print(", " );
     
    mappedValue = map(moistureValue,minADC,maxADC, 0, 100); 
     
    Serial.print("Moisture value = " );         // print mapped results to the serial monitor:
    Serial.println(mappedValue);
     
    delay(500);                                 // wait 500 milliseconds and then repeat
    }