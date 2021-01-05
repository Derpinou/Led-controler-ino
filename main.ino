#include <IRremote.h> //appel de la bibliotheque du recepteur IR
IRrecv recepteurIR(2);// création de la fonction recepteurIR associée au port d’entrée 2
decode_results results;// variable de stockage du code de touche en sortie du recepteur IR
const int Led_1 = 5; //R
const int Led_2 = 3; //G
const int Led_3 = 9; //B
int val = 0;
//. . . . . . . . . . . . . . . . . . 
void setup(){
  Serial.begin(9600);// démarrage de la liaison série
  recepteurIR.enableIRIn();  // validation du fonctionnement du recepteur IR
  pinMode(Led_1,OUTPUT);// port led paramétré en sortie
  pinMode(Led_2,OUTPUT);// port led paramétré en sortie
 }
void loop()
{
  if (recepteurIR.decode(&results))// si le recepteur fournit un code de touche
 {   
      switch(results.value)// test de la valeur du code de touche
      {     
          case 0xF7C03F://code touche ON
            val = 255;
            Led_ON(val, val, val);// appel de la fonction allumage
            Serial.println("Allumé");
          break;
          case 0xF740BF://code touche OFF
           Led_OFF();// appel de la fonction extinction
          Serial.println("éteint");
          break;
          case 16195807: //R
            Led_ON(val, 0, 0);// appel de la fonction allumage
            Serial.println("Red") ;         
          break;
          case 16228447: //G
            Led_ON(0, val, 0);// appel de la fonction allumage
            Serial.println("Green");
          break;
          case 16212127: //B
            Led_ON(0, 0, val);// appel de la fonction allumage
            Serial.println("Blue");
          break;
          case 0xF7807F://code touche DIMMER -
            Serial.println("DIMMER -"); //............
            val = val - 10;
            if (val < 0) {
                val = 0;
            }
            Led_ON(val, val, val);// appel de la fonction allumage
            Serial.print("Rapport Cyclique: ");
            Serial.println(calc_Duty_Cycle(val));
          break;
          case 0xF700FF://code  touche DIMMER +
            Serial.println("DIMMER +");//............
            val = val + 10;
            if (val > 255) {
                val = 255;
            }
            Led_ON(val, val, val);// appel de la fonction allumage
            Serial.print("Rapport Cyclique: ");
            Serial.println(calc_Duty_Cycle(val));
          break ;                    
        }
       recepteurIR.resume(); // remise du recepteur IR en attente du code suivant
  }
}

void Led_ON(int r, int g, int b) {//Allumer les leds selonsl'appel de la fonction
  analogWrite(Led_1, r);
  analogWrite(Led_2, g);
  analogWrite(Led_3, b);
}

void Led_OFF(){//éteinde toutes les led
  analogWrite(Led_1, LOW);
  analogWrite(Led_2, LOW);
  analogWrite(Led_3, LOW);
}

int calc_Duty_Cycle(int a) {//Fonction de calcul du rapport cyclique
    return a*100/255;
}
