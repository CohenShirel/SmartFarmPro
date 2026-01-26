#ifndef FARMLOGIC_H
#define FARMLOGIC_H

#include <Arduino.h>

// --- Global Shared Variables ---
extern bool isSmartMode;
extern float sTemp, sHumid, sSoil, sWater, sRain, sLight;
extern String lcdMessage;

// --- Functional Prototypes ---
void performFeeding();
void executeSmartLogic();
void refreshSensorData();
long getDistance();
void playAlarmMelody();

#endif