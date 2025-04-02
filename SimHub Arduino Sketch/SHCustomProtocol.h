#ifndef __SHCUSTOMPROTOCOL_H__
#define __SHCUSTOMPROTOCOL_H__

#include <Arduino.h>
#include <SPI.h>
#include "mcp2515_can.h"

// Set Canbus Pin
const int SPI_CS_PIN = 9;
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin

// Set kBus
#define kbus Serial

// Set Speedo Pin
#define SPEED_PIN 46

// Set Relay Pins
int pinABS = 14;
int pinParkingpbrake = 15;
int pinClusterlight = 16;

// Custom Variables
int hibeam = 0; //2
int pbrk = 0; //4
int tc = 0; //10
int turnleft = 0; //20
int turnright = 0; //40
int hazard = 0; //60
int oilwarn = 0; //100
int batt = 0; //200
int absBlink = 0; //400

// Set Clustervariables
int MaxRPM = 7000;
float RPMSendVal = 0.00f;
int SpeedSendVal = 50;
float TempSendVal = 50.00f;
int fuellevel = 0;

// K-Bus Variables
byte LightByte1 = 0x00;
byte LightByte2 = 0x00;

// Can-Bus Variables
byte DME4_Load0 = 0x00;
byte DME4_Load3 = 0x00;
byte DME4_Load5 = 0x00;
byte DME6_Load1 = 0x00;
byte AT_Gear = 0x00;

// SimHub Variables
int Speed = 0;
int RPM = 0;
int Temp = 0;
int fuelpercentage = 0;
int oilpress = 0;    
String checkEngine_ETS = "0";
String blinkerleft;
String blinkerright;   
String cruise;
String parkingbreak;
String oil_warn;
String batWarning = "FALSE";
String lights; 
int turnLeft = 0;
int turnRight = 0;
int absWarning = 0;   
int dscWarning = 0;
int dscSwitch = 0;
String checkEngine_PCARS = "0";
String Highbeam = "False";
int pcars_mcarflags = 0;
int acc_lightstage = 0;
int acc_flashlight =  0;
int handbrake = 0;
int turnleft_fs = 0;
int turnright_fs = 0;
String cruise_fs;
String engine_fs;
String lights_fs;
int parkingbreak_beam = 0;
int turnleft_beam = 0;
int turnright_beam = 0;
int foglight_beam = 0;
int oillight_beam = 0;
int abslight_beam = 0;
int watertemp_beam = 0;
int lowhighbeam_beam = 0;
int highbeam_beam = 0;
int tclight_beam = 0;

String gear;
int showLights = 0;

String Game = "ETS2";

// Backlight Options
int inputIngameoption = 49;
int inputHardwareoption = 50;
int inputAlwaysonoption = 51;
int inputHardwareswitch = 53;

class SHCustomProtocol {
private:

public:

  /*
  CUSTOM PROTOCOL CLASS
  SEE https://github.com/zegreatclan/SimHub/wiki/Custom-Arduino-hardware-support

  GENERAL RULES :
    - ALWAYS BACKUP THIS FILE, reinstalling/updating SimHub would overwrite it with the default version.
    - Read data AS FAST AS POSSIBLE in the read function
    - NEVER block the arduino (using delay for instance)
    - Make sure the data read in "read()" function READS ALL THE DATA from the serial port matching the custom protocol definition
    - Idle function is called hundreds of times per second, never use it for slow code, arduino performances would fall
    - If you use library suspending interrupts make sure to use it only in the "read" function when ALL data has been read from the serial port.
      It is the only interrupt safe place

  COMMON FUNCTIONS :
    - FlowSerialReadStringUntil('\n')
      Read the incoming data up to the end (\n) won't be included
    - FlowSerialReadStringUntil(';')
      Read the incoming data up to the separator (;) separator won't be included
    - FlowSerialDebugPrintLn(string)
      Send a debug message to simhub which will display in the log panel and log file (only use it when debugging, it would slow down arduino in run conditions)

  */

