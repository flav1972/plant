// use at your own risk
#include <Time.h>
#include <TimeAlarms.h>
#include <DS1307RTC.h>

// see also http://bildr.org/2012/03/rfp30n06le-arduino/

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

// another led put outside 
int out1 = 4;
int out2 = 5;
int out3 = 9;

int delay1 = 20;
int delay2 = 120;
int delay3 = 120;

void setup() {
  Serial.begin(57600);  
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  pinMode(out1, OUTPUT); 
  pinMode(out2, OUTPUT); 
  pinMode(out3, OUTPUT); 
  // writes a messages on serial
  Serial.println("Time for water plants");
  Serial.println("Setup done!!!"); 

  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus()!= timeSet) 
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time");
     
  // set time to 8:30:0 on 1 Jully 2016
  //setTime(8, 30, 0, 1, 7, 2016);
  //Alarm.timerRepeat(10, alarm1);
  // menthe
  Alarm.alarmRepeat(22, 04, 0, alarm1);
  //
  Alarm.alarmRepeat(22, 05, 0, alarm2);
  Alarm.alarmRepeat(22, 06, 0, alarm3);
   
  //Alarm.alarmRepeat(dowSaturday, 22, 33, 0, alarm2);
  //Alarm.alarmRepeat(dowSaturday, 22, 7, 0, alarm3);
  Serial.println("AlarmOne: each 60s");
}

void loop() {
  digitalClockDisplay();
  digitalWrite(led, HIGH);
  Alarm.delay(500);
  digitalWrite(led, LOW);
  Alarm.delay(500);
}

void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void alarm1()
{
  Serial.print("This is Alarm 1: ");
  digitalClockDisplay();
  digitalWrite(out1, HIGH);
  Alarm.timerOnce(delay1, alarm1End);
}

void alarm1End()
{
  Serial.print("Alarm 1 Ended: ");
  digitalClockDisplay();
  digitalWrite(out1, LOW);
}

void alarm2()
{
  Serial.print("This is Alarm 2: ");
  digitalClockDisplay();
  digitalWrite(out2, HIGH);
  Alarm.timerOnce(delay2, alarm2End);
}

void alarm2End()
{
  Serial.print("Alarm 2 Ended: ");
  digitalClockDisplay();
  digitalWrite(out2, LOW);
}

void alarm3()
{
  Serial.print("This is Alarm 3: ");
  digitalClockDisplay();
  digitalWrite(out3, HIGH);
  Alarm.timerOnce(delay3, alarm3End);
}

void alarm3End()
{
  Serial.print("Alarm 3 Ended: ");
  digitalClockDisplay();
  digitalWrite(out3, LOW);
}


