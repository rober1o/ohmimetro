#include "ohmimetro.h"

int main()
{
    inicializar_hardware();
    desenha_fig(cor_resistor, BRILHO_PADRAO, pio, sm);
    while (true)
    {

        float resistencia = calcular_resistencia();
        
        atualizar_display(resistencia);
        exibir_faixas_matriz(resistencia);
        sleep_ms(700);
    }
}

void gpio_irq_handler(uint gpio, uint32_t events)
{
    if (gpio == BOTAO_A && debounce_ok(gpio))  // Alterna o estado do botão A
    {
        botao_a_pressionado = !botao_a_pressionado;
    }
    else if (gpio == BOTAO_B && debounce_ok(gpio))  // Ativa o modo BOOTSEL quando o botão B é pressionado
    {
        reset_usb_boot(0, 0);
    }
    else if (gpio == BOTAO_C && debounce_ok(gpio))  // Alterna a resolução do ADC com o botão C para ajustar a queda de tensão quando ligado na bateria
    {
        if (botao_c_pressionado)
        {
            ADC_RESOLUTION = 4095;  
        }
        else
        {
            ADC_RESOLUTION = 3585;  
        }

        botao_c_pressionado = !botao_c_pressionado;  // Alterna o estado do botão C
    }
}


// ROTINA PARA INICIALIZAR PERIFERICOS NECESSÁRIOS
void inicializar_hardware()
{
    // Inicializa os botões (A, B e C) com interrupção
    inicializar_botao(BOTAO_A);
    inicializar_botao(BOTAO_B);
    inicializar_botao(BOTAO_C);

    // Inicializa o barramento I2C a 400Khz
    i2c_init(I2C_PORT, 400 * 1000);
    configurar_pinos_i2c();

    // Inicializa o display SSD1306
    inicializar_display();

    // Inicializa o ADC
    adc_init();
    adc_gpio_init(ADC_PIN); // GPIO 28 como entrada analógica

    // Configura o PIO para controle da matriz de LEDs
    pio = pio0;
    configurar_clock();

    // Inicializa a comunicação serial
    stdio_init_all();

    // Carrega o programa PIO para controle da matriz de LEDs
    int offset = pio_add_program(pio, &Matriz_5x5_program);
    sm = pio_claim_unused_sm(pio, true);
    Matriz_5x5_program_init(pio, sm, offset, MATRIZ_PIN);
}

// Função para inicializar um botão com interrupção
void inicializar_botao(uint gpio)
{
    gpio_init(gpio);
    gpio_set_dir(gpio, GPIO_IN);
    gpio_pull_up(gpio);
    gpio_set_irq_enabled_with_callback(gpio, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
}

// Função para configurar os pinos do I2C
void configurar_pinos_i2c()
{
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);  // Define a função I2C para o pino SDA
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);  // Define a função I2C para o pino SCL
    gpio_pull_up(I2C_SDA);                      // Habilita o pull-up para o pino SDA
    gpio_pull_up(I2C_SCL);                      // Habilita o pull-up para o pino SCL
}

// Função para inicializar o display SSD1306
void inicializar_display()
{
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, ENDERECO_DISPLAY, I2C_PORT);  // Inicializa o display
    ssd1306_config(&ssd);  // Configura o display
    ssd1306_send_data(&ssd);  // Envia os dados para o display
    ssd1306_fill(&ssd, false);  // Limpa o display
    ssd1306_send_data(&ssd);  // Envia os dados para o display
}

