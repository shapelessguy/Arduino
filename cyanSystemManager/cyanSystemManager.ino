#include <String.h>
#define AUDIO_PIN 3
#define LIGHT_PIN 2
bool default_audio_on = true;
bool audio_status = true;
bool keep_audio = false;
bool light_status = true;

void setup() {
  Serial.begin(9600);
  pinMode(AUDIO_PIN, OUTPUT);
  pinMode(LIGHT_PIN, OUTPUT);
}

int sec_autonomy = 60;
int auto_shutdown_audio = 10 * sec_autonomy;
char deviceCode = '_';
int DELAY = 100;

void loop() {

  for(int i=0; i<Serial.available(); i++){
    char ch = Serial.read();
    if (ch == 'p') auto_shutdown_audio = 10 * sec_autonomy;

    // Read first byte
    if(i==0) { 
      if(ch == 'Q') Serial.println("cyanSystemManager");
      deviceCode = ch;
    }

    // Read second byte
    else if(i==1){
      if (deviceCode == 'A'){ // Audio device selected
        if(ch == 'H') { digitalWrite(AUDIO_PIN, HIGH); default_audio_on = true; audio_status = true; keep_audio = false;}
        else if(ch == 'K') { digitalWrite(AUDIO_PIN, HIGH); default_audio_on = true; audio_status = true; keep_audio = true;}
        else if(ch == 'L') { digitalWrite(AUDIO_PIN, LOW); default_audio_on = false; audio_status = false; keep_audio = false;}
        else if(ch == 'S') { Serial.println(audio_status + default_audio_on + keep_audio);}
      }
      else if (deviceCode == 'L'){ // Light device selected
        if(ch == 'H') { digitalWrite(LIGHT_PIN, HIGH); light_status = true;}
        else if(ch == 'L') { digitalWrite(LIGHT_PIN, LOW); light_status = false;}
        else if(ch == 'S') { Serial.println(light_status);}
      }
    }
  }

  // Collect noisy values
  while(Serial.available() > 0) {
    char t = Serial.read();
  }
  
  if (!keep_audio) auto_shutdown_audio -= 1;
  if (auto_shutdown_audio < 0){
    auto_shutdown_audio = 0;
    if (audio_status) {
      digitalWrite(AUDIO_PIN, LOW); 
      audio_status = false;
    }
  }
  else{
    if (default_audio_on) {
      digitalWrite(AUDIO_PIN, HIGH); 
      audio_status = true;
    }
  }
  delay(DELAY);
}