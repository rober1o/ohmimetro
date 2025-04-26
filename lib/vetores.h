// Valores comerciais da serie E24 de 510Ω a 100kΩ
const int serieE24[] = {
    510, 560, 620, 680, 820, 910, 1000, 1100, 1200, 1300, 1500, 1600,
    1800, 2000, 2200, 2400, 2700, 3000, 3300, 3900, 4300, 4700, 5100, 5600,
    6200, 6800, 7500, 8200, 9100, 10000, 11000, 12000, 13000, 15000, 16000,
    18000, 20000, 22000, 24000, 27000, 30000, 33000, 36000, 39000, 43000,
    47000, 56000, 62000, 68000, 75000, 82000, 91000, 100000
};

// Mapeamento de valores para cores
const char* cores_faixas[] = {
    "preto",   // 0
    "marrom",  // 1
    "vermelho",// 2
    "laranja", // 3
    "amarelo", // 4
    "verde",   // 5
    "azul",    // 6
    "violeta", // 7
    "cinza",   // 8
    "branco"   // 9
};

// Mapeamento de multiplicadores
const char* cores_multiplicador[] = {
    "preto",   // ×1
    "marrom",  // ×10
    "vermelho",// ×100
    "laranja", // ×1000
    "amarelo", // ×10000
    "verde",   // ×100000
    "azul",    // ×1000000
    "violeta", // ×10000000
    "cinza",   // ×100000000
    "branco"   // ×1000000000
};