  // Called when starting the arduino (setup method in main sketch)
  void setup() {

// Input Definition
  pinMode(inputIngameoption, INPUT_PULLUP);
  pinMode(inputHardwareoption, INPUT_PULLUP);
  pinMode(inputAlwaysonoption, INPUT_PULLUP);
  pinMode(inputHardwareswitch, INPUT_PULLUP);
  
// Output Definition
  pinMode(pinABS, OUTPUT);
  pinMode(pinParkingpbrake, OUTPUT);
  pinMode(pinClusterlight, OUTPUT);
// // Output Set
  digitalWrite(pinABS, HIGH);
  digitalWrite(pinParkingpbrake, HIGH);
  digitalWrite(pinClusterlight, HIGH);
    
    pinMode(SPEED_PIN, OUTPUT);
    fuelgauge.attach(10);
    fuelgauge.write(0);

    kbus.begin(9600, SERIAL_8E1);

   CAN.begin(CAN_500KBPS); // init can bus : baudrate = 500k
  }

  // Called when new data is coming from computer
  void read() {
    // EXAMPLE 1 - read the whole message and sent it back to simhub as debug message
    // Protocol formula can be set in simhub to anything, it will just echo it
    // -------------------------------------------------------
      Speed = FlowSerialReadStringUntil(';').toInt();
      RPM = FlowSerialReadStringUntil(';').toInt();
      Temp = FlowSerialReadStringUntil(';').toInt();
      fuelpercentage = FlowSerialReadStringUntil(';').toInt();
      oilpress = FlowSerialReadStringUntil(';').toInt();
      checkEngine_ETS = FlowSerialReadStringUntil(';');
      blinkerright = FlowSerialReadStringUntil(';');
      blinkerleft = FlowSerialReadStringUntil(';');
      cruise = FlowSerialReadStringUntil(';');
      parkingbreak = FlowSerialReadStringUntil(';');
      oil_warn = FlowSerialReadStringUntil(';');
      batWarning = FlowSerialReadStringUntil(';');
      lights = FlowSerialReadStringUntil(';');
      turnLeft = FlowSerialReadStringUntil(';').toInt();
      turnRight = FlowSerialReadStringUntil(';').toInt();
      absWarning = FlowSerialReadStringUntil(';').toInt();
      dscWarning = FlowSerialReadStringUntil(';').toInt();
      dscSwitch = FlowSerialReadStringUntil(';').toInt();
      checkEngine_PCARS = FlowSerialReadStringUntil(';');
      Highbeam = FlowSerialReadStringUntil(';');
      pcars_mcarflags = FlowSerialReadStringUntil(';').toInt();
      acc_lightstage = FlowSerialReadStringUntil(';').toInt();
      acc_flashlight =  FlowSerialReadStringUntil(';').toInt();
      handbrake =  FlowSerialReadStringUntil(';').toInt();
      turnleft_fs =  FlowSerialReadStringUntil(';').toInt();
      turnright_fs =  FlowSerialReadStringUntil(';').toInt();
      cruise_fs = FlowSerialReadStringUntil(';');
      engine_fs = FlowSerialReadStringUntil(';');
      lights_fs = FlowSerialReadStringUntil(';');
      gear = FlowSerialReadStringUntil(';');
      showLights = FlowSerialReadStringUntil(';').toInt();
      parkingbreak_beam = FlowSerialReadStringUntil(';').toInt();
      turnleft_beam = FlowSerialReadStringUntil(';').toInt();
      turnright_beam = FlowSerialReadStringUntil(';').toInt();
      foglight_beam = FlowSerialReadStringUntil(';').toInt();
      oillight_beam = FlowSerialReadStringUntil(';').toInt();
      abslight_beam = FlowSerialReadStringUntil(';').toInt();
      watertemp_beam = FlowSerialReadStringUntil(';').toInt();
      lowhighbeam_beam = FlowSerialReadStringUntil(';').toInt();
      highbeam_beam = FlowSerialReadStringUntil(';').toInt();
      tclight_beam = FlowSerialReadStringUntil(';').toInt();
      Game = FlowSerialReadStringUntil('\n');
  
    /*
    // -------------------------------------------------------
    // EXAMPLE 2 - reads speed and gear from the message
    // Protocol formula must be set in simhub to
    // format([DataCorePlugin.GameData.NewData.SpeedKmh],'0') + ';' + isnull([DataCorePlugin.GameData.NewData.Gear],'N')
    // -------------------------------------------------------

    int speed = FlowSerialReadStringUntil(';').toInt();
    String gear = FlowSerialReadStringUntil('\n');

    FlowSerialDebugPrintLn("Speed : " + String(speed));
    FlowSerialDebugPrintLn("Gear : " + gear);
    */
  }

