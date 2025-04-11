#ifndef __SHCUSTOMPROTOCOL_H__
#define __SHCUSTOMPROTOCOL_H__

#include <Arduino.h>
#include <SPI.h>
#include <mcp_can.h>

// Set Canbus Pin
const int SPI_CS_PIN = 9;
MCP_CAN CAN(SPI_CS_PIN); // Set CS pin

// Set kBus
#define kbus Serial2

// Set Speedo Pin
#define SPEED_PIN 46

// Set Relay Pins
int pinABS = 44;
int pinParkingpbrake = 40;
int pinClusterlight = 42;



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
String currentDateTime; // Aktuelle Uhrzeit als String
int hour, minute, second; // Einzelne Teile der Uhrzeit


String gear;
int showLights = 0;

String Game = "ETS2";

// Backlight Options
int inputIngameoption = 30;
int inputHardwareoption = 32;
int inputAlwaysonoption = 34;
int inputHardwareswitch = 36;

class SHCustomProtocol {
private:

public:

  void setup() {

  pinMode(inputIngameoption, INPUT_PULLUP);
  pinMode(inputHardwareoption, INPUT_PULLUP);
  pinMode(inputAlwaysonoption, INPUT_PULLUP);
  pinMode(inputHardwareswitch, INPUT_PULLUP);  
  pinMode(pinABS, OUTPUT);
  pinMode(pinParkingpbrake, OUTPUT);
  pinMode(pinClusterlight, OUTPUT);
  digitalWrite(pinABS, HIGH);
  digitalWrite(pinParkingpbrake, HIGH);
  digitalWrite(pinClusterlight, HIGH);
    
    pinMode(SPEED_PIN, OUTPUT);


    kbus.begin(9600, SERIAL_8E1);

   CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ);
   CAN.setMode(MCP_NORMAL);
  }

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
      currentDateTime = FlowSerialReadStringUntil(';'); // Datum und Uhrzeit als String
      // Beispiel, wie man die Uhrzeit trennt:
      hour = currentDateTime.substring(0, 2).toInt();
      minute = currentDateTime.substring(3, 5).toInt();
      second = currentDateTime.substring(6, 8).toInt();

  
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

 
  void loop() {
  
    // Hier holst du die Uhrzeit von SimHub
    currentDateTime = FlowSerialReadStringUntil(';');
    hour = currentDateTime.substring(0, 2).toInt();
    minute = currentDateTime.substring(3, 5).toInt();
    second = currentDateTime.substring(6, 8).toInt();

    // Senden der Uhrzeit über den K-Bus
    byte timeDataKbus[] = {hour, minute, second, 0x00, 0x00, 0x00, 0x00};
    sendKbus(timeDataKbus);


// Start Assetto Corsa 
if(Game.equalsIgnoreCase("AssettoCorsa")) {

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

// End Assetto Corsa

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

// No Game Data
if(Game.equalsIgnoreCase("ETS2") || Game.equalsIgnoreCase("AssettoCorsa")) {
  
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
