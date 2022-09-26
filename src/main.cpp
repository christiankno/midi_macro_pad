#include <Arduino.h>
#include <BLEMidi.h>
#include <note_values.h>
#define USING_MATRIX

// pins used. not needed once matrix is set up
#define BUTTON1_PIN 22
#define BUTTON4_PIN 19
#define BUTTON7_PIN 23
#define BUTTON10_PIN 18

#define BTN_UP_PIN 16
#define ENC_UP_A_PIN 17
#define ENC_UP_B_PIN 5


// dummy definitions not really connected. should be removed in the end
#define BTN_DOWN_PIN     13 
#define BTN_LEFT_PIN     13 
#define BTN_RIGHT_PIN    13  
#define ENC_DOWN_A_PIN   13   
#define ENC_DOWN_B_PIN   13   
#define ENC_LEFT_A_PIN   13   
#define ENC_LEFT_B_PIN   13   
#define ENC_RIGHT_A_PIN  13    
#define ENC_RIGHT_B_PIN  13    

#define BUTTON2_PIN      13 
#define BUTTON3_PIN      13 
#define BUTTON5_PIN      13 
#define BUTTON6_PIN      13 
#define BUTTON8_PIN      13 
#define BUTTON9_PIN      13 
#define BUTTON11_PIN     13  
#define BUTTON12_PIN     13  


// debounce delays
#define DEBOUNCE_DELAY 20
#define TRIGGER_DEBOUNCE_DELAY 1

#define COLUMN_SCAN_DELAY_MS 30

// MIDI settings
#define DEVICE_NAME "MIDI-PAD2"
#define MIDI_CHANNEL 1
#define CC_UP 1
#define CC_DOWN 127


/*
################  
#|     UP     |#   #########
#|LEFT + RIGHT|#   #| MAG |#
#|    DOWN    |#   #########
################  

########################
#|LAYER | NOTE | NOTE |#           
#|SELECT|ACTION|ACTION|#            
#|--------------------|#            
#|  1   |  2   |  3   |#         
#|  4   |  5   |  6   |#         
#|  7   |  8   |  9   |#         
#|  10  |  11  |  12  |#          
########################
*/



// input numbering. the order should be the same as in the mappingStruct
#define N_ENC_MAG     0
#define N_ENC_UP      (N_ENC_MAG + 1)
#define N_ENC_DOWN    (N_ENC_UP + 1)
#define N_ENC_LEFT    (N_ENC_DOWN + 1)
#define N_ENC_RIGHT   (N_ENC_LEFT + 1)
#define N_BUTTON_UP        (N_ENC_RIGHT + 1)
#define N_BUTTON_DOWN      (N_BUTTON_UP + 1)
#define N_BUTTON_LEFT      (N_BUTTON_DOWN + 1)
#define N_BUTTON_RIGHT     (N_BUTTON_LEFT + 1)
#define N_BUTTON_1    (N_BUTTON_RIGHT + 1)   
#define N_BUTTON_2    (N_BUTTON_1 + 1)   
#define N_BUTTON_3    (N_BUTTON_2 + 1)   
#define N_BUTTON_4    (N_BUTTON_3 + 1)   
#define N_BUTTON_5    (N_BUTTON_4 + 1)   
#define N_BUTTON_6    (N_BUTTON_5 + 1)   
#define N_BUTTON_7    (N_BUTTON_6 + 1)   
#define N_BUTTON_8    (N_BUTTON_7 + 1)   
#define N_BUTTON_9    (N_BUTTON_8 + 1)   
#define N_BUTTON_10   (N_BUTTON_9 + 1)    
#define N_BUTTON_11   (N_BUTTON_10 + 1)    
#define N_BUTTON_12   (N_BUTTON_11 + 1)    

#define N_INPUTS      (N_BUTTON_12 + 1)
  