// Função para configurar o clock do sistema
void configurar_clock()
{
    bool clock_setado = set_sys_clock_khz(133000, false);
    if (clock_setado)
    {
        printf("Clock setado %ld\n", clock_get_hz(clk_sys));
    }
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

// Função para atualizar o display com a resistência e seus cálculos
void atualizar_display(float resistencia)
{
    // Calcula os valores necessários
    float valor_comercial = encontrar_faixa_comercial(resistencia);
    float desvio = resistencia - valor_comercial;

    // Converte os valores para string
    sprintf(valor_resistencia, "%1.0f", resistencia);
    sprintf(valor_adc, "%1.0f", valor_comercial);
    sprintf(variacao, "%1.0f", desvio);

    ssd1306_fill(&ssd, false);                      // Limpa o display
    ssd1306_rect(&ssd, 3, 3, 122, 58, true, false); // Desenha o retângulo principal

    if (botao_a_pressionado && valor_comercial > 0)
    {
        // Exibe a faixa e desvio
        ssd1306_draw_string(&ssd, "E24:", 12, 15);     // Faixa 1
        ssd1306_draw_string(&ssd, valor_adc, 45, 15);
        ssd1306_line(&ssd, 4, 33, 121, 33, true);      // Linha horizontal
        ssd1306_draw_string(&ssd, "Desvio:", 8, 45);   // Desvio
        ssd1306_draw_string(&ssd, variacao, 70, 45);
    }
    else if (valor_comercial > 0)
    {
        // Obtém as cores das faixas
        const char **cores = valor_para_cores((int)valor_comercial);

        // Exibe as cores das faixas
        ssd1306_draw_string(&ssd, "F1:", 6, 6);  // Faixa 1
        ssd1306_draw_string(&ssd, "F2:", 6, 18); // Faixa 2
        ssd1306_draw_string(&ssd, "M:", 6, 30);  // Multiplicador

        // Imprime as cores (faixa1, faixa2, multiplicador)
        ssd1306_draw_string(&ssd, cores[0], 30, 6);
        ssd1306_draw_string(&ssd, cores[1], 30, 18);
        ssd1306_draw_string(&ssd, cores[2], 30, 30);

        // Linha horizontal
        ssd1306_line(&ssd, 4, 42, 121, 42, true); // Linha horizontal

        // Exibe o valor da resistência
        ssd1306_draw_string(&ssd, "RR:", 8, 50);              // Texto "RR: (Resistência real)"
        ssd1306_draw_string(&ssd, valor_resistencia, 40, 50); // Valor da resistência
    }
    else
    {
        // Exibe mensagem quando o valor está fora da faixa
        ssd1306_draw_string(&ssd, "FORA DE FAIXA", 11, 20);  // Exibe "FORA DE FAIXA"
        ssd1306_line(&ssd, 4, 42, 121, 42, true);            // Linha horizontal

        // Exibe o valor da resistência
        ssd1306_draw_string(&ssd, "RR:", 8, 50);              // Texto "RR: (Resistência real)"
        ssd1306_draw_string(&ssd, valor_resistencia, 40, 50); // Valor da resistência
    }

    ssd1306_send_data(&ssd); // Atualiza o display
}


float calcular_resistencia()
{
    adc_select_input(2); // Seleciona o ADC para eixo X. O pino 28 como entrada analógica
    float R_x = 0.0;     // Resistor desconhecido
    float soma = 0.0f;
    for (int i = 0; i < 250; i++)
    {
        soma += adc_read();
    }

    float media = soma / 250.0f;
    // Fórmula simplificada: R_x = R_CONHECIDO * ADC_encontrado /(ADC_RESOLUTION - adc_encontrado)
    R_x = (R_CONHECIDO * media) / (ADC_RESOLUTION - media);
    return R_x;
}

// Função para verificar se a resistencia está dentro da tolerancia da faixa comercial da serie E24
int encontrar_faixa_comercial(float valor)
{
    for (int i = 0; i < TAMANHO_SERIE; i++)
    {
        int menor = serieE24[i] * 95 / 100;
        int maior = serieE24[i] * 105 / 100;

        if (valor >= menor && valor <= maior)
        {
            return serieE24[i];
        }
    }
    return -1; // Não encontrado
}

// Função para converter valor para cores
const char **valor_para_cores(int valor_resistor)
{
    static const char *cores_resultado[3]; // Array para armazenar as 3 cores

    int digito1, digito2, multiplicador = 0;
    float resul = valor_resistor;

    // Divida até que resul seja menor que 100
    while (resul >= 100)
    {
        resul /= 10;     // Divide o número por 10
        multiplicador++; // Incrementa o multiplicador
    }

    // Primeiro dígito: parte inteira de resul
    digito1 = (int)(resul) / 10;

    // Segundo dígito: pega o resto da divisão por 10
    digito2 = (int)(resul) % 10;

    // Armazenar os resultados no array
    cores_resultado[0] = cores_faixas[digito1];
    cores_resultado[1] = cores_faixas[digito2];
    cores_resultado[2] = cores_multiplicador[multiplicador];

    // Retornar o array de cores
    return cores_resultado;
}

// Função para converter valor para cores
void exibir_faixas_matriz(int valor_resistor)
{
    int resistencia_comercial = encontrar_faixa_comercial(valor_resistor);

    if (resistencia_comercial != -1)
    {
        int digito1, digito2, multiplicador = 0;
        float resul = resistencia_comercial;

        // Divide até que resul seja menor que 100
        while (resul >= 100)
        {
            resul /= 10;     // Divide o número por 10
            multiplicador++; // Incrementa o multiplicador
        }

        // Obtém os dígitos e atribui diretamente às cores
        cor_resistor[2] = cores_faixas_matriz[(int)(resul) / 10];       // Cor da primeira faixa
        cor_resistor[12] = cores_faixas_matriz[(int)(resul) % 10];      // Cor da segunda faixa
        cor_resistor[22] = cores_multiplicador_matriz[multiplicador];    // Cor do multiplicador

        desenha_fig(cor_resistor, BRILHO_PADRAO, pio, sm);
    }
    else
    {
        desenha_fig(matriz_apagada, BRILHO_PADRAO, pio, sm);  // Caso fora de faixa
    }
}

// função de debunce das interrupções
bool debounce_ok(uint gpio)
{
    uint32_t tempo_atual = to_ms_since_boot(get_absolute_time());

    if (gpio == BOTAO_A)
    {
        if (tempo_atual - ultimo_tempoA > DEBOUNCE_TIME)
        {
            ultimo_tempoA = tempo_atual;
            return true;
        }
    }
    else if (gpio == BOTAO_B)
    {
        if (tempo_atual - ultimo_tempoB > DEBOUNCE_TIME)
        {
            ultimo_tempoB = tempo_atual;
            return true;
        }
    }
    else if (gpio == BOTAO_C)
    {
        if (tempo_atual - ultimo_tempoC > DEBOUNCE_TIME)
        {
            ultimo_tempoC = tempo_atual;
            return true;
        }
    }
    return false;
}
