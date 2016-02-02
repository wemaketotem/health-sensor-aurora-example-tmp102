#include "mbed.h"

I2C TMP102(P0_3, P0_2);                                                     //I2C verbinding

Serial pc(USBTX, USBRX);                                                    //RX TX voor monitoren pc
const int addr = 0x90;                                                      //sensor adres 0x90 wanneer add0 laag is!!!!!!!!!!
char regByte[3];                                                            //config bytes decl                                    
char temp_read[2];                                                          //rouwe sensor waarde 2 bytes breed
float temp;                                                                 //sensor waarde

int main() {
    regByte[0] = 0x01;                                                      //configureer register
    regByte[1] = 0x60;                                                      //configureer byte 1
    regByte[2] = 0xA0;                                                      //configureer byte 2
    
    TMP102.write(addr, regByte, 3);                                         //schrijf config-data naar temp sensor
    regByte[0] = 0x00;                                                      //pointer register 
    TMP102.write(addr, regByte, 1);                                         //pointer naar lees data
    while(1) {
        wait(1);
        TMP102.read(addr, temp_read, 2);                                    //lees de twee bytes
        temp = 0.0625 * (((temp_read[0] << 8) + temp_read[1]) >> 4);        //convert eer data naar float
        pc.printf("Temperatuur = %.2fC\n\r", temp);                         //schrijf float temp naar serieele monitor
    }   
}
