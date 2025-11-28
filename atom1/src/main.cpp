#include <Arduino.h>
#include <M5_PbHub.h>
#include <MicroOscSlip.h>
#include <FastLED.h>
#include <M5_Encoder.h>
#include <VL53L0X.h>

MicroOscSlip<128> monOsc(& Serial);

#define CANAL_KEY_UNIT_ANGLE_Y 0 //Atom 1
#define CANAL_KEY_UNIT_ANGLE_X 1 //Atom 1
#define MA_BROCHE_BOUTON 27 //Atom 1 et 2 pour diffencier avec les couleurs lequel atom et lequel.

unsigned long monChronoDepart;

M5_PbHub myPbHub;
CRGB atomPixel;
VL53L0X  myTOF;


void setup() {

  Serial.begin(115200); 
  myPbHub.begin(); 
  Wire.begin(); 
  myTOF.init();

  pinMode( MA_BROCHE_BOUTON , INPUT ); 
  FastLED.addLeds<WS2812, MA_BROCHE_BOUTON , GRB>(&atomPixel, 1); 

  //Animation de depart pour differencier atom 1 et 2
  delay(600);
  atomPixel = CRGB(255,0,0);
  FastLED.show();
  delay(600);
  atomPixel = CRGB(0,255,0);
  FastLED.show();
  delay(600);
  atomPixel = CRGB(255,0,0);
  FastLED.show();
}

void loop() {

  if ( millis() - monChronoDepart >= 200 ) { 
    monChronoDepart = millis(); 


    /*---Envois OSC Pbhub----*/
    int lectureAngleY = myPbHub.analogRead( CANAL_KEY_UNIT_ANGLE_Y );
    int lectureAngleX = myPbHub.analogRead( CANAL_KEY_UNIT_ANGLE_X );


      //Amira 1 et 2
    monOsc.sendInt("/angley", lectureAngleY); 
    monOsc.sendInt("/anglex", lectureAngleY); 





    /*---Envois OSC TOF---*/
    int mesure = myTOF.readRangeSingleMillimeters();

      //Radhouane 2
    monOsc.sendInt("/tofvisuel", mesure);

  }

}


/*
--=== Bibliotheque outils ===--

-----ENCODER COULEUR-------
https://t-o-f.info/aide/#/m5stack/units/encoder/

  if(changementEncodeur < 0) {
   myEncoder.setLEDColorLeft( 0, 255, 0 );
   myEncoder.setLEDColorRight( 0, 0, 0 );
  } else if(changementEncodeur > 0) {
   myEncoder.setLEDColorRight( 0, 255, 0 );
   myEncoder.setLEDColorLeft( 0, 0, 0 );
  }

-----TOF-------
https://t-o-f.info/aide/#/m5stack/units/tof/


-----TRANSMITTER SANS ENCODER-------
https://t-o-f.info/aide/#/unity/osc/extosc/


/*void myOscMessageParser(MicroOscMessage & receivedOscMessage) {

  if (receivedOscMessage.checkOscAddress("/pixel")) {  
       int premierArgument = receivedOscMessage.nextAsInt();
       int deuxiemerArgument = receivedOscMessage.nextAsInt(); 
       myPbHub.setPixelColor( CANAL_KEY_UNIT_BOUTON , 0 , premierArgument,deuxiemerArgument,0 ); 
   } 
}
*/




