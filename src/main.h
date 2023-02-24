#ifndef MAIN_H
#define MAIN_H
#include <Arduino.h>
#include <autobindings.h>

// MATRIX
// MATRIX dimensions. buttons and encoders share rows.
#define BTN_COLUMNS 4
#define BTN_ROWS 4
#define ENC_ROWS 4
#define ENC_COLUMNS 2

// MATRIX PINS
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

// OLED definitions
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

// I2C pins
#define SDA 0
#define SCL 4

// OLD Input number definitions
#ifndef AUTOBINDINGS_H
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
  //TOTAL
  #define N_INPUTS      (N_BUTTON_12 + 1)
    
  // layer numbering. Same order as in mappingStruct.layerMappings
  #define N_LAYER_1     128
  #define N_LAYER_2U    (N_LAYER_1 + 1)
  #define N_LAYER_2D    (N_LAYER_2U + 1)
  #define N_LAYER_3     (N_LAYER_2D + 1)
  #define N_LAYER_4U    (N_LAYER_3 + 1)
  #define N_LAYER_4L    (N_LAYER_4U + 1)
  #define N_LAYER_4D    (N_LAYER_4L + 1)
  //TOTAL
  #define N_LAYERS      (N_LAYER_4D + 1 - 128)
#endif


// FUNCTIONS
void magencSetup();
void bleMidiSetup();

void setupOLED();
void displayON();
void displayOFF();
void displayPrepLn(uint x, uint row);
void displayPrintLn(uint x, uint row, String text);
void displayPrintLn(uint x, uint row, int number);

void setupInputMatrix();

void scanButtonMatrix();
void scanEncoderMatrix();
void scanInputMatrix();

void processRotation(int16_t& pendingRotation, uint16_t ccNumber);
void processButton(int16_t& pendingPress, int16_t& pendingRelease, uint16_t noteNumber);
void processButRot(int16_t& pendingPress, int16_t& pendingRelease, uint16_t midiNumber, bool isEncoder);
void processInputs();

void setupInterruptMatrix();

void enterSleep();
void enterNap();

void sendReinitialization();
void sendKeystroke();

