#include <String.h>
#define LIGHT_PIN 2
int DELAY = 100;
char deviceCode = '_';

void setup() {
  Serial.begin(9600);
  pinMode(LIGHT_PIN, OUTPUT);
}

void loop() {
  for(int i=0; i<Serial.available(); i++){
    char ch = Serial.read();

    // Read first byte
    if(i==0) { 
      deviceCode = ch;
    }
    else if (i == 1){
      if (deviceCode == 'L'){
        if(ch == '+') digitalWrite(LIGHT_PIN, HIGH);
        else if(ch == '-') digitalWrite(LIGHT_PIN, LOW);
      }
    }
  }

  // Collect noisy values
  while(Serial.available() > 0) {
    char t = Serial.read();
  }
  delay(DELAY);
}
