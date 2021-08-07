#include <Esp.h>
#include "src/Data.h"

#include <sys/time.h>
#include <time.h>
#include <sntp-lwip2.cpp>

extern "C" int clock_gettime(clockid_t unused, struct timespec *tp);

#define PERIOD 3

Data        dataHandler;

uint32_t    odometerData;
uint32_t    hourmeterData;
uint32_t    tfuData;
uint8_t     velocityData;
uint8_t     fuelData;
uint32_t    otherData;

uint32_t id = 675;
uint32_t timestamp; 
uint16_t type = 2;

time_t getTime() {
  timeval tv;
  struct timezone tz;
  timespec tp;
  gettimeofday(&tv, &tz);
  clock_gettime(0, &tp); // also supported by esp8266 code
  return time(nullptr);
}

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n3");
    delay(1000);
    Serial.println("2");
    delay(1000);
    Serial.println("1");
    delay(1000);

    odometerData = 7500123;
    hourmeterData = 675010;
    tfuData = 2142892;
    velocityData = 112;
    fuelData = 50;
    otherData = 123456789;
}

unsigned long ant_millis = 0;
void loop() {
    if (millis() - ant_millis >= 2*1000) {
        char* msg = dataHandler.getMsg(id, getTime(), type, 
                                    odometerData, 
                                    hourmeterData, 
                                    tfuData, 
                                    velocityData, 
                                    fuelData);
        Serial.print("MSG 1: "); Serial.println(msg);     

        msg = dataHandler.getMsg(id, getTime(), type, 
                                odometerData, 
                                hourmeterData, 
                                tfuData, 
                                velocityData, 
                                fuelData,
                                otherData);
        Serial.print("MSG 2: "); Serial.println(msg);
        Serial.println("");
        ant_millis = millis();                    
    } 
}