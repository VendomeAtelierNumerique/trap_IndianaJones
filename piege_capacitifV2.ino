// piège capacitif par Arthur Baude pour Makery
// avec un coup de main bienvenu de Raphaël Yancey !
// modifié par Vendôme Atelier Numérique pour utiliser 3 Led et un buzzer

#include <CapacitiveSensor.h>

CapacitiveSensor cs_4_6 = CapacitiveSensor(4,6); 
int buzzerPin = 3;
int ledPinPres = 12;
int ledPinAssezLoin = 10;
int ledPinLoin = 9;

int seuilTrapLoin = 65;
int seuilTrapAssezLoin = 90;
int seuilTrapPres = 110;

#define freqTrapPres      4000
#define freqTrapAssezLoin 2000
#define freqTrapLoin      1000

boolean isTrapped = false;

void setup()                    
{   
   Serial.begin(9600);
   pinMode(buzzerPin, OUTPUT);
   pinMode(ledPinPres, OUTPUT);
   pinMode(ledPinAssezLoin, OUTPUT);
   pinMode(ledPinLoin, OUTPUT);
}

// Cette fonction active le buzzer pendant x millisecondes
void buzz(int x) {
  analogWrite(buzzerPin, 800);
  delay(x);
  analogWrite(buzzerPin, 0);
  delay(500);
}

// Cette fonction est la séquence a déclencher quand le piège s'active, à savoir les LED et le buzzer
void trappedSequence(int valeur) {
  
  // on allume une led si on est loin, 2 si on est assez loin et 3 si on est tout pres
  if(valeur > seuilTrapPres) 
  {
    analogWrite(ledPinPres, 1023); // LED on
  }
  if(valeur > seuilTrapAssezLoin) 
  {
    analogWrite(ledPinAssezLoin, 1023); // LED on
  }
  if(valeur > seuilTrapLoin) 
  {
    analogWrite(ledPinLoin, 1023); // LED on
  }

  if(valeur > seuilTrapPres) tone(buzzerPin, freqTrapPres, 500); 
  else if(valeur > seuilTrapAssezLoin) tone(buzzerPin, freqTrapAssezLoin, 500);
  else  tone(buzzerPin, freqTrapLoin, 500); 
  
  delay(500);
  analogWrite(ledPinPres, 0); // LED off
  noTone(buzzerPin);
  analogWrite(ledPinAssezLoin, 0); // LED off
  analogWrite(ledPinLoin, 0); // LED off
}

void loop()                    
{
  long start = millis();
  long total = cs_4_6.capacitiveSensor(30);
  
  isTrapped = total > seuilTrapLoin; // A chaque loop on calcule si le piège a été déclenché

  if(isTrapped) {
    trappedSequence(total);
    Serial.println(total);
  }
  
  //Serial.println(total);       
  delay(10); // limite les loops à toutes les 10ms
}
