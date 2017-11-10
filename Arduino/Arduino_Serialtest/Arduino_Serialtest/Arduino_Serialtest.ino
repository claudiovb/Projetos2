
#include <math.h>  
#define _PI 3.14159 
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);
 // Serial.println("Comecando");
}

#define BUFF 20
char recording = 'r',stopping = 's';
size_t dataLength;
char dataString[10] = {0};
bool transmitting = false;
void  senwrite();
void loop() 
{
  if (Serial.available() >= 1)
  {
    //Serial.println("recebi dados");
     dataLength = Serial.available();
     Serial.readBytes(dataString, dataLength); 
     Serial.flush();    
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
  
  message[0] = 'A';
  message[1] = 'b';
  
  //Serial.println(header);
  for(int i= 0; i < (BUFF); i++)
  {
    //value = sin(((double)500/(double)48000)*(2*_PI)*sin_time);
    //x = (short)round(16384*value);
    x = 0x7FFF;
    xlow = (char)(x & 0xff);
    xhigh= (char)(x >> 8);
    message[2*i+2] = xhigh;
    message[2*i+3] = xlow;
    //Serial.println(x);
    sin_time++;
    
    if(sin_time >= 32767) 
      sin_time = 0;
  }
  //Serial.println("seno escrito");
  Serial.write(message,sizeof(message));
  return;

}

