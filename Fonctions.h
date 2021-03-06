#include <Arduino.h>
#include <U8glib.h>       // U8glib modified 
#include "SerialRelais16.h"

#ifndef Fonctions_h
  #define Fonctions_h
    
  struct Ligne_typ 
  {
    char  Ligne[16];
    char Position;
  };
  struct Lignes_typ 
  {
    char NbLignes;
    Ligne_typ Lignes[4];
  };
  
  const uint8_t BmpON[] U8G_PROGMEM = 
  {
    0xFE,         // 11111110
    0xFE,         // 11111110
    0xFE,         // 11111110  
    0xFE,         // 11111110
    0xFE,         // 11111110 
    0xFE,         // 11111110
    0xFE,         // 11111110  
    0xFE,         // 11111110
  };
  
  const uint8_t BmpOFF[] U8G_PROGMEM = 
  {
    0xFE,         // 11111110 
    0x82,         // 10000010
    0x82,         // 10000010
    0x82,         // 10000010
    0x82,         // 10000010 
    0x82,         // 10000010
    0x82,         // 10000010 
    0xFE,         // 11111110
  };
  
  const uint8_t BmpX[] U8G_PROGMEM = {
    0x82,         // 10000010 
    0x44,         // 01000100
    0x28,         // 00101000
    0x10,         // 00010000
    0x10,         // 00010000 
    0x28,         // 00101000
    0x44,         // 01000100 
    0x82,         // 10000010
  };
  
      
  const uint8_t LogoJeedom[] U8G_PROGMEM = {
    0x00, 0x00, 0x60, 0x00, 0x00,
    0x00, 0x00, 0x70, 0x00, 0x00,
    0x00, 0x00, 0xf8, 0x00, 0x80,
    0x00, 0x01, 0xf8, 0x00, 0x80,
    0x00, 0x03, 0xfc, 0x04, 0x80,
    0x00, 0x03, 0xfc, 0x04, 0x80,
    0x00, 0x03, 0xfc, 0x04, 0x80,
    0x00, 0x07, 0xfe, 0x3f, 0x00,
    0x00, 0x07, 0xff, 0x3f, 0x80,
    0x00, 0x0f, 0xff, 0xbf, 0x00,
    0x00, 0x1f, 0xdf, 0xbf, 0x00,
    0x00, 0x3f, 0x8f, 0xff, 0x00,
    0x00, 0x3f, 0x0f, 0xff, 0x00,
    0x00, 0x7e, 0x07, 0xff, 0x00,
    0x00, 0xfe, 0x03, 0xff, 0x00,
    0x01, 0xff, 0xff, 0xff, 0x00,
    0x01, 0xff, 0xff, 0xff, 0x00,
    0x03, 0xff, 0xff, 0xfe, 0x00,
    0x07, 0xff, 0xff, 0xff, 0x00,
    0x00, 0x78, 0xff, 0xff, 0x00,
    0x00, 0x78, 0xff, 0xff, 0x80,
    0x00, 0x78, 0xff, 0xff, 0xc0,
    0x00, 0x7f, 0xff, 0xef, 0xc0,
    0x00, 0x7f, 0xff, 0xe7, 0xe0,
    0x00, 0x78, 0xff, 0xe3, 0xf0,
    0x00, 0x78, 0xff, 0xe0, 0x00,
    0x00, 0x78, 0xff, 0xe0, 0x00,
    0x00, 0x78, 0xff, 0xe0, 0x00,
    0x00, 0x78, 0xff, 0xe0, 0x00,
    0x00, 0x78, 0xff, 0xe0, 0x00,
    0x00, 0x78, 0xff, 0xe0, 0x00,
    0x00, 0x78, 0xff, 0xe0, 0x00,
    0x00, 0x38, 0xff, 0xc0, 0x00,
    0x07, 0x07, 0x00, 0x00, 0x00,
    0x07, 0x87, 0x00, 0x00, 0x00,
    0x07, 0x87, 0x00, 0x00, 0x00,
    0x07, 0xff, 0x00, 0x00, 0x00,
    0x07, 0xff, 0x00, 0x00, 0x00,
    0x07, 0xff, 0x00, 0x00, 0x00
  };
  
  void AffichageEcran(void* pAfficheur,char* Message,SERIAL_RELAIS_16* SerialRelai16); 
  void FormatIntDigit(int Valeur,char numdigit,char* Resultat);
//  void FormatIntDigit(int Valeur,char numdigit,String* Resultat);
//  void sJour(char jour,String* Resultat);
//  void sMois(char jour,String* Resultat);
  void ResetWatchdog(int Watchdog_Pin,void (*ptrWait) (const uint32_t));
  void FormatMessage(char* TmpMessage);
  void sJour(char jour,char* Resultat);
  void sMois(char mois,char* Resultat);  
#endif
