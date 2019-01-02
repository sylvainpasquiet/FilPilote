/**
 * The MySensors Arduino library handles the wireless radio link and protocol
 * between your home built sensors/actuators and HA controller of choice.
 * The sensors forms a self healing radio network with optional repeaters. Each
 * repeater and gateway builds a routing tables in EEPROM which keeps track of the
 * network topology allowing messages to be routed to nodes.
 *
 * Created by Henrik Ekblad <henrik.ekblad@mysensors.org>
 * Copyright (C) 2013-2015 Sensnology AB
 * Full contributor list: https://github.com/mysensors/Arduino/graphs/contributors
 *
 * Documentation: http://www.mysensors.org
 * Support Forum: http://forum.mysensors.org
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 *******************************
 *
 * REVISION HISTORY
 * Version 1.0 - Henrik Ekblad
 *
 * DESCRIPTION
 * Example sketch showing how to control physical relays.
 * This example will remember relay state after power failure.
 * http://www.mysensors.org/build/relay
 */

// Enable debug prints to serial monitor
#define MY_DEBUG
#define MY_SPLASH_SCREEN_DISABLED

// Enable and select radio type attached
#define MY_RADIO_NRF24
//#define MY_RADIO_RFM69

// Enable repeater functionality for this node
#define MY_REPEATER_FEATURE
#define MY_DISABLED_SERIAL

#define MY_DEFAULT_LED_BLINK_PERIOD 100
// Flash leds on rx/tx/err
// Uncomment to override default HW configurations
#define MY_DEFAULT_ERR_LED_PIN 2  // Error led pin
#define MY_DEFAULT_RX_LED_PIN  4  // Receive led pin
#define MY_DEFAULT_TX_LED_PIN  3  // the PCB, on board LED

#define MY_NODE_ID 10

#define MY_RF24_CHANNEL  125
#define MY_RF24_PA_LEVEL RF24_PA_HIGH

#include <MySensors.h>
#include <SPI.h>
#include "Fonctions.h"
#include <Time.h>
#include <Timezone.h>

#define WATCHDOG_PIN 5

#define AFFICHAGE_SERIAL

MyMessage gMsg;

SERIAL_RELAIS_16 gRelais(7,8,6);
U8GLIB_SSD1306_128X64 gAfficheur;
unsigned char gEtape=0;
unsigned long gTempo=0;
unsigned long gOldTime=0;
bool gResetSignal=false;
bool gMajSignal=false;  
bool gDateSignal=false; 
bool gRelaiSignal=false; 

unsigned short int gOldErreur=999;
unsigned short int gActualErreur;

unsigned short int gOldCompteurReboot=999;
unsigned short int gActualCompteurReboot;

time_t gDate;

//Central European Time (Frankfurt, Paris)
TimeChangeRule CEST = {"CEST", Last, Sun, Mar, 2, 120};     //Central European Summer Time
TimeChangeRule CET = {"CET ", Last, Sun, Oct, 3, 60};       //Central European Standard Time
Timezone CE(CEST, CET);


#define CHILD_ID_RELAIS           0
#define CHILD_ID_REBOOT           1
#define CHILD_ID_ERREUR_MYSENSORS 2
#define CHILD_ID_CMD_RESET_STATS  3
#define CHILD_ID_CMD_MAJ          4

bool MajHeure(bool l_cmd,bool* l_statut)
{
  if (!*l_statut)
  {
    if  (l_cmd)
    {
      *l_statut=true;
      if (!requestTime(true))              
      {
          return(false);
      }  
    }
  }
  return(true);
}

