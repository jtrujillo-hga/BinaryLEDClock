// Set up Pins
const int second[] = {2, 3, 4, 5, 6, 19};                                 // second[0] is the least significant byte
const int minute[] = {18, 17, 16, 15, 7, 8};                              // minute[0] is least significant byte
const int hour[] = {11, 10, 9};                                           // hour[0] is least significant byte
const int pins[] = {2, 3, 4, 5, 6, 19, 18, 17, 16, 15, 7, 8, 9, 10, 11};
const int button[] = {12, 13};

enum set {
  normal,
  stopwatch,
};
set mode = normal;

int parsedTime[] = {0, 0, 0};
int stopwatchTime[] = {0, 0, 0};

boolean stop = false;
int buttonReading[] = {HIGH, HIGH};

unsigned long now = 0;
unsigned long nextTime = 0;
unsigned long period = 1000;
unsigned long modeButtonPeriod = 3000;
unsigned long lastDebounceTime[] = {0, 0};
unsigned long debouncePeriod = 100;
unsigned long count = 0;
boolean startPress = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 2; i < 20; i++) {
    if (i == 12 || i == 13) {
      //pinMode(i, INPUT_PULLUP);                 pinMode for buttons
    }
    else {
      pinMode(i, OUTPUT);
      digitalWrite(i, LOW);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //  testPins();
  now = millis();
//  if (digitalRead(button[1]) == LOW) {
//    count++;
//  }
//  else {
//    count = 0;
//  }
//  if (count > 20000) {
//    nextMode();
//  }
  
//  buttonReading[1] = digitalRead(button[1]);
//  if (buttonReading[1] == LOW) {
//     if (startPress == false) {
//      startPress = true;
//      lastDebounceTime[1] = millis(); 
//    }
//  }
//  
//  else {
//     startPress = false;
//     if (millis() - lastDebounceTime[1] > 3000) {
//      //  Serial.println(millis() - lastDebounceTime[1]);
//     }
//  }

  if (Serial.available() == 8) {
    readTime();
  }
  if (mode == stopwatch) {
    stopwatchMode();
  }
  else if (mode == normal) {
    lightTime(parsedTime[2], parsedTime[1], parsedTime[0]);
  }
  //  else if (mode == timer) {
  //
  //  }


  if (now > nextTime) {
    updateTime(parsedTime);
    nextTime = now + period;
//    for (int i = 0; i < 3; i++) {
//    
//    if (i==0) {
//      Serial.println(parsedTime[i] % 8, BIN);
//    }
//    else {
//      Serial.println(parsedTime[i], BIN);
//    }
//    
//  }
  }
  
}


void readTime() {
  int newInt[] = {0, 0, 0, 0, 0, 0};
  int z = 0;
  while (Serial.available() > 0) {
    char rawInput = Serial.read();
 //   Serial.print(newInput);
    char newInput = rawInput - 48;
    if (newInput >= 0 && newInput < 10) {
      newInt[z] = newInput;
      z++;
    }
  }
 // Serial.println();
  for (int i = 0; i < 3; i++) {
    parsedTime[2-i] = 10 * newInt[2 * i] + newInt[2 * i + 1];
//    if (i==2) {
//      Serial.println(parsedTime[i] % 8, BIN);
//    } 
//    else {
//      Serial.println(parsedTime[i], BIN);
//    }
//    
  }
}

void lightTime(int h, int m, int s) {

  for (int i = 0; i < 6; i++) {
    digitalWrite(minute[5 - i], ((m >> (5 - i))) & 1);
    digitalWrite(second[5 - i], ((s >> (5 - i))) & 1);
    if (i < 3) {
      digitalWrite(hour[i], ((h % 8) >> (2 - i)) & 1);
    }
  }
}
void resetClock() {
  for (int i = 0; i < 3; i++) {
    parsedTime[i] = 0;
  }
  for (int i = 2; i < 20; i++) {
    if (i != 12 && i != 13) {
      digitalWrite(i, LOW);
    }
  }
}

void updateTime(int a[]) {
  a[0] = a[0] + 1;
  if (a[0] == 60) {
    a[0] = 0;
    a[1] = a[1] + 1;
    if (a[1] == 60) {
      a[1] = 0;
      a[2] = a[2] + 1;
      Serial.println("tick");
      if (a[2] == 24) {
        a[2] = 0;
      }
    }
  }
  for (int i = 0; i < 3; i++) {
    if (stopwatch == true) {
      stopwatchTime[i] = a[i];
    }
    else {
      parsedTime[i] = a[i];
    }
  }
}

void testPins() {     // checks that all LEDs are wired
  for (int i = 0; i < 15; i++) {
    digitalWrite(pins[i], HIGH);
    delay(500);
    digitalWrite(pins[i], LOW);
  }
}

void stopwatchMode() {

  lightTime(stopwatchTime[0], stopwatchTime[1], stopwatchTime[2]);
  if (stop == false) {
    if (now > nextTime) {
      updateTime(stopwatchTime);
      nextTime = now + period;
    }
  }
  buttonReading[1] = digitalRead(button[1]);
  if (buttonReading[1] = LOW) {
    if (stop == true) {
      stop = false;
    }
    else {
      stop = true;
    }
  }

}

void nextMode() {
  
    if (mode == normal) {
      mode = stopwatch;
    }
    else if (mode == stopwatch) {
      mode = normal;
    }
  
}

