#include <WiFi.h>
#include <HTTPClient.h>
#include <esp_wifi.h> 

#define UART Serial
// Replace these with your network credentials
const char* ssid = "acts";
const char* password = "";
uint8_t newMACAddress[] = {0xf4, 0x96, 0x34, 0x9d, 0xe5, 0xd6};  // f9 f4:96:34:9d:e0:e0 f4:96:34:9d:e5:d6
// Replace with your ThingSpeak credentials
const char* serverName = "http://api.thingspeak.com/update";
const char* apiKey = "YO44GNXIBTVG8NI4";
String incomingData;
int temp;
int humidity;


void setup() {
  Serial.begin(115200);
  UART.begin(115200);
  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);      
  esp_wifi_set_mac(WIFI_IF_STA, &newMACAddress[0]); // for wifi spoofing
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi");
}

void loop() {

  if (UART.available()) {
    // Read the incoming data as a string
    incomingData = UART.readStringUntil('\n'); // Read until newline character

    // Convert the string to an integer
    temp = incomingData.toInt();
    incomingData = UART.readStringUntil('\n');
    humidity = incomingData.toInt();
    // Print the received integer value to the Serial Monitor
    Serial.print("Received humid Value: ");
    Serial.println(humidity);
    Serial.print("Received temp Value: ");
    Serial.println(temp);
    // You can now use the integer value in your application
    // For example, controlling an LED based on the received value
  }

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    // Form the URL with the API key and data
    String url = String(serverName) + "?api_key=" + apiKey + "&field1=" + String(temp)+"&field2=" + String(humidity);

    http.begin(url);
    int httpResponseCode = http.GET();
    
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Response: " + response);
    } else {
      Serial.println("Error on HTTP request");
    }
    
    http.end();
  }

  // Wait before sending new data
  delay(15000); // 15 seconds
}