// layer numbering. Same order as in mappingStruct.layerMappings
#define N_LAYER_1     128
#define N_LAYER_2U    (N_LAYER_1 + 1)
#define N_LAYER_2D    (N_LAYER_2U + 1)
#define N_LAYER_3     (N_LAYER_2D + 1)
#define N_LAYER_4U    (N_LAYER_3 + 1)
#define N_LAYER_4L    (N_LAYER_4U + 1)
#define N_LAYER_4D    (N_LAYER_4L + 1)


#define N_LAYERS      (N_LAYER_4D + 1 - 128)



// matrix dimensions. rows are shared by buttons and encoders. but encoders are treated as a separate matrix with two separate columns
#define BTN_COLUMNS 4
#define BTN_ROWS 4
#define ENC_ROWS 4
#define ENC_COLUMNS 2

// temporary values for matrix pins. unused right now, should be updated when true values are known
#define COLUMN_PIN_1 22 
#define COLUMN_PIN_2 19
#define COLUMN_PIN_3 23
#define COLUMN_PIN_4 18
#define COLUMN_PIN_A 17
#define COLUMN_PIN_B 5
#define ROW_PIN_1 16
#define ROW_PIN_2 2
#define ROW_PIN_3 15
#define ROW_PIN_4 13



int16_t buttonsPressedArr[N_INPUTS] = {0};
int16_t pendingPressArr[N_INPUTS] = {0};
int16_t pendingReleaseArr[N_INPUTS] = {0};
uint16_t currentLayer = 0;


// Input classes declaration and definition
class Button{
  private:
    //pin config 
    uint pin = 0;
    uint mode = 1;
    //debounce timings
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = DEBOUNCE_DELAY;
    //current and past states
    bool buttonState=1;
    bool lastButtonState=1;
    //pending actions
    int16_t *pendingPressPtr = NULL;
    int16_t *pendingReleasePtr = NULL; 
    int16_t *buttonPressedPtr = NULL; 

  public:
    Button(int16_t N){
      //adress for pending actions

      pendingPressPtr = &(pendingPressArr[N]);
      pendingReleasePtr = &(pendingReleaseArr[N]);
      buttonPressedPtr = &(buttonsPressedArr[N]);
      
    }

    Button(int16_t& pendingPress, int16_t& pendingRelease){
      //address for epnding actions
      pendingPressPtr = &pendingPress;
      pendingReleasePtr = &pendingRelease;
    }

    Button(unsigned long DebounceDelay, int16_t& pendingPress, int16_t& pendingRelease){
      //debounce config
      debounceDelay = DebounceDelay;
      //address for epnding actions
      pendingPressPtr = &pendingPress;
      pendingReleasePtr = &pendingRelease;
    }

    Button(uint Pin, uint Mode, unsigned long DebounceDelay, int16_t& pendingPress, int16_t& pendingRelease){
      //pin config
      pin = Pin;
      mode = Mode;
      //debounce config
      debounceDelay = DebounceDelay;
      //state initialization
      buttonState = digitalRead(pin);
      lastButtonState = digitalRead(pin);

      pendingPressPtr = &pendingPress;
      pendingReleasePtr = &pendingRelease;
    }

    void setup(){
      pinMode(pin, mode);
    }

    void update(){
      if (!pin) {return;}
      this->update(digitalRead(pin));
    }

    void update(bool reading){
      if (reading != lastButtonState){
        lastDebounceTime = millis();
      }
      if ((millis() - lastDebounceTime) > debounceDelay){
        if (reading!=buttonState){
          buttonState=reading;
          if (buttonPressedPtr!=NULL) {*buttonPressedPtr = !buttonState;}
          if (!buttonState){
            (*pendingPressPtr)++;
            Serial.print("Button pressed for Pin: ");
            Serial.println(pin);
          } else{
            (*pendingReleasePtr)++;
            Serial.print("Button released for Pin: ");
            Serial.println(pin);
          }
        }
      } 
      lastButtonState = reading;
    }

