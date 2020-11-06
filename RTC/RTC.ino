#include <Wire.h>
#include "RTClib.h"

DateTime now;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

RTC_DS3231 rtc;

void showDate(void);
void showTime(void);
void showDay(void); 


void setup ()
{
  Serial.begin(9600);
  //delay(2000);
  if (! rtc.begin()) 
  {
    Serial.println("Couldn't find RTC Module");
    while (1);
  }

  if (rtc.lostPower()) 
  {
  
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop () 
{
  now = rtc.now();
  showDate();
  showDay();
  showTime();
  delay(10000);
}
   

 void showDate()
 {
  Serial.print(now.day());
  Serial.print('/');
  Serial.print(now.month());
  Serial.print('/');
  Serial.print(now.year());
 }
 void showDay()
 {

  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
 }
 void showTime()
 {
  Serial.print("Time:");
  Serial.print(now.hour());
  Serial.print(':');
  Serial.print(now.minute());
  Serial.print(':');
  Serial.print(now.second());
  Serial.print("    ");
  
 } 
