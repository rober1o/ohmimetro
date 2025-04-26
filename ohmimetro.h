#ifndef OHMIMETRO // Previne múltiplas inclusões do cabeçalho
#define OHMIMETRO

// =============================
// Bibliotecas necessárias
// =============================
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "lib/ssd1306.h"
#include "lib/font.h"
#include "lib/vetores.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "pico/bootrom.h"
// =============================
// Portas usadas
// =============================

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C
#define ADC_PIN 28 // GPIO para o ohmimetro
#define Botao_A 5  // GPIO para botão A
#define botaoB 6   // GPIO para botão B

// =============================
// Variaeveis globais
// =============================

int R_conhecido = 10000;   // Resistor de 10k ohm
float ADC_VREF = 3.31;     // Tensão de referência do ADC
int ADC_RESOLUTION = 4095; // Resolução do ADC (12 bits)
ssd1306_t ssd;             // Inicializa a estrutura do display
char valor_adc[5];         // Buffer para armazenar a string
char valor_resistencia[5]; // Buffer para armazenar a string

// =============================
// FUNÇÕES E ROTINAS
// =============================

void gpio_irq_handler(uint gpio, uint32_t events);
void inicializar_hardware();
void atualizar_display(float resistencia);
float calcular_resistencia();

#endif // OHMIMETRO
