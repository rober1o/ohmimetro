#include "ohmimetro.h"

int main()
{
    inicializar_hardware();
    desenha_fig(resistores, BRILHO_PADRAO, pio, sm);
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

        // Define o PIO 0 para controle da matriz de LEDs
        pio = pio0;

        // Configura o clock do sistema para 133 MHz
        bool clock_setado = set_sys_clock_khz(133000, false);
    
        // Inicializa a comunicação serial
        stdio_init_all();
    
        // Exibe mensagem na serial caso o clock tenha sido configurado com sucesso
        if (clock_setado)
            printf("Clock setado %ld\n", clock_get_hz(clk_sys));
    
        // Carrega o programa PIO para controle da matriz de LEDs
        int offset = pio_add_program(pio, &Matriz_5x5_program);
    
        // Obtém um state machine livre para o PIO
        sm = pio_claim_unused_sm(pio, true);
    
        // Inicializa o programa PIO na matriz de LEDs
        Matriz_5x5_program_init(pio, sm, offset, MATRIZ_PIN);


}

void desenha_fig(uint32_t *_matriz, uint8_t _intensidade, PIO pio, uint sm)
{
    uint32_t pixel = 0;
    uint8_t r, g, b;

    for (int i = 24; i > 19; i--) // Linha 1
    {
        pixel = _matriz[i];
        b = ((pixel >> 16) & 0xFF) * (_intensidade / 100.00); // Isola os 8 bits mais significativos (azul)
        g = ((pixel >> 8) & 0xFF) * (_intensidade / 100.00);  // Isola os 8 bits intermediários (verde)
        r = (pixel & 0xFF) * (_intensidade / 100.00);         // Isola os 8 bits menos significativos (vermelho)
        pixel = 0;
        pixel = (g << 16) | (r << 8) | b;
        pio_sm_put_blocking(pio, sm, pixel << 8u);
    }

    for (int i = 15; i < 20; i++) // Linha 2
    {
        pixel = _matriz[i];
        b = ((pixel >> 16) & 0xFF) * (_intensidade / 100.00); // Isola os 8 bits mais significativos (azul)
        g = ((pixel >> 8) & 0xFF) * (_intensidade / 100.00);  // Isola os 8 bits intermediários (verde)
        r = (pixel & 0xFF) * (_intensidade / 100.00);         // Isola os 8 bits menos significativos (vermelho)
        pixel = 0;
        pixel = (b << 16) | (r << 8) | g;
        pixel = (g << 16) | (r << 8) | b;
        pio_sm_put_blocking(pio, sm, pixel << 8u);
    }

    for (int i = 14; i > 9; i--) // Linha 3
    {
        pixel = _matriz[i];
        b = ((pixel >> 16) & 0xFF) * (_intensidade / 100.00); // Isola os 8 bits mais significativos (azul)
        g = ((pixel >> 8) & 0xFF) * (_intensidade / 100.00);  // Isola os 8 bits intermediários (verde)
        r = (pixel & 0xFF) * (_intensidade / 100.00);         // Isola os 8 bits menos significativos (vermelho)
        pixel = 0;
        pixel = (g << 16) | (r << 8) | b;
        pio_sm_put_blocking(pio, sm, pixel << 8u);
    }

    for (int i = 5; i < 10; i++) // Linha 4
    {
        pixel = _matriz[i];
        b = ((pixel >> 16) & 0xFF) * (_intensidade / 100.00); // Isola os 8 bits mais significativos (azul)
        g = ((pixel >> 8) & 0xFF) * (_intensidade / 100.00);  // Isola os 8 bits intermediários (verde)
        r = (pixel & 0xFF) * (_intensidade / 100.00);         // Isola os 8 bits menos significativos (vermelho)
        pixel = 0;
        pixel = (g << 16) | (r << 8) | b;
        pio_sm_put_blocking(pio, sm, pixel << 8u);
    }

    for (int i = 4; i > -1; i--) // Linha 5
    {
        pixel = _matriz[i];
        b = ((pixel >> 16) & 0xFF) * (_intensidade / 100.00); // Isola os 8 bits mais significativos (azul)
        g = ((pixel >> 8) & 0xFF) * (_intensidade / 100.00);  // Isola os 8 bits intermediários (verde)
        r = (pixel & 0xFF) * (_intensidade / 100.00);         // Isola os 8 bits menos significativos (vermelho)
        pixel = 0;
        pixel = (g << 16) | (r << 8) | b;
        pio_sm_put_blocking(pio, sm, pixel << 8u);
    }
}

void atualizar_display(float resistencia)
{
    float teste = encontrar_faixa_comercial(resistencia);
    
    sprintf(valor_resistencia, "%1.0f", resistencia);  // Converte o float em string
    sprintf(valor_adc, "%1.0f", teste);  // Converte o float em string

    // Obtendo as três cores (faixa1, faixa2 e multiplicador)
    const char** cores = valor_para_cores((int)teste);  // Chama a função que retorna as cores

    ssd1306_fill(&ssd, false);  // Limpa o display
    ssd1306_rect(&ssd, 3, 3, 122, 58, true, false);  // Desenha o retângulo principal

    // Desenha os títulos das faixas e multiplicador
    ssd1306_draw_string(&ssd, "F1:", 6, 6);  // Faixa 1
    ssd1306_draw_string(&ssd, "F2:", 6, 18); // Faixa 2
    ssd1306_draw_string(&ssd, "M:", 6, 30);  // Multiplicador

    // Imprime as cores (faixa1, faixa2, multiplicador)
    ssd1306_draw_string(&ssd, cores[0], 30, 6);
    ssd1306_draw_string(&ssd, cores[1], 30, 18);
    ssd1306_draw_string(&ssd, cores[2], 30, 30);

    // Desenha a linha horizontal começando em y = 42
    ssd1306_line(&ssd, 4, 42, 121, 42, true);  // Linha horizontal de quase ponta a ponta

    // Apenas "RR" e os valores
    ssd1306_draw_string(&ssd, "RR:", 8, 50);  // Texto "RR:"
    ssd1306_draw_string(&ssd, valor_resistencia, 40, 50);  // Valor da resistência
    
    ssd1306_send_data(&ssd);  // Atualiza o display
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

int encontrar_faixa_comercial(float valor) {
    for (int i = 0; i < TAMANHO_SERIE; i++) {
        int menor = serieE24[i] * 95 / 100;
        int maior = serieE24[i] * 105 / 100;

        if (valor >= menor && valor <= maior) {
            return serieE24[i];
        }
    }
    return -1; // Não encontrado
}

// Função para converter valor para cores
const char** valor_para_cores(int valor_resistor) {
    static const char* cores_resultado[3];  // Array para armazenar as 3 cores

    int digito1, digito2, multiplicador = 0;
    float resul = valor_resistor;

    // Divida até que resul seja menor que 100
    while (resul >= 100) { 
        resul /= 10;  // Divide o número por 10
        multiplicador++;   // Incrementa o multiplicador
    }

    // Primeiro dígito: parte inteira de resul
    digito1 = (int)(resul) / 10;

    // Segundo dígito: pegamos o resto da divisão por 10
    digito2 = (int)(resul) % 10;

    // Armazenar os resultados no array
    cores_resultado[0] = cores_faixas[digito1];
    cores_resultado[1] = cores_faixas[digito2];
    cores_resultado[2] = cores_multiplicador[multiplicador];

    // Retornar o array de cores
    return cores_resultado;
}