/*************************************************************
  Author  : Ahmed Magdy
  Date    : 10/2/2024
  MCU     : ESP32
  @brief  : How to control Virtual Pins to make simple Traffic
  -light Control system by the power of IOT technology........
 *************************************************************/

/* Define Pins */
#define Red     13
#define Yellow  12
#define Green   14  

//---------------------------- Blynk definitions
/* Fill-in information from Blynk Device Info here */
//Go to https://blynk.io/ "Make your template and get your device info" 
#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

// Libraries
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char networK_name[] = ""; // Set Your Network Name Here as a String
char network_pass[] = ""; // Set Your Network Password Here as a String

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin V1
//RED
BLYNK_WRITE(V1)
{
 // assigning incoming value from pin V1 to a variable
  digitalWrite(Red, param.asInt());
}


// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin V2
//YELLOW
BLYNK_WRITE(V2)
{
  // assigning incoming value from pin V2 to a variable
  digitalWrite(Yellow,param.asInt());
}

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin V3
//GREEN
BLYNK_WRITE(V3)
{
 // assigning incoming value from pin V3 to a variable
  digitalWrite(Green,param.asInt());
}

void setup()
{
  // Set the Direction of the Pins
  pinMode(Red,OUTPUT);
  pinMode(Yellow,OUTPUT);
  pinMode(Green,OUTPUT);

  // Debug console
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, networK_name, network_pass);
  
}

void loop()
{
  Blynk.run();
}