bool Update(MyMessage* l_Msg, unsigned char l_Child,unsigned char l_Type,float l_Actual, float* l_Last,unsigned short int* l_Erreur,bool* l_statut)
{
  if (!*l_statut)
  {
    if ((abs(l_Actual-*l_Last)>0.05))              
    {
        *l_statut=true;
        if (!send(l_Msg->setSensor(l_Child).setType(l_Type).set(l_Actual,1),true))   {(*l_Erreur)++;return(false);}
        *l_Last=l_Actual;
    }  
  }
  return(true);
}
bool Update(MyMessage* l_Msg, unsigned char l_Child,unsigned char l_Type,unsigned char l_Actual, unsigned char* l_Last,unsigned short int* l_Erreur,bool* l_statut)
{
  if (!*l_statut)
  {
    if (l_Actual!=*l_Last)             
    {
        *l_statut=true;
        if (!send(l_Msg->setSensor(l_Child).setType(l_Type).set(l_Actual),true))  {(*l_Erreur)++;return(false);}
        *l_Last=l_Actual;
    }  
  }
  return(true);
}
bool Update(MyMessage* l_Msg, unsigned char l_Child,unsigned char l_Type,unsigned short int l_Actual, unsigned short int* l_Last,unsigned short int* l_Erreur,bool* l_statut)
{
  if (!*l_statut)
  {
    if (l_Actual!=*l_Last)                 
    {
        *l_statut=true;
        if (!send(l_Msg->setSensor(l_Child).setType(l_Type).set(l_Actual),true))   {(*l_Erreur)++;return(false);}
        *l_Last=l_Actual;
    }  
  }
  return(true);
}
bool Update(MyMessage* l_Msg, unsigned char l_Child,unsigned char l_Type,unsigned long l_Actual, unsigned long* l_Last,unsigned short int* l_Erreur,bool* l_statut)
{
  if (!*l_statut)
  {
    if (l_Actual!=*l_Last)             
    {
        *l_statut=true;
        if (!send(l_Msg->setSensor(l_Child).setType(l_Type).set(l_Actual),true))   {(*l_Erreur)++;return(false);}
        *l_Last=l_Actual;
    }  
  }
  return(true);
}
bool Update(MyMessage* l_Msg, unsigned char l_Child,unsigned char l_Type,char* l_Actual, char* l_Last,unsigned short int* l_Erreur,bool* l_statut)
{
  if (!*l_statut)
  {
    if ((strlen(l_Actual)!=strlen(l_Last))||(strcmp(l_Actual,l_Last)!=0))              
    {
        *l_statut=true;
        if (!send(l_Msg->setSensor(l_Child).setType(l_Type).set(l_Actual),true))   {(*l_Erreur)++;return(false);}
        strcpy(l_Last,l_Actual);
    } 
  }
  return(true);
}

void ResetStatistiques()
{
  gActualErreur=0;
  gActualCompteurReboot=0;
  gOldErreur=99;
  gOldCompteurReboot=99;
}

void before()
{
  char gMessageChr[20];
  Serial.begin(115200);
  sprintf(gMessageChr,"\n\nBooting\0");
  AffichageEcran(&gAfficheur,gMessageChr,&gRelais);
  gRelais.SetAllRelai(INCONNU);
  gRelais.Refresh();
  sprintf(gMessageChr,"\nInit\nMySensor\0");
  AffichageEcran(&gAfficheur,gMessageChr,&gRelais);
}

void setup()
{
  gActualCompteurReboot     =(((unsigned short int)loadState(0))<<8) + (unsigned short int)loadState(1);
  gActualErreur             =(((unsigned short int)loadState(2))<<8) + (unsigned short int)loadState(3);
}

void presentation()
{
  // Send the sketch version information to the gateway and Controller
  sendSketchInfo("Carte Fil Pilote", "2.00");
  
  present(CHILD_ID_RELAIS           , S_CUSTOM);  
  present(CHILD_ID_REBOOT           , S_CUSTOM);
  present(CHILD_ID_ERREUR_MYSENSORS , S_CUSTOM);
  
  request(CHILD_ID_RELAIS           , V_VAR5);
  request(CHILD_ID_REBOOT           , V_VAR1);
  request(CHILD_ID_ERREUR_MYSENSORS , V_VAR1);
}

void SaveData(unsigned char Offset,unsigned short int Value)
{
  saveState(0+Offset, (char)(((unsigned short int)gActualCompteurReboot>>8)& 0x00ff));
  saveState(1+Offset, (char)(((unsigned short int)gActualCompteurReboot>>0)& 0x00ff));  
}

