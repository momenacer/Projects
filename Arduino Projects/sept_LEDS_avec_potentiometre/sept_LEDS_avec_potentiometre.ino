
const int led1 = 7; 
const int led2 = 8;
const int led3 = 9;
const int led4 = 10;
const int led5 = 11;
const int led6 = 12;
const int led7 = 13;

 
void setup() {
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  
}

void loop() {
  
  int poten = analogRead(A0);
  int val = map(poten, 0, 1023, 0, 7); 


  digitalWrite(led1, val >= 1);
  digitalWrite(led2, val >= 2);
  digitalWrite(led3, val >= 3);
  digitalWrite(led4, val >= 4);
  digitalWrite(led5, val >= 5);
  digitalWrite(led6, val >= 6);
  digitalWrite(led7, val >= 7);
}
