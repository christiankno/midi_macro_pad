#include <Arduino.h>

#define CC_UP 1
#define CC_DOWN 127

#define	A0	21
#define	As0	22
#define	Bb0	22
#define	B0	23
#define	C1	24
#define	Cs1	25
#define	Db1	25
#define	D1	26
#define	Ds1	27
#define	Eb1	27
#define	E1	28
#define	F1	29
#define	Fs1	30
#define	Gb1	30
#define	G1	31
#define	Gs1	32
#define	Ab1	32
#define	A1	33
#define	As1	34
#define	Bb1	34
#define	B1	35
#define	C2	36
#define	Cs2	37
#define	Db2	37
#define	D2	38
#define	Ds2	39
#define	Eb2	39
#define	E2	40
#define	F2	41
#define	Fs2	42
#define	Gb2	42
#define	G2	43
#define	Gs2	44
#define	Ab2	44
#define	A2	45
#define	As2	46
#define	Bb2	46
#define	B2	47
#define	C3	48
#define	Cs3	49
#define	Db3	49
#define	D3	50
#define	Ds3	51
#define	Eb3	51
#define	E3	52
#define	F3	53
#define	Fs3	54
#define	Gb3	54
#define	G3	55
#define	Gs3	56
#define	Ab3	56
#define	A3	57
#define	As3	58
#define	Bb3	58
#define	B3	59
#define	C4	60
#define	Cs4	61
#define	Db4	61
#define	D4	62
#define	Ds4	63
#define	Eb4	63
#define	E4	64
#define	F4	65
#define	Fs4	66
#define	Gb4	66
#define	G4	67
#define	Gs4	68
#define	Ab4	68
#define	A4	69
#define	As4	70
#define	Bb4	70
#define	B4	71
#define	C5	72
#define	Cs5	73
#define	Db5	73
#define	D5	74
#define	Ds5	75
#define	Eb5	75
#define	E5	76
#define	F5	77
#define	Fs5	78
#define	Gb5	78
#define	G5	79
#define	Gs5	80
#define	Ab5	80
#define	A5	81
#define	As5	82
#define	Bb5	82
#define	B5	83
#define	C6	84
#define	Cs6	85
#define	Db6	85
#define	D6	86
#define	Ds6	87
#define	Eb6	87
#define	E6	88
#define	F6	89
#define	Fs6	90
#define	Gb6	90
#define	G6	91
#define	Gs6	92
#define	Ab6	92
#define	A6	93
#define	As6	94
#define	Bb6	94
#define	B6	95
#define	C7	96
#define	Cs7	97
#define	Db7	97
#define	D7	98
#define	Ds7	99
#define	Eb7	99
#define	E7	100
#define	F7	101
#define	Fs7	102
#define	Gb7	102
#define	G7	103
#define	Gs7	104
#define	Ab7	104
#define	A7	105
#define	As7	106
#define	Bb7	106
#define	B7	107
#define	C8	108
#define	Cs8	109
#define	Db8	109
#define	D8	110
#define	Ds8	111
#define	Eb8	111
#define	E8	112
#define	F8	113
#define	Fs8	114
#define	Gb8	114
#define	G8	115
#define	Gs8	116
#define	Ab8	116
#define	A8	117
#define	As8	118
#define	Bb8	118
#define	B8	119
#define	C9	120
#define	Cs9	121
#define	Db9	121
#define	D9	122
#define	Ds9	123
#define	Eb9	123
#define	E9	124
#define	F9	125
#define	Fs9	126
#define	Gb9	126
#define	G9	127


const char *noteNames[] PROGMEM = {
"A0 ",   //21;
"As0",   //22;
"B0 ",   //23;
"C1 ",   //24;
"Cs1",   //25;
"D1 ",   //26;
"Ds1",   //27;
"E1 ",   //28;
"F1 ",   //29;
"Fs1",   //30;
"G1 ",   //31;
"Gs1",   //32;
"A1 ",   //33;
"As1",   //34;
"B1 ",   //35;
"C2 ",   //36;
"Cs2",   //37;
"D2 ",   //38;
"Ds2",   //39;
"E2 ",   //40;
"F2 ",   //41;
"Fs2",   //42;
"G2 ",   //43;
"Gs2",   //44;
"A2 ",   //45;
"As2",   //46;
"B2 ",   //47;
"C3 ",   //48;
"Cs3",   //49;
"D3 ",   //50;
"Ds3",   //51;
"E3 ",   //52;
"F3 ",   //53;
"Fs3",   //54;
"G3 ",   //55;
"Gs3",   //56;
"A3 ",   //57;
"As3",   //58;
"B3 ",   //59;
"C4 ",   //60;
"Cs4",   //61;
"D4 ",   //62;
"Ds4",   //63;
"E4 ",   //64;
"F4 ",   //65;
"Fs4",   //66;
"G4 ",   //67;
"Gs4",   //68;
"A4 ",   //69;
"As4",   //70;
"B4 ",   //71;
"C5 ",   //72;
"Cs5",   //73;
"D5 ",   //74;
"Ds5",   //75;
"E5 ",   //76;
"F5 ",   //77;
"Fs5",   //78;
"G5 ",   //79;
"Gs5",   //80;
"A5 ",   //81;
"As5",   //82;
"B5 ",   //83;
"C6 ",   //84;
"Cs6",   //85;
"D6 ",   //86;
"Ds6",   //87;
"E6 ",   //88;
"F6 ",   //89;
"Fs6",   //90;
"G6 ",   //91;
"Gs6",   //92;
"A6 ",   //93;
"As6",   //94;
"B6 ",   //95;
"C7 ",   //96;
"Cs7",   //97;
"D7 ",   //98;
"Ds7",   //99;
"E7	",   //100;
"F7	",   //101;
"Fs7",   //102;
"G7	",   //103;
"Gs7",   //104;
"A7	",   //105;
"As7",   //106;
"B7	",   //107;
"C8	",   //108;
"Cs8",   //109;
"D8	",   //110;
"Ds8",   //111;
"E8	",   //112;
"F8	",   //113;
"Fs8",   //114;
"G8	",   //115;
"Gs8",   //116;
"A8	",   //117;
"As8",   //118;
"B8	",   //119;
"C9	",   //120;
"Cs9",   //121;
"D9	",   //122;
"Ds9",   //123;
"E9	",   //124;
"F9	",   //125;
"Fs9",   //126;
"G9	",   //127;
};

