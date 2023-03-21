#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#ifndef STASSID
#define STASSID "WifiNameHere"
#define STAPSK "WifiPasswordHere"
#define COLOURLENGTH 2
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const char* host = "hostnamehere";
const uint16_t port = 80;
const char* endpoint = "/ifrequired";


ESP8266WiFiMulti WiFiMulti;

const int ledPin = LED_BUILTIN;
const int redLed = 12;
const int greenLed = 13;
const int blueLed = 14;
int ledState = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  //analogWrite(redLed, 128);

  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  // Serial.println("IP address: ");
  // Serial.println(WiFi.localIP());
  printWifiStatus();
  delay(500);
}


void loop() {
  String payload;
  String redValue;
  String redLedValue;
  String greenValue;
  String greenLedValue;
  String blueValue;
  String blueLedValue;

  int redLedValueInt;
  int greenLedValueInt;
  int blueLedValueInt;
  
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);
  Serial.println(endpoint);
  if (ledState == LOW) {
    ledState = HIGH;
  } else {
    ledState = LOW;
  }
  digitalWrite(ledPin, ledState);
  // Use WiFiClient class to create Wifi connections
  WiFiClient client;
  // Use HTTPClient to create connection to endpoint via the Wifi Connection
  HTTPClient http;

  Serial.println("wait 1 sec...");
  delay(1000);

  Serial.println("Start HTTP Method");
  // if (http.begin(client, "http://" + host + ":" + port + endpoint)) {
  if (http.begin(client, "http://host.com/endpoint")) {
    Serial.print("[HTTP] GET...\n");
    int httpCode = http.GET();
    if (httpCode > 0) {
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      // Send GET to endpoint once connected
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = http.getString(); // Digest returned value
        // Strip leading # from returned value
        payload.replace("#", "");
        // Serial.println(payload);
        // Value returned is HTML Hex Code RRGGBB representing the colour of the bin lid
        redValue = payload.substring(0, 2);
        greenValue = payload.substring(2, 4);
        blueValue = payload.substring(4, 6);

        char redstr_array[redValue.length()]; // Define character array of length
        redValue.toCharArray(redstr_array, redValue.length());
        // Serial.println("redValue: " + redValue);
        redLedValue = redValue;
        // Serial.println("redLedValue: " + redLedValue);
        redLedValueInt = strtoul(redLedValue.c_str(), NULL, 16); // Pass the Hex Colour Value (00-FF) to a function to convert this to Decimal for use with PWM output

        char greenstr_array[greenValue.length()]; // Define character array of length
        greenValue.toCharArray(greenstr_array, greenValue.length());
        //Serial.println("greenValue: " + greenValue);
        greenLedValue = greenValue;
        greenLedValueInt = strtoul(greenLedValue.c_str(), NULL, 16); // Pass the Hex Colour Value (00-FF) to a function to convert this to Decimal for use with PWM output

        char bluestr_array[blueValue.length()]; // Define character array of length
        blueValue.toCharArray(bluestr_array, blueValue.length());
        // Serial.println("blue Value: " + blueValue);
        blueLedValue = blueValue;
        blueLedValueInt = strtoul(blueLedValue.c_str(), NULL, 16); // Pass the Hex Colour Value (00-FF) to a function to convert this to Decimal for use with PWM output

        // Serial.println("Red = " + redLedValueInt);
        // Serial.println("Blue = " + blueLedValueInt);
        // Serial.println("Green = " + greenLedValueInt);
        delay(500);
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  } else {
    Serial.println("[HTTP] Unable to connect");
  }
  analogWrite(redLed, redLedValueInt);
  analogWrite(blueLed, blueLedValueInt);
  analogWrite(greenLed, greenLedValueInt);
  Serial.println("5 second pause");
  delay(5000);
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