  // Called once per arduino loop, timing can't be predicted, 
  // but it's called between each command sent to the arduino
 
  void loop() {
  
// ##############
// START GAMEDATA
// ##############
// Start pCars
if(Game.equalsIgnoreCase("pCars")) {

if (oilpress <= 0.2) {
  DME4_Load3 = 0x02;
} else if(Temp >= 120) {
  DME4_Load3 = 0x08;
} else {
  DME4_Load3 = 0x00;
}

if((pcars_mcarflags == 3) || (pcars_mcarflags == 131) || (pcars_mcarflags == 11)){
  LightByte2 = 0x30;
} else {
  LightByte2 = 0x00;
}

// Cluster Backlight Ingame
if(digitalRead(inputIngameoption) == LOW){
if((pcars_mcarflags == 3) || (pcars_mcarflags == 131) || (pcars_mcarflags == 11)) {
digitalWrite(pinClusterlight, LOW);  
}
else {
digitalWrite(pinClusterlight, HIGH);
}
}

if (checkEngine_PCARS < "0.2") {
  DME4_Load0 = 0x00;
} 
else {
  DME4_Load0 = 0x02;
}

  DME4_Load5 = 0x00;

}
// End pCars

// Start Assetto Corsa Competizione
if(Game.equalsIgnoreCase("AssettoCorsaCompetizione")) {

  DME4_Load3 = 0x00;
  DME4_Load5 = 0x00;
  
if(acc_lightstage == 2){
  LightByte2 = 0x30;
} else {
  LightByte2 = 0x00;
}

// Cluster Backlight Ingame
if(digitalRead(inputIngameoption) == LOW){
if(acc_lightstage == 2) {
digitalWrite(pinClusterlight, LOW);  
}
else {
digitalWrite(pinClusterlight, HIGH);
}
}

if(acc_flashlight == 1) {
  LightByte1 = 0x04;
} else {
  LightByte1 = 0x00;
}
  
}

// End Assetto Corsa Competizione

// Start ETS
if(Game.equalsIgnoreCase("ETS2") || Game.equalsIgnoreCase("ATS")) {

if(lights.equalsIgnoreCase("true")) {
  LightByte2 = 0x30;
} else {
  LightByte2 = 0x00;
}

// Cluster Backlight Ingame
if(digitalRead(inputIngameoption) == LOW){
if(lights.equalsIgnoreCase("true")) {
digitalWrite(pinClusterlight, LOW);  
}
else {
digitalWrite(pinClusterlight, HIGH);
}
}

if (batWarning.equalsIgnoreCase("False")) {
  DME4_Load5 = 0x00;
} else if (batWarning.equalsIgnoreCase("0")) {
  DME4_Load5 = 0x00;
} else {
  DME4_Load5 = 0x01;     
}

if (oilpress <= 1) {
  DME4_Load3 = 0x02;
} else if(Temp >= 120) {
  DME4_Load3 = 0x08;
} else {
  DME4_Load3 = 0x00;
}

// Cruisecontrol and Enginecheck
if (checkEngine_ETS > "0.2") {
  DME4_Load0 = 0x02;
} else if (cruise.equalsIgnoreCase("True")) {
  DME4_Load0 = 0x08;
} else {
  DME4_Load0 = 0x00;
}

// Indicators Left / Right

if(blinkerleft.equalsIgnoreCase("False") && blinkerright.equalsIgnoreCase("False") && Highbeam.equalsIgnoreCase("False")) {
  LightByte1 = 0x00;
} else if(blinkerleft.equalsIgnoreCase("False") && blinkerright.equalsIgnoreCase("False") && Highbeam.equalsIgnoreCase("True")) {
  LightByte1 = 0x04;
} else if(blinkerleft.equalsIgnoreCase("True") && blinkerright.equalsIgnoreCase("False") && Highbeam.equalsIgnoreCase("False")) {
  LightByte1 = 0x40;
} else if(blinkerleft.equalsIgnoreCase("False") && blinkerright.equalsIgnoreCase("True") && Highbeam.equalsIgnoreCase("False")) {
  LightByte1 = 0x20;
} else if(blinkerleft.equalsIgnoreCase("True") && blinkerright.equalsIgnoreCase("True") && Highbeam.equalsIgnoreCase("False")) {
  LightByte1 = 0x60;
} else if(blinkerleft.equalsIgnoreCase("True") && blinkerright.equalsIgnoreCase("False") && Highbeam.equalsIgnoreCase("True")) {
  LightByte1 = 0x44;
} else if(blinkerleft.equalsIgnoreCase("False") && blinkerright.equalsIgnoreCase("True") && Highbeam.equalsIgnoreCase("True")) {
  LightByte1 = 0x24;
} else if(blinkerleft.equalsIgnoreCase("True") && blinkerright.equalsIgnoreCase("True") && Highbeam.equalsIgnoreCase("True")) {
  LightByte1 = 0x64;
}
  
// Parkingbrake
if(parkingbreak.equalsIgnoreCase("true")) {
  digitalWrite(pinParkingpbrake, LOW);  
}
else {
  digitalWrite(pinParkingpbrake, HIGH); 
}

}
// End ETS2

// Start Forza Horizon 5
if(Game.equalsIgnoreCase("FH5")) {

LightByte1 = 0x00; // Lights not supported by game

//No lighting Informations
LightByte2 = 0x00;
if(digitalRead(inputIngameoption) == LOW){
digitalWrite(pinClusterlight, LOW);  
}

DME4_Load3 = 0x00; // Oilpressure not supported by game
DME4_Load0 = 0x00; // Enginedamage not known the values at the moment
DME4_Load5 = 0x00; // Battery Warning not supported by game

// Handbrake
if (handbrake > 1) {
  digitalWrite(pinParkingpbrake, LOW);  
} 
else {
  digitalWrite(pinParkingpbrake, HIGH);  
}


}
// End Forza Horizon 5

// Start Fernbus Simulator
if(Game.equalsIgnoreCase("FernbusSimulator")) {

if(lights_fs.equalsIgnoreCase("true")) {
  LightByte2 = 0x30;
} else {
  LightByte2 = 0x00;
}

// Cluster Backlight Ingame
if(digitalRead(inputIngameoption) == LOW){
if(lights_fs.equalsIgnoreCase("true")) {
digitalWrite(pinClusterlight, LOW);  
}
else {
digitalWrite(pinClusterlight, HIGH);
}
}

if (engine_fs.equalsIgnoreCase("False")) {
  DME4_Load5 = 0x00;
} else if (batWarning.equalsIgnoreCase("0")) {
  DME4_Load5 = 0x00;
} else {
  DME4_Load5 = 0x01;     
}

// Cruisecontrol and Enginecheck
if (cruise_fs.equalsIgnoreCase("True")) {
  DME4_Load0 = 0x08;
} else {
  DME4_Load0 = 0x00;
}

// Indicators Left / Right
if((turnright_fs == 0) && (turnleft_fs == 0)) {
  LightByte1 = 0x00;
} else if((turnright_fs > 0) && (turnleft_fs == 0)) {
  LightByte1 = 0x40;
} else if((turnright_fs == 0) && (turnleft_fs > 0)) {
  LightByte1 = 0x20;
} else if((turnright_fs > 0) && (turnleft_fs > 0)) {
  LightByte1 = 0x60;
}
  
// Handbrake
if (handbrake > 1) {
  digitalWrite(pinParkingpbrake, LOW);  
} 
else {
  digitalWrite(pinParkingpbrake, HIGH);  
}

DME4_Load3 = 0x00;

}
// End Fernbus Simulator

// Start BeamNG
if(Game.equalsIgnoreCase("BeamNgDrive")) {
      
// Low Light
if(lowhighbeam_beam == 1) {
  LightByte2 = 0x30;
} else {
  LightByte2 = 0x00;
}

// Cluster Backlight Ingame
if(digitalRead(inputIngameoption) == LOW){
if(lowhighbeam_beam == 1) {
digitalWrite(pinClusterlight, LOW);  
} else {
digitalWrite(pinClusterlight, HIGH);
}}

// Remap Watertemp
Temp = watertemp_beam;

// Overheat light
if(Temp >= 120) {
  DME4_Load3 = 0x08;
} else {
  DME4_Load3 = 0x00;
}

// Turn sisgnals + high beam + foglight
if((turnleft_beam == 0) && (turnright_beam == 0) && (highbeam_beam == 1) && (foglight_beam == 0)) {
  LightByte1 = 0x04;
} else if((turnleft_beam == 0) && (turnright_beam == 1) && (highbeam_beam == 0) && (foglight_beam == 0)) {
  LightByte1 = 0x40;
} else if((turnleft_beam == 1) && (turnright_beam == 0) && (highbeam_beam == 0) && (foglight_beam == 0)) {
  LightByte1 = 0x20;
} else if((turnleft_beam == 1) && (turnright_beam == 1) && (highbeam_beam == 0) && (foglight_beam == 0)) {
  LightByte1 = 0x60;
} else if((turnleft_beam == 0) && (turnright_beam == 1) && (highbeam_beam == 1) && (foglight_beam == 0)) {
  LightByte1 = 0x44;
} else if((turnleft_beam == 1) && (turnright_beam == 0) && (highbeam_beam == 1) && (foglight_beam == 0)) {
  LightByte1 = 0x24;
} else if((turnleft_beam == 1) && (turnright_beam == 1) && (highbeam_beam == 1) && (foglight_beam == 0)) {
  LightByte1 = 0x64;
} else if((turnleft_beam == 0) && (turnright_beam == 0) && (highbeam_beam == 1) && (foglight_beam == 1)) {
  LightByte1 = 0x14;
} else if((turnleft_beam == 0) && (turnright_beam == 1) && (highbeam_beam == 0) && (foglight_beam == 1)) {
  LightByte1 = 0x58;
} else if((turnleft_beam == 1) && (turnright_beam == 0) && (highbeam_beam == 0) && (foglight_beam == 1)) {
  LightByte1 = 0x38;
} else if((turnleft_beam == 1) && (turnright_beam == 1) && (highbeam_beam == 0) && (foglight_beam == 1)) {
  LightByte1 = 0x78;
} else if((turnleft_beam == 0) && (turnright_beam == 1) && (highbeam_beam == 1) && (foglight_beam == 1)) {
  LightByte1 = 0x54;
} else if((turnleft_beam == 1) && (turnright_beam == 0) && (highbeam_beam == 1) && (foglight_beam == 1)) {
  LightByte1 = 0x34;
} else if((turnleft_beam == 1) && (turnright_beam == 1) && (highbeam_beam == 1) && (foglight_beam == 1)) {
  LightByte1 = 0x74;
} else if((turnleft_beam == 0) && (turnright_beam == 0) && (highbeam_beam == 0) && (foglight_beam == 1)) {
  LightByte1 = 0x08;
} else {
  LightByte1 = 0x00;
}

// ABS Light
if(abslight_beam == 1) {
  absWarning = 0;
} else if(abslight_beam == 0) {
  absWarning = 1;
}

// Oilwarn
if(oillight_beam == 1) {
  DME4_Load0 = 0x02;
} else {
  DME4_Load0 = 0x00;
}

// Handbrake
if(parkingbreak_beam == 1) {
  digitalWrite(pinParkingpbrake, LOW);
} else {
  digitalWrite(pinParkingpbrake, HIGH);
}

// Remap DSC
dscSwitch = tclight_beam;

}
// End BeamNG

// No Game Data
if(Game.equalsIgnoreCase("ETS2") || Game.equalsIgnoreCase("ATS") || Game.equalsIgnoreCase("AssettoCorsaCompetizione") || Game.equalsIgnoreCase("pCars") || Game.equalsIgnoreCase("FH5") || Game.equalsIgnoreCase("FernbusSimulator") || Game.equalsIgnoreCase("BeamNgDrive")) {
  
} else {
  digitalWrite(pinParkingpbrake, HIGH);
  LightByte1 = 0x00;
  LightByte2 = 0x00;
  DME4_Load0 = 0x00;
  DME4_Load3 = 0x00;
  DME4_Load5 = 0x00;
}

// End No Game Data

// Begin all games data

// Cluster Backlight Alwayson
if(digitalRead(inputAlwaysonoption) == LOW) {
digitalWrite(pinClusterlight, LOW);  
}

// Cluster Backlight Hardwareswitch
if(digitalRead(inputHardwareoption) == LOW){
if(digitalRead(inputHardwareswitch) == LOW) {
digitalWrite(pinClusterlight, LOW);  
}
else {
digitalWrite(pinClusterlight, HIGH);
}
}

// dscWarning + dscSwitch
if ((dscWarning == 1) && (dscSwitch == 1)) {
DME6_Load1 = 0x01;
}
else if ((dscWarning == 1) && (dscSwitch == 0)) {
DME6_Load1 = 0x01;
}
else if ((dscWarning == 0) && (dscSwitch == 1)) {
DME6_Load1 = 0x01;
}
else if ((dscWarning == 0) && (dscSwitch == 0)) {
DME6_Load1 = 0x00;
}

// absWarning
if (absWarning == 0) {
digitalWrite(pinABS, HIGH);
}
else {
digitalWrite(pinABS, LOW);
}

// Gear indicator for numbers
if (gear.equalsIgnoreCase("1")) {
  AT_Gear = 0x01;
} else if (gear.equalsIgnoreCase("2")) {
  AT_Gear = 0x02;
} else if (gear.equalsIgnoreCase("3")) {
  AT_Gear = 0x03;
} else if (gear.equalsIgnoreCase("4")) {
  AT_Gear = 0x04;
} else if (gear.equalsIgnoreCase("5")) {
  AT_Gear = 0x09;
} else if (gear.equalsIgnoreCase("6")) {
  AT_Gear = 0x0A;
} else if (gear.equalsIgnoreCase("R")) {
  AT_Gear = 0x07;
} else if (gear.equalsIgnoreCase("N")) {
  AT_Gear = 0x06;
}

// ############
// END GAMEDATA
// ############

Speedometer();

  // RPM Scaling to Float based on MaxRPM

  // Clamp the RPM to the defined maximum
  if(RPM > MaxRPM) { RPM = MaxRPM; }
  // Map the RPM to a value for the cluster
  RPMSendVal = map(RPM, 0, 7000, 0, 175.00f); // 0.00f = 0rpm, 175.00f = 7000rpm
  
  // RPM
  // L2 = RPM LSB
  // L3 = RPM MSB from 0.00f to 175.00f
  // unsigned char message1[8] = {0x05, 0x62, 0xFF, RPMSendVal, 0x65, 0x12, 0, 62};
  // CAN.sendMsgBuf(0x316, 0, 8, message1);
  CanSend(0x316, 0x05, 0x62, 0xFF, RPMSendVal, 0x65, 0x12, 0, 62);
  // DME 4
  // L0 = 0x10=EML, 0x08=Cruise Control, 0x02=Motor Light
  // L1 = ? Probably L/100km -> Maybe the Change of Rate is needed to calculate in the cluster
  // L3 = 0x08=Overheat Light, 0x02=Oillight
  // L4 = ? Probably Oiltemp -> not as analog in the cluster, so ignored for now
  // L5 = Charging Light 0x00=off, 0x01=on
  CanSend(0x545, DME4_Load0, 0x00, 0x00, DME4_Load3, 0x00, DME4_Load5, 0x00, 0x00);
  // Coolant Temperature
  // Calculation, maxTemp=260.00f, minTemp=50.00f
  // Temp Scaling to Float based on temperaturerange from 50 to 130 Degree Celsius

  // Map the Temp to a value for the cluster
  if(Temp >= 130) {
    Temp = 125;  // Keep Temp in save Value
  }
  if(Temp <= 50) {
    Temp = 50;
  }
  TempSendVal = map(Temp, 50, 130, 50.00f, 260.00f);
  CanSend(0x329, 0x00, TempSendVal, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);  
  // Seems to clear the (!) and Traction control lights?
  // L1 = 0x01=Traction Control
  CanSend(0x153, 0x00, DME6_Load1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
  
  // AT Display
  CanSend(0x43F, 0x00, AT_Gear, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00); 
  
  // Begin K-Bus-Data
  // For Lightbyte1
  // 0x04=Indicator Highbeam
  // 0x08=Indicator Foglight rear
  // 0x10=Indicator Foglight front
  // 0x14=Fogrear+Highbeam
  // 0x20=Indicator Left
  // 0x24=Left+Highbeam
  // 0x28=Left+Fogrear
  // 0x30=Left+Fogfront
  // 0x34=Left+Fogfront+Highbeam
  // 0x38=Left+Fogfront+Fogrear
  // 0x40=Indicator Right
  // 0x44=Right+Highbeam
  // 0x50=Right+Fogfront
  // 0x54=Right+Fogfront+Highbeam
  // 0x58=Right+Fogfront+Fogrear
  // 0x60=Both Indicators
  // 0x64=Both+Highbeam
  // 0x70=Both+Fogfront
  // 0x74=Both+Fogrfront+Highbeam
  // 0x78=Both+Fogfront+Fogrear
  // For Lightbyte2
  // 0x30=Frontlights
  
  byte mes1[] = {0xD0, 0x08, 0xBF, 0x5B, LightByte1, 0x00, 0x00, LightByte2, 0x00, 0x58, 0x00};
  sendKbus(mes1);
    
  }

  // Called once between each byte read on arduino,
  // THIS IS A CRITICAL PATH :
  // AVOID ANY TIME CONSUMING ROUTINES !!!
  // PREFER READ OR LOOP METHOS AS MUCH AS POSSIBLE
  // AVOID ANY INTERRUPTS DISABLE (serial data would be lost!!!)
  void idle() {
  }

void CanSend(short address, byte a, byte b, byte c, byte d, byte e, byte f, byte g, byte h) {
  unsigned char DataToSend[8] = {a, b, c, d, e, f, g, h};
  CAN.sendMsgBuf(address, 0, 8, DataToSend);
}

void sendKbus(byte *data)
{
  int end_i = data[1]+2 ;
  data[end_i-1] = iso_checksum(data, end_i-1);
  kbus.write(data, end_i + 1);
}

void Speedometer()
{
  // Speedometer Calculate and Output
  if(Speed == 0)
  {
    noTone(SPEED_PIN); 
  }else{
    SpeedSendVal = map(Speed, 0, 250, 0, 1680);
    tone(SPEED_PIN, SpeedSendVal); // 250KmH=1680, 0KmH=0
  }

}


byte iso_checksum(byte *data, byte len)//len is the number of bytes (not the # of last byte)
{
  byte crc=0;
  for(byte i=0; i<len; i++)
  {    
    crc=crc^data[i];
  }
  return crc;
}

};

#endif
