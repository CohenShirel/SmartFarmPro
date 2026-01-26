#include "FarmLogic.h"
#include "Config.h"
#include <ESP32Servo.h>
#include <dht11.h>

extern Servo petFeederServo;
extern dht11 dhtSensor;

void softStartFan(bool turnOn) {
    static bool isCurrentlyOn = false;
    
    if (turnOn && !isCurrentlyOn) {
        Serial.println("Starting Fan (Soft Start)...");
        for (int duty = 0; duty <= 255; duty += 5) {
            ledcWrite(FAN_PIN, duty);
            delay(15); 
        }
        isCurrentlyOn = true;
    } else if (!turnOn && isCurrentlyOn) {
        ledcWrite(FAN_PIN, 0);
        isCurrentlyOn = false;
    }
}

void performFeeding() {
    petFeederServo.attach(SERVO_PIN);
    petFeederServo.write(80);
    delay(1000);
    petFeederServo.write(160);
    delay(500);
    petFeederServo.detach();
}

long getDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    long duration = pulseIn(ECHO_PIN, HIGH);
    return duration * 0.034 / 2;
}

void playAlarmMelody() {
    static unsigned long lastToneChange = 0;
    static int toneStep = 0;
    if (millis() - lastToneChange < 150) return; 
    lastToneChange = millis();

    switch(toneStep) {
        case 0: ledcWriteTone(BUZZER_PIN, 532); break;
        case 1: ledcWriteTone(BUZZER_PIN, 587); break;
        case 2: ledcWriteTone(BUZZER_PIN, 659); break;
        case 3: 
            for(int freq = 200; freq <= 1000; freq += 200) ledcWriteTone(BUZZER_PIN, freq);
            break;
        default: toneStep = -1; break;
    }
    toneStep++;
}

void executeSmartLogic() {
    if (!isSmartMode) return;

    long distance = getDistance();
    if (distance > 0 && distance < 5) {
        performFeeding(); 
    }

    if (sSoil < SOIL_DRY_THRESHOLD) digitalWrite(RELAY_PIN, HIGH);
    else digitalWrite(RELAY_PIN, LOW);

    if (sTemp > TEMP_HOT_THRESHOLD) {
        softStartFan(true);
    } else {
        softStartFan(false);
    }

    if (digitalRead(PIR_PIN) == HIGH) {
        playAlarmMelody();
    } else {
        ledcWriteTone(BUZZER_PIN, 0);
    }

    if (sLight < 15) digitalWrite(LED_PIN, HIGH);
    else digitalWrite(LED_PIN, LOW);
}