    void resetPending(){
      *(this->pendingPressPtr)=0;
      *(this->pendingReleasePtr)=0;
    }
    
    bool getState(){ return buttonState;}   // True if button is not pressed when using pull_up
    bool isPressed(){ return !buttonState;} // True if button is pressed (with a value of LOW due to the pull-up)

};

class Encoder{
  private:
    //pin config
    uint pinA = 0;
    uint pinB = 0;
    uint mode = INPUT_PULLUP;
    //debounce timings
    unsigned long lastDebounceTimeTrigger = 0;
    unsigned long debounceDelayTrigger = TRIGGER_DEBOUNCE_DELAY;
    //current and past states
    bool triggerState=1;
    bool lastTriggerState=1;
    //pending actions
    int16_t *pendingRotationPtr = NULL;

  public:
    #ifdef USING_MATRIX
    Encoder(int16_t N){
      //adress for pending actions
      pendingRotationPtr = &(pendingPressArr[N]);
    }
    #else
    Encoder(int16_t& pendingRotation){
      //adress for pending actions
      pendingRotationPtr = &pendingRotation;
    }
    #endif

    Encoder(unsigned long DebounceDelayTrigger, int16_t& pendingRotation){
      //debounce config
      debounceDelayTrigger = DebounceDelayTrigger;
      //adress for pending actions
      pendingRotationPtr = &pendingRotation;
    }

    Encoder(uint PinA, uint PinB, uint Mode, unsigned long DebounceDelayTrigger, int16_t& pendingRotation){
      //pin config
      pinA = PinA;
      pinB = PinB;
      mode = Mode;
      //debounce config
      debounceDelayTrigger = DebounceDelayTrigger;

      //state initialization
      triggerState = digitalRead(pinA);
      lastTriggerState = triggerState;

      pendingRotationPtr = &pendingRotation;
    }

    void setup(){
      pinMode(pinA, mode);
      pinMode(pinB, mode);
    }

    void update(){ // Reads and Updates pendingRotation counter with the appropiate amount of clicks.
      if (!pinA && !pinB) {return;}
      this->update(digitalRead(pinA), digitalRead(pinB));
    }

    void update(bool readingA, bool readingB) {
      if (readingA != lastTriggerState){
        lastDebounceTimeTrigger = millis();
      }
      if ((millis() - lastDebounceTimeTrigger) > debounceDelayTrigger){
        if (readingA!=triggerState){
          triggerState=readingA;

          if (!readingB){
            (*pendingRotationPtr) += (!triggerState? 1 : -1);
            Serial.print((!triggerState? "Right":"Left"));
            Serial.print(" Rotation.\t");
            Serial.print((!triggerState? CC_UP:CC_DOWN));
            Serial.print("\tPending Rotation:");
            Serial.println(*(this->pendingRotationPtr));
          }
        }
      } 
      lastTriggerState = readingA;
    }

    void resetPending(){ //resets pending pressses and rotations
      *(this->pendingRotationPtr) = 0;
    }

};

// input instances declarations

