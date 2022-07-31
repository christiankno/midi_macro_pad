#include <Arduino.h>
#include <BLEMidi.h>
#include <note_values.h>

int incomingByte = 0; // for incoming serial data
bool lock = 0;

#define CC_UP 1
#define CC_DOWN 127

#define BUTTON1_PIN 22
#define BUTTON2_PIN 19
#define BUTTON3_PIN 23
#define BUTTON4_PIN 18

#define ENC1_BTN_PIN 16
#define ENC1_A_PIN 17
#define ENC1_B_PIN 5

#define SWITCH_PIN 2

#define DEBOUNCE_DELAY 20
#define TRIGGER_DEBOUNCE_DELAY 1

#define DEVICE_NAME "MIDI-PAD"

// int8_t up_value = 1;
// int8_t down_value = 1;

class Button{
  private:
    //pin config 
    uint pin = 0;
    uint mode = 1;
    //debounce timings
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 50;
    //current and past states
    bool buttonState=0;
    bool lastButtonState=0;

  public:
    //mappings
    uint mappedValue = 0x60;
    //pending actions
    int pendingPress = 0;
    int pendingRelease = 0;

    Button(uint Pin, uint Mode, unsigned long DebounceDelay, uint MappedValue){
      //pin config
      pin = Pin;
      mode = Mode;
      //debounce config
      debounceDelay = DebounceDelay;
      //mapping config
      mappedValue = MappedValue;
      //state initialization
      buttonState = digitalRead(pin);
      lastButtonState = digitalRead(pin);
    }

    void setup(){
      pinMode(pin, mode);
    }

    void update(){
      bool reading = digitalRead(pin);
      if (reading != lastButtonState){
        lastDebounceTime = millis();
      }
      if ((millis() - lastDebounceTime) > debounceDelay){
        if (reading!=buttonState){
          buttonState=reading;
          if (!buttonState){
            pendingPress++;
            Serial.print("Button pressed for Note: ");
            Serial.println(int2Note(mappedValue));
          } else{
            pendingRelease++;
            Serial.print("Button released for Note: ");
            Serial.println(int2Note(mappedValue));

          }
        }
      } 
      lastButtonState = reading;
    }

    void resetPending(){
      this->pendingPress=0;
      this->pendingRelease=0;
    }

    bool getState(){ // True if button is not pressed when using pull_up
      return buttonState;
    }

    bool isPressed(){ // True if button is pressed (with a value of LOW due to the pull-up)
      return !buttonState;
    }

};

class Encoder{
  private:
    //pin config
    uint pinA = 0;
    uint pinB = 0;
    uint pinBtn = 0;
    uint mode = 1;
    //debounce timings
    unsigned long lastDebounceTimeTrigger = 0;
    unsigned long debounceDelayTrigger = 50;
    unsigned long lastDebounceTimeBtn = 0;
    unsigned long debounceDelayBtn = 50;

    //current and past states
    bool buttonState=0;
    bool lastButtonState=0;
    bool triggerState=0;
    bool lastTriggerState=0;


  public:
    //mappings
    uint mapBtn = 0x60;
    uint mapE = 0x61;
    //pending actions
    int pendingPress = 0;
    int pendingRelease = 0;
    int pendingRotation = 0;

    Encoder(uint PinA, uint PinB, uint PinBtn, uint Mode, unsigned long DebounceDelayTrigger, unsigned long DebounceDelayBtn, uint MapE, uint MapBtn){
      //pin config
      pinA = PinA;
      pinB = PinB;
      pinBtn = PinBtn;
      mode = Mode;
      //mapping config
      mapE = MapE;
      mapBtn = MapBtn;
      //debounce config
      debounceDelayBtn = DebounceDelayBtn;
      debounceDelayTrigger = DebounceDelayTrigger;

      //state initialization
      buttonState = digitalRead(pinBtn);
      lastButtonState = buttonState;
      triggerState = digitalRead(pinA);
      lastTriggerState = triggerState;

    }

    void setup(){
      pinMode(pinBtn, mode);
      pinMode(pinA, mode);
      pinMode(pinB, mode);
    }

    void updateBtn(){
      bool reading = digitalRead(pinBtn);
      if (reading != lastButtonState){
        lastDebounceTimeBtn = millis();
      }
      if ((millis() - lastDebounceTimeBtn) > debounceDelayBtn){
        if (reading!=buttonState){
          buttonState=reading;
          if (!buttonState){
            pendingPress++;
            Serial.print("Button pressed for Note: ");
            Serial.println(int2Note(mapBtn));
          } else{
            pendingRelease++;
            Serial.print("Button released for Note: ");
            Serial.println(int2Note(mapBtn));

          }
        }
      } 
      lastButtonState = reading;
    }

