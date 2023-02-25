
// #include "AiEsp32RotaryEncoder.h"
// #include <Arduino.h>
// #include <BLEMidi.h>
// #include <note_values.h>

// #define ENCODER1_A_pin 22
// #define ENCODER1_B_PIN 19
// #define ENCODER2_A_PIN 23
// #define ENCODER2_B_PIN 18
// #define ENCODER3_A_PIN 5
// #define ENCODER3_B_PIN 17
// #define ENCODER4_A_PIN 16
// #define ENCODER4_B_PIN 2


// #define ROTARY_ENCODER_BUTTON_PIN 25 // ?????????????
// #define ROTARY_ENCODER_VCC_PIN -1
// #define ROTARY_ENCODER_STEPS 4 //depending on your encoder - try 1,2 or 4 to get expected behaviour



// AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ENCODER1_A_pin, ENCODER1_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);


// void rotary_loop() {
// 	//dont print anything unless value changed
// 	if (rotaryEncoder.encoderChanged())
// 	{
// 		Serial.print("Value: ");
// 		Serial.println(rotaryEncoder.readEncoder());
// 	}
// 	if (rotaryEncoder.isEncoderButtonClicked())
// 	{
// 		rotary_onButtonClick();
// 	}
// }

// void IRAM_ATTR readEncoderISR() {
// 	rotaryEncoder.readEncoder_ISR();
// }


// void rotaryEncoderSetup(){
//   rotaryEncoder.begin();
// 	rotaryEncoder.setup(readEncoderISR);
// 	bool circleValues = false;
// 	rotaryEncoder.setBoundaries(0, 1000, circleValues); //minValue, maxValue, circleValues true|false (when max go to min and vice versa)
//   rotaryEncoder.setAcceleration(250);
// }

// void setup() {
//   Serial.begin(115200);
//   rotaryEncoderSetup();
//   Serial.println("Initializing bluetooth");
//   BLEMidiServer.begin("Basic MIDI device");
//   Serial.println("Waiting for connections...");
//   BLEMidiServer.enableDebugging();  // Uncomment if you want to see some debugging output from the library (not much for the server class...)
// }

// int incomingByte = 0; // for incoming serial data
// bool lock = 0;

// void loop() {
//   if(BLEMidiServer.isConnected()) {             // If we've got a connection, we send an A4 during one second, at full velocity (127)
//     if (Serial.available() > 0) {
//       // read the incoming byte:
//       incomingByte = Serial.read();
//       if (!lock){
//         Serial.print("Sending Note: ");
//         Serial.println(incomingByte, DEC);
//         delay(1000);
//         Serial.print("in 5 ");
//         delay(1000);
//         Serial.print("4 ");
//         delay(1000);
//         Serial.print("3 ");
//         delay(1000);
//         Serial.print("2 ");
//         delay(1000);
//         Serial.print("1 ");
//         delay(1000);
//         Serial.println("0");

//         // say what you got:
//         BLEMidiServer.noteOn(0, incomingByte, 127);
//       }

//       Serial.println(incomingByte, DEC);
//       lock=1;
//     }

//     BLEMidiServer.noteOn(0, 69, 127);
//     delay(1000);
//     BLEMidiServer.noteOff(0, 69, 127);        // Then we make a delay of one second before returning to the beginning of the loop
//     delay(1000);
//   }
// }

// // void loop() {
  
// // }