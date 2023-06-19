#include <Manchester.h>

#define TX_PIN 1
#define RX_PIN 3

uint8_t data[20] = {11, '1','2', '3', '4', '5', '6', '7', '8', '9','1','2','3','4','5','6','7','8','9'};


void setup() {
  man.setupTransmit(TX_PIN, MAN_1200);
  man.setupReceive(RX_PIN, MAN_1200);
  man.beginReceive();
}

void loop() {
  
  man.transmit(data);

  if (man.receiveComplete()) {
    uint16_t m = man.getMessage();
    serial.println(m);
    man.beginReceive(); 
  }

}
