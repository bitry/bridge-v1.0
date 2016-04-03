#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <SoftwareSerial.h>
SoftwareSerial dist(2, 3);
//SoftwareSerial dist1(4, 5);


char command;
String answer="";
int data[55];

const uint64_t pipe02 = 0xF0F1F2F3F1LL; // индитификатор передачи, "труба" 

RF24 radio(9, 10); // CE, CSN 
void setup() {
  Serial.begin(19200);
  dist.begin(19200);
  //dist1.begin(19200);
  radio.begin(); 
delay(20); 
radio.setChannel(100); // канал (0-127) 

// скорость, RF24_250KBPS, RF24_1MBPS или RF24_2MBPS 
// RF24_250KBPS на nRF24L01 (без +) неработает. 
// меньше скорость, выше чувствительность приемника. 
radio.setDataRate(RF24_250KBPS); 

// мощьность передатчика, RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_MED=-6dBM, 
radio.setPALevel(RF24_PA_LOW); 

radio.openReadingPipe(2,pipe02); // открываем первую трубу с индитификатором "pipe"
  radio.startListening(); // включаем приемник, начинаем слушать трубу
}

void loop() {
  if (radio.available())
  { // проверяем не пришло ли чего в буфер.
    radio.read(&command, sizeof(command)); // читаем данные и указываем сколько байт читать
  
  //Serial.println(command);
 // if (Serial.available()>0)
 // {
 //   command=Serial.read();
//    Serial.println(command);
    // отправляем данные и указываем сколько байт пакет 
//    radio.write(&command, sizeof(command)); 
     dist.print(command);
     //dist1.print(command);
     delay(1000);

    for(int i = 0; i <16; i++)
    {
      data[i] = dist.read();
      delay(100);            
    }
   Serial.println();
   
   for(int i=0;i<16;i++)
   {
    answer = answer + String(char(data[i]));
    //Serial.println(char(data[i]));
    
   }
   const char *str= new char[16];
   
   str=answer.c_str();
   Serial.println(str);
   //Serial.print(answer);
   radio.stopListening();
   radio.openWritingPipe(pipe02);
   //radio.write(&answer, sizeof(answer));
   radio.write(str, 16);
   Serial.flush();
   answer = "";
   radio.openReadingPipe(2, pipe02);
   radio.startListening();
   
    //Serial.println();
  
  }
}
  

