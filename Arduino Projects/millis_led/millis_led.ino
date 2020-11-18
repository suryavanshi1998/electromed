const int ledPin =  12; // the LED pin number connected
int ledState = LOW;             // used to set the LED state
unsigned long previousMillis = 0;  //will store last time LED was blinked
const long period = 1000;         // period at which to blink in ms

void setup() {
  pinMode(ledPin, OUTPUT); // set ledpin as output
}

void loop() {
 unsigned long currentMillis = millis(); // store the current time
  if (currentMillis - previousMillis >= period) { // check if 1000ms passed
   previousMillis = currentMillis;   // save the last time you blinked the LED
   if (ledState == LOW) { // if the LED is off turn it on and vice-versa
     ledState = HIGH;
   } else {
ledState = LOW;
}
   digitalWrite(ledPin, ledState);//set LED with ledState to blink again
 }
}
