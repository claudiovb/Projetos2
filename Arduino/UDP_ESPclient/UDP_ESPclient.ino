/*
 Name:    UDP_client.ino
 Created: 9/10/2017 7:07:23 PM
 Author:  claudio
*/
#define _PI 3.14159 
#define BUFF 512
#define IncomeBuff 10
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <math.h>  
/*-------------------------------------------------------------------------------------------------------------------------------
 * ---------------------------WI-FI Variables------------------------------------------------------------------------------------
 ------------------------------------------------------------------------------------------------------------------------------*/
const char* ssid = "teste";
const char* password = "a1b2c3d4e5";
const int influx_port = 9283;
const char* influx_host = "192.168.1.233";
WiFiUDP Client;

byte serdata = 0;
byte fromserver = 0;
char header = 'A',startT = 0x3,endT = 0x2;
/*-------------------------------------------------------------------------------------------------------------------------------
 * ---------------------------Serial Variables------------------------------------------------------------------------------------
 ------------------------------------------------------------------------------------------------------------------------------*/
char dataString[BUFF] ={0};
size_t dataLength;
size_t serial_index = 0;
// data Serial buffer
char AudioData[BUFF] = {0};
bool the_first = true;
bool trasmitting = false;
void SerialCatch(char *dataString, size_t *dataLength)
{
  
  if (Serial.available() > 1)
  {
     dataLength[0] = Serial.available();
     //Serial.println(dataLength[0]);
     if(serial_index == 0)
        Serial.readBytes(&dataString[serial_index+2], dataLength[0]); 
     else
        Serial.readBytes(&dataString[serial_index], dataLength[0]);   
     //Serial.flush();
     /*for(int i = 2; i< dataLength[0];i++)
      Serial.print(dataString[i],HEX);
      
     Serial.println("");
     Serial.println(serial_index);*/
   /*  if(dataString[0] =='A' && dataString[1] =='b'){
    Serial.print(dataString);
     for(int i = 2; i< IncomeBuff; i++){
      if(the_first){
        AudioData[i + serial_index] =dataString[i]; 
      }
      else
        AudioData[i -2 + serial_index] =dataString[i]; 
     }   
     }
     //Serial.print(AudioData);
    //Serial.println(dataString); 
    // Serial.println(serial_index);
    */
  }
  if(trasmitting){
   // the_first = false;
    serial_index +=  dataLength[0];
  }
  // 
 
}
void SerialSend(char *paramSend,int packetSize){
  Serial.write(paramSend,packetSize);
 //  Serial.println("Tentando enviar serial");
}

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(2000000);
  //Serial.swap();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.softAP(ssid, password);
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
  Serial.flush();
  Client.begin(8888);
//  int  p = teste();
  dataString[0] = 'A';
  dataString[1] = 'b';

}





char packetBuffer[BUFF];  //buffer to hold incoming packet
char recording = 'r',stopping = 's';






// the loop function runs over and over again until power down or reset
void loop() {


  short value_recieved = 0;
  //delayMicroseconds(1);
  //SerialCatch(dataString, &dataLength);
  int packetSize = Client.parsePacket();
  if(packetSize)
  {

    
     // Serial.print("Received packet of size ");
      //Serial.println(packetSize);
     // Serial.print("From ");
     // IPAddress remote = Client.remoteIP();
  
     
      //for (int i = 0; i < 4; i++) {
      //  Serial.print(remote[i], DEC);
       // if (i < 3) {
        //  Serial.print(".");
       // }
     // }
  
     
     // Serial.print(", port ");
     // Serial.println(Client.remotePort());
  
     
       Client.read(packetBuffer, BUFF);
      // Serial.println(packetBuffer);
       header = packetBuffer[0];
      // Serial.println(header);
    //  for(int i = 0; i< packetSize;i++)
      //Serial.print(packetBuffer[i],HEX);
      
      switch(header)
      {
          case '0':
          trasmitting = true;
          SerialSend(&recording,sizeof(recording));
          break;
          case 'f':
          trasmitting = false;
          the_first = true;
          SerialSend(&stopping,sizeof(stopping));
          break;  
          case 0x55:
          SerialSend(packetBuffer,packetSize);
         // value_recieved =  (short)(((short)packetBuffer[5]) << 8) | (0xff & packetBuffer[6]);
          //Serial.println(value_recieved);
          break;
          default:
          break;
      }
  

    
  }


  
  if(trasmitting && serial_index > 256)
  {
    udpsend();
  }
   
}


static int sin_time = 0;
char message[BUFF] = {0};
char my[] = "teste";

void udpsend()
{
  //senwrite();
  //Serial.println("Entrei aqui");
  
  Client.beginPacket(influx_host, influx_port);
  
  // Client.write(message,sizeof(message));
 
  Client.write(dataString,serial_index);
  Client.endPacket();
  serial_index = 0;
  return;
}


void  senwrite()
{
  double value = 0;
  char xlow = 0;
  char xhigh = 0;
  short x = 0;
  message[0] = 'A';
  message[1] = 'b';
  //Serial.println(header);
  for(int i= 0; i < (BUFF >> 1) - 2; i++){
    value = sin(((double)500/(double)48000)*(2*_PI)*sin_time);
    x = (short)round(16384*value);
   // x = 0xAAAA;
    xlow = (char)(x & 0xff);
    xhigh= (char)(x >> 8);
    message[2*i+2] = xhigh;
    message[2*i+3] = xlow;
    //Serial.println(x);
    sin_time++;
    if(sin_time >= 48000) sin_time = 0;
  }
  //Serial.println("seno escrito");
  return;

}

