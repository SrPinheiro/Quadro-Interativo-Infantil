#include "LedController.h"
#include <Arduino.h>

// Construtor: Inicialize aqui se necessário
LedController::LedController() {}

// Função para alterar o estado de um LED
void LedController::alterarEstadoLed(bool estado, int pino) {
    pinMode(pino, OUTPUT);  // Define o pino como saída
    digitalWrite(pino, estado ? HIGH : LOW);  // Liga ou desliga o LED
}

// Função para alterar o estado de uma linha de LEDs, de acordo com o nível
void LedController::alterarEstadoDaTrilha(int linha, int nivel) {
    // Defina uma matriz de pinos correspondente às linhas de LEDs
    int pinos[5][5] = {
        {2, 3, 4, 5, 6},   // Pinos da linha 1
        {7, 8, 9, 10, 11}, // Pinos da linha 2
        {12, 13, 14, 15, 16}, // Pinos da linha 3
        {17, 18, 19, 20, 21}, // Pinos da linha 4
        {22, 23, 24, 25, 26}  // Pinos da linha 5
    };

    // Limite o nível entre 0 e 5
    nivel = constrain(nivel, 0, 5);

    // Alterar o estado de cada LED na linha
    for (int i = 0; i < 5; i++) {
        alterarEstadoLed(i < nivel, pinos[linha][i]);  // Liga os LEDs de acordo com o nível
    }
}
