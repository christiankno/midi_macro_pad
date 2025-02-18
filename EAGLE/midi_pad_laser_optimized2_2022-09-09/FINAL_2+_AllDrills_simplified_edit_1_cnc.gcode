(G-CODE GENERATED BY FLATCAM v8.994 - www.flatcam.org - Version Date: 2020/11/7)

(Name: FINAL_2+_AllDrills_simplified_edit_2_cnc)
(Type: G-code from Geometry)
(Units: MM)

(Created on Sonntag, 11 September 2022 at 11:52)

(This preprocessor is used with a motion controller loaded with GRBL firmware.)
(It is configured to be compatible with almost any version of GRBL firmware.)


(TOOLS DIAMETER: )
(Tool: 1 -> Dia: 2.2)
(Tool: 2 -> Dia: 4.0)

(FEEDRATE Z: )
(Tool: 1 -> Feedrate: 15.0)
(Tool: 2 -> Feedrate: 15.0)

(FEEDRATE RAPIDS: )
(Tool: 1 -> Feedrate Rapids: 1500)
(Tool: 2 -> Feedrate Rapids: 1500)

(Z_CUT: )
(Tool: 1 -> Z_Cut: -2.5)
(Tool: 2 -> Z_Cut: -3.7)

(Tools Offset: )
(Tool: 1 -> Offset Z: 0.0)
(Tool: 2 -> Offset Z: 0.0)

(Z_MOVE: )
(Tool: 1 -> Z_Move: 2)
(Tool: 2 -> Z_Move: 2)

(Z Toolchange: 30.0 mm)
(X,Y Toolchange: 0.0000, 0.0000 mm)
(Z Start: None mm)
(Z End: 10.0 mm)
(X,Y End: None mm)
(Steps per circle: 64)
(Steps per circle: 64)
(Preprocessor Excellon: GRBL_11_no_M6)

(X range:   26.5100 ...  136.2900  mm)
(Y range:   20.8600 ...   82.0100  mm)

(Spindle Speed: 12000 RPM)
G21
G90
G17
G94


G01 F15.00

M5             
G00 Z30.0000
G00 X0.0000 Y0.0000                
T1
(MSG, Change to Tool Dia = 2.2000 ||| Total drills for tool T1 = 8)
M0
G00 Z30.0000
        
G01 F15.00
M03 S12000
G00 X27.6100 Y51.8200
G01 Z-2.5000
G01 Z0
G00 Z2.0000
G00 X27.6100 Y51.8200
G01 Z-2.5000
G01 Z0
G00 Z2.0000
G00 X27.6100 Y39.6200
G01 Z-2.5000
G01 Z0
G00 Z2.0000
G00 X40.5600 Y26.6700
G01 Z-2.5000
G01 Z0
G00 Z2.0000
G00 X52.7600 Y26.6700
G01 Z-2.5000
G01 Z0
G00 Z2.0000
G00 X65.7100 Y39.6200
G01 Z-2.5000
G01 Z0
G00 Z2.0000
G00 X65.7100 Y51.8200
G01 Z-2.5000
G01 Z0
G00 Z2.0000
G00 X52.7600 Y64.7700
G01 Z-2.5000
G01 Z0
G00 Z2.0000
G00 X40.5600 Y64.7700
G01 Z-2.5000
G01 Z0
G00 Z2.0000
G01 F15.00

M5             
G00 Z30.0000
G00 X0.0000 Y0.0000                
T2
(MSG, Change to Tool Dia = 4.0000 ||| Total drills for tool T2 = 12)
M0
G00 Z30.0000
        
G01 F15.00
M03 S12000
G00 X96.1900 Y60.9600
G01 Z-3.7000
G01 Z0
G00 Z2.0000
G00 X96.1900 Y60.9600
G01 Z-3.7000
G01 Z0
G00 Z2.0000
G00 X115.2400 Y60.9600
G01 Z-3.7000
G01 Z0
G00 Z2.0000
G00 X134.2900 Y60.9600
G01 Z-3.7000
G01 Z0
G00 Z2.0000
G00 X134.2900 Y80.0100
G01 Z-3.7000
G01 Z0
G00 Z2.0000
G00 X115.2400 Y80.0100
G01 Z-3.7000
G01 Z0
G00 Z2.0000
G00 X96.1900 Y80.0100
G01 Z-3.7000
G01 Z0
G00 Z2.0000
G00 X96.1900 Y41.9100
G01 Z-3.7000
G01 Z0
G00 Z2.0000
G00 X96.1900 Y22.8600
G01 Z-3.7000
G01 Z0
G00 Z2.0000
G00 X115.2400 Y22.8600
G01 Z-3.7000
G01 Z0
G00 Z2.0000
G00 X134.2900 Y22.8600
G01 Z-3.7000
G01 Z0
G00 Z2.0000
G00 X134.2900 Y41.9100
G01 Z-3.7000
G01 Z0
G00 Z2.0000
G00 X115.2400 Y41.9100
G01 Z-3.7000
G01 Z0
G00 Z2.0000
M05
G00 Z10.00


