// Valores comerciais da serie E24 de 510Ω a 100kΩ
const int serieE24[] = {
    510, 560, 620, 680, 820, 910, 1000, 1100, 1200, 1300, 1500, 1600,
    1800, 2000, 2200, 2400, 2700, 3000, 3300, 3900, 4300, 4700, 5100, 5600,
    6200, 6800, 7500, 8200, 9100, 10000, 11000, 12000, 13000, 15000, 16000,
    18000, 20000, 22000, 24000, 27000, 30000, 33000, 36000, 39000, 43000,
    47000, 56000, 62000, 68000, 75000, 82000, 91000, 100000};

// Mapeamento de valores para cores
const char *cores_faixas[] = {
    "preto",    // 0
    "marrom",   // 1
    "vermelho", // 2
    "laranja",  // 3
    "amarelo",  // 4
    "verde",    // 5
    "azul",     // 6
    "violeta",  // 7
    "cinza",    // 8
    "branco"    // 9
};

// Mapeamento de multiplicadores
const char *cores_multiplicador[] = {
    "preto",    // ×1
    "marrom",   // ×10
    "vermelho", // ×100
    "laranja",  // ×1000
    "amarelo",  // ×10000
    "verde",    // ×100000
    "azul",     // ×1000000
    "violeta",  // ×10000000
    "cinza",    // ×100000000
    "branco"    // ×1000000000
};

uint32_t cores_faixas_matriz[] = {
    0x00000000, // preto
    0xff1b1b5a, // marrom
    0xff0000ff, // vermelho
    0xff0457ff, // laranja
    0xff04dcff, // amarelo
    0xff00ff42, // verde
    0xffff2800, // azul
    0xff800080, // violeta
    0xff404040, // cinza
    0xfffff2f6, // branco
};

uint32_t cores_multiplicador_matriz[] = {
    0x00000000, // preto
    0xff1b1b5a, // marrom
    0xff0000ff, // vermelho
    0xff0457ff, // laranja
    0xff04dcff, // amarelo
    0xff00ff42, // verde
    0xffff2800, // azul
    0xff800080, // violeta
    0xff404040, // cinza
    0xfffff2f6, // branco
};

// matriz para colorir de acordo a resistencia

uint32_t cor_resistor[25] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};

uint32_t matriz_apagada[25] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};

// matriz com todas as cores possiveis do resistor

uint32_t resistores[25] = {
    0xff1b1b5a, 0x00000000, 0xff0000ff, 0x00000000, 0xff0457ff,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0xff04dcff, 0x00000000, 0xff00ff42, 0x00000000, 0xffff2800,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0xff800080, 0x00000000, 0xff404040, 0x00000000, 0xfffff2f6};