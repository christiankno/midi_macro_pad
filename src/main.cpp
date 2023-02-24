#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <AS5600.h>

//#define ONLY_KEYBOARD

#ifndef ONLY_KEYBOARD
#include <MyBLEMidi.h>
#else
#include <BleKeyboard.h>
#endif

#include <main.h>

#include <autobindings.h>

#ifndef AUTOBINDINGS_H
#include <note_values.h>
#endif



#ifndef ONLY_KEYBOARD
// delays
#define DEBOUNCE_DELAY 20
#define TRIGGER_DEBOUNCE_DELAY 1

#define COLUMN_SCAN_DELAY_MS 30
#define MAG_READ_DELAY 100

#define NAP_DELAY 5000ULL    //30s
#define SLEEP_DELAY 300000ULL //5min

// MIDI settings
#define DEVICE_NAME "MIDI-PAD"
#define MIDI_CHANNEL 1



// MAGENC Setup
AS5600 as5600(&Wire);
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// BLEMidiServerClass BLEMidiServer(DEVICE_NAME);

//Initialization of pending Events
RTC_DATA_ATTR int16_t buttonsPressedArr[N_INPUTS] = {0};
RTC_DATA_ATTR int16_t pendingPressArr[N_INPUTS] = {0};
RTC_DATA_ATTR int16_t pendingReleaseArr[N_INPUTS] = {0};
RTC_DATA_ATTR uint16_t currentLayer = 0;

RTC_DATA_ATTR uint64_t lastPressTime = 0;
uint64_t lastMagRead = 0;
uint64_t connectionStart =0;

// AS5600 setup 
void magencSetup(){
  as5600.begin(255);
  as5600.setDirection(AS5600_CLOCK_WISE);
  as5600.setHysteresis(3);
}

// BLE MIDI setup
void bleMidiSetup(){
  Serial.println("Initializing bluetooth");
  BLEMidiServer.begin(DEVICE_NAME);
  Serial.println("Waiting for connections...");
  //BLEMidiServer.enableDebugging();  // Uncomment if you want to see some debugging output from the library (not much for the server class...)
  while (!BLEMidiServer.isConnected()) {
    Serial.print(".");
    delay(1000);
  }
  connectionStart = millis();
  Serial.println();
  Serial.println("Connected");
  sendReinitialization();
}
//OLED setup
void setupOLED(){
  Wire.begin(0,4);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
  }

  displayON();
  display.display();
  delay(500);
  display.clearDisplay();
  display.display();
}
void displayON(){
  display.ssd1306_command(SSD1306_DISPLAYON);
}
void displayOFF(){
  display.ssd1306_command(SSD1306_DISPLAYOFF);
}

// OLED helper functions
void displayPrepLn(uint x, uint row){
  display.writeFillRect(x,row*16,SCREEN_WIDTH-x,16, BLACK);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(x,row*16);
  //display.display();
}
void displayPrintLn(uint x, uint row, String text){
  displayPrepLn(x,row);
  display.println(text);
  display.display();
}
void displayPrintLn(uint x, uint row, int number){
  displayPrepLn(x,row);
  display.println(number);
  display.display();
}






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
    Encoder(int16_t N){
      //adress for pending actions
      pendingRotationPtr = &(pendingPressArr[N]);
    }

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

// Create Intance of each Input
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

// Matrix Geometry initialization
const uint16_t btnColPins[BTN_COLUMNS] = {COLUMN_PIN_1, COLUMN_PIN_2, COLUMN_PIN_3, COLUMN_PIN_4};
const uint16_t btnRowPins[BTN_ROWS] = {ROW_PIN_1, ROW_PIN_2, ROW_PIN_3, ROW_PIN_4};

const uint16_t encRowPins[ENC_ROWS] = {ROW_PIN_1, ROW_PIN_2, ROW_PIN_3, ROW_PIN_4};
const uint16_t encColPins[ENC_COLUMNS] = {COLUMN_PIN_A, COLUMN_PIN_B};


