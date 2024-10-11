#include <Arduino.h>
#include <RFIDController.h>
#include <MFRC522.h>

RFIDController rfid;

void setup() {
    Serial.begin(9600);
    rfid.iniciar();
    Serial.println("Aguardando cartao...");
}

void loop() {
    rfid.iniciar();
    String codigo = rfid.lerCodigoRFID();
    if(codigo != ""){
        Serial.println("Codigo do cartao: " + codigo);
    }
    delay(1000);
   
    
}
