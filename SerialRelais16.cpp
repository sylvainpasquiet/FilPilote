#include "SerialRelais16.h"
    
SERIAL_RELAIS_16::SERIAL_RELAIS_16(int _latchPin,int _dataPin,int _clockPin)
{
  latchPin  = _latchPin;
  dataPin   = _dataPin;
  clockPin  = _clockPin;
  pinMode(_latchPin, OUTPUT);
  pinMode(_dataPin, OUTPUT);  
  pinMode(_clockPin, OUTPUT);
  digitalWrite(latchPin, HIGH); 
}

EtatRelai SERIAL_RELAIS_16::GetRelai(char index)
{
  return(Relais[index]);
}

void SERIAL_RELAIS_16::SetRelai(char index,EtatRelai Valeur)
{
  Relais[index]=Valeur;
}

void SERIAL_RELAIS_16::SetAllRelai(EtatRelai Valeur)
{
  for(char i=0;i<16;i++)
  {
    Relais[i]=Valeur;
  }
}

void SERIAL_RELAIS_16::Refresh()
{
    digitalWrite(latchPin, LOW);
    unsigned int data=0;
    for (char i=0;i<16;i++)
    {
      if (Relais[i]!=FERME) data|=(0x01<<i);
    }
    shiftOut(dataPin, clockPin, MSBFIRST, (data>>8));  
    shiftOut(dataPin, clockPin, MSBFIRST, (data & 0xFF));  
    digitalWrite(latchPin, HIGH);
}

