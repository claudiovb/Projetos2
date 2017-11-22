
#include <math.h>  
#define _PI 3.14159 
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Comecando");
}

#define BUFF 10
char recording = 'r',stopping = 's';
size_t dataLength;
byte dataString[10] = {0};
bool transmitting = false;
void  senwrite();
void loop() 
{
   short value_recieved = 0;
  if (Serial.available() >= 7)
  {
    //Serial.println("recebi dados");
     dataLength = Serial.available();
     Serial.readBytes(dataString, dataLength); 
     Serial.flush();    
     for(int i = 0; i< dataLength-2;i++)
      Serial.print(dataString[i],HEX);
  value_recieved =  (short)(((short)dataString[5]) << 8) | (0xff & dataString[6]);
  Serial.println(value_recieved);
  }
 
  
   
  
  
  switch(dataString[0])
  {
    case 'r':
    dataString[0] = 'n';
    transmitting = true;
   // Serial.println("Comecando");
    break;
    case 's':
    dataString[0] = 'n';
    transmitting = false;
    //Serial.println("Parando");
    break;  
    case 'a':
    dataString[0] = 'n';
   //Serial.println(dataString);
    break;
    case 'b':
    dataString[0] = 'n';
    //Serial.println(dataString);
    break;
    default:
    break;
  }
    
  if(transmitting)
  {
    senwrite();
  }
}


char message[BUFF] = {0};
int sin_time = 0;

void  senwrite()
{
  
  double value = 0;
  char xlow = 0;
  char xhigh = 0;
  short x = 0;
  

  
  //Serial.println(header);
  for(int i= 0; i < (BUFF >> 1); i++)
  {
    //value = sin(((double)500/(double)48000)*(2*_PI)*sin_time);
    //x = (short)round(16384*value);
    x = (short)0xAAAA;
    xlow = (char)(x & 0xff);
    xhigh= (char)(x >> 8);
    //message[2*i] = xhigh;
   // message[2*i+1] = xlow;
      message[2*i] = 0x02;
      message[2*i+1] = 0x02;
    //Serial.println(x);
    sin_time++;
  // Serial.print(message[2*i],HEX); 
 //  Serial.print(message[2*i+1],HEX);
    if(sin_time >= 32767) 
      sin_time = 0;
  }
  //for(int i = 0; i< BUFF;i++)
      //Serial.print(message[i],HEX);
 // Serial.println(" ");
  //Serial.println("seno escrito");
  Serial.write(message,BUFF);
 // delay(200);
  return;

}

