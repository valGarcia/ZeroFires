/** by Valerie Garcia
 *  arduino code
 */
#include <SPI.h>
#include <WiFi101.h>

char ssid[] = "Val";     // the name of your network
int status = WL_IDLE_STATUS;     // the Wifi radio's status
WiFiServer server(80);

char thingSpeakAddress[] = "api.thingspeak.com";
String APIKey = "C8ECK7F11PJKUXB6";
//enter channel's write API key
const int updateThingSpeakInterval = 10 * 1000; //10second interval to update thingspeak

const int analogPin = A4;    // the pin that the potentiometer is attached to
const int ledCount = 10;    // the number of LEDs in the bar graph

int ledPins[] = {
  11,12,9,8,13,6,1,4,3,2 // Here we have the number of LEDs to use in the BarGraph
  };   


long lastConnectionTime = 0;
boolean lastConnected = false;

WiFiClient client;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT);
    digitalWrite(ledPins[thisLed], LOW);
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to open SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid);

    // wait 10 seconds for connection:
    delay(5000);

    
  }
  printWifiStatus();

  // you're connected now, so print out the data:
  Serial.println("You're connected to the network");

}

void loop() {
  // check the network connection once every 10 seconds:

    int alcohol = analogRead(A4);
    
    int ledLevel = map(alcohol, 500, 1023, 0, ledCount);
    //turn on led's for alcohol level
  


  int flameReading = analogRead(A1);
  
  float voltage = analogRead(A0) * (3.3 / 1024); //convert from range 0 - 1023 to 0 - 3.3
//  Serial.println(voltage);
  int tempVal = (voltage - .05) * 100; //convert to celcuis using offset of .5V
  String temp = String(tempVal,DEC);
  if(client.available()){
    char c = client.read();
    Serial.print(c);
  }
  //disconnect
  if(!client.connected() && lastConnected){
    Serial.println("...disconnected");
    client.stop();
  }
  //update thinkspeak
  if(!client.connected() && (millis() - lastConnectionTime > 
  updateThingSpeakInterval)){
    updateThingSpeak("field1=" + temp + "&field2=" + flameReading + "&field3=" + alcohol);
  }
  lastConnected = client.connected();
  

  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    if (thisLed < ledLevel) {
      digitalWrite(ledPins[thisLed], HIGH);
    }

    else {
      digitalWrite(ledPins[thisLed], LOW);
    } 
  }
  
}

void updateThingSpeak(String tsData) {
  if (client.connect(thingSpeakAddress, 80)) {
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + APIKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(tsData.length());
    client.print("\n\n");
    client.print(tsData);
    lastConnectionTime = millis();

    if (client.connected()) {
      Serial.println("Connecting to ThingSpeak...");
      Serial.println();
    }
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}



