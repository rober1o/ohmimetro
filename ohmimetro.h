#ifndef OHMIMETRO // Previne múltiplas inclusões do cabeçalho
#define OHMIMETRO

// =============================
// Bibliotecas necessárias
// =============================
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"  // Controle do PIO (Programável I/O)
#include "hardware/clocks.h" // Manipulação de clock
#include "pio_wave.pio.h"  // Código PIO 
#include "lib/ssd1306.h"
#include "lib/font.h"
#include "lib/vetores.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "pico/bootrom.h"

// =============================
// Portas usadas
// =============================

#define BRILHO_PADRAO 100  // Intensidade padrão do brilho
// Matriz de LEDs
#define MATRIZ_PIN 7       // Pino da matriz de LEDs
#define NUM_PIXELS 25      // Número de pixels na matriz

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C
#define ADC_PIN 28 // GPIO para o ohmimetro
#define Botao_A 5  // GPIO para botão A
#define botaoB 6   // GPIO para botão B
#define TAMANHO_SERIE (sizeof(serieE24) / sizeof(serieE24[0]))
// Configurações gerais


// =============================
// Variaeveis globais
// =============================

PIO pio;        // Instância do PIO
int sm;         // Máquina de estado do PIO

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
void desenha_fig(uint32_t *_matriz, uint8_t _intensidade, PIO pio, uint sm);
void inicializar_hardware();
void atualizar_display(float resistencia);
float calcular_resistencia();
int encontrar_faixa_comercial(float valor);
const char** valor_para_cores(int valor_resistor);
void exibir_faixas_matriz(int valor_resistor);


#endif // OHMIMETRO
