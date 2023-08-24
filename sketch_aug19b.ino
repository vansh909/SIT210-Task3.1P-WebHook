#include <WiFiNINA.h>
#include <ThingSpeak.h> 
const int LDRPin = A0;
char ssid[] = "Galaxy M314C7C";     // WiFi SSID
char pass[] = "12345678";

unsigned long channelID = 2250464;         // Your ThingSpeak Channel ID
const char *apiKey = "I7EA4016TQP1ROKD"; 
WiFiClient client;

void setup()
{
  Serial.begin(9600);
  connectWiFi();
  ThingSpeak.begin(client);
}

void loop()
{
  delay(1000);
  int Value=analogRead(LDRPin);
  Serial.print("Analog Value: ");
  Serial.println(Value);
   if (!isnan(Value))
   {
    sendDataToThingSpeak(Value);
  } else 
  {
    Serial.println("Failed to read from LDR ");
  }
}
 void connectWiFi() 
  {
    while (WiFi.status() != WL_CONNECTED) 
    {
      Serial.print("Connecting to WiFi...");
      WiFi.begin(ssid, pass);
      delay(1000);
    }
    Serial.println("Connected to WiFi");
  }

void sendDataToThingSpeak(int value) 
{
  ThingSpeak.setField(1, value);
  int httpCode = ThingSpeak.writeFields(channelID, apiKey);

  if (httpCode == 200) 
  {
    Serial.println("Data sent to ThingSpeak");
  } 
  else
  {
    Serial.println("Error sending data to ThingSpeak");
  }
}   
  
 
