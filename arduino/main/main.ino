#include <DS3231.h>
#include <Wire.h>

int wateringModePin = 2;
int wateringModeIndicatorPin = 12;

int waterSensorPin = 11;

int ledPin = 3;
int motorPin = 9;

DS3231 clock;

byte year;
byte month;
byte date;
byte dow;
byte hour;
byte minute;
byte second;

bool centuryFlag;
bool pmFlag;
bool h12Flag;

// HIGH: eau non  détectée, LOW: eau détectée
int waterSensorVal = HIGH;

// mode d'arrosage: 
//   0 pour arrosage régulier
//   1 pour prendre en compte le détecteur d'eau
int wateringMode = 0;

bool shouldWater = false;
bool didWater = false;

int lastWateringDate = -1;
int lastWateringHour = -1;
int lastWateringMinute = -1;

// durée d'arrosage en secondes
int wateringDuration = 5;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  pinMode(wateringModePin, INPUT);
  pinMode(wateringModeIndicatorPin, OUTPUT);
  pinMode(waterSensorPin, INPUT);

  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);

  printNow();
  Serial.println("Format YYMMDDwhhmmssx");
}

void loop() {

  date = clock.getDate();
  hour = clock.getHour(h12Flag, pmFlag);
  minute = clock.getMinute();

  // gestion de l'éclairage, éteindre de 2h à 7h
  if (hour < 7 && hour > 1) {
    digitalWrite(ledPin, LOW);
  } else {
    digitalWrite(ledPin, HIGH);
  }

  waterSensorVal = digitalRead(waterSensorPin);
  Serial.print("Water sensor: ");
  Serial.println(waterSensorVal);

  // passe au mode arrosage suivant quand on appuie sur le bouton 
  if (digitalRead(wateringModePin) == HIGH) {
    wateringMode = (wateringMode + 1) % 2;
  }

  // affiche le mode actuel
  if (wateringMode == 0) {
    digitalWrite(wateringModeIndicatorPin, LOW);
  } else {
    digitalWrite(wateringModeIndicatorPin, HIGH);
  }

  shouldWater = false;
  didWater = false;

  // détermine si on devrait arroser suivant le mode  
  if (wateringMode == 0) {
    if (hour%4 == 0 && minute == 5) {
      shouldWater = true;
    }
  } else if (wateringMode == 1) {
    if (waterSensorVal == HIGH && minute == 5) {
      shouldWater = true;
    }
  }

  if (shouldWater) {
    Serial.println("Should water");
    // vérifie qu'on a pas arrosé les 3 heures précédentes
    if ((lastWateringHour == -1) || (date == lastWateringDate && hour > lastWateringHour + 3) || (date != lastWateringDate && hour > 3)) {
      didWater = true;
      lastWateringDate = date;
      lastWateringHour = hour;
      lastWateringMinute = minute;

      digitalWrite(motorPin, HIGH);
      
      Serial.println("Do watering");
      delay(1000 * wateringDuration);
    } else {
      Serial.println("Skipping watering");
    }
  } else {
    Serial.println("Should not water");
  }

  digitalWrite(motorPin, LOW);
  
  delay(1000);
}

void printNow() {
  Serial.print(clock.getYear(), DEC);
  Serial.print("-");
  Serial.print(clock.getMonth(centuryFlag), DEC);
  Serial.print("-");
  Serial.print(clock.getDate(), DEC);
  Serial.print(" ");
  Serial.print(clock.getHour(h12Flag, pmFlag), DEC); //24-hr
  Serial.print(":");
  Serial.print(clock.getMinute(), DEC);
  Serial.print(":");
  Serial.println(clock.getSecond(), DEC); 
}
