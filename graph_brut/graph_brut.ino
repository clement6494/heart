//  Variables
float capteurcardiaque = A0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0

int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int seuil = 850;            // Determine which Signal to "count as a beat", and which to ingore.


// The SetUp Function:
void setup() {

   Serial.begin(9600);         // Set's up Serial Communication at certain speed.

}

// The Main Loop Function
void loop() {
  Signal = analogRead(capteurcardiaque);  // Read the PulseSensor's value.

   Serial.println(Signal);                    // Send the Signal value to Serial Plotter.
  

delay(10);


}