    void updateRotation(){
      bool reading = digitalRead(pinA);
      if (reading != lastTriggerState){
        lastDebounceTimeTrigger = millis();
      }
      if ((millis() - lastDebounceTimeTrigger) > debounceDelayTrigger){
        if (reading!=triggerState){
          triggerState=reading;

          if (!digitalRead(this->pinB)){
            pendingRotation += (!triggerState? 1 : -1);
            Serial.print((!triggerState? "Right":"Left"));
            Serial.print(" Rotation. CC");
            Serial.print(this->mapE);
            Serial.print(" ");
            Serial.println((!triggerState? CC_UP:CC_DOWN));
            Serial.print("Pending Rotation:");
            Serial.println(this->pendingRotation);
            
          }

          // if (!triggerState && !digitalRead(this->pinB)){
          //   pendingRotation++;
          //   Serial.print("Right Rotation. CC");
          //   Serial.print(this->mapE);
          //   Serial.print(" ");
          //   Serial.println(CC_UP);
          //   Serial.print("Pending Rotation:");
          //   Serial.println(this->pendingRotation);
          // } 
          // if (triggerState && !digitalRead(this->pinB)){
          //   pendingRotation--;
          //   Serial.print("Left Rotation. CC");
          //   Serial.print(this->mapE);
          //   Serial.print(" ");
          //   Serial.println(CC_DOWN);
          //   Serial.print("Pending Rotation:");
          //   Serial.println(this->pendingRotation);
          // }


        }
      } 
      lastTriggerState = reading;
    }

    void update(){
      this->updateBtn();
      this->updateRotation();
    }

    void resetPending(){
      this->pendingPress=0;
      this->pendingRelease=0;
      this->pendingRotation=0;
    }

    bool getState(){ // True if button is not pressed when using pull_up
      return buttonState;
    }

    bool isPressed(){ // True if button is pressed (with a value of LOW due to the pull-up)
      return !buttonState;
    }

};

Button btn1(BUTTON1_PIN,INPUT_PULLUP,DEBOUNCE_DELAY,A0);
Button btn2(BUTTON2_PIN,INPUT_PULLUP,DEBOUNCE_DELAY,As0);
Button btn3(BUTTON3_PIN,INPUT_PULLUP,DEBOUNCE_DELAY,B0);
Button btn4(BUTTON4_PIN,INPUT_PULLUP,DEBOUNCE_DELAY,C1);
Button swtch(SWITCH_PIN,INPUT_PULLUP,DEBOUNCE_DELAY,Cs1);

Encoder enc0(ENC1_A_PIN, ENC1_B_PIN, ENC1_BTN_PIN, INPUT_PULLUP, TRIGGER_DEBOUNCE_DELAY, DEBOUNCE_DELAY, D1, E1);





void sendPendingButtonNote(Button& btn, uint velocity){
  if (btn.pendingPress>0){
    BLEMidiServer.noteOn(0, btn.mappedValue, velocity);
    btn.pendingPress--;
    // delayMicroseconds(300);
  }
  if (btn.pendingRelease>0){
    BLEMidiServer.noteOff(0, btn.mappedValue, velocity);        // Then we make a delay of one second before returning to the beginning of the loop
    btn.pendingRelease--;
    // delayMicroseconds(300);
  }
  //btn.resetPending();
}

void sendPendingRotationNote(Encoder& enc, uint velocity){
  if (enc.pendingRotation>0){
    BLEMidiServer.controlChange(0, enc.mapE, CC_UP);
    enc.pendingRotation--;
    // delayMicroseconds(30);
  }
  if (enc.pendingRotation<0){
    BLEMidiServer.controlChange(0, enc.mapE, CC_DOWN);
    enc.pendingRotation++;
    // delayMicroseconds(30);
  }
}



void inputSetup(){
  btn1.setup();
  btn2.setup();
  btn3.setup();
  btn4.setup();
  swtch.setup();
  enc0.setup();
}

void inputUpdate(){
  // unsigned long time0 = micros();

  btn1.update();


  btn2.update();


  btn3.update();


  btn4.update();

  swtch.update();

  enc0.update();

  // Serial.print(micros()-time0);
  // Serial.print("\t");
  // Serial.println(micros());
  // Serial.print("Time spent updating: ");
}

void sendPending(){
  uint velocity = 64;
  sendPendingButtonNote(btn1, velocity);
  sendPendingButtonNote(btn2, velocity);
  sendPendingButtonNote(btn3, velocity);
  sendPendingButtonNote(btn4, velocity);
  sendPendingButtonNote(swtch, velocity);
  sendPendingRotationNote(enc0, velocity);
}  

void bleMidiSetup(){
  Serial.println("Initializing bluetooth");
  BLEMidiServer.begin(DEVICE_NAME);
  Serial.println("Waiting for connections...");
  BLEMidiServer.enableDebugging();  // Uncomment if you want to see some debugging output from the library (not much for the server class...)
  while (!BLEMidiServer.isConnected()) {Serial.print(".");}
  Serial.println();
  Serial.println("Connected");
}


void setup() {
  Serial.begin(115200);
  inputSetup();
  inputUpdate();
  bleMidiSetup();
}


void loop() {
  if(BLEMidiServer.isConnected()) {             // If we've got a connection, we send an A4 during one second, at full velocity (127)
    inputUpdate();
    sendPending();
    
  }
}
