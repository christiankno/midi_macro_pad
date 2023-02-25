 #ifndef  AUTOBINDINGS_H             
 #define  AUTOBINDINGS_H             
            
#include <Arduino.h>           
            
#define CC_UP 1          
#define CC_DOWN 127          
            
// input type          
#define IS_ENCODER 1          
#define IS_BUTTON 0          
            
#define A0 21          
#define As0 22          
#define Bb0 22          
#define B0 23          
#define C1 24          
#define Cs1 25          
#define Db1 25          
#define D1 26          
#define Ds1 27          
#define Eb1 27          
#define E1 28          
#define F1 29          
#define Fs1 30          
#define Gb1 30          
#define G1 31          
#define Gs1 32          
#define Ab1 32          
#define A1 33          
#define As1 34          
#define Bb1 34          
#define B1 35          
#define C2 36          
#define Cs2 37          
#define Db2 37          
#define D2 38          
#define Ds2 39          
#define Eb2 39          
#define E2 40          
#define F2 41          
#define Fs2 42          
#define Gb2 42          
#define G2 43          
#define Gs2 44          
#define Ab2 44          
#define A2 45          
#define As2 46          
#define Bb2 46          
#define B2 47          
#define C3 48          
#define Cs3 49          
#define Db3 49          
#define D3 50          
#define Ds3 51          
#define Eb3 51          
#define E3 52          
#define F3 53          
#define Fs3 54          
#define Gb3 54          
#define G3 55          
#define Gs3 56          
#define Ab3 56          
#define A3 57          
#define As3 58          
#define Bb3 58          
#define B3 59          
#define C4 60          
#define Cs4 61          
#define Db4 61          
#define D4 62          
#define Ds4 63          
#define Eb4 63          
#define E4 64          
#define F4 65          
#define Fs4 66          
#define Gb4 66          
#define G4 67          
#define Gs4 68          
#define Ab4 68          
#define A4 69          
#define As4 70          
#define Bb4 70          
#define B4 71          
#define C5 72          
#define Cs5 73          
#define Db5 73          
#define D5 74          
#define Ds5 75          
#define Eb5 75          
#define E5 76          
#define F5 77          
#define Fs5 78          
#define Gb5 78          
#define G5 79          
#define Gs5 80          
#define Ab5 80          
#define A5 81          
#define As5 82          
#define Bb5 82          
#define B5 83          
#define C6 84          
#define Cs6 85          
#define Db6 85          
#define D6 86          
#define Ds6 87          
#define Eb6 87          
#define E6 88          
#define F6 89          
#define Fs6 90          
#define Gb6 90          
#define G6 91          
#define Gs6 92          
#define Ab6 92          
#define A6 93          
#define As6 94          
#define Bb6 94          
#define B6 95          
#define C7 96          
#define Cs7 97          
#define Db7 97          
#define D7 98          
#define Ds7 99          
#define Eb7 99          
#define E7 100          
#define F7 101          
#define Fs7 102          
#define Gb7 102          
#define G7 103          
#define Gs7 104          
#define Ab7 104          
#define A7 105          
#define As7 106          
#define Bb7 106          
#define B7 107          
#define C8 108          
#define Cs8 109          
#define Db8 109          
#define D8 110          
#define Ds8 111          
#define Eb8 111          
#define E8 112          
#define F8 113          
#define Fs8 114          
#define Gb8 114          
#define G8 115          
#define Gs8 116          
#define Ab8 116          
#define A8 117          
#define As8 118          
#define Bb8 118          
#define B8 119          
#define C9 120          
#define Cs9 121          
#define Db9 121          
#define D9 122          
#define Ds9 123          
#define Eb9 123          
#define E9 124          
#define F9 125          
#define Fs9 126          
#define Gb9 126          
#define G9 127          
            
 //  	                //NOTES  	Code             
 #define    	NO_ACTION  	0             
 #define    	NOTE_ROTATE_L  	1             
 #define    	NOTE_ROTATE_R  	2             
 #define    	NOTE_LIGHTTABLE  	3             
 #define    	NOTE_DARKROOM  	4             
 #define    	NOTE_PREVIOUS  	5             
 #define    	NOTE_NEXT  	6             
   	  	             
   	  	             
   	  	             
   	  	             
   	  	             
   	  	             
   	  	             
   	  	             
   	  	             
            
 //  	//Controller  Change  	Code             
 #define    	NO_ACTION  	0             
 #define    	CC_ROTATION  	1             
 #define    	CC_CROP_UP  	2             
 #define    	CC_CROP_DOWN  	3             
 #define    	CC_CROP_LEFT  	4             
 #define    	CC_CROP_RIGHT  	5             
 #define    	CC_NEG_SCAN_BIAS  	6             
 #define    	CC_NEG_DMAX  	7             
 #define    	CC_NEG_SHADOW_RED_OFFSET  	8             
 #define    	CC_NEG_SHADOW_GREEN_OFFSET  	9             
 #define    	CC_NEG_SHADOW_BLUE_OFFSET  	10             
 #define    	CC_NEG_HIGHLIGHTS_RED_OFFSET  	11             
 #define    	CC_NEG_HIGHLIGHTS_GREEN_OFFSET  	12             
 #define    	CC_NEG_HIGHLIGHTS_BLUE_OFFSET  	13             
 #define    	CC_COLOR_CORRECTION_WHITE_V  	14             
 #define    	CC_COLOR_CORRECTION_WHITE_H  	15             
 #define    	CC_COLOR_CORRECTION_BLACK_V  	16             
 #define    	CC_COLOR_CORRECTION_BLACK_H  	17             
 #define    	CC_COLOR_BALANCE_CONTRAST  	18             
 #define    	CC_COLOR_BALANCE_SHADOWS_FACTOR  	19             
 #define    	CC_COLOR_BALANCE_SHADOWS_HUE  	20             
 #define    	CC_COLOR_BALANCE_SHADOWS_SATURATION  	21             
 #define    	CC_COLOR_BALANCE_MIDS_FACTOR  	22             
 #define    	CC_COLOR_BALANCE_MIDS_HUE  	23             
 #define    	CC_COLOR_BALANCE_MIDS_SATURATION  	24             
 #define    	CC_COLOR_BALANCE_HIGHLIGHTS_FACTOR  	25             
 #define    	CC_COLOR_BALANCE_HIGHLIGHTS_HUE  	26             
 #define    	CC_COLOR_BALANCE_HIGHLIGTHS_SATURATION  	27             
 #define    	CC_NEG_DMIN_R  	28             
 #define    	CC_NEG_DMIN_G  	29             
 #define    	CC_NEG_DMIN_B  	30             
   	  	             
   	  	             
   	  	             
   	  	             
   	  	             
   	  	             
   	  	             
            
 //  	//LAYERS  	CODE             
 #define    	N_LAYERS  	8             
 #define    	N_LAYER_1  	128             
 #define    	N_LAYER_2L  	129             
 #define    	N_LAYER_2U  	130             
 #define    	N_LAYER_2B  	131             
 #define    	N_LAYER_3  	132             
 #define    	N_LAYER_4U  	133             
 #define    	N_LAYER_4L  	134             
 #define    	N_LAYER_4D  	135             
   	  	             
   	  	             
   	  	             
   	  	             
   	  	             
   	  	             
   	  	             
            
 //  	//LAYERS  	NUMBER             
 #define    	N_INPUTS  	21             
 #define    	N_ENC_MAG  	0             
 #define    	N_ENC_UP  	1             
 #define    	N_ENC_DOWN  	2             
 #define    	N_ENC_LEFT  	3             
 #define    	N_ENC_RIGHT  	4             
 #define    	N_BUTTON_UP  	5             
 #define    	N_BUTTON_DOWN  	6             
 #define    	N_BUTTON_LEFT  	7             
 #define    	N_BUTTON_RIGHT  	8             
 #define    	N_BUTTON_1  	9             
 #define    	N_BUTTON_2  	10             
 #define    	N_BUTTON_3  	11             
 #define    	N_BUTTON_4  	12             
 #define    	N_BUTTON_5  	13             
 #define    	N_BUTTON_6  	14             
 #define    	N_BUTTON_7  	15             
 #define    	N_BUTTON_8  	16             
 #define    	N_BUTTON_9  	17             
 #define    	N_BUTTON_10  	18             
 #define    	N_BUTTON_11  	19             
 #define    	N_BUTTON_12  	20             
   	  	             
   	  	             
   	  	             
   	  	             
   	  	             
            
            
            
            
 const  char*  ccDict[]  PROGMEM  ={             
 "NO_ACTION",  	//  0             
 "CC_ROTATION",  	//  1             
 "CC_CROP_UP",  	//  2             
 "CC_CROP_DOWN",  	//  3             
 "CC_CROP_LEFT",  	//  4             
 "CC_CROP_RIGHT",  	//  5             
 "CC_NEG_SCAN_BIAS",  	//  6             
 "CC_NEG_DMAX",  	//  7             
 "CC_NEG_SHADOW_RED_OFFSET",  	//  8             
 "CC_NEG_SHADOW_GREEN_OFFSET",  	//  9             
 "CC_NEG_SHADOW_BLUE_OFFSET",  	//  10             
 "CC_NEG_HIGHLIGHTS_RED_OFFSET",  	//  11             
 "CC_NEG_HIGHLIGHTS_GREEN_OFFSET",  	//  12             
 "CC_NEG_HIGHLIGHTS_BLUE_OFFSET",  	//  13             
 "CC_COLOR_CORRECTION_WHITE_V",  	//  14             
 "CC_COLOR_CORRECTION_WHITE_H",  	//  15             
 "CC_COLOR_CORRECTION_BLACK_V",  	//  16             
 "CC_COLOR_CORRECTION_BLACK_H",  	//  17             
 "CC_COLOR_BALANCE_CONTRAST",  	//  18             
 "CC_COLOR_BALANCE_SHADOWS_FACTOR",  	//  19             
 "CC_COLOR_BALANCE_SHADOWS_HUE",  	//  20             
 "CC_COLOR_BALANCE_SHADOWS_SATURATION",  	//  21             
 "CC_COLOR_BALANCE_MIDS_FACTOR",  	//  22             
 "CC_COLOR_BALANCE_MIDS_HUE",  	//  23             
 "CC_COLOR_BALANCE_MIDS_SATURATION",  	//  24             
 "CC_COLOR_BALANCE_HIGHLIGHTS_FACTOR",  	//  25             
 "CC_COLOR_BALANCE_HIGHLIGHTS_HUE",  	//  26             
 "CC_COLOR_BALANCE_HIGHLIGTHS_SATURATION",  	//  27             
 "CC_NEG_DMIN_R",  	//  28             
 "CC_NEG_DMIN_G",  	//  29             
 "CC_NEG_DMIN_B",  	//  30             
};            
            
            
            
            
            
            
            
 const  char*  noteDict[]  PROGMEM  ={             
 "NO_ACTION",  	//  0             
 "NOTE_ROTATE_L",  	//  1             
 "NOTE_ROTATE_R",  	//  2             
 "NOTE_LIGHTTABLE",  	//  3             
 "NOTE_DARKROOM",  	//  4             
 "NOTE_PREVIOUS",  	//  5             
 "NOTE_NEXT",  	//  6             
};            
            
            
            
            
            
            
 const  char*  layerDict[]  PROGMEM  ={             
 "N_LAYER_1",  	//  128             
 "N_LAYER_2L",  	//  129             
 "N_LAYER_2U",  	//  130             
 "N_LAYER_2B",  	//  131             
 "N_LAYER_3",  	//  132             
 "N_LAYER_4U",  	//  133             
 "N_LAYER_4L",  	//  134             
 "N_LAYER_4D",  	//  135             
};            
            
            
            
            
            
            
            
 struct  {             
     const  uint8_t  inputNumber;             
     const  bool  isEncoder;             
     const  uint16_t  layerMapping[N_LAYERS];             
 }  const  mappingStruct[N_INPUTS]  PROGMEM  =  {  //  USE  SAME  ORDER  FROM  DEFINITION  OF  N_(ENC|BUTTON)_*             
// inputNumber isEncoder { N_LAYER_1 N_LAYER_2L N_LAYER_2U N_LAYER_2B N_LAYER_3 N_LAYER_4U N_LAYER_4L N_LAYER_4D }},
{ N_ENC_MAG, IS_ENCODER, { CC_ROTATION, CC_NEG_SCAN_BIAS, CC_NEG_SCAN_BIAS, CC_NEG_SCAN_BIAS, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, }},
{ N_ENC_UP, IS_ENCODER, { CC_CROP_UP, CC_NEG_DMIN_R, CC_NEG_SHADOW_RED_OFFSET, CC_NEG_HIGHLIGHTS_RED_OFFSET, NO_ACTION, CC_COLOR_BALANCE_SHADOWS_FACTOR, CC_COLOR_BALANCE_MIDS_FACTOR, CC_COLOR_BALANCE_HIGHLIGHTS_FACTOR, }},
{ N_ENC_DOWN, IS_ENCODER, { CC_CROP_DOWN, CC_NEG_DMIN_B, CC_NEG_SHADOW_BLUE_OFFSET, CC_NEG_HIGHLIGHTS_BLUE_OFFSET, NO_ACTION, CC_COLOR_BALANCE_SHADOWS_SATURATION, CC_COLOR_BALANCE_MIDS_SATURATION, CC_COLOR_BALANCE_HIGHLIGTHS_SATURATION, }},
{ N_ENC_LEFT, IS_ENCODER, { CC_CROP_LEFT, CC_NEG_DMIN_G, CC_NEG_SHADOW_GREEN_OFFSET, CC_NEG_HIGHLIGHTS_GREEN_OFFSET, NO_ACTION, CC_COLOR_BALANCE_SHADOWS_HUE, CC_COLOR_BALANCE_MIDS_HUE, CC_COLOR_BALANCE_HIGHLIGHTS_HUE, }},
{ N_ENC_RIGHT, IS_ENCODER, { CC_CROP_RIGHT, CC_NEG_DMAX, CC_NEG_DMAX, CC_NEG_DMAX, NO_ACTION, CC_COLOR_BALANCE_CONTRAST, CC_COLOR_BALANCE_CONTRAST, CC_COLOR_BALANCE_CONTRAST, }},
{ N_BUTTON_UP, IS_BUTTON, { NO_ACTION, N_LAYER_2U, N_LAYER_2U, N_LAYER_2U, NO_ACTION, N_LAYER_4U, N_LAYER_4U, N_LAYER_4U, }},
{ N_BUTTON_DOWN, IS_BUTTON, { NO_ACTION, N_LAYER_2B, N_LAYER_2B, N_LAYER_2B, NO_ACTION, N_LAYER_4D, N_LAYER_4D, N_LAYER_4D, }},
{ N_BUTTON_LEFT, IS_BUTTON, { NO_ACTION, N_LAYER_2L, N_LAYER_2L, N_LAYER_2L, NO_ACTION, N_LAYER_4L, N_LAYER_4L, N_LAYER_4L, }},
{ N_BUTTON_RIGHT, IS_BUTTON, { NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, }},
{ N_BUTTON_1, IS_BUTTON, { NOTE_ROTATE_L, NOTE_ROTATE_L, NOTE_ROTATE_L, NOTE_ROTATE_L, NOTE_ROTATE_L, NOTE_ROTATE_L, NOTE_ROTATE_L, NOTE_ROTATE_L, }},
{ N_BUTTON_2, IS_BUTTON, { NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, }},
{ N_BUTTON_3, IS_BUTTON, { NOTE_LIGHTTABLE, NOTE_LIGHTTABLE, NOTE_LIGHTTABLE, NOTE_LIGHTTABLE, NOTE_LIGHTTABLE, NOTE_LIGHTTABLE, NOTE_LIGHTTABLE, NOTE_LIGHTTABLE, }},
{ N_BUTTON_4, IS_BUTTON, { NOTE_PREVIOUS, NOTE_PREVIOUS, NOTE_PREVIOUS, NOTE_PREVIOUS, NOTE_PREVIOUS, NOTE_PREVIOUS, NOTE_PREVIOUS, NOTE_PREVIOUS, }},
{ N_BUTTON_5, IS_BUTTON, { NOTE_ROTATE_R, NOTE_ROTATE_R, NOTE_ROTATE_R, NOTE_ROTATE_R, NOTE_ROTATE_R, NOTE_ROTATE_R, NOTE_ROTATE_R, NOTE_ROTATE_R, }},
{ N_BUTTON_6, IS_BUTTON, { NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, }},
{ N_BUTTON_7, IS_BUTTON, { NOTE_DARKROOM, NOTE_DARKROOM, NOTE_DARKROOM, NOTE_DARKROOM, NOTE_DARKROOM, NOTE_DARKROOM, NOTE_DARKROOM, NOTE_DARKROOM, }},
{ N_BUTTON_8, IS_BUTTON, { NOTE_NEXT, NOTE_NEXT, NOTE_NEXT, NOTE_NEXT, NOTE_NEXT, NOTE_NEXT, NOTE_NEXT, NOTE_NEXT, }},
{ N_BUTTON_9, IS_BUTTON, { N_LAYER_1, N_LAYER_1, N_LAYER_1, N_LAYER_1, N_LAYER_1, N_LAYER_1, N_LAYER_1, N_LAYER_1, }},
{ N_BUTTON_10, IS_BUTTON, { N_LAYER_2L, N_LAYER_2L, N_LAYER_2L, N_LAYER_2L, N_LAYER_2L, N_LAYER_2L, N_LAYER_2L, N_LAYER_2L, }},
{ N_BUTTON_11, IS_BUTTON, { N_LAYER_3, N_LAYER_3, N_LAYER_3, N_LAYER_3, N_LAYER_3, N_LAYER_3, N_LAYER_3, N_LAYER_3, }},
{ N_BUTTON_12, IS_BUTTON, { N_LAYER_4U, N_LAYER_4U, N_LAYER_4U, N_LAYER_4U, N_LAYER_4U, N_LAYER_4U, N_LAYER_4U, N_LAYER_4U, }},
            
};            
            
#endif            
