/*************************************************************
  Author  : Ahmed Magdy
  Date    : 10/3/2024
  MCU     : ESP32
  @brief  : Make a Water-level sensor that sense the level of
  the water and show it on a virural guage and give yor an 
  alert if the water level is too low.......................
 *************************************************************/
 
//Define Pins
//important parameters used to detecting the distance between 
//the Ultrasonic-sensor and the water level
#define distance_to_tank_bottom   9   // distance from sensor to zero% level
#define max_distance    		  5   // distance from sensor to 100% level

// Pins for Ultrasonic-sensor
#define trigPin  12
#define echoPin  13

// Pins for Alert system and light indication
#define buzzer         14
#define red_led        27
#define green_led1     26
#define green_led2     25
#define green_led3     33
#define green_led4     32

//formula to get the depth of the tank
int tank_depth= distance_to_tank_bottom-max_distance;

// Ultrasonic-sensor variables 
long duration=0;
int distance=0;
int sensor_reading=0;
int water_level=0;

//flag variable to send the alert notification to the owner device
int is_notification_sent=0;

 
 
//---------------------------- Blynk definitions
//Go to https://blynk.io/ "Make your template and get your device info" 
/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL2QkJmcFJv"
#define BLYNK_TEMPLATE_NAME "level"
#define BLYNK_AUTH_TOKEN "gZeoOf-AuD6dQKn0Uujrq9qBN3J9Arsb"
 
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
BlynkTimer timer;
 
// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
 
 Blynk.virtualWrite(V0,water_level);
//------------------------------ calculating water level
 sensor_reading=read_ultrasonic_sensor();
 if(sensor_reading>distance_to_tank_bottom)sensor_reading=distance_to_tank_bottom;
 else if(sensor_reading<max_distance)sensor_reading=max_distance;
 sensor_reading=sensor_reading-max_distance;
 sensor_reading=tank_depth-sensor_reading;
 water_level=sensor_reading*100/tank_depth;
 water_level = ((water_level + 5) / 10) * 10;  /// roundedReading

//------------------------------ end of calculating water level
 
 Serial.println(water_level); 
 if(water_level>=0 && water_level<20 )
 { 
 digitalWrite(buzzer,HIGH);delay(100);digitalWrite(buzzer,LOW);delay(30);
 digitalWrite(red_led,HIGH);
 digitalWrite(green_led1,LOW);
 digitalWrite(green_led2,LOW);
 digitalWrite(green_led3,LOW);
 digitalWrite(green_led4,LOW);
 
 if(is_notification_sent==0)
    {
      Blynk.logEvent("alert", "The water level is low.\n\n   مستوى الماء منخفض") ;
      is_notification_sent=1;
    }
 
 }
 else if(water_level>=25 && water_level<50 )
 { 
 digitalWrite(red_led,LOW);
 digitalWrite(green_led1,HIGH);
 digitalWrite(green_led2,LOW);
 digitalWrite(green_led3,LOW);
 digitalWrite(green_led4,LOW);
 is_notification_sent=0;
 }
 else if(water_level>=50 && water_level<75 )
 { 
 digitalWrite(red_led,LOW);
 digitalWrite(green_led1,HIGH);
 digitalWrite(green_led2,HIGH);
 digitalWrite(green_led3,LOW);
 digitalWrite(green_led4,LOW);
 
 is_notification_sent=0;
 }
 else if(water_level>=75 && water_level<100 )
 { 
 digitalWrite(red_led,LOW);
 digitalWrite(green_led1,HIGH);
 digitalWrite(green_led2,HIGH);
 digitalWrite(green_led3,HIGH);
 digitalWrite(green_led4,LOW);
 is_notification_sent=0;
 }
 else
 {
 digitalWrite(red_led,LOW);
 digitalWrite(green_led1,HIGH);
 digitalWrite(green_led2,HIGH);
 digitalWrite(green_led3,HIGH);
 digitalWrite(green_led4,HIGH);
 is_notification_sent=0;
 }
}
 
//---------------------------- End of Blynk definitions
 
void setup() {
 
//---------------------------- Blynk initialization
Serial.begin(115200);
Blynk.begin(BLYNK_AUTH_TOKEN, networK_name, network_pass);
// Setup a function to be called every second
timer.setInterval(1000L, myTimerEvent);
//---------------------------- End of Blynk initialization
 
 //Set Direction of the pins
 pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
 pinMode(echoPin, INPUT); // Sets the echoPin as an Input

 pinMode(buzzer,OUTPUT);
 pinMode(red_led,OUTPUT);
 pinMode(green_led1,OUTPUT);
 pinMode(green_led2,OUTPUT);
 pinMode(green_led3,OUTPUT);
 pinMode(green_led4,OUTPUT);

//Intialize the pins by LOGIC_LOW
 digitalWrite(buzzer,LOW);
 digitalWrite(red_led,LOW);
 digitalWrite(green_led1,LOW);
 digitalWrite(green_led2,LOW);
 digitalWrite(green_led3,LOW);
 digitalWrite(green_led4,LOW);
 
}

void loop() {
//---------------------------- Blynk Loop
Blynk.run();
timer.run(); // Initiates BlynkTimer
if ( ! Blynk.connected() )
{
  while ( ! Blynk.connected() )
   {
    // try connect again
    Serial.println("-Try to connect");
    delay(100);
   Blynk.begin(BLYNK_AUTH_TOKEN, networK_name, network_pass);
   }
 
    Serial.println("-Connected.. ^_^ ");
    delay(500);
 }
//---------------------------- End of Blynk Loop
}
int read_ultrasonic_sensor()
{
  digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        duration = pulseIn(echoPin, HIGH);
        distance = duration * 0.017;
        if (distance >= 4 )
        {
          return distance;
        }
        else return 0;
}