void loop()
{
  bool l_Statut;
  static bool l_MAJHeure=false;
  char gMessageChr[40];
  char temp[20]="\0";
  
  ResetWatchdog(WATCHDOG_PIN,wait);
  l_Statut=false;
  
  switch(gEtape)
  {
    case 0:
      gActualCompteurReboot++;
      SaveData(0,gActualCompteurReboot);   
      sprintf(gMessageChr,"\nMySensor\nok\0");
      AffichageEcran(&gAfficheur,gMessageChr,&gRelais);      
      gTempo=millis();
      gOldTime=millis();
      gEtape=1;
      break;
    case 1:
      if (millis()-gTempo>1000) gEtape=10;
      break;       
    case 10: 
      sprintf(gMessageChr,"Reboot\n%u\nErr Com\n%u\0",gActualCompteurReboot,gActualErreur);
      AffichageEcran(&gAfficheur,gMessageChr,&gRelais);
      gTempo=millis();
      gEtape=11;
      break;  
    case 11:
      if (millis()-gTempo>1000) gEtape=20;
      break;   
    case 20: 
      sprintf(gMessageChr,"\nMise a\njour\ndate");
      AffichageEcran(&gAfficheur,gMessageChr,&gRelais);
      l_MAJHeure=true;
      gEtape=21;
      break;  
    case 21: 
      if (gDateSignal) {l_MAJHeure=false;gDateSignal=false;gEtape=30;}    
      break;     
    case 30:
      sprintf(gMessageChr,"\nMise a\njour\nrelais");
      AffichageEcran(&gAfficheur,gMessageChr,&gRelais);
      l_Statut=true;
      request(CHILD_ID_RELAIS           , V_VAR5);
      if (gRelaiSignal) {gRelaiSignal=false;gEtape=40;}
      else {gEtape=31;}
      break;      
     case 31:
      AffichageEcran(&gAfficheur,gMessageChr,&gRelais);
      l_Statut=true;
      request(CHILD_ID_RELAIS           , V_VAR5);
      if (gRelaiSignal) {gRelaiSignal=false;gEtape=40;}
      else {gEtape=31;}
      break;         
    case 40:
      strcpy(gMessageChr,"\0");
      sJour((char)weekday(gDate),gMessageChr);
      sMois((char)month(gDate),temp);
      sprintf(gMessageChr,"%s\n%u\n%s\n%u",gMessageChr,day(gDate),temp,year(gDate));
      AffichageEcran(&gAfficheur,gMessageChr,&gRelais);
      gTempo=millis();
      gEtape=41;
      break;  
    case 41:
      if (millis()-gTempo>1000) 
      {
        gEtape=100;
        gTempo=millis();
      }
      break;        
    default:
      sprintf(gMessageChr,"\n\n%02u:%02u:%02u",hour(gDate),minute(gDate),second(gDate));
      AffichageEcran(&gAfficheur,gMessageChr,&gRelais);
      if (millis()-gTempo>1000) {gEtape++;gTempo=millis();}
      if (gEtape>180) gEtape=20;
      if (gMajSignal) {gEtape=30;gMajSignal=false;}
      if (gResetSignal) {gEtape=200;gResetSignal=false;}
      break;
      
    case 200:
      ResetStatistiques();
      SaveData(0,gActualCompteurReboot);
      SaveData(2,gActualErreur);
      gEtape=10;
      break;
  } 
  
  MajHeure(l_MAJHeure,&l_Statut);
  Update(&gMsg,CHILD_ID_REBOOT            ,V_VAR1 ,gActualCompteurReboot  ,&gOldCompteurReboot ,&gActualErreur ,&l_Statut);   
  Update(&gMsg,CHILD_ID_ERREUR_MYSENSORS  ,V_VAR1 ,gActualErreur          ,&gOldErreur         ,&gActualErreur ,&l_Statut);   

  if (millis()-gOldTime>=1000)
  {
    gOldTime=millis();
    gDate++;
  }
  
  wait(50);
}

void receive(const MyMessage &l_message)
{
  char l_i;
  char l_EtatRelaisStr[40];
  //Serial.println(l_message.sensor);
  //Serial.println(l_message.type);
  if ((l_message.type==V_VAR5)&&(l_message.sensor==CHILD_ID_RELAIS))
  {
    memset(l_EtatRelaisStr,0,sizeof(l_EtatRelaisStr));
    l_message.getString(l_EtatRelaisStr);
    FormatMessage(l_EtatRelaisStr);
    gRelais.SetAllRelai(INCONNU);
    if (strlen(l_EtatRelaisStr)==18)
    {
      gRelaiSignal=true;   
      for (l_i=2;l_i<18;l_i++)
      {
        switch(l_EtatRelaisStr[l_i])
        {
          case '0': gRelais.SetRelai(l_i-2,OUVERT);  break;           
          case '1': gRelais.SetRelai(l_i-2,FERME);   break;        
          default:  gRelais.SetRelai(l_i-2,INCONNU); break;
        }
      } 
    }
    gRelais.Refresh();                                                                          
  }  
  if ((l_message.type==V_CUSTOM)&&(l_message.sensor==CHILD_ID_CMD_RESET_STATS))
  {
    gResetSignal=true;
  }     
  if ((l_message.type==V_CUSTOM)&&(l_message.sensor==CHILD_ID_CMD_MAJ))
  {
    gMajSignal=true;                                                                             
  }
}

void receiveTime(unsigned long ts)
{
  gDate=CE.toLocal(ts);
  gDateSignal=true; 
}

