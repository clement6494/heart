//  Variables
float capteurcardiaque = A0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
float LED = 3;   //  The on-board Arduion LED
float LED1 =  2;

int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int seuil = 850;            // Determine which Signal to "count as a beat", and which to ingore.


// The SetUp Function:
void setup() {
  pinMode(LED,OUTPUT);         // pin that will blink to your heartbeat!
  pinMode(LED1,OUTPUT);
   Serial.begin(1200);         // Set's up Serial Communication at certain speed.

}

// The Main Loop Function
void loop() {
  Signal = analogRead(capteurcardiaque);  // Read the PulseSensor's value.
if ((Signal<1200)&&(Signal>550)){
   Serial.println(Signal);                    // Send the Signal value to Serial Plotter.
   if(Signal > seuil){                          // If the signal is above "550", then "turn-on" Arduino's on-Board LED.
     digitalWrite(LED,HIGH);
   } else {
     digitalWrite(LED,LOW);                //  Else, the sigal must be below "550", so "turn-off" this LED.
   }
} else{
  digitalWrite(LED1,HIGH);
}


delay(10);


}
