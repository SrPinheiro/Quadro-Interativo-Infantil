#include "RFIDController.h"
#include <Arduino.h>

RFIDController::RFIDController() : mfrc522(portas[0], portas[4]) {
    this->portas[0] = 10;  // SDA
    this->portas[1] = 13;  // SCK
    this->portas[2] = 11;  // MOSI
    this->portas[3] = 12;  // MISO
    this->portas[4] = 9;   // RST
}

void RFIDController::iniciar() {
    SPI.begin();
    mfrc522.PCD_Init();
}

String RFIDController::lerCodigoRFID() {
    int contagem = 0; // essa contagem limita em 10 segundos para colocar o cartao no leitor :)

    while(true){
        if(contagem >= 20){
            throw "[010] Limite de tempo para colocar o cartão"; // se passar 10 segundos e nao ler, ele lanca um erro
        }

        if (mfrc522.PICC_IsNewCardPresent()) {
            break;
        }
        delay(500);
    }

    String codigo = ""; 
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        codigo += (mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
        codigo += String(mfrc522.uid.uidByte[i], HEX);
    }

    mfrc522.PICC_HaltA();

    return codigo;
}
