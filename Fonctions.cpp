#include "Fonctions.h"

void AffichageEcran(void* pAfficheur,char* Message,SERIAL_RELAIS_16* SerialRelai16) 
{
  #ifndef AFFICHAGE_SERIAL
    U8GLIB_SSD1306_128X64* LocalAfficheur = pAfficheur;
  #endif
  char i;
  char f=0;
  char* Position;
  char Position1;
  char Position2;
  struct Lignes_typ Lignes;
  Lignes.NbLignes=0;
  while(strlen(Message)>0) 
  {
    Position=strchr(Message,'\n');
    if(Message==Position)
    {
      //Premier caractère est un retour à la ligne
      f=f+1;  
      memmove(Message,Message+1,strlen(Message));
    }
    else
    {
      Lignes.Lignes[Lignes.NbLignes].Ligne[0]=0;
      if (Position==0) 
      {
        // pas d'autre retour à la ligne
        strcpy(Lignes.Lignes[Lignes.NbLignes].Ligne,Message);
        Message[0]=0; 
      }
      else
      {
        // extraire les donnees jusqu'au retour à la ligne
        strncpy(Lignes.Lignes[Lignes.NbLignes].Ligne,Message,Position-Message);
        Lignes.Lignes[Lignes.NbLignes].Ligne[Position-Message]=0;
        // on supprime la chaine et le retour à la ligne 
        memmove(Message,Position+1,strlen(Position)-1);       
        Message[strlen(Position)-1]=0;
      }
      Lignes.Lignes[Lignes.NbLignes].Position=f;
      f=f+2;
      Lignes.NbLignes++;
    }
  }

  LocalAfficheur->firstPage();  
  do 
  {
    
    LocalAfficheur->setColorIndex(1);
    LocalAfficheur->setFont(u8g_font_unifont); 

    LocalAfficheur->drawBitmapP( -4, 2, 5, 37, LogoJeedom); 

    if (Lignes.NbLignes)
    {
      for (i=0;i<Lignes.NbLignes;i++)
      {
        Position1= 37 + ((123-37)>>1) - ((LocalAfficheur->getStrWidth(Lignes.Lignes[i].Ligne))>>1);
        Position2=(((unsigned char)(LocalAfficheur->getFontAscent()<<1) + ((unsigned char)Lignes.Lignes[i].Position*(LocalAfficheur->getFontAscent() - LocalAfficheur->getFontDescent()))>>1));
        LocalAfficheur->drawStr(Position1, Position2, Lignes.Lignes[i].Ligne);  
      }  
    }
    
    LocalAfficheur->drawLine(0,52,127,52);
    
    for (i=0;i<16;i++)
    {    
      if (SerialRelai16->GetRelai(i)==INCONNU)  LocalAfficheur->drawBitmapP( 0+8*i, 55, 1, 8, BmpX);
      if (SerialRelai16->GetRelai(i)==OUVERT)   LocalAfficheur->drawBitmapP( 0+8*i, 55, 1, 8, BmpOFF);
      if (SerialRelai16->GetRelai(i)==FERME)    LocalAfficheur->drawBitmapP( 0+8*i, 55, 1, 8, BmpON);
    }       
  } while(LocalAfficheur->nextPage());
  
}

void FormatIntDigit(int Valeur,char numdigit,String* Resultat)
{
  String Result=String(Valeur);
  while(Result.length() < numdigit)
  {
    Result="0"+Result;
  }
  *Resultat+=Result;
  return;
}

void FormatIntDigit(int Valeur,char numdigit,char* Resultat)
{
  char ValueStr[10];
  sscanf(ValueStr,"%u",Valeur);
  strcpy(Resultat,"\0");
  while(strlen(Resultat)< numdigit)
  {
    strcat(Resultat,"\0");
  }
  strcat(Resultat,ValueStr);
  return;
}

