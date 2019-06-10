/*
   Voici le code pour le tutoriel tracker solaire

   vous pouvez retrouver le contenu du tutoriel sur http://ouiaremakers.com/

*/

//Tout d'abord on appele les bibliothèques

/*
//bibliotheque ecran LCD RGB
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

//reglage des couleur car mon LCD est un RGB
const int colorR = 100;
const int colorG = 100;
const int colorB = 100;
*/

//bibliotheque servo moteur
#include <Servo.h>

Servo MonServo; // crée l’objet pour contrôler le servomoteur

int PosServo;  // Variable de position du servo1, de 0 à 180°

// Variables de valeur des photorésistances
int PhotoGauche; 
int PhotoDroite;

//Joystick
const int x_axis = A3;  
const int y_axis = A4;
const int stick_clic = 2;

bool manualmode = false;
const int LED = 13;

int manual_speed = 2;

int Tampon = 10; // écart permis entre les photoresistances sans qu'il y ai d'ajustement des servo 
int entreePhotoGauche = A0; // Photorésistances sur A0 et A1
int entreePhotoDroite = A1;


bool mouvement = false; //condition pour mouvement des servo, cela permet d'avoir un mouvement continu
//tant que nous ne somme pas a l'equilibre +/- tampon et d'avoir une tempo lorsque nous avons l'équilibre
//(les servos cherchent moins souvent )

void setup()
{
  Serial.begin(9600);  // Monoteur série
  MonServo.attach(9); // Servo sur pin 9
  pinMode(stick_clic, INPUT_PULLUP); //pin 2 en mode lecture et pull up pour le clic du joystick
  
  pinMode(LED, OUTPUT); //pour la led
  
  //servo en position initiale
  PosServo = 90;
  MonServo.write(PosServo);
  delay (1000);
  Serial.println("Initialisation réussie");

}
void loop()
{
  //lecture du click pour savoir si on est sur le mode manuel
  int valeurStickClic = digitalRead(stick_clic);
  //Serial.print("valeurStickClic = ");
  //Serial.println(valeurStickClic);
  
  if (valeurStickClic == 0){
    delay(500);
    manualmode = !manualmode;
    if (manualmode == true){
      digitalWrite(LED, HIGH);
      Serial.println("ModeManuel");
    }
    else{
      digitalWrite(LED, LOW); 
      Serial.println("ModeAuto");
    }
  }
  
  if(manualmode)
  {
    delay(100);
    int valeurY = analogRead(y_axis);
    if (valeurY == 1023){
      PosServo-=(1*manual_speed);
      MonServo.write(PosServo);
    }
    if (valeurY == 0){
      PosServo+=(1*manual_speed);
      MonServo.write(PosServo);
    }
  }

  //mode normal de tracking
  else{
    
    delay(100);
    mouvement = false;

    // On lit les photoresistances
    PhotoGauche = analogRead(entreePhotoGauche);
    PhotoDroite = analogRead(entreePhotoDroite)+100;

    Serial.print("valeurG = ");
    Serial.println(PhotoGauche);
    Serial.print("valeurD = ");
    Serial.println(PhotoDroite);
    
    // Si la valeur de droite est plus grande (plus de lumière) que la gauche on tourne vers la droite
    if ( PhotoDroite > (PhotoGauche + Tampon)) // on applique la valeur tampon pour plus de stabilité des servos
    {
      if (PosServo < 179)
        PosServo++;
      MonServo.write(PosServo);
      mouvement = true;
    }
  
    // Si la valeur de gauche est plus grande (plus de lumière) que la droite on tourne vers la gauche
    if (PhotoGauche > (PhotoDroite + Tampon))// on applique la valeur tampon pour plus de stabilité des servos
    {
      if (PosServo > 1)
        PosServo -= 1;
      MonServo.write(PosServo);
      mouvement = true;
    } //fin boucle du Servo horizontal
  
    if (mouvement == false)
    {
      delay(500); //si on suit le soleil on peut mettre un long delay, sinon pour plus de reactivité, un faible delay
    }
  
  }




  
  

}
