#include <SPI.h> 
#include <nRF24L01.h> 
#include <RF24.h>
#include <SoftwareSerial.h>
SoftwareSerial dist(2, 3);


char command;
String answer;

const uint64_t pipe01 = 0xF0F1F2F3F4LL;      // индитификатор передачи, "труба" 
//const uint64_t pipe02 = 0xF0F1F2F3F1LL;   // индитификатор передачи, "труба" 

RF24 radio(9, 10); // CE, CSN 

    void setup() {
      Serial.begin(19200);
      dist.begin(19200);
      radio.begin(); 
      delay(20); 
      radio.setChannel(100);            // канал (0-127) 

radio.setDataRate(RF24_250KBPS);        // скорость, RF24_250KBPS, RF24_1MBPS или RF24_2MBPS 
                                        // RF24_250KBPS на nRF24L01 (без +) неработает. 
                                        // меньше скорость, выше чувствительность приемника. 

radio.setPALevel(RF24_PA_LOW);          // мощьность передатчика, 
                                        //RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_MED=-6dBM,  

radio.openWritingPipe(pipe01);          // открываем трубу на передачу. 

}

void loop() {
  
  if (Serial.available()>0)
  {
    command = Serial.read();
      
      if (command == '0')
    {
        radio.stopListening();
        radio.openWritingPipe(pipe01);
        radio.write(&command,sizeof(command));
        delay(1000);
        radio.openReadingPipe(1, pipe01);
        radio.startListening();
    }
    
    else if (command == '0')
    {
       radio.stopListening();
       radio.openWritingPipe(pipe01);
       radio.write(&command,sizeof(command));
       delay(1000);
       radio.openReadingPipe(1, pipe01);
       radio.startListening();
    }
  }
  
  if (radio.available())
  {
    char *str=new char[16];
    radio.read(str, 16);
    Serial.println(str);
    Serial.flush();
    
    
  }
 
}
