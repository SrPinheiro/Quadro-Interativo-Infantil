#include "RFIDController.h"
#include <Arduino.h>

RFIDController::RFIDController(): mfrc522(22, 23) {
    // PORTAS DO RFID, esta na sequencia com o leitor virado para cima, a porta IRQ nao sera usada!
    this->portas[0] = 22;  // SDA
    this->portas[1] = 52;  // SCK
    this->portas[2] = 51;  // MOSI
    this->portas[3] = 50;  // MISO
    this->portas[6] = 23;   // RST
}

void RFIDController::iniciar() {
    SPI.begin();
    mfrc522.PCD_Init();
}

String RFIDController::lerCodigoRFID() {
    int contagem = 0;
    while(true){
        if(contagem >= 20){
            
            return "";
        }

        if(mfrc522.PICC_IsNewCardPresent()) {
            break;
        }

        delay(500);
        contagem++;
    }
    if(!mfrc522.PICC_ReadCardSerial()) {

        return "";
    }
    

    String conteudoDaTag = "";

    for(byte i = 0; i < mfrc522.uid.size; i++) {
        conteudoDaTag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
        conteudoDaTag.concat(String(mfrc522.uid.uidByte[i], HEX));
    }

    mfrc522.PICC_HaltA();

    return conteudoDaTag;
}