#ifndef USING_MATRIX
Button btn1(BUTTON1_PIN,INPUT_PULLUP,DEBOUNCE_DELAY,pendingPressArr[N_BUTTON_1],pendingReleaseArr[N_BUTTON_1]);
Button btn2(BUTTON2_PIN,INPUT_PULLUP,DEBOUNCE_DELAY,pendingPressArr[N_BUTTON_2],pendingReleaseArr[N_BUTTON_2]);
Button btn3(BUTTON3_PIN,INPUT_PULLUP,DEBOUNCE_DELAY,pendingPressArr[N_BUTTON_3],pendingReleaseArr[N_BUTTON_3]);
Button btn4(BUTTON4_PIN,INPUT_PULLUP,DEBOUNCE_DELAY,pendingPressArr[N_BUTTON_4],pendingReleaseArr[N_BUTTON_4]);
Button btn5(BUTTON5_PIN,INPUT_PULLUP,DEBOUNCE_DELAY,pendingPressArr[N_BUTTON_5],pendingReleaseArr[N_BUTTON_5]);
Button btn6(BUTTON6_PIN,INPUT_PULLUP,DEBOUNCE_DELAY,pendingPressArr[N_BUTTON_6],pendingReleaseArr[N_BUTTON_6]);
Button btn7(BUTTON7_PIN,INPUT_PULLUP,DEBOUNCE_DELAY,pendingPressArr[N_BUTTON_7],pendingReleaseArr[N_BUTTON_7]);
Button btn8(BUTTON8_PIN,INPUT_PULLUP,DEBOUNCE_DELAY,pendingPressArr[N_BUTTON_8],pendingReleaseArr[N_BUTTON_8]);
Button btn9(BUTTON9_PIN,INPUT_PULLUP,DEBOUNCE_DELAY,pendingPressArr[N_BUTTON_9],pendingReleaseArr[N_BUTTON_9]);
Button btn10(BUTTON10_PIN,INPUT_PULLUP,DEBOUNCE_DELAY,pendingPressArr[N_BUTTON_10],pendingReleaseArr[N_BUTTON_10]);
Button btn11(BUTTON11_PIN,INPUT_PULLUP,DEBOUNCE_DELAY,pendingPressArr[N_BUTTON_11],pendingReleaseArr[N_BUTTON_11]);
Button btn12(BUTTON12_PIN,INPUT_PULLUP,DEBOUNCE_DELAY,pendingPressArr[N_BUTTON_12],pendingReleaseArr[N_BUTTON_12]);

Button btnUp(BTN_UP_PIN,INPUT_PULLUP,DEBOUNCE_DELAY,pendingPressArr[N_BUTTON_UP],pendingReleaseArr[N_BUTTON_UP]);
Button btnDown(BTN_DOWN_PIN,INPUT_PULLUP,DEBOUNCE_DELAY,pendingPressArr[N_BUTTON_DOWN],pendingReleaseArr[N_BUTTON_DOWN]);
Button btnLeft(BTN_LEFT_PIN,INPUT_PULLUP,DEBOUNCE_DELAY,pendingPressArr[N_BUTTON_LEFT],pendingReleaseArr[N_BUTTON_LEFT]);
Button btnRight(BTN_RIGHT_PIN,INPUT_PULLUP,DEBOUNCE_DELAY,pendingPressArr[N_BUTTON_RIGHT],pendingReleaseArr[N_BUTTON_RIGHT]);
Encoder encUp(ENC_UP_A_PIN, ENC_UP_B_PIN, INPUT_PULLUP, TRIGGER_DEBOUNCE_DELAY, pendingPressArr[N_ENC_UP]);
Encoder encDown(ENC_DOWN_A_PIN, ENC_DOWN_B_PIN, INPUT_PULLUP, TRIGGER_DEBOUNCE_DELAY, pendingPressArr[N_ENC_DOWN]);
Encoder encLeft(ENC_LEFT_A_PIN, ENC_LEFT_B_PIN, INPUT_PULLUP, TRIGGER_DEBOUNCE_DELAY, pendingPressArr[N_ENC_LEFT]);
Encoder encRight(ENC_RIGHT_A_PIN, ENC_RIGHT_B_PIN, INPUT_PULLUP, TRIGGER_DEBOUNCE_DELAY, pendingPressArr[N_ENC_RIGHT]);

#else

Button btn1(N_BUTTON_1);
Button btn2(N_BUTTON_2);
Button btn3(N_BUTTON_3);
Button btn4(N_BUTTON_4);
Button btn5(N_BUTTON_5);
Button btn6(N_BUTTON_6);
Button btn7(N_BUTTON_7);
Button btn8(N_BUTTON_8);
Button btn9(N_BUTTON_9);
Button btn10(N_BUTTON_10);
Button btn11(N_BUTTON_11);
Button btn12(N_BUTTON_12);

Button btnUp(N_BUTTON_UP);
Button btnDown(N_BUTTON_DOWN);
Button btnLeft(N_BUTTON_LEFT);
Button btnRight(N_BUTTON_RIGHT);
Encoder encUp(N_ENC_UP);
Encoder encDown(N_ENC_DOWN);
Encoder encLeft(N_ENC_LEFT);
Encoder encRight(N_ENC_RIGHT);
#endif





struct {
  // PGM_P name;
  const uint8_t inputNumber;
  // int16_t pendingPress;
  // int16_t pendingRelease;
  const bool isEncoder;
  const uint16_t layerMapping[N_LAYERS];
} const mappingStruct[N_INPUTS] PROGMEM = { // USE SAME ORDER FROM DEFINITION OF N_(ENC|BUTTON)_*
	// inputNumber	isEncoder        {LAYER_1		         LAYER_2U		                     LAYER_2B		                        LAYER_3		                    LAYER_4U		                         LAYER_4L		                          LAYER_4D}	
  {	N_ENC_MAG,     IS_ENCODER,     {	CC_ROTATION,     CC_NEG_SCAN_BIAS,               CC_NEG_SCAN_BIAS,                  NO_ACTION,                    CC_COLOR_BALANCE_CONTRAST,           CC_COLOR_BALANCE_CONTRAST,           CC_COLOR_BALANCE_CONTRAST              }},
  {	N_ENC_UP,      IS_ENCODER,     {	CC_CROP_UP,      CC_NEG_SHADOW_RED_OFFSET,       CC_NEG_HIGHLIGHTS_RED_OFFSET,      CC_COLOR_CORRECTION_WHITE_V,  CC_COLOR_BALANCE_SHADOWS_FACTOR,     CC_COLOR_BALANCE_MIDS_FACTOR,        CC_COLOR_BALANCE_HIGHLIGHTS_FACTOR     }},
  {	N_ENC_DOWN,    IS_ENCODER,     {	CC_CROP_DOWN,    CC_NEG_SHADOW_BLUE_OFFSET,      CC_NEG_HIGHLIGHTS_BLUE_OFFSET,     CC_COLOR_CORRECTION_BLACK_V,  CC_COLOR_BALANCE_SHADOWS_SATURATION, CC_COLOR_BALANCE_MIDS_SATURATION,    CC_COLOR_BALANCE_HIGHLIGTHS_SATURATION }},
  {	N_ENC_LEFT,    IS_ENCODER,     {	CC_CROP_LEFT,    CC_NEG_SHADOW_GREEN_OFFSET,     CC_NEG_HIGHLIGHTS_GREEN_OFFSET,    CC_COLOR_CORRECTION_BLACK_H,  CC_COLOR_BALANCE_SHADOWS_HUE,        CC_COLOR_BALANCE_MIDS_HUE,           CC_COLOR_BALANCE_HIGHLIGHTS_HUE        }},
  {	N_ENC_RIGHT,   IS_ENCODER,     {	CC_CROP_RIGHT,   CC_NEG_DMAX,                    CC_NEG_DMAX,                       CC_COLOR_CORRECTION_WHITE_H,  NO_ACTION,                           NO_ACTION,                           NO_ACTION                              }},
  {	N_BUTTON_UP,        IS_BUTTON,      {	NO_ACTION,       N_LAYER_2U,                     N_LAYER_2U,                        NO_ACTION,                    N_LAYER_4U,                          N_LAYER_4U,                          N_LAYER_4U                             }},
  {	N_BUTTON_DOWN,      IS_BUTTON,      {	NO_ACTION,       N_LAYER_2D,                     N_LAYER_2D,                        NO_ACTION,                    N_LAYER_4D,                          N_LAYER_4D,                          N_LAYER_4D                             }},
  {	N_BUTTON_LEFT,      IS_BUTTON,      {	NO_ACTION,       NO_ACTION,                      NO_ACTION,                         NO_ACTION,                    N_LAYER_4L,                          N_LAYER_4L,                          N_LAYER_4L                             }},
  {	N_BUTTON_RIGHT,     IS_BUTTON,      {	NO_ACTION,       NO_ACTION,                      NO_ACTION,                         NO_ACTION,                    NO_ACTION,                           NO_ACTION,                           NO_ACTION                              }},
  {	N_BUTTON_1,    IS_BUTTON,      {	N_LAYER_1,       N_LAYER_1,                      N_LAYER_1,                         N_LAYER_1,                    N_LAYER_1,                           N_LAYER_1,                           N_LAYER_1                              }},
  {	N_BUTTON_2,    IS_BUTTON,      {	NOTE_ROTATE_L,   NOTE_ROTATE_L,                  NOTE_ROTATE_L,                     NOTE_ROTATE_L,                NOTE_ROTATE_L,                       NOTE_ROTATE_L,                       NOTE_ROTATE_L                          }},
  {	N_BUTTON_3,    IS_BUTTON,      {	NOTE_ROTATE_R,   NOTE_ROTATE_R,                  NOTE_ROTATE_R,                     NOTE_ROTATE_R,                NOTE_ROTATE_R,                       NOTE_ROTATE_R,                       NOTE_ROTATE_R                          }},
  {	N_BUTTON_4,    IS_BUTTON,      {	N_LAYER_2U,      N_LAYER_2U,                     N_LAYER_2U,                        N_LAYER_2U,                   N_LAYER_2U,                          N_LAYER_2U,                          N_LAYER_2U                             }},
  {	N_BUTTON_5,    IS_BUTTON,      {	NO_ACTION,       NO_ACTION,                      NO_ACTION,                         NO_ACTION,                    NO_ACTION,                           NO_ACTION,                           NO_ACTION                              }},
  {	N_BUTTON_6,    IS_BUTTON,      {	NO_ACTION,       NO_ACTION,                      NO_ACTION,                         NO_ACTION,                    NO_ACTION,                           NO_ACTION,                           NO_ACTION                              }},
  {	N_BUTTON_7,    IS_BUTTON,      {	N_LAYER_3,       N_LAYER_3,                      N_LAYER_3,                         N_LAYER_3,                    N_LAYER_3,                           N_LAYER_3,                           N_LAYER_3                              }},
  {	N_BUTTON_8,    IS_BUTTON,      {	NOTE_LIGHTTABLE, NOTE_LIGHTTABLE,                NOTE_LIGHTTABLE,                   NOTE_LIGHTTABLE,              NOTE_LIGHTTABLE,                     NOTE_LIGHTTABLE,                     NOTE_LIGHTTABLE                        }},
  {	N_BUTTON_9,    IS_BUTTON,      {	NOTE_DARKROOM,   NOTE_DARKROOM,                  NOTE_DARKROOM,                     NOTE_DARKROOM,                NOTE_DARKROOM,                       NOTE_DARKROOM,                       NOTE_DARKROOM                          }},
  {	N_BUTTON_10,   IS_BUTTON,      {	N_LAYER_4U,      N_LAYER_4U,                     N_LAYER_4U,                        N_LAYER_4U,                   N_LAYER_4U,                          N_LAYER_4U,                          N_LAYER_4U                             }},
  {	N_BUTTON_11,   IS_BUTTON,      {	NOTE_PREVIOUS,   NOTE_PREVIOUS,                  NOTE_PREVIOUS,                     NOTE_PREVIOUS,                NOTE_PREVIOUS,                       NOTE_PREVIOUS,                       NOTE_PREVIOUS                          }},
  {	N_BUTTON_12,   IS_BUTTON,      {	NOTE_NEXT,       NOTE_NEXT,                      NOTE_NEXT,                         NOTE_NEXT,                    NOTE_NEXT,                           NOTE_NEXT,                           NOTE_NEXT                              }},

};




