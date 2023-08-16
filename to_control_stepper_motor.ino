#include<WiFi.h>
#include <WiFiUdp.h>
const char * ssid = "Sike...";
const char * pass = "12345678";
const char * udpaddress = "192.168.68.7";
const int udpport = 8080;
char pktbuf[10]="\0";
WiFiUDP udp;

// Defining the terminals for motors a,b,c

#define a1 26 
#define a2 25 //Motor-A
#define ena 13 //Speed control for motor-A

#define b1 27
#define b2 14
#define enb 21 //Motor-B

#define c1 23
#define c2 22
#define enc 12 //Motor-C
 
#define offsetFB 45 // Offset factor to ensure correct forward/backward motion
#define offsetLR 5 // Offset factor to ensure correct Left/Right motion
#define spcontrol 60 //speed control for clockwise/anti-clockwise direction

void setup() {
  
  // setup code: set the pins characteristics (I/O)
  
  pinMode(a1, OUTPUT); //Motor-A
  pinMode(a2, OUTPUT);
  
  pinMode(b1, OUTPUT); //Motor-B
  pinMode(b2, OUTPUT);
  
  pinMode(c1, OUTPUT); //Motor-C
  pinMode(c2, OUTPUT);
  
  Serial.begin(9600);

  WiFi.begin(ssid,pass);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
}
  Serial.println("");
  Serial.print("connected to");
  Serial.println(ssid);
  Serial.print(WiFi.localIP());
  udp.begin(udpport);

}

void loop() {
  int rp=udp.parsePacket();
  int inp;
  if(rp){
    pktbuf[1]='\0';
    pktbuf[2]='\0';
    udp.read(pktbuf,10);
    Serial.println(pktbuf);
    inp=*pktbuf;
    }if(inp==97){
      anticlockwise(); 
    }if(inp==99){
      clockwise();
    }if(inp==115){
      stopmotion();
    }if(inp==102){
      forwardmotion();
    }if(inp==98){
      backwardmotion();
    }if(inp==108){
      leftmotion();
    }if(inp==114){
      rightmotion();
    }
}

// Functions for Right, left, front, back, clockwise and anti-clockwise motion
void rightmotion(){
    
  digitalWrite(a1, HIGH);
  digitalWrite(a2, LOW);
  analogWrite(ena, 100 - offsetLR);

  digitalWrite(b1, HIGH);
  digitalWrite(b2, LOW);
  analogWrite(enb, 100 - offsetLR);  
  
  digitalWrite(c1, LOW);
  digitalWrite(c2, HIGH);
  analogWrite(enc, 200); 
  
  delay(100); 
}

void stopmotion(){
    
  digitalWrite(a1, LOW);
  digitalWrite(a2, LOW);
  analogWrite(ena,0);

  digitalWrite(b1, LOW);
  digitalWrite(b2, LOW);
  analogWrite(enb, 0);  
  
  digitalWrite(c1, LOW);
  digitalWrite(c2, LOW);
  analogWrite(enc, 0); 
  
  delay(100); 
}

void leftmotion(){

  digitalWrite(a1, LOW);
  digitalWrite(a2, HIGH);
  analogWrite(ena, 100 - offsetLR);

  digitalWrite(b1, LOW);
  digitalWrite(b2, HIGH);
  analogWrite(enb, 100 - offsetLR);  
  
  digitalWrite(c1, HIGH);
  digitalWrite(c2, LOW);
  analogWrite(enc, 200); 
  
  delay(100); 
}

void forwardmotion(){
    
  digitalWrite(a1, HIGH);
  digitalWrite(a2, LOW); //A is clockwise
  analogWrite(ena, 200+offsetFB);

  digitalWrite(b1, LOW);
  digitalWrite(b2, HIGH); //B is anticlockwise
  analogWrite(enb, 200);  
  
  digitalWrite(c1, LOW);
  digitalWrite(c2, LOW);
  analogWrite(enc, 0);
    
  delay(100); 
}

void backwardmotion(){
    
  digitalWrite(a1, LOW);
  digitalWrite(a2, HIGH);
  analogWrite(ena, 200+offsetFB);

  digitalWrite(b1, HIGH);
  digitalWrite(b2, LOW);
  analogWrite(enb, 200);  
  
  digitalWrite(c1, LOW);
  digitalWrite(c2, LOW);
  analogWrite(enc, 0); 
   
  delay(100); 
}

void clockwise(){

  digitalWrite(a1, LOW);
  digitalWrite(a2, HIGH);
  analogWrite(ena, spcontrol);

  digitalWrite(b1, LOW);
  digitalWrite(b2, HIGH);
  analogWrite(enb, spcontrol);  
  
  digitalWrite(c1, LOW);
  digitalWrite(c2, HIGH);
  analogWrite(enc, spcontrol); 
   
  delay(100); 
  
}

void anticlockwise(){

  digitalWrite(a1, HIGH);
  digitalWrite(a2, LOW);
  analogWrite(ena, spcontrol);

  digitalWrite(b1, HIGH);
  digitalWrite(b2, LOW);
  analogWrite(enb, spcontrol);  
  
  digitalWrite(c1, HIGH);
  digitalWrite(c2, LOW);
  analogWrite(enc, spcontrol); 
   
  delay(100); 
  
}
