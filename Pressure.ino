#include <WiFiNINA.h>
#include <ThingSpeak.h>
#include "secrets.h"

int pressureAnalogPin = 0; //pin where our pressure pad is located.
int pressureReading; //variable for storing our reading
int LEDpin = 2;

//Adjust these if required.
int noPressure = 5; //max value for no pressure on the pad
int lightPressure = 100; //max value for light pressure on the pad
int mediumPressure = 200; //max value for medium pressure on the pad

char ssid[] = SECRET_SSID;    //  your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password, none for RIT-Legacy network
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;
unsigned long myChannelNumber = 1225415;
const char* myWriteAPIKey = V0A6PD3I0I65XILS;
 
void setup(void) {
  Serial.begin(9600);
  pinMode(LEDpin, OUTPUT);

    // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }
    
  ThingSpeak.begin(client);  //Initialize ThingSpeak
}
 
void loop(void) {
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
  
  pressureReading = analogRead(pressureAnalogPin);
  
  Serial.print("Pressure Pad Reading = ");
  Serial.println(pressureReading);

  if (pressureReading < noPressure) {
    Serial.println(" - No pressure");
  } else if (pressureReading < lightPressure) {
    Serial.println(" - Light Pressure");
  } else if (pressureReading < mediumPressure) {
    Serial.println(" - Medium Pressure");
  } else{
    Serial.println(" - High Pressure");
  }

  if(pressureReading > 7){
    int x = ThingSpeak.writeField(myChannelNumber, 1, pressureReading, myWriteAPIKey); //send data to ThingSpeak
    digitalWrite(LEDpin, HIGH);
    delay(2000);
  }
  else{
        digitalWrite(LEDpin, LOW);
  }

  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }


  delay(1000);
  

  
}