const uint16_t btnColPins[BTN_COLUMNS] = {COLUMN_PIN_1, COLUMN_PIN_2, COLUMN_PIN_3, COLUMN_PIN_4};
const uint16_t btnRowPins[BTN_ROWS] = {ROW_PIN_1, ROW_PIN_2, ROW_PIN_3, ROW_PIN_4};
const uint16_t encRowPins[ENC_ROWS] = {ROW_PIN_1, ROW_PIN_2, ROW_PIN_3, ROW_PIN_4};
const uint16_t encColPins[ENC_COLUMNS] = {COLUMN_PIN_A, COLUMN_PIN_B};

Button* buttonMatrix[BTN_ROWS][BTN_COLUMNS] = {
  {&btn2, &btn3, &btn1, &btnUp},
  {&btn5, &btn6, &btn4, &btnLeft},
  {&btn8, &btn9, &btn7, &btnDown},
  {&btn11, &btn12, &btn10, &btnRight},
};

Encoder* encoderMatrix[ENC_ROWS] = {
  &encUp,
  &encLeft,
  &encDown,
  &encRight,
};






// setup Matrix
void setupInputMatrix(){
  // Initialize columns as Outputs on HIGH, and Rows as Inputs Pulled Up
  for (int col=0; col<BTN_COLUMNS; col++){
    pinMode(btnColPins[col], OUTPUT);
    digitalWrite(btnColPins[col], HIGH);
  }
  for (int col=0; col<ENC_COLUMNS; col++){
    pinMode(encColPins[col], OUTPUT);
    digitalWrite(encColPins[col], HIGH);
  }
  for (int row=0; row<BTN_ROWS; row++){
    pinMode(btnRowPins[row],INPUT_PULLUP);
  }
  for (int row=0; row<ENC_ROWS; row++){
    pinMode(encRowPins[row],INPUT_PULLUP);
  }
}

