#include "ohmimetro.h"

int main()
{
    inicializar_hardware();

    while (true)
    {

        float resistencia = calcular_resistencia();

        atualizar_display(resistencia);

        sleep_ms(700);
    }
}

// Trecho para modo BOOTSEL com botão B

void gpio_irq_handler(uint gpio, uint32_t events)
{
    reset_usb_boot(0, 0);
}

// ROTINA PARA INICIALIZAR PERIFERICOS NECESSÁRIOS

void inicializar_hardware()
{
    // Para ser utilizado o modo BOOTSEL com botão B
    gpio_init(botaoB);
    gpio_set_dir(botaoB, GPIO_IN);
    gpio_pull_up(botaoB);
    gpio_set_irq_enabled_with_callback(botaoB, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    // Aqui termina o trecho para modo BOOTSEL com botão B

    gpio_init(Botao_A);
    gpio_set_dir(Botao_A, GPIO_IN);
    gpio_pull_up(Botao_A);

    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);                    // Set the GPIO pin function to I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);                    // Set the GPIO pin function to I2C
    gpio_pull_up(I2C_SDA);                                        // Pull up the data line
    gpio_pull_up(I2C_SCL);                                        // Pull up the clock line
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); // Inicializa o display
    ssd1306_config(&ssd);                                         // Configura o display
    ssd1306_send_data(&ssd);                                      // Envia os dados para o display

    // Limpa o display. O display inicia com todos os pixels apagados.
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);

    adc_init();
    adc_gpio_init(ADC_PIN); // GPIO 28 como entrada analógica
}

void atualizar_display(float resistencia)
{
    sprintf(valor_resistencia, "%1.0f", resistencia); // Converte o float em string
    //  Atualiza o conteúdo do display com animações
    ssd1306_fill(&ssd, false);                            // Limpa o display
    ssd1306_rect(&ssd, 3, 3, 122, 60, true, false);       // Desenha um retângulo
    ssd1306_line(&ssd, 3, 25, 123, 25, true);             // Desenha uma linha
    ssd1306_line(&ssd, 3, 37, 123, 37, true);             // Desenha uma linha
    ssd1306_draw_string(&ssd, "ROBERTO", 30, 6);          // Desenha uma string
    ssd1306_draw_string(&ssd, "EMBARCATECH", 20, 16);     // Desenha uma string
    ssd1306_draw_string(&ssd, "  Ohmimetro", 10, 28);     // Desenha uma string
    ssd1306_draw_string(&ssd, "ADC", 13, 41);             // Desenha uma string
    ssd1306_draw_string(&ssd, "Resisten.", 50, 41);       // Desenha uma string
    ssd1306_line(&ssd, 44, 37, 44, 60, true);             // Desenha uma linha vertical
    ssd1306_draw_string(&ssd, valor_adc, 8, 52);          // Desenha uma string
    ssd1306_draw_string(&ssd, valor_resistencia, 59, 52); // Desenha uma string
    ssd1306_send_data(&ssd);                              // Atualiza o display
}

float calcular_resistencia()
{
    adc_select_input(2); // Seleciona o ADC para eixo X. O pino 28 como entrada analógica
    float R_x = 0.0;     // Resistor desconhecido
    float soma = 0.0f;
    for (int i = 0; i < 500; i++)
    {
        soma += adc_read();
        sleep_ms(1);
    }

    float media = soma / 500.0f;
    // Fórmula simplificada: R_x = R_conhecido * ADC_encontrado /(ADC_RESOLUTION - adc_encontrado)
    R_x = (R_conhecido * media) / (ADC_RESOLUTION - media);
    return R_x;
}