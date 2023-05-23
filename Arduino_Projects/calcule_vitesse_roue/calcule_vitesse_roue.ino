// Définition des broches utilisées pour l'encodeur et la console série
 
#define encoderPinA 2
#define encoderPinB 3
#define serialBaudRate 115200

// Constantes pour le calcul de la vitesse

const float wheelDiameter = 6.5;                 // Diamètre de la roue en centimètres
const float ticksPerRevolution = 3200;          // Nombre de tics codeurs par tour de roue

volatile int encoderTicks = 0;
volatile unsigned long lastUpdateTime = 0;

float distancePerTick = 0;
volatile float speed = 0;

// Fonction d'interruption appelée lorsqu'un tic codeur est détecté sur le pin A de l'encodeur
void encoderISR() {
  
  if (digitalRead(encoderPinB) == HIGH) {
    encoderTicks++;
  } else {
    encoderTicks--;
  }
}


void setup() {

  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);

  digitalWrite(encoderPinA, HIGH);
  digitalWrite(encoderPinB, HIGH);

  // Configuration de l'interruption pour le signal d'encodeur A
  attachInterrupt(digitalPinToInterrupt(encoderPinA), encoderISR, CHANGE);

  // Calcul de la distance parcourue par tic codeur
  distancePerTick = (wheelDiameter * PI) / ticksPerRevolution;

  Serial.begin(9600);
}


void loop() {
  
  // Calcul du temps écoulé depuis la dernière mise à jour de la vitesse
  unsigned long elapsedTime = millis() - lastUpdateTime;

  // Vérification si suffisamment de temps est écoulé pour mettre à jour la vitesse
  if (elapsedTime >= 100) { // Mettre à jour toutes les 100 ms
    // Calcul de la vitesse en centimètres par seconde
    speed = (encoderTicks * distancePerTick * 1000) / elapsedTime;

    // Réinitialisation du compteur de tics codeurs et du temps de mise à jour
    encoderTicks = 0;
    lastUpdateTime = millis();
  }

  // Affichage de la vitesse sur la console série
  Serial.print("Speed: ");
  Serial.print(speed);
  Serial.println(" cm/s");

  delay(100);
}
