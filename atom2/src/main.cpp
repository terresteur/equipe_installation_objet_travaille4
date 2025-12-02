#include <Arduino.h>
#include <MicroOscSlip.h>
#include <FastLED.h>
#include <M5_Encoder.h>
#include <VL53L0X.h>

MicroOscSlip<128> monOsc(&Serial);

#define MA_BROCHE_BOUTON 27

unsigned long monChronoDepart;

CRGB atomPixel;
VL53L0X myTOF;
M5_Encoder myEncoder;

void setup()
{

  Serial.begin(115200);
  Wire.begin();
  myTOF.init();
  myEncoder.begin();
  pinMode(MA_BROCHE_BOUTON, INPUT);
  FastLED.addLeds<WS2812, MA_BROCHE_BOUTON, GRB>(&atomPixel, 1);

  // Animation de depart pour differencier atom 1 et 2
  delay(600);
  atomPixel = CRGB(255, 0, 0);
  FastLED.show();
  delay(600);
  atomPixel = CRGB(0, 255, 0);
  FastLED.show();
  delay(600);
  atomPixel = CRGB(0, 0, 255);
  FastLED.show();
}

void loop()
{
  //---Envois OSC Encodeur----
  myEncoder.update();
  int valeurEncodeur = myEncoder.getEncoderRotation();
  int changementEncodeur = myEncoder.getEncoderChange();
  int etatBouton = myEncoder.getButtonState();

  if (millis() - monChronoDepart >= 20)
  {
    monChronoDepart = millis();

    // Ting Yung 1
    monOsc.sendInt("/angle_encod1_sons", changementEncodeur);
    monOsc.sendInt("/bouton_encod1_sons", etatBouton);

    //---Envois OSC TOF---
    int mesure = myTOF.readRangeSingleMillimeters();

    // Ting Yung 2
    monOsc.sendInt("/tof_sons", mesure);
  }

  // Couleur du encodeur
  if (changementEncodeur < 0)
  {
    myEncoder.setLEDColorLeft(0, 255, 0);
    myEncoder.setLEDColorRight(0, 0, 0);
  }
  else if (changementEncodeur > 0)
  {
    myEncoder.setLEDColorLeft(0, 0, 0);
    myEncoder.setLEDColorRight(0, 255, 0);
  }
  else
  {
    myEncoder.setLEDColorLeft(0, 0, 0);
    myEncoder.setLEDColorRight(0, 0, 0);
  }

  if (etatBouton == 0)
  {
    myEncoder.setLEDColorLeft(0, 0, 255);
    myEncoder.setLEDColorRight(0, 0, 255);
  }
}

/*
--=== Bibliotheque outils ===--

-----TOUTCH DESIGNER-------
https://t-o-f.info/aide/#/touchdesigner/aspect/

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