// definition of encoder positioning. Order: UP, LEFT, DONW, RIGHT. according to electrical connections 
Encoder* encoderMatrix[ENC_ROWS] = {
  &encUp,
  &encLeft,
  &encDown,
  &encRight,
};

// definition of button Positioning
Button* buttonMatrix[BTN_ROWS][BTN_COLUMNS] = {
  {&btn1, &btn5, &btn9, &btnUp},
  {&btn2, &btn6, &btn10, &btnLeft},
  {&btn3, &btn7, &btn11, &btnDown},
  {&btn4, &btn8, &btn12, &btnRight},
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
  
  lastPressTime = millis();
  // Change layer
  if (midiNumber > 127){
    currentLayer = midiNumber - 128;
    Serial.print("Changing to Layer: ");
    Serial.println(layerDict[currentLayer]);

    displayPrepLn(0,0);
    display.println(layerDict[currentLayer]);
    display.display();

    pendingPress = 0;
    pendingRelease = 0;
    return;
  }

  // if encoder, process rotation
  if (isEncoder) {processRotation(pendingPress, midiNumber);}
  // if button, process Press and Release
  else {processButton(pendingPress, pendingRelease, midiNumber);}
}

void processInputs(){
  for (int n=0; n<N_INPUTS; n++){
    processButRot(pendingPressArr[n], pendingReleaseArr[n], mappingStruct[n].layerMapping[currentLayer], mappingStruct[n].isEncoder);
  }
}

void setupInterruptMatrix(){
  for (int col=0; col<BTN_COLUMNS; col++){
    pinMode(btnColPins[col], OUTPUT);
    digitalWrite(btnColPins[col], LOW);
  }
  for (int col=0; col<ENC_COLUMNS; col++){
    pinMode(encColPins[col], OUTPUT);
    digitalWrite(encColPins[col], LOW);
  }
  for (int row=0; row<BTN_ROWS; row++){
    pinMode(btnRowPins[row],INPUT_PULLUP);
  }
  for (int row=0; row<ENC_ROWS; row++){
    pinMode(encRowPins[row],INPUT_PULLUP);
  }
}

// Sleep routine
void enterSleep(){
  // sleep routine entered after SLEEP_DELAY

  //turn display off
  displayOFF();
  //pull columns low
  setupInterruptMatrix();
  //set interrupts on rows. Not Possible. Using external Interrupt on pin13 AKA row4
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_13,0);
  //go to deep sleep
  Serial.println("Entering Deep Sleep now");
  delay(1000);
  esp_deep_sleep_start();

  // ON WAKE UP (ON INPUT)
  Serial.println("Awake");
  //reconnect bluetooth? (necessary?)

  //remove interrupts from rows

  //setupInputMatrix()
  setupInputMatrix();
  //turn display on
  displayON();
  //reset lastPressTime
  lastPressTime = millis();
}

void enterNap(){
  return;
  // nap routine entered after NAP_DELAY

  //pull columns low
  setupInterruptMatrix();
  //set interrupts on rows
  gpio_wakeup_enable(GPIO_NUM_16,GPIO_INTR_LOW_LEVEL);
  gpio_wakeup_enable(GPIO_NUM_2, GPIO_INTR_LOW_LEVEL);
  gpio_wakeup_enable(GPIO_NUM_15,GPIO_INTR_LOW_LEVEL);
  gpio_wakeup_enable(GPIO_NUM_13,GPIO_INTR_LOW_LEVEL);
  esp_sleep_enable_gpio_wakeup();
  //set timer interrupt to NAP_DURATION. to check if deepSleep is needed

  //go to light sleep. keeping ble connection active
  Serial.println("Entering Light Sleep now");
  delay(100);
  esp_light_sleep_start();


  // ON WAKE UP (ON INPUT OR TIMER)
  Serial.println("Awake");
  Serial.print("BLE is: ");
  Serial.println(BLEMidiServer.isConnected()? "Connected":"Disconnected");
  //remove interrupts from rows

  //setupInputMatrix()
  setupInputMatrix();
  //reset lastPressTime
  lastPressTime = millis();
}

