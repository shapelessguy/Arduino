#define TRIG_PIN 8
#define ECHO_PIN 9
#define MIC_PIN 10
#define OUT LED_BUILTIN

int val=1;
int val_prec=1;
unsigned long timeout = 400000;

void setup() {
  Serial.begin(9600);
  pinMode(MIC_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(OUT,LOW);
}

void loop() {
      unsigned long tempo = pulseIn(MIC_PIN, LOW, timeout);
      if(tempo>0) {
        delay(200);
        tempo = pulseIn(MIC_PIN, LOW, timeout);
        if(tempo>0) Activate();
        }
}

void Activate(){
  Serial.println("Activated");
  int out = digitalRead(OUT); 
  if(out==1) digitalWrite(OUT,LOW); 
  else digitalWrite(OUT,HIGH); 
  delay(1000);
}