#ifndef AUTOBINDINGS_H
  // Struct containing input index N, input type, and mappings for each layer 
  struct {
    const uint8_t inputNumber;
    const bool isEncoder;
    const uint16_t layerMapping[N_LAYERS];
  } const mappingStruct[N_INPUTS] PROGMEM = { // USE SAME ORDER FROM DEFINITION OF N_(ENC|BUTTON)_*
    // inputNumber	      isEncoder        {LAYER_1		         LAYER_2U		                     LAYER_2B		                        LAYER_3		                    LAYER_4U		                         LAYER_4L		                          LAYER_4D}	
    {	N_ENC_MAG,          IS_ENCODER,     {	CC_ROTATION,     CC_NEG_SCAN_BIAS,               CC_NEG_SCAN_BIAS,                  NO_ACTION,                    CC_COLOR_BALANCE_CONTRAST,           CC_COLOR_BALANCE_CONTRAST,           CC_COLOR_BALANCE_CONTRAST              }},
    {	N_ENC_UP,           IS_ENCODER,     {	CC_CROP_UP,      CC_NEG_SHADOW_RED_OFFSET,       CC_NEG_HIGHLIGHTS_RED_OFFSET,      CC_COLOR_CORRECTION_WHITE_V,  CC_COLOR_BALANCE_SHADOWS_FACTOR,     CC_COLOR_BALANCE_MIDS_FACTOR,        CC_COLOR_BALANCE_HIGHLIGHTS_FACTOR     }},
    {	N_ENC_DOWN,         IS_ENCODER,     {	CC_CROP_DOWN,    CC_NEG_SHADOW_BLUE_OFFSET,      CC_NEG_HIGHLIGHTS_BLUE_OFFSET,     CC_COLOR_CORRECTION_BLACK_V,  CC_COLOR_BALANCE_SHADOWS_SATURATION, CC_COLOR_BALANCE_MIDS_SATURATION,    CC_COLOR_BALANCE_HIGHLIGTHS_SATURATION }},
    {	N_ENC_LEFT,         IS_ENCODER,     {	CC_CROP_LEFT,    CC_NEG_SHADOW_GREEN_OFFSET,     CC_NEG_HIGHLIGHTS_GREEN_OFFSET,    CC_COLOR_CORRECTION_BLACK_H,  CC_COLOR_BALANCE_SHADOWS_HUE,        CC_COLOR_BALANCE_MIDS_HUE,           CC_COLOR_BALANCE_HIGHLIGHTS_HUE        }},
    {	N_ENC_RIGHT,        IS_ENCODER,     {	CC_CROP_RIGHT,   CC_NEG_DMAX,                    CC_NEG_DMAX,                       CC_COLOR_CORRECTION_WHITE_H,  NO_ACTION,                           NO_ACTION,                           NO_ACTION                              }},
    {	N_BUTTON_UP,        IS_BUTTON,      {	NO_ACTION,       N_LAYER_2U,                     N_LAYER_2U,                        NO_ACTION,                    N_LAYER_4U,                          N_LAYER_4U,                          N_LAYER_4U                             }},
    {	N_BUTTON_DOWN,      IS_BUTTON,      {	NO_ACTION,       N_LAYER_2D,                     N_LAYER_2D,                        NO_ACTION,                    N_LAYER_4D,                          N_LAYER_4D,                          N_LAYER_4D                             }},
    {	N_BUTTON_LEFT,      IS_BUTTON,      {	NO_ACTION,       NO_ACTION,                      NO_ACTION,                         NO_ACTION,                    N_LAYER_4L,                          N_LAYER_4L,                          N_LAYER_4L                             }},
    {	N_BUTTON_RIGHT,     IS_BUTTON,      {	NO_ACTION,       NO_ACTION,                      NO_ACTION,                         NO_ACTION,                    NO_ACTION,                           NO_ACTION,                           NO_ACTION                              }},
    {	N_BUTTON_1,         IS_BUTTON,      {	N_LAYER_1,       N_LAYER_1,                      N_LAYER_1,                         N_LAYER_1,                    N_LAYER_1,                           N_LAYER_1,                           N_LAYER_1                              }},
    {	N_BUTTON_2,         IS_BUTTON,      {	NOTE_ROTATE_L,   NOTE_ROTATE_L,                  NOTE_ROTATE_L,                     NOTE_ROTATE_L,                NOTE_ROTATE_L,                       NOTE_ROTATE_L,                       NOTE_ROTATE_L                          }},
    {	N_BUTTON_3,         IS_BUTTON,      {	NOTE_ROTATE_R,   NOTE_ROTATE_R,                  NOTE_ROTATE_R,                     NOTE_ROTATE_R,                NOTE_ROTATE_R,                       NOTE_ROTATE_R,                       NOTE_ROTATE_R                          }},
    {	N_BUTTON_4,         IS_BUTTON,      {	N_LAYER_2U,      N_LAYER_2U,                     N_LAYER_2U,                        N_LAYER_2U,                   N_LAYER_2U,                          N_LAYER_2U,                          N_LAYER_2U                             }},
    {	N_BUTTON_5,         IS_BUTTON,      {	NO_ACTION,       NO_ACTION,                      NO_ACTION,                         NO_ACTION,                    NO_ACTION,                           NO_ACTION,                           NO_ACTION                              }},
    {	N_BUTTON_6,         IS_BUTTON,      {	NO_ACTION,       NO_ACTION,                      NO_ACTION,                         NO_ACTION,                    NO_ACTION,                           NO_ACTION,                           NO_ACTION                              }},
    {	N_BUTTON_7,         IS_BUTTON,      {	N_LAYER_3,       N_LAYER_3,                      N_LAYER_3,                         N_LAYER_3,                    N_LAYER_3,                           N_LAYER_3,                           N_LAYER_3                              }},
    {	N_BUTTON_8,         IS_BUTTON,      {	NOTE_LIGHTTABLE, NOTE_LIGHTTABLE,                NOTE_LIGHTTABLE,                   NOTE_LIGHTTABLE,              NOTE_LIGHTTABLE,                     NOTE_LIGHTTABLE,                     NOTE_LIGHTTABLE                        }},
    {	N_BUTTON_9,         IS_BUTTON,      {	NOTE_DARKROOM,   NOTE_DARKROOM,                  NOTE_DARKROOM,                     NOTE_DARKROOM,                NOTE_DARKROOM,                       NOTE_DARKROOM,                       NOTE_DARKROOM                          }},
    {	N_BUTTON_10,        IS_BUTTON,      {	N_LAYER_4U,      N_LAYER_4U,                     N_LAYER_4U,                        N_LAYER_4U,                   N_LAYER_4U,                          N_LAYER_4U,                          N_LAYER_4U                             }},
    {	N_BUTTON_11,        IS_BUTTON,      {	NOTE_PREVIOUS,   NOTE_PREVIOUS,                  NOTE_PREVIOUS,                     NOTE_PREVIOUS,                NOTE_PREVIOUS,                       NOTE_PREVIOUS,                       NOTE_PREVIOUS                          }},
    {	N_BUTTON_12,        IS_BUTTON,      {	NOTE_NEXT,       NOTE_NEXT,                      NOTE_NEXT,                         NOTE_NEXT,                    NOTE_NEXT,                           NOTE_NEXT,                           NOTE_NEXT                              }},

  };
#endif


#endif