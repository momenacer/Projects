#define SERVOPIN 6
#include <Servo.h>
namespace window
{
Servo myservo;
float openDegree = 70;
float closeDegree = 170;
int delayTime = 50;

void open()
{
  myservo.write(openDegree);
 

}
void close()
{
  myservo.write(closeDegree);
 
}
void set()
{
  // this function need to be called in the setup function .
  myservo.attach(SERVOPIN);
  close() ;
}
}
