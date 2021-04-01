#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

void setup()
{
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Serial.begin(9600);
}

struct signal{
  byte xx;
};
int buttonPin = 4;
int buttonPress = 0; 
//Signal data;
/*int mapJoystickValues(int val, int lower, int middle, int upper, bool reverse)
{
  val = constrain(val,lower upper)
}*/

int counter = 0;

void loop() 
{
  int vrx, vry;
  vrx = analogRead(A0);//up & down
  vry = analogRead(A1);//right & left
  //sw = analogRead(A2);//push//useless
 
  char buf[100];
  int order[2];
  //sprintf(buf, "VRx=%d, VRy=%d, SW=%d", vrx, vry, sw);
  order[0] = vrx;
  order[1] = vry;
  sprintf(buf, "VRx=%d, VRy=%d", vrx, vry);
  Serial.println(buf);
  //radio.write(&buf, sizeof(buf));
  radio.write(&order, sizeof(order));//傳資料出去
  Serial.println(counter);
  counter++;
  delay(1000);

/*
  int vrx;
  vrx = analogRead(A0);
  const char text[100];
  int X;
  sprintf(text, "VRx=%d", vrx);
  radio.write(&vrx, sizeof(vrx));
  Serial.println(vrx);
  delay(1000);
*/
}
