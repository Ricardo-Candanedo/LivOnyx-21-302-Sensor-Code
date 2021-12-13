// Ricardo Candanedo
// LivOnyx 21-302: Sensor Code

// The code provided below is what was intended to be used with the
// microcontroller to help power the nozzle array.
// The user would put their hand within 6 cm within the range 
// of the sensor, and then the sensor would send a 5V power out
// through pin 6 to drive the circuit. This code was kept as simple
// as possible for others in the future to make edits quickly and
// efficiently 

// The library "SR04.h" is by Elegoo, the make of the sensor 
// (HC-SR04) that was going to be implemented into the project

// Some of the code you see here regarding TRIG_PIN, ECHO_PIN, 
// and sr04 was taken from the example provided by Elegoo, which is
// also attached  within the Software folder titled "SR04_Example"


#include "SR04.h"

// TRIG_PIN and ECHO_PIN needed for the sensor to function properly
#define TRIG_PIN 12
#define ECHO_PIN 11

// This is used to use the functions within the SR04.h
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);

// Variable that will be used for distance that something is 
// detected  
long a;

// flag variable used for when a user's hand is kept in front 
// of the sensor after 5 seconds
int flag = 0;

void setup() {
  
   // Need for Serial Monitor, which was used for testing code
   Serial.begin(9600);
   delay(1000);

   // Made pin 6 an output
   pinMode(6, OUTPUT);
}

void loop() {
   // sets a to the distance being detected
   a=sr04.Distance();

   // Prints the distance in centimeters that an obstacle is being 
   // detected 
   Serial.print(a);
   Serial.println("cm");
   delay(1000);

    // Used to reset flag variable (this is for if a hand is still
    // in the system after the spray went off for 5 seconds)
    if (flag == 1 && a > 6) {
        Serial.println("Flag is reset");
        flag = 0;
    }

   // If a (the obstacle being detected) if less than 6 centimeters away,
   // then the output is set to HIGH (5V)
   if (a < 6 && flag == 0) {
      flag = 1;
      Serial.println("power is being outputed for 5 seconds...");
      digitalWrite(6, HIGH);
      delay(5000);
      digitalWrite(6, LOW);
      Serial.println("power is being shut off...");
    } 
}