// scan Matrix
void scanButtonMatrix(){
  // Scan Buttons
  for (int col=0; col<BTN_COLUMNS; col++){
    digitalWrite(btnColPins[col],LOW);
    delayMicroseconds(COLUMN_SCAN_DELAY_MS);

    for (int row=0; row<BTN_ROWS; row++){
      (*(buttonMatrix[row][col])).update(digitalRead(btnRowPins[row]));
    }
    digitalWrite(btnColPins[col],HIGH);
  }
}

void scanEncoderMatrix(){
  bool encoderReadings[ENC_ROWS][ENC_COLUMNS] = {0};

  for (int col=0; col<ENC_COLUMNS; col++){
    digitalWrite(encColPins[col],LOW);
    delayMicroseconds(COLUMN_SCAN_DELAY_MS);

    for (int row=0; row<ENC_ROWS; row++){
      encoderReadings[row][col] = digitalRead(btnRowPins[row]);
    }    
    digitalWrite(encColPins[col],HIGH);
  }

  for (int row=0; row<ENC_ROWS; row++){
    (*(encoderMatrix[row])).update(encoderReadings[row][0],encoderReadings[row][1]);
  }    
}

void scanInputMatrix(){
  scanButtonMatrix();
  scanEncoderMatrix();
}

// Process inputs and perform related action. either send midi command, or perform internal action/change layer
void processRotation(int16_t& pendingRotation, uint16_t ccNumber){
  while (pendingRotation > 0){
    BLEMidiServer.controlChange(MIDI_CHANNEL, ccNumber, CC_UP);
    Serial.print("ControlChange UP\t");
    Serial.println(ccNumber);
    Serial.print(ccDict[ccNumber]);
    Serial.println("++");
    pendingRotation--;
  }

  while (pendingRotation < 0){
    BLEMidiServer.controlChange(MIDI_CHANNEL, ccNumber, CC_DOWN);
    Serial.print("ControlChange DOWN\t");
    Serial.println(ccNumber);
    Serial.print(ccDict[ccNumber]);
    Serial.println("--");
    pendingRotation++;
  }
  
}

