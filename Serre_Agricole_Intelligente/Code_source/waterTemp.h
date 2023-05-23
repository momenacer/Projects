#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 5
namespace waterTemp{
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
void set() {}
float get () {
  sensors.requestTemperatures();
  return   sensors.getTempCByIndex(0);
}
}
