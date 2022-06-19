#include <Wire.h>
#include <SoftwareSerial.h> //Library to convert Digital Output pins of the board to transmitter as well as receiver
 
#define RE 8
#define DE 7
 
const byte nitro[]  = {0x01,0x03, 0x00, 0x1E, 0x00, 0x01, 0xE4, 0x0C};
const byte phosp[]  = {0x01,0x03, 0x00, 0x1F, 0x00, 0x01, 0xB5, 0xCC};
const byte potas[]  = {0x01,0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xC0};


byte values5[11];
byte values6[11];
byte values7[11];


SoftwareSerial mod(2,3); // RX, TX ( Creates a new SoftwareSerial object )
 
void setup() {
  Serial.begin(9600);
  mod.begin(9600);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
}
 
void loop() {
  byte val5;
  val5 = Nitro();
  delay(250);
  byte val6;
  val6 = Phosp();
  delay(250);
  byte val7;
  val7 = Potas();
  delay(250);

  

  Serial.print("Soil N: ");
  Serial.print(val5);
  Serial.println(" mg/kg");
  Serial.print("Soil P: ");
  Serial.print(val6);
  Serial.println(" mg/kg");
  Serial.print("Soil K: ");
  Serial.print(val7);
  Serial.println(" mg/kg");
  Serial.println();
  delay(2000);

}


byte Nitro(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(nitro,sizeof(nitro))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(mod.read(),HEX);
    values5[i] = mod.read();
    Serial.print(values5[i],HEX);
    Serial.print("\t");
    }
    Serial.println();
  }
  return values5[4];
}

byte Phosp(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(phosp,sizeof(phosp))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(mod.read(),HEX);
    values6[i] = mod.read();
    Serial.print(values6[i],HEX);
    Serial.print("\t");
    }
    Serial.println();
  }
  return values6[4];
}

byte Potas(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(potas,sizeof(potas))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(mod.read(),HEX);
    values7[i] = mod.read();
    Serial.print(values7[i],HEX);
   Serial.print("\t");
    }
    Serial.println();
  }
  return values7[4];
}
