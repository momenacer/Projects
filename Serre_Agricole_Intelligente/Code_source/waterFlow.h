#define FLOWSENSORPIN 2
namespace waterFlow {
volatile long flowTic ;
void flow () // Interrupt function
{
  flowTic++;
}
void set() {
  pinMode(FLOWSENSORPIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(FLOWSENSORPIN), flow, RISING); // Setup Interrupt
}


void openFor(float auxWaterVolume , void (*open)()  , void (*close)()) {
  long oldTicNumber = flowTic ;
  float neededTics =  auxWaterVolume / 0.00255;
  Serial.print(" neededTics");
  Serial.println( neededTics);
  Serial.print("dif");
  Serial.println(flowTic - oldTicNumber);
  while (neededTics > flowTic - oldTicNumber) {
    Serial.print("irigation : ");
    Serial.print((flowTic - oldTicNumber)* 0.00255); 
    Serial.println(" L");
    open();
  }
  close() ;
}
}
