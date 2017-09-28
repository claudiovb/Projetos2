/*
 Name:    UDP_client.ino
 Created: 9/10/2017 7:07:23 PM
 Author:  claudio
*/
#define _PI 3.14159 
#define BUFF 512
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <math.h>  



const char* ssid = "O_Xilarau";
const char* password = "naotemsenha";
const int influx_port = 8888;
const char* influx_host = "10.42.0.1";


WiFiUDP Client;

byte serdata = 0;
byte fromserver = 0;
byte header = 0xA,startT = 0x3,endT = 0x2;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  Serial.println("Ta funcionando");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Client.begin(81);

}
// the loop function runs over and over again until power down or reset
void loop() {
  udpsend();
   
}
static int sin_time = 0;
char message[BUFF] = {0};
String my = "teste";
bool transflag = false,stopflag = false;
void udpsend()
{
  const char ip[] = "192.168.15.9";
  Client.beginPacket(ip, 8888);
  
  if(transflag){
    senwrite();
    Client.write(message, sizeof(message));
    Client.endPacket();
  } else{
    if(!stopflag){
      Serial.println("Trying to start transmission");
      message[0] = 0x3;
      message[1] = 0x3;
      message[2] = 0x3;
      message[3] = 0x3;
      
      Client.write(message,sizeof(message));
      Client.endPacket();
      transflag = true;

    }else{
//      Serial.println("Ending transmission");
      message[0] = endT;
      Client.write(message,sizeof(message));
      Client.endPacket();
    }
  }
  //Serial.println(my);
  //delay(1000);
  return;
}
void  senwrite(){
  double value = 0;
  char xlow = 0;
  char xhigh = 0;
  short x = 0;
  message[0] = header;
  message[1] = header;
  for(int i= 0; i < (BUFF >> 1) - 2; i++){
    value = sin(((double)500/(double)48000)*(2*_PI)*sin_time);
    x = (short)round(16383*value);
    xlow = (char)(x & 0xff);
    xhigh= (char)(x >> 8);
    message[2*i+2] = xhigh;
    message[2*i+3] = xlow;
    //Serial.println(x);
    sin_time++;
  }
  if(sin_time>48000){
    sin_time = 0;
    stopflag = true;
    transflag = false;
  }
  return;

}

