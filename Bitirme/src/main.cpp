#include <Arduino.h>
#include "functions.h"
#include "WiFi.h"
#include <WebServer.h>

#define DEVICE ESP32_WROOM_32 // ESP32 WROOM 32 is the device

#define BAUD_RATE 115200      // Setup serial communication

  /************************************************************************************************************/
  /************************************************************************************************************/
  /************************************************************************************************************/

void setup() {

  EEPROM.begin(512);        // Initialize EEPROM
  delay(500);

  GPIO_setup();
  
  Serial.begin(BAUD_RATE);  // Initialize serial communication
  while (!Serial)           // May not need in final version
    delay(10);              // will pause Zero, Leonardo, etc until serial console open

  if(!CheckWIFICreds())     // If there is no credential stored in EEPROM...
  {      
    Serial.println("No WIFI credentials stored in memory. Loading form..."); // Debug purposes
    while(loadWIFICredsForm()); // AP initialization 
  }  

}

  /************************************************************************************************************/
  /************************************************************************************************************/
  /************************************************************************************************************/

void loop() {

  /************************************************************************************************************/

  currentMillis = millis(); // Timer

  if(digitalRead(0) == LOW) // If pin 0 is high erase EEPROM
   {  
     Serial.println("Wiping WiFi credentials from memory...");
     wipeEEPROM();
     while(loadWIFICredsForm()); // Initialize AP again for getting WiFi credentials
   }

  /************************************************************************************************************/

   if(WifiSetup)              // Wifi Setup (Only runs once, will need to reset device to enter again)
  {   
  
    String s = EEPROM.readString(100);  // Reads ssid from EEPROM
    String p = EEPROM.readString(200);  // Reads password from EEPROM
    const char* ssid = s.c_str();       // Converts string ssid to const char*
    const char* password = p.c_str();   // Converts string password to const char*

    WiFi.onEvent(WiFiEvent);            // Opens Wifi
    //set_LEDs(PROVISION, SAME, SAME);
    Serial.println("");
    Serial.print("connecting to ");
    Serial.println(ssid);
    
    WiFi.begin(ssid, password);                     // Connects Wifi
//  WiFi.begin(ssid, password, 0, 0, true);         // Hakan Bey'in Mesh problemini çözer, test et üst satır yerine yaz
  
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    //set_LEDs(OK, SAME, SAME);        // LED's will need to be reworked
    WifiSetup = false;                 // Wifi setup ended. Will need to restart the device to enter again

    client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  }

  /************************************************************************************************************/

  if(WiFi.status() == WL_CONNECTED && TelegramBotSetupBool)  // Setup for Telegram bot
  {
    TelegramBotSetup();
    TelegramBotSetupBool = false;
  }

  /************************************************************************************************************/

  // Check if data is available
  //if (Serial.available()) {         // Read the data
    
    booleanData = Serial.read();

    //Serial.println(booleanData);    // Print the data

    if(booleanData && (currentMillis - AlarmMillis > AlarmInterval))                 // If alarm is active, enter alarm state
    {
      Alarm();
      SendTextBool = true;
      Serial.println("Alarm State Engaged");  // DEBUG
      AlarmMillis = currentMillis;
    }
    else                            // If alarm is no longer active, disengage alarm state
    {
      if(!SendTextBool && (currentMillis - AlarmMillis > AlarmInterval))              // Will only disengage once
      {
      AlarmDisable();
      SendTextBool = false;
      Serial.println("Alarm State Disengaged");  // DEBUG
      }
    }
  //}

  /************************************************************************************************************/

  // In an alarm situation, send a text to Telegram channel. Need to implement a timer to prevent continious messaging
  if(WiFi.status() == WL_CONNECTED && SendTextBool && (currentMillis - TelegramMillis > TelegramInterval))
  {
    bot.sendMessage(CHAT_ID, "Alarm!!!", "");            // Needs rework
    TelegramMillis = currentMillis;
    Serial.println("trying to send telegram data");
  }

  /************************************************************************************************************/
}
