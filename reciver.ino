#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#include <printf.h>

Servo s1;//s1就是旋轉馬達
RF24 radio(7, 8); // CE, CSN 接在pin 7.8上面
const byte address[6] = "00001";
const int In1 = 3;
const int In2 = 4;
const int In3 = 5;      
const int In4 = 6; 

void setup() {
  s1.attach(9);//旋轉馬達接在pin 9上面
  Serial.begin(9600);//initial 監控視窗
  radio.begin();//初始化 nRF24L01 模組
  printf_begin();// //初始化 RF24 的列印輸出功能
  radio.openReadingPipe(0, address);//開啟寫入管線
  radio.setPALevel(RF24_PA_MIN);//設為低功率, 預設為 RF24_PA_MAX
  radio.startListening();//接收端開始接收
  radio.printDetails();//印出nRF24L01詳細狀態
  Serial.println("NRF24L01 receiver");
  Serial.println("waiting...");
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
}

int s1_degree=90;

void mstop(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}
void mfront(){
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}
void mback(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
}
void mleft(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}
void mright(){
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}

void loop() 
{  
  // reply only when you receive data:
  if (radio.available()) //檢查有沒有收到
  {
    int text[2]={0};
    // read the incoming byte:
    radio.read(&text, sizeof(text));//讀取收到的內容

    // say what you got:
    Serial.print("I received: ");
    for(int i=0; i<2; i++)
    {
        Serial.println(text[i]); 
    }
    int vrx = text[0];
    int vry = text[1];
    
    if( (vrx<700&&vrx>400) && (vry<1100&&vry>900) )
    {   //left//0
        Serial.print("I received: left\n");
        mleft();
        delay(1000);
    }
    else if( (vrx<600 && vrx>400) && (vry>=0 && vry<100) )
    {    //right//1
        Serial.print("I received: right\n");
        mright();
        delay(1000);
    }
    else if( (vrx>=0 && vrx<100) && (vry<850 && vry>450) )
    {    //forward//2
        Serial.print("I received: forward\n");
        mfront();
        delay(1000);
    }
    else if( (vrx<1100 && vrx>900) && (vry<900 && vry>450) )
    {    //Back//3
        Serial.print("I received: back\n");
        mback();
        delay(1000);
    }
    
    else if( (vrx<600 && vrx>400) && (vry<600 && vry>400) )
    {    //stay//4
        Serial.print("I received: stop\n");
        mstop();
        delay(1000);
    }    

  }

}
/*
  if (radio.available()) 
  {
    Serial.println(1);
    char text[32] = "";
    int vrx;
    radio.read(&vrx, sizeof(vrx));
    
    Serial.println(vrx);
    
    //s1_degree=map(vrx, 0, 1023, 0, 180);
    
    if(vrx==1023)
    {
      s1_degree+=15;
    }
    else if(vrx==0)
    {
      s1_degree-=15;
    }
    
    s1.write(s1_degree);
 /*for ( int pos = 0; pos <= 360; pos ++)  
  {    
    Serial.println(vrx); 
    
    s1.write(pos) ; // 告訴 servo 走到 'pos' 的位置
    delay(15);        // 等待 15ms 讓 servo 走到指定位置
  } /*
    
    Serial.println(vrx);
  }
 */
