#include "Config.h"
#include "WebPages.h"
#include "FarmLogic.h"
#include <WiFi.h>
#include <WebServer.h>
#include <LiquidCrystal_I2C.h>
#include <dht11.h>
#include <ESP32Servo.h>

bool isSmartMode = false;
float sTemp=0, sHumid=0, sSoil=0, sWater=0, sRain=0, sLight=0;
String lcdMessage = "System Ready";

dht11 dhtSensor;
LiquidCrystal_I2C lcdDisplay(0x27, 16, 2);
Servo petFeederServo;
WebServer webServer(80);

void setup() 
{
    Serial.begin(115200); 
    
    pinMode(LED_PIN, OUTPUT);
    pinMode(RELAY_PIN, OUTPUT); 
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(TRIG_PIN, OUTPUT); 
    pinMode(WATER_PIN, INPUT); 
    pinMode(PIR_PIN, INPUT); 
    pinMode(ECHO_PIN, INPUT); 
    pinMode(PHYS_BTN, INPUT_PULLUP);

    ledcAttachChannel(BUZZER_PIN, 1000, 8, 4); 
    ledcAttachChannel(FAN_PIN, 5000, 8, 1);

    digitalWrite(LED_PIN, LOW);
    digitalWrite(RELAY_PIN, LOW);
    ledcWrite(FAN_PIN, 0);
    ledcWriteTone(BUZZER_PIN, 0);

    WiFi.softAP(WIFI_SSID, WIFI_PASS);
    Serial.println("Access Point Started");

    lcdDisplay.init(); 
    lcdDisplay.backlight();
    lcdDisplay.setCursor(0, 0); 
    lcdDisplay.print("Farm IP:"); 
    lcdDisplay.setCursor(0, 1); 
    lcdDisplay.print(WiFi.softAPIP());

    webServer.on("/", HTTP_GET, [](){
        webServer.send(200, "text/html", index_html);
    });
    webServer.on("/data", HTTP_GET, handleDataRequest);
    webServer.on("/set", HTTP_GET, handleControlRequest);
    webServer.on("/lcd", HTTP_GET, handleLCDRequest);
    
    webServer.begin();
    Serial.println("Web Server Ready");
}

void loop() {
    webServer.handleClient();

    if (digitalRead(PHYS_BTN) == LOW) {
        digitalWrite(LED_PIN, !digitalRead(LED_PIN)); 
        delay(300); 
    }

    static unsigned long lastExecution = 0;
    if (millis() - lastExecution > 2000) {
        updateInternalSensors();
        if (isSmartMode) {
            executeSmartLogic(); 
        } else {
            ledcWriteTone(BUZZER_PIN, 0);
        }
        lastExecution = millis();
    }
}

void handleDataRequest() {
    String json = "{";
    json += "\"t\":" + String(sTemp) + ",\"h\":" + String(sHumid) + ",";
    json += "\"s\":" + String(sSoil) + ",\"w\":" + String(sWater) + ",";
    json += "\"r\":" + String(sRain) + ",\"li\":" + String(sLight) + ",";
    json += "\"m\":\"" + String(isSmartMode ? "Smart" : "Manual") + "\"}";
    webServer.send(200, "application/json", json);
}

void handleControlRequest() {
    String cmd = webServer.arg("value");
    if(cmd == "A") digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    if(cmd == "smart") {
        isSmartMode = !isSmartMode;
        if(!isSmartMode) { 
            ledcWrite(FAN_PIN, 0);
            ledcWriteTone(BUZZER_PIN, 0);
        }
    }
    if(cmd == "C") performFeeding();
    if(cmd == "B") {
        static bool fanState = false;
        fanState = !fanState;
        ledcWrite(FAN_PIN, fanState ? 255 : 0);
    }
    if(cmd == "D") digitalWrite(RELAY_PIN, !digitalRead(RELAY_PIN)); 
    webServer.send(200, "text/plain", "OK");
}

void updateInternalSensors() 
{
    dhtSensor.read(DHT11_PIN);
    sTemp = dhtSensor.temperature;
    sHumid = dhtSensor.humidity;
    sWater = constrain(map(analogRead(WATER_PIN), 0, 4095, 0, 100), 0, 100);
    sSoil = constrain(map(analogRead(SOIL_PIN), 0, 4095, 0, 100), 0, 100);
    sRain = constrain(map(analogRead(RAIN_PIN), 0, 4095, 0, 100), 0, 100);
    sLight = constrain(map(analogRead(LIGHT_PIN), 0, 4095, 0, 100), 0, 100);
}

void handleLCDRequest() 
{
    if (webServer.hasArg("text")) 
    {
        lcdDisplay.clear(); 
        lcdDisplay.setCursor(0, 0); 
        lcdDisplay.print(webServer.arg("text")); 
        webServer.send(200, "text/plain", "OK"); 
    }
}