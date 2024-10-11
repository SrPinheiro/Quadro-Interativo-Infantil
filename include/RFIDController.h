#ifndef RFIDController_H
#define RFIDController_H
#include <SPI.h>
#include <MFRC522.h>

class RFIDController {
    public:
        int portas[5];
        MFRC522 mfrc522;
        RFIDController();
        void iniciar();
        String lerCodigoRFID();
};

#endif