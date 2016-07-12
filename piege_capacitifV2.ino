// piège capacitif par Arthur Baude pour Makery
// avec un coup de main bienvenu de Raphaël Yancey !

#include <CapacitiveSensor.h>

CapacitiveSensor cs_4_6 = CapacitiveSensor(4,6); 
int buzzerPin = 9;
int ledPin = 10;

boolean isTrapped = false;

void setup()                    
{   
   Serial.begin(9600);
   pinMode(buzzerPin, OUTPUT);
}

// Cette fonction active le buzzer pendant x millisecondes
void buzz(int x) {
  analogWrite(buzzerPin, 800);
  delay(x);
  analogWrite(buzzerPin, 0);
  delay(500);
}

// Cette fonction est la séquence a déclencher quand le piège s'active, à savoir LED + buzzer
void trappedSequence() {
  analogWrite(ledPin, 1023); // LED on
  buzz(1000); 
 
  analogWrite(ledPin, 0); // LED off
}

void loop()                    
{
  long start = millis();
  long total = cs_4_6.capacitiveSensor(30);
  
  isTrapped = total > 105; // A chaque loop on calcule si le piège a été déclenché - c'est ici qu'on change le seuil du capacitif

 
  if(isTrapped) trappedSequence();

  
  Serial.println(total);       
  delay(10); // limite les loops à toutes les 10ms
}
