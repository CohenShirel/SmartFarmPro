#ifndef CONFIG_H
#define CONFIG_H

// --- Pin Mapping ---
#define DHT11_PIN 17
#define LED_PIN 27
#define FAN_PIN 19
#define RELAY_PIN 25
#define BUZZER_PIN 16
#define SERVO_PIN 26
#define PIR_PIN 23
#define TRIG_PIN 12
#define ECHO_PIN 13
#define RAIN_PIN 35
#define SOIL_PIN 32
#define WATER_PIN 33
#define LIGHT_PIN 34
#define PHYS_BTN 5

// --- WiFi Credentials ---
#define WIFI_SSID   "Smart_Farm"
#define WIFI_PASS   "12345678"

// --- Thresholds ---
#define SOIL_DRY_THRESHOLD 30
#define TEMP_HOT_THRESHOLD 28

#endif