#include <Adafruit_NeoPixel.h>

#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>    

#include <OSCBundle.h>
#include <OSCBoards.h>

#define PIN 6
#define LEDS 450

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS, PIN, NEO_GRB + NEO_KHZ800);

EthernetUDP Udp;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // you can find this written on the board of some Arduino Ethernets or shields

//the Arduino's IP
IPAddress ip(10, 0, 1, 101);

//port numbers
const unsigned int inPort = 7770;

void setup() {
  //setup ethernet part
  Ethernet.begin(mac,ip);
  Udp.begin(inPort);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

byte buffer[128];

//reads and dispatches the incoming message
void loop(){ 
  OSCBundle bundleIN;
  int size;

  if((size = Udp.parsePacket())>0) {
    
//    for (int i = 0; i < LEDS; i++) {
//      if (i < size) {
//        strip.setPixelColor(i, strip.Color(255, 0, 0));
//      } else {
//        strip.setPixelColor(i, strip.Color(0, 0, 0));
//      }
//    }
    
    
    for (int i = 0; i < size; i++) {
      buffer[i] = Udp.read();
    }
    
    if (size == 48) {
      int rr = buffer[39];
      int gg = buffer[43];
      int bb = buffer[47];
      
      rr = min(max(0, rr), 100);
      gg = min(max(0, gg), 100);
      bb = min(max(0, bb), 100);
      
      for (int i = 0; i < LEDS; i++) {
        strip.setPixelColor(i, strip.Color(rr, gg, bb));
      }
        
      strip.show();
    }
  }
}


