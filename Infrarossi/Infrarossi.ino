#define PIR_PIN 8
#define LED_PIN LED_BUILTIN

bool state = false;

void setup() {
    pinMode(PIR_PIN, INPUT);
    pinMode (LED_PIN, OUTPUT);
}

void loop() {
  
    if(digitalRead(PIR_PIN) ==HIGH){
      if(!state) {
        digitalWrite(LED_PIN, HIGH);
        state = true;
      }
    }
    else{
      if(state) {
        digitalWrite(LED_PIN, LOW);
        state = false;
      }
    }
  delay(10);
}