// /// BLE Keyboard tests
void sendReinitialization(){
  Serial.println("reinitializing");
  BLEMidiServer.press(KEY_LEFT_CTRL);
  BLEMidiServer.press(KEY_LEFT_ALT);
  BLEMidiServer.press(KEY_LEFT_SHIFT);
  BLEMidiServer.print("i");
  // BLEMidiServer.pressRaw(37);
  // delay(200);
  // BLEMidiServer.pressRaw(50);
  // delay(200);
  // BLEMidiServer.pressRaw(64);
  // delay(200);
  // BLEMidiServer.pressRaw(31);

  
  delay(100);
  BLEMidiServer.releaseAll();
}
void sendKeystroke(){
  Serial.println("about to send greetings");
  BLEMidiServer.print("Hello");
}


void darktableInit(){      
  while ((millis()-connectionStart)<5000) {
    delay(100);
  }
  sendReinitialization();
}

void setup() {
  Serial.begin(115200);
  bleMidiSetup();
  //setupKeyboard();
  darktableInit();
  setupInputMatrix();
  setupOLED();
  Serial.println("SetupFinished!!!");
  lastPressTime = millis();
  lastMagRead=millis();
}
uint64_t lastPrint = 0;
uint64_t magReadCounter = 0;
void loop() {
  if (BLEMidiServer.isConnected()) {
    scanInputMatrix();
    processInputs();
  } else{
    Serial.println("BLE not connected");
    delay(1000);
  }

  // if ((millis() - lastPrint) > 2000){
  //   if (BLEMidiServer.isConnected()){
  //     //sendKeystroke();
  //     sendReinitialization();
  //     Serial.println("bleKeyboard connected");
  //     Serial.println(((millis()-connectionStart)*1.0)/1000);
  //   } else {Serial.println("bleKeyboard not connected");}
  //   lastPrint=millis();
  // }
  if ((millis() - lastPressTime) > NAP_DELAY) {
    if ((millis() - lastPressTime) > SLEEP_DELAY) { enterSleep(); }
    else{ enterNap(); }
  }


  if ((millis() - lastMagRead) > MAG_READ_DELAY) { //FOR OLED
    lastMagRead=millis();
    magReadCounter++;
    uint64_t t0 = millis();
    uint16_t magnetValue = as5600.readAngle();
    displayPrintLn(0,1,magnetValue);
    if (magReadCounter > 10) { // FOR SERIAL
      Serial.println(magnetValue);
      magReadCounter = 0;
    }
    Serial.print("S2: ");
    Serial.println(millis()-t0);
  }
}


#else
BleKeyboard bleKeyboard("MIDI-PAD");

void setupKeyboard(){
  bleKeyboard.begin();
  Serial.println("reinitializing");
  bleKeyboard.press(KEY_LEFT_CTRL);
  delay(200);
  bleKeyboard.press(KEY_LEFT_ALT);
  delay(200);
  bleKeyboard.press(KEY_LEFT_SHIFT);
  delay(200);
  bleKeyboard.print("i");
  delay(1000);
  bleKeyboard.releaseAll();
}

// /// BLE Keyboard tests
void sendReinitialization(){
  Serial.println("reinitializing");
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press(KEY_LEFT_ALT);
  bleKeyboard.press(KEY_LEFT_SHIFT);
  bleKeyboard.print("i");
  delay(1000);
  bleKeyboard.releaseAll();
}
void sendKeystroke(){
  Serial.println("about to send greetings");
  bleKeyboard.print("Hello");
}




void setup() {
  Serial.begin(115200);
  setupKeyboard();
}
uint64_t lastTime=0;

void loop() {
  if(bleKeyboard.isConnected()) {
    if ((millis() - lastTime) > 3000){
        sendReinitialization();
        Serial.println("bleKeyboard connected");
        lastTime=millis();
    } 
    
  }else {Serial.println("bleKeyboard not connected");}

}


#endif