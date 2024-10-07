/*************************************************************
  Author  : Ahmed Magdy
  Date    : 10/4/2024
  MCU 	  : ESP32
  @brief  : Make a SmartHome control system to control the 
  the light and the fan by the power of IOT technology.... 
 *************************************************************/

// Define Pins
#define lighting      13
#define fan           12

//---------------------------- Blynk definitions
/* Fill-in information from Blynk Device Info here */
//Go to https://blynk.io/ "Make your template and get your device info" 
#define BLYNK_TEMPLATE_ID "TMPL2epQ8O0fx"
#define BLYNK_TEMPLATE_NAME "SmartHome"
#define BLYNK_AUTH_TOKEN "NSjPq5_UJ4ihjhSZYXhLfEJkjoHJidqM"
 
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

//Libraries 
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
 
// Your WiFi credentials.
// Set password to "" for open networks.
char networK_name[] = ""; // Set Your Network Name Here as a String
char network_pass[] = ""; // Set Your Network Password Here as a String

BLYNK_WRITE(V0)   //lightValue
{
  int lightValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if(lightValue==HIGH)
  {
  digitalWrite(lighting,LOW);
  pinMode(lighting,OUTPUT);
  }
 
  if(lightValue==LOW)
  {
  digitalWrite(lighting,HIGH);
  pinMode(lighting,INPUT);
  }
}

BLYNK_WRITE(V1)   // Fan
{
  int fanValue = param.asInt(); // assigning incoming value from pin V2 to a variable
  if(fanValue==HIGH)
  {
  digitalWrite(fan,HIGH);
  }
  if(fanValue==LOW)
  {
  digitalWrite(fan,LOW);
  }
 
}
 
 
void setup()
{
  pinMode(fan,OUTPUT);
  digitalWrite(lighting,HIGH);
  pinMode(lighting,INPUT);
 
  // Debug console
  Serial.begin(115200);
 
  Blynk.begin(BLYNK_AUTH_TOKEN, networK_name, network_pass);
 
}
 
void loop()
{
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}