const char *int2Note(uint i){
    return noteNames[i-21];
}



// MIDI controller numbers
#define NO_ACTION                                    0
#define	CC_ROTATION                                  1
#define	CC_CROP_UP                                   2
#define	CC_CROP_DOWN                                 3
#define	CC_CROP_LEFT                                 4
#define	CC_CROP_RIGHT                                5
#define	CC_NEG_SCAN_BIAS                             6
#define	CC_NEG_DMAX                                  7
#define	CC_NEG_SHADOW_RED_OFFSET                     8
#define	CC_NEG_SHADOW_GREEN_OFFSET                   9
#define	CC_NEG_SHADOW_BLUE_OFFSET                    10
#define	CC_NEG_HIGHLIGHTS_RED_OFFSET                 11
#define	CC_NEG_HIGHLIGHTS_GREEN_OFFSET               12
#define	CC_NEG_HIGHLIGHTS_BLUE_OFFSET                13
#define	CC_COLOR_CORRECTION_WHITE_V                  14
#define	CC_COLOR_CORRECTION_WHITE_H                  15
#define	CC_COLOR_CORRECTION_BLACK_V                  16
#define	CC_COLOR_CORRECTION_BLACK_H                  17
#define	CC_COLOR_BALANCE_CONTRAST                    18
#define	CC_COLOR_BALANCE_SHADOWS_FACTOR              18
#define	CC_COLOR_BALANCE_SHADOWS_HUE                 19
#define	CC_COLOR_BALANCE_SHADOWS_SATURATION          20
#define	CC_COLOR_BALANCE_MIDS_FACTOR                 21
#define	CC_COLOR_BALANCE_MIDS_HUE                    22
#define	CC_COLOR_BALANCE_MIDS_SATURATION             23
#define	CC_COLOR_BALANCE_HIGHLIGHTS_FACTOR           24
#define	CC_COLOR_BALANCE_HIGHLIGHTS_HUE              25
#define	CC_COLOR_BALANCE_HIGHLIGTHS_SATURATION       26

// MIDI note numbers
#define NOTE_ROTATE_L         1
#define NOTE_ROTATE_R         2
#define NOTE_LIGHTTABLE       3
#define NOTE_DARKROOM         4
#define NOTE_PREVIOUS         5
#define NOTE_NEXT             6

// input type
#define IS_ENCODER 1
#define IS_BUTTON  0


const char* ccDict[]={
        "NO_ACTION",                                    //0
        "CC_ROTATION",                                  //1
        "CC_CROP_UP",                                   //2
        "CC_CROP_DOWN",                                 //3
        "CC_CROP_LEFT",                                 //4
        "CC_CROP_RIGHT",                                //5
        "CC_NEG_SCAN_BIAS",                             //6
        "CC_NEG_DMAX",                                  //7
        "CC_NEG_SHADOW_RED_OFFSET",                     //8
        "CC_NEG_SHADOW_GREEN_OFFSET",                   //9
        "CC_NEG_SHADOW_BLUE_OFFSET",                    //10
        "CC_NEG_HIGHLIGHTS_RED_OFFSET",                 //11
        "CC_NEG_HIGHLIGHTS_GREEN_OFFSET",               //12
        "CC_NEG_HIGHLIGHTS_BLUE_OFFSET",                //13
        "CC_COLOR_CORRECTION_WHITE_V",                  //14
        "CC_COLOR_CORRECTION_WHITE_H",                  //15
        "CC_COLOR_CORRECTION_BLACK_V",                  //16
        "CC_COLOR_CORRECTION_BLACK_H",                  //17
        "CC_COLOR_BALANCE_CONTRAST",                    //18
        "CC_COLOR_BALANCE_SHADOWS_FACTOR",              //18
        "CC_COLOR_BALANCE_SHADOWS_HUE",                 //19
        "CC_COLOR_BALANCE_SHADOWS_SATURATION",          //20
        "CC_COLOR_BALANCE_MIDS_FACTOR",                 //21
        "CC_COLOR_BALANCE_MIDS_HUE",                    //22
        "CC_COLOR_BALANCE_MIDS_SATURATION",             //23
        "CC_COLOR_BALANCE_HIGHLIGHTS_FACTOR",           //24
        "CC_COLOR_BALANCE_HIGHLIGHTS_HUE",              //25
        "CC_COLOR_BALANCE_HIGHLIGTHS_SATURATION",       //26
};


// MIDI note numbers
const char* noteDict[]={
        "NO_ACTION",             //0
        "NOTE_ROTATE_L",         //1
        "NOTE_ROTATE_R",         //2
        "NOTE_LIGHTTABLE",       //3
        "NOTE_DARKROOM",         //4
        "NOTE_PREVIOUS",         //5
        "NOTE_NEXT",             //6
};