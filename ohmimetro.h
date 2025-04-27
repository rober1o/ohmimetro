#ifndef OHMIMETRO_H
#define OHMIMETRO_H

// =============================
// Bibliotecas necessárias
// =============================
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "pico/bootrom.h"

// Bibliotecas locais
#include "lib/ssd1306.h"
#include "lib/font.h"
#include "lib/vetores.h"
#include "pio_wave.pio.h"

// =============================
// Definições de pinos e constantes
// =============================

// Matriz de LEDs
#define MATRIZ_PIN          7       // Pino da matriz de LEDs
#define NUM_PIXELS          25      // Número de pixels na matriz
#define BRILHO_PADRAO       100     // Intensidade padrão do brilho

// Comunicação I2C
#define I2C_PORT            i2c1
#define I2C_SDA             14
#define I2C_SCL             15
#define ENDERECO_DISPLAY    0x3C    // Endereço do display OLED

// ADC (Ohmímetro)
#define ADC_PIN             28      // GPIO usado para leitura ADC
#define ADC_VREF            3.31f   // Tensão de referência do ADC

// Botões
#define BOTAO_A             5
#define BOTAO_B             6
#define BOTAO_C             22

// Constantes de operação
#define R_CONHECIDO         10000   // Resistor conhecido de 10k Ohms
#define TAMANHO_SERIE       (sizeof(serieE24) / sizeof(serieE24[0]))
#define DEBOUNCE_TIME       200

// =============================
// Variáveis globais
// =============================

PIO pio;                   // Instância do PIO
int sm;                    // Máquina de estado do PIO

ssd1306_t ssd;             // Instância do display OLED

char valor_adc[5];          // Buffer para valor do ADC
char valor_resistencia[5];  // Buffer para valor da resistência
char variacao[5];           // Buffer para variação
int ADC_RESOLUTION = 4095;

bool botao_a_pressionado;     // Estado do botão A ou B
bool botao_c_pressionado;   // Estado do botão C
// verificação de debunce
static uint32_t ultimo_tempoA = 0;
static uint32_t ultimo_tempoB = 0;
static uint32_t ultimo_tempoC = 0;

// =============================
// Protótipos de funções
// =============================

// Inicialização
void inicializar_hardware();

// Interrupções
void gpio_irq_handler(uint gpio, uint32_t events);
bool debounce_ok(uint gpio);

// Operações gerais
void desenha_fig(uint32_t *_matriz, uint8_t _intensidade, PIO pio, uint sm);
void atualizar_display(float resistencia);
float calcular_resistencia();

// Manipulação de resistores
int encontrar_faixa_comercial(float valor);
const char** valor_para_cores(int valor_resistor);
void exibir_faixas_matriz(int valor_resistor);
#endif // OHMIMETRO_H
