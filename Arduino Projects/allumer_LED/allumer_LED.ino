const int lampPin = 2;

void setup() {
  pinMode(lampPin, OUTPUT);  
}

void loop() {
  digitalWrite(lampPin, HIGH); 
  delay(1000);  // Attendre 1 seconde
  
  digitalWrite(lampPin, LOW);  // Éteindre la lampe
  delay(1000);  // Attendre 1 seconde
  
}
