#include <Arduino.h>

#include <BLEMIDI_Transport.h>

//#include <hardware/BLEMIDI_ESP32_NimBLE.h>
#include <hardware/BLEMIDI_ESP32.h>
//#include <hardware/BLEMIDI_ArduinoBLE.h>
//#include <hardware/BLEMIDI_Client_ESP32.h>

#define POT D2 // GPIO pin for the potentiometer

BLEMIDI_CREATE_INSTANCE("ESP32BLEMIDI", MIDI);

unsigned long t0 = millis();
bool isConnected = false;
unsigned int mappedPot;
int potValue = 0; // Initialize potValue to track changes
int lastPotValue = 0; // Initialize lastPotValue to track changes


void setup() {

  Serial.begin(115200);
    
  MIDI.begin();
  
  BLEMIDI.setHandleConnected([]() {
    isConnected = true;
//    digitalWrite(BT_LED, HIGH);
  });

  BLEMIDI.setHandleDisconnected([]() {
    isConnected = false;
//    digitalWrite(BT_LED, LOW);    
  });

  MIDI.setHandleControlChange([](byte channel, byte control, byte value) {
  });
}

void loop() {
  
  //MIDI.read();
      
      potValue = analogRead(POT);
      if (isConnected && (millis() - t0) > 1000 && (abs(potValue-lastPotValue) > 50))
      
    {
     mappedPot = map(potValue, 0, 4095, 0, 127);
     MIDI.sendControlChange(2,mappedPot,1); // Example: Send Control Change on channel 1, control 2, value mappedPot
     lastPotValue = potValue;
     t0 = millis();
     //Serial.printf("Sensor Value: %d\n", mappedPot);
    }  
}