void processButton(int16_t& pendingPress, int16_t& pendingRelease, uint16_t noteNumber){  
  if (pendingPress > 0) {
    BLEMidiServer.noteOn(MIDI_CHANNEL, noteNumber, 64);
    Serial.print("NoteOn\t");
    Serial.println(noteNumber);
    Serial.print(noteDict[noteNumber]);
    Serial.println(" Pressed");
    pendingPress--;
  }

  if (pendingRelease > 0) {
    BLEMidiServer.noteOff(MIDI_CHANNEL, noteNumber, 64);
    Serial.print("NoteOff\t");
    Serial.println(noteNumber);
    Serial.print(noteDict[noteNumber]);
    Serial.println(" Relased");
    pendingRelease--;
  } 
  
}

void processButRot(int16_t& pendingPress, int16_t& pendingRelease, uint16_t midiNumber, bool isEncoder){
  // No Action pending for this input
  if (!(pendingPress || pendingRelease)) { 
    return;
  }
  if (!midiNumber) { 
    Serial.println(ccDict[0]);
    pendingPress = 0;
    pendingRelease = 0;
    return;
  }
  
  // Change layer
  if (midiNumber > 127){
    currentLayer = midiNumber - 128;
    Serial.print("Changing to Layer: ");
    Serial.println(currentLayer);
    pendingPress = 0;
    pendingRelease = 0;
    return;
  }

  // if encoder, process rotation
  if (isEncoder) {processRotation(pendingPress, midiNumber);}
  // if button, process Press and Release
  else {processButton(pendingPress, pendingRelease, midiNumber);}
}

void processRows(){
  for (int n=0; n<N_INPUTS; n++){
    processButRot(pendingPressArr[n], pendingReleaseArr[n], mappingStruct[n].layerMapping[currentLayer], mappingStruct[n].isEncoder);
  }
}




#ifndef USING_MATRIX
// not needed once matrix is set up
void inputSetup(){
  btn1.setup();
  btn4.setup();
  btn7.setup();
  btn10.setup();

  btnUp.setup();
  encUp.setup();
}

// not needed once matrix is set up
void inputUpdate(){
  btn1.update();
  btn4.update();
  btn7.update();
  btn10.update();

  btnUp.update();
  encUp.update();
}
#endif

void bleMidiSetup(){
  Serial.println("Initializing bluetooth");
  BLEMidiServer.begin(DEVICE_NAME);
  Serial.println("Waiting for connections...");
  //BLEMidiServer.enableDebugging();  // Uncomment if you want to see some debugging output from the library (not much for the server class...)
  while (!BLEMidiServer.isConnected()) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.println("Connected");
}


//#define TESTING
#ifndef TESTING
void setup() {
  Serial.begin(115200);
  #ifndef USING_MATRIX
  inputSetup();
  inputUpdate();
  #else
  #endif

  bleMidiSetup();
  Serial.println("SetupFinished!!!");
  setupInputMatrix();
}


void loop() {
  if(BLEMidiServer.isConnected()) {             // If we've got a connection, we send an A4 during one second, at full velocity (127)
    #ifndef USING_MATRIX
    inputUpdate();
    #else
    scanInputMatrix();
    #endif
    processRows();
  }
}
#else

// Potentiometer is connected to GPIO 34 (Analog ADC1_CH6) 
const int potPin = 12;

// variable for storing the potentiometer value
int potValue = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(12, OUTPUT);
  digitalWrite(12,HIGH);
}

void loop() {
  // Reading potentiometer value
  potValue = analogRead(potPin);
  Serial.println(potValue);
  delay(500);
}
#endif