/**************************************************************************************************************************************************************************************/
/*                                                                                                                                                                                    */
/*  V01.00                                                                                                                                                                            */
/*      Passage en MySensors       	                                                                                                                                         */
/**************************************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************************************/
/*                                                                                                                                                                                    */
/*  V00.21                                                                                                                                                                            */
/*      Le croquis utilise 28 186 octets (91%) de l'espace de stockage de programmes. Le maximum est de 30 720 octets.                                                                */
/*      Les variables globales utilisent 1 335 octets (65%) de mémoire dynamique, ce qui laisse 713 octets pour les variables locales. Le maximum est de 2 048 octets.                */
/*  Log:                                                                                                                                                                              */
/*      - Integration des requetes vers jeedom dans une classe JEEDOM afin d'augmenter la lisibilité du code principal, d'améliorer sa modularité et réduire le code                  */
/**************************************************************************************************************************************************************************************/
/*                                                                                                                                                                                    */
/*  V00.20                                                                                                                                                                            */
/*      Le croquis utilise 28 260 octets (91%) de l'espace de stockage de programmes. Le maximum est de 30 720 octets.                                                                */
/*      Les variables globales utilisent 1 343 octets (65%) de mémoire dynamique, ce qui laisse 705 octets pour les variables locales. Le maximum est de 2 048 octets.                */
/*  Log:                                                                                                                                                                              */
/*      - Intégration pilotage des 16 relais via deux 74HC595(SPI vers parallele) en utilsant une com SPI sous la forme d'une classe SERIAL_74HC595 implementant les fonctions de base*/
/*        et d'une classe SERIAL_RELAIS_16 gérant 2 objets SERIAL_74HC595 (74HC595 cablés en série)                                                                                   */
/**************************************************************************************************************************************************************************************/
/*                                                                                                                                                                                    */
/*  V00.11                                                                                                                                                                            */
/*      Le croquis utilise 27 916 octets (90%) de l'espace de stockage de programmes. Le maximum est de 30 720 octets.                                                                */
/*      Les variables globales utilisent 1 312 octets (64%) de mémoire dynamique, ce qui laisse 736 octets pour les variables locales. Le maximum est de 2 048 octets.                */
/*  Log:                                                                                                                                                                              */
/*      - Passage sur une version lègère MyU8glib de la bibliotèque U8glib pour limitation de la taille du code                                                                       */
/*        Fichier u8g_font_data.c / définition police const "u8g_fntpgm_uint8_t u8g_font_unifont[5551]" => "u8g_fntpgm_uint8_t u8g_font_unifont[3343]"                                */
/**************************************************************************************************************************************************************************************/
/*  V00.10 Premiere version                                                                                                                                                           */
/*      Le croquis utilise 30 124 octets (98%) de l'espace de stockage de programmes. Le maximum est de 30 720 octets.                                                                */
/*      Les variables globales utilisent 1 312 octets (64%) de mémoire dynamique, ce qui laisse 736 octets pour les variables locales. Le maximum est de 2 048 octets.                */
/*                                                                                                                                                                                    */
/**************************************************************************************************************************************************************************************/

