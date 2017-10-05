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



const char* ssid = "teste2";
const char* password = "a1b2c3d4e5";
const int influx_port = 9283;
const char* influx_host = "192.168.1.233";


WiFiUDP Client;

byte serdata = 0;
byte fromserver = 0;
byte header = 0x2,startT = 0x3,endT = 0x2;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 // WiFi.softAP(ssid, password);
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
  Client.begin(8888);
  

}
char packetBuffer[BUFF];  //buffer to hold incoming packet
bool trasmitting = false;
// the loop function runs over and over again until power down or reset
void loop() {
  int packetSize = Client.parsePacket();
  if(packetSize){
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remote = Client.remoteIP();
    for (int i = 0; i < 4; i++) {
      Serial.print(remote[i], DEC);
      if (i < 3) {
        Serial.print(".");
      }
    }
    Serial.print(", port ");
    Serial.println(Client.remotePort());
     Client.read(packetBuffer, BUFF);
     Serial.println(packetBuffer);
     header = packetBuffer[0];
     Serial.println(header);
    switch(header){
      case '0':
      trasmitting = true;
      Serial.println(trasmitting);
      break;
      case 'f':
      trasmitting = false;
      Serial.println(trasmitting);
      break;
      default:
      break;  
    }
  }
  if(trasmitting){
    udpsend();
  }
   
}
static int sin_time = 0;
char message[BUFF] = {0};
char my[] = "teste";
void udpsend()
{
  senwrite();
  Client.beginPacket(influx_host, influx_port);
  Client.write(message,sizeof(message));
  Client.endPacket();

  
/*
    Client.write(message, sizeof(message));
    Client.endPacket();

      Client.write(message,sizeof(message));
      Client.endPacket();

      Client.write(message,sizeof(message));
      Client.endPacket();
*/

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
    x = (short)round(32767*value);
    xlow = (char)(x & 0xff);
    xhigh= (char)(x >> 8);
    message[2*i+2] = xhigh;
    message[2*i+3] = xlow;
    //Serial.println(x);
    sin_time++;
  }
  Serial.println("seno escrito");
  return;

}

