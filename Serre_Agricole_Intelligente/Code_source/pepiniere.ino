#include "tempSensor.h"
#include "soilMoise.h"
#include "window.h"
#include "waterPump1.h"
#include "waterPump2.h"
#include "fan.h"
#include "waterLvl.h"
#include "led1.h"
#include "led2.h"
#include "valve.h"
#include "rainSensor.h"
#include "buzzer.h"
#include "gazSensor.h"
#include "lightSensor.h"

//#include <LiquidCrystal_I2C.h>
//#include <Wire.h>
//
//LiquidCrystal_I2C lcd(0x27,16,2);

/// --------------captuer present.
float soileMoiseData;
float internTempData;
float internHumidityData;
float waterLevelData;
bool rainSensorData;
float gazSensorData;
float lightSensorData;

///-------------- Target
float targetsoilMoise = 50 ;
float targetHumidity = 45 ;
float targetWaterLevel = 80 ;
float waterLimit = 20 ;
float targetInternTemp = 35;
float tempBorn = 5 ;
float targetGaz = 80 ;
float targetLight = 15;

void sensorsPrint();
void setup()
{
  Serial.begin(9600);

  //  lcd.begin(16,2);

  // Sensors set
  internSenrso.begin();
  soilMoise::set();
  waterLvl::set();
  rainSensor::set();
  gazSensor::set();
  lightSensor::set();

  // Actionneur set
  waterPump1::set();
  waterPump2::set();
  window::set();
  fan::set();
  led1::set();
  led2::set();
  valve::set();
  buzzer::set();
}

void loop()
{

  // updating the sensors data .
  
  soileMoiseData = soilMoise::get();
  internTempData = internSenrso.readTemperature();
  internHumidityData = internSenrso.readHumidity();
  waterLevelData = waterLvl::get();
  rainSensorData = rainSensor::get();
  gazSensorData = gazSensor::get();
  lightSensorData = lightSensor::get();
  
  ////////////////////////////////////////////////

  mainProg();

  sensorsPrint();
}

void mainProg()
{
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //  // Soil Moise system with VALVE
  if ( soileMoiseData < targetsoilMoise  ) {
    Serial.println("watering on");
    valve::open();
  } else {
    Serial.println("watering off");
    valve::close();
  }
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // water level and pump -2-
  if ( waterLevelData < waterLimit ) {
    Serial.println("water pump for reservoire on");
    waterPump2::on();
  } else  {
    Serial.println("water pump for reservoire off");
    waterPump2::off();
  }
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  //  //   fan System
  if ( targetHumidity < internHumidityData  )
  {
    Serial.println(" fan on ");
    fan::on();
  } else {
    Serial.println(" fan off ");
    fan::off();
  }




  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  //  //   light system
  if (  lightSensorData < targetLight  )
  {
    Serial.println(" LED -2- off  ");
    led2::on();
  } else {
    Serial.println(" LED -2- on ");
    led2::off();
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  ///  //   window system

  if ( !rainSensorData )
  {
    Serial.println("window open ");
    window::open();
  } else {
    Serial.println("window closed ");
    window::close();
  }


  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //   gaz system

  if ( targetGaz < gazSensorData )
  {
    Serial.println("warning buzzer ON");
    buzzer::on();
  } else {
    Serial.println("everything is safe ");
    buzzer::off();
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //
  //// cooling system pump -1- + Lampe
  //
  //
  if (  targetInternTemp + tempBorn < internTempData ) {
    Serial.println(" cooling system on ");
    waterPump1::on();


  } else  if (targetInternTemp - tempBorn > internTempData ) {
    Serial.println(" LED 1 ON ");
    led1::on();
  } else {
    Serial.println("temperature is great");
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void sensorsPrint() {
  Serial.print(F("Intern Humidity: "));
  Serial.print(internHumidityData);
  Serial.print(F("%  Intern Temperature: "));
  Serial.print(internTempData);
  Serial.print(F("°C "));
  Serial.print(F(" water level: "));
  Serial.print(waterLevelData);
  Serial.print(F(" light intensity : "));
  Serial.print(lightSensorData);
  Serial.print(F(" rain sensor : "));
  Serial.print(rainSensorData);
  Serial.print(F(" soil moise : "));
  Serial.print(soileMoiseData);
  Serial.print(F(" Gaz is : "));
  Serial.println(gazSensorData);


  //  lcd.backlight();
  //  lcd.setCursor(1,0);
  //  lcd.print("Intern Humidity is :");
  //  lcd.setCursor(2,1);
  //  lcd.print(internHumidityData);

}