//void sJour(char jour,String* Resultat)
//{
//  switch(jour)
//  {
//    case 1:   *Resultat+="Dimanche\0";  return;  
//    case 2:   *Resultat+="Lundi\0";     return;  
//    case 3:   *Resultat+="Mardi\0";     return;  
//    case 4:   *Resultat+="Mercredi\0";  return;  
//    case 5:   *Resultat+="Jeudi\0";     return;  
//    case 6:   *Resultat+="Vendredi\0";  return;  
//    case 7:   *Resultat+="Samedi\0";    return;  
//    default:  *Resultat+="?\0";         return;             
//  }
//}
//
//void sMois(char mois,String* Resultat)
//{
//  switch(mois)
//  {
//    case 1:   *Resultat+="Janvier\0";     return;  
//    case 2:   *Resultat+="Fevrier\0";     return;  
//    case 3:   *Resultat+="Mars\0";        return;  
//    case 4:   *Resultat+="Avril\0";       return;  
//    case 5:   *Resultat+="Mai\0";         return;  
//    case 6:   *Resultat+="Juin\0";        return;  
//    case 7:   *Resultat+="Juillet\0";     return;  
//    case 8:   *Resultat+="Aout\0";        return;  
//    case 9:   *Resultat+="Septembre\0";   return;  
//    case 10:  *Resultat+="Octobre\0";     return;  
//    case 11:  *Resultat+="Novembre\0";    return;  
//    case 12:  *Resultat+="Decembre\0";    return;      
//    default:  *Resultat+="?\0";           return;            
//  }
//}

void sJour(char jour,char* Resultat)
{
  switch(jour)
  {
    case 1:   strcpy(Resultat,"Dimanche\0");  return;  
    case 2:   strcpy(Resultat,"Lundi\0");     return;  
    case 3:   strcpy(Resultat,"Mardi\0");     return;  
    case 4:   strcpy(Resultat,"Mercredi\0");  return;  
    case 5:   strcpy(Resultat,"Jeudi\0");     return;  
    case 6:   strcpy(Resultat,"Vendredi\0");  return;  
    case 7:   strcpy(Resultat,"Samedi\0");    return;  
    default:  strcpy(Resultat,"?\0");         return;             
  }
}

void sMois(char mois,char* Resultat)
{
  switch(mois)
  {
    case 1:   strcpy(Resultat,"Janvier\0");  return;  
    case 2:   strcpy(Resultat,"Fevrier\0");  return;  
    case 3:   strcpy(Resultat,"Mars\0");     return;  
    case 4:   strcpy(Resultat,"Avril\0");    return;  
    case 5:   strcpy(Resultat,"Mai\0");      return;  
    case 6:   strcpy(Resultat,"Juin\0");     return;  
    case 7:   strcpy(Resultat,"Juillet\0");  return;  
    case 8:   strcpy(Resultat,"Aout\0");     return;  
    case 9:   strcpy(Resultat,"Septembre\0");return;  
    case 10:  strcpy(Resultat,"Octobre\0");  return;  
    case 11:  strcpy(Resultat,"Novemebre\0");return;      
    case 12:  strcpy(Resultat,"Decembre\0"); return;   
    default:  strcpy(Resultat,"?\0");        return;            
  }
}

void ResetWatchdog(int Watchdog_Pin,void (*ptrWait) (const uint32_t))
{
  pinMode(Watchdog_Pin, OUTPUT);
  digitalWrite(Watchdog_Pin,LOW);
  ptrWait(100);
  pinMode(Watchdog_Pin, INPUT);
}

void FormatMessage(char* TmpMessage)
{
  char longueur,i,j;

  for(i=0;i<strlen(TmpMessage)-2;i++)
  {
    if ((TmpMessage[i]=='\"')&&(TmpMessage[i+1]=='\"'))
    {
      TmpMessage[i+1]='x';
      for (j=i;j<strlen(TmpMessage)-1;j++) TmpMessage[j]=TmpMessage[j+1];
      TmpMessage[j]=0;  
    }
  }
}

