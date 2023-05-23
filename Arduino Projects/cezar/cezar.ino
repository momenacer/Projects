const int buttonPin = 5;
const int greenLedPin = 6;
const int yellowLedPin = 7;
const int redLedPin = 8;

char message[100];
int state = 0;
int shift = 2;

void setup() {
  
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);

  digitalWrite(greenLedPin, LOW);
  digitalWrite(yellowLedPin, LOW);
  digitalWrite(redLedPin, LOW);

  Serial.begin(9600);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    state = (state + 1) % 3;
    updateLedState();
    delay(500); 
  }
}

void updateLedState() {
  digitalWrite(greenLedPin, state == 2 ? HIGH : LOW);
  digitalWrite(yellowLedPin, state == 0 ? HIGH : LOW);
  digitalWrite(redLedPin, state == 1 ? HIGH : LOW);
  
  if (state == 0) {
    
    Serial.println("Etat 1 : Led Jaune allumée - Entrez un message : ");
    while (Serial.available() == 0);
    Serial.readBytesUntil('\n', message, sizeof(message));
    Serial.print("Message : ");
    Serial.println(message);
  } else if (state == 1) {
    Serial.println("Etat 2 : Led Rouge allumée - Message crypté : ");
    encrypt(message, shift);
    Serial.println(message);
  } else if (state == 2) {
    Serial.println("Etat 3 : Led Verte allumée - Message décrypté : ");
    decrypt(message, shift);
    Serial.println(message);
  }
  
}

void encrypt(char *message, int shift) {
  
  int i = 0;
  while (message[i] != '\0') {
    if (message[i] >= 'A' && message[i] <= 'Z')
      message[i] = 'A' + (message[i] - 'A' + shift) % 26;
    else if (message[i] >= 'a' && message[i] <= 'z')
      message[i] = 'a' + (message[i] - 'a' + shift) % 26;
    i++;
  }
  
}

void decrypt(char *message, int shift) {
  
  encrypt(message, 26 - shift);
  
}
