#include "pitches.h"


#define POTENTIOMETER_PIN  25  // ESP32 pin GPIO25 connected to the Potentiometer
#define BUZZER_PIN         27  // ESP32 pin GPIO27 connected to the Buzzer
#define VOLTAGE_THRESHOLD1  1.1 // Voltage threshold for the first song
#define VOLTAGE_THRESHOLD2  2.2 // Voltage threshold for the second song

// Song 1: Jingle Bells
int melody1[] = {
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
  NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_G5
};
int durations1[] = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8,
  2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4
};

// Song 2: Twinkle Twinkle Little Star
int melody2[] = {
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4
};
int durations2[] = {
  4, 4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 4, 2
};

void setup() {
  pinMode(BUZZER_PIN, OUTPUT); // Initialize the buzzer pin as an output
}

void loop() {
  while (true) {
    float voltage = readVoltage();
    if (voltage > VOLTAGE_THRESHOLD1 && voltage < VOLTAGE_THRESHOLD2) {
      playMelody(melody1, durations1, sizeof(melody1) / sizeof(melody1[0]));
    } else if (voltage >= VOLTAGE_THRESHOLD2) {
      playMelody(melody2, durations2, sizeof(melody2) / sizeof(melody2[0]));
    } else {
      break; // Exit the loop if voltage is outside the thresholds
    }
  }
}

float readVoltage() {
  int analogValue = analogRead(POTENTIOMETER_PIN);
  return floatMap(analogValue, 0, 1023, 0, 3.3); // Map to 3.3V range
}

float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void playMelody(int melody[], int durations[], int size) {
  for (int thisNote = 0; thisNote < size; thisNote++) {
    int noteDuration = 1000 / durations[thisNote];
    tone(BUZZER_PIN, melody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZER_PIN);
  }
}
