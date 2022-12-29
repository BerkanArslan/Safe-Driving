#include <WiFiClientSecure.h>
#include "WiFiManager.h"
#include <UniversalTelegramBot.h>

// Pins are not determined yet
#define led_alarm      GPIO_NUM_13
#define buzzer_alarm   GPIO_NUM_27

#define BOTtoken "5557332872:AAH_udpu7TK3jhqp2tF94rQO99V1DeEVRag"  // your Bot Token (Get from Botfather)
#define CHAT_ID "1414617805" // Get from IDBot

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

uint32_t currentMillis = 0;
uint32_t TelegramMillis = 0;
uint32_t TelegramInterval = 10000;
uint32_t AlarmMillis = 0;
uint32_t AlarmInterval = 3000;

bool booleanData = true; 
bool WifiSetup = true;
bool WifiLoop = false;
bool SendTextBool = false;
bool TelegramBotSetupBool = true;

void GPIO_setup()
{
  digitalWrite(led_alarm, LOW);
  digitalWrite(buzzer_alarm, LOW);
}

void Alarm()
{
    digitalWrite(led_alarm, HIGH);
    digitalWrite(buzzer_alarm, HIGH);
}

void AlarmDisable()
{
    digitalWrite(led_alarm, LOW);
    digitalWrite(buzzer_alarm, LOW);
}

void wipeEEPROM() // EEPROM wipe function
{
  for(int i=0;i<512;i++){
    EEPROM.writeByte(i,0);
  }
  EEPROM.commit();
}

void WiFiEvent(WiFiEvent_t event) // WiFi event function
{ 
  Serial.printf("[WiFi-event] event: %d\n", event);
  switch(event) {
    case SYSTEM_EVENT_STA_GOT_IP:
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println("WiFi lost connection");
      //set_LEDs(ERROR , SAME, SAME);   // Needs rework
      break;
  }
}

void TelegramBotSetup()
{
    UniversalTelegramBot bot(BOTtoken, client);
    bot.sendMessage(CHAT_ID, "Bot started up", "");
}