#ifndef SerialRelais16_h
  #define SerialRelais16_h

  #include "Arduino.h"
  
  enum EtatRelai {
    INCONNU,
    OUVERT,
    FERME
  };
  
  class SERIAL_RELAIS_16
  {
    public:
      SERIAL_RELAIS_16(int _latchPin,int _dataPin,int _clockPin);
      EtatRelai GetRelai(char index);
      void SetRelai(char index,EtatRelai Valeur);
      void SetAllRelai(EtatRelai Valeur);
      void Refresh();
    private:
      EtatRelai Relais[16];
      int latchPin;
      int dataPin;
      int clockPin;
  };
  
#endif


