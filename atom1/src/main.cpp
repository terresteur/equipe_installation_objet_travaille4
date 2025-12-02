#include <Arduino.h>
#include <M5_PbHub.h>
#include <MicroOscSlip.h>
#include <FastLED.h>
#include <M5_Encoder.h>
#include <VL53L0X.h>

MicroOscSlip<128> monOsc(&Serial);

#define CANAL_KEY_UNIT_ANGLE_Y 0      // amira
#define CANAL_KEY_UNIT_ANGLE_X 1      // amira
#define CANAL_KEY_UNIT_ANGLE_VOLUME 2 // megane
#define CANAL_KEY_UNIT_BOUTON 3       // radhouane
#define MA_BROCHE_BOUTON 27

unsigned long monChronoDepart;

M5_PbHub myPbHub;
CRGB atomPixel;
M5_Encoder myEncoder;
VL53L0X myTOF;

void setup()
{

  Serial.begin(115200);
  myPbHub.begin();
  myTOF.init();
  Wire.begin();
  myEncoder.begin();
  pinMode(MA_BROCHE_BOUTON, INPUT);
  FastLED.addLeds<WS2812, MA_BROCHE_BOUTON, GRB>(&atomPixel, 1);
  myPbHub.setPixelCount(CANAL_KEY_UNIT_BOUTON, 1);

  // Animation de depart pour differencier atom 1 et 2
  delay(600);
  atomPixel = CRGB(0, 0, 255);
  FastLED.show();
  delay(600);
  atomPixel = CRGB(0, 255, 0);
  FastLED.show();
  delay(600);
  atomPixel = CRGB(255, 0, 0);
  FastLED.show();
}

void loop()
{

  // analog et digital read n'on pas besoin d'être ralenti, sauf les envois osc
  // lecture des unit connecté au arduino
  int lectureAngleY = myPbHub.analogRead(CANAL_KEY_UNIT_ANGLE_Y);
  int lectureAngleX = myPbHub.analogRead(CANAL_KEY_UNIT_ANGLE_X);
  // int lectureAngleVolume = myPbHub.analogRead( CANAL_KEY_UNIT_ANGLE_VOLUME );
  int maLectureKey = myPbHub.digitalRead(CANAL_KEY_UNIT_BOUTON);
  int mesure = myTOF.readRangeSingleMillimeters();
  if (millis() - monChronoDepart >= 20)
  {
    monChronoDepart = millis();
    // changement couleur key
    if (maLectureKey == 0)
    {
      atomPixel = CRGB(50, 205, 50);
      FastLED.show();
    }
    else if (maLectureKey == 1)
    {
      atomPixel = CRGB(0, 0, 0);
      FastLED.show();
    }

    // Amira 1 et 2
    monOsc.sendInt("/angle_y", lectureAngleY);
    monOsc.sendInt("/angle_x", lectureAngleX);
    // Megane 1
    // monOsc.sendInt("/angle_volume", lectureAngleY);
    // Radhouane 1
    monOsc.sendInt("/bouton", maLectureKey);

    //---Envois OSC Encodeur----
    /*int changementEncodeur = myEncoder.getEncoderChange();
    int etatBouton = myEncoder.getButtonState();

    //Megane 2
    monOsc.sendInt("/angle_encod2_visuel", changementEncodeur);
    monOsc.sendInt("/bouton_encod2_visuel", etatBouton);
    myEncoder.update();*/

    //---Envois OSC TOF---

    // Radhouane 2
    monOsc.sendInt("/tof_visuel", mesure);
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