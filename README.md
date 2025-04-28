# SISTEMA PARA MEDIÇÃO DE RESISTÊNCIA RELATIVA

O projeto tem como finalidade medir a resistência de resistores utilizando como base um resistor de valor conhecido, permitindo assim a determinação da resistência desconhecida por meio de comparação. Além disso, o sistema fornecerá informações adicionais relevantes, como a faixa de cores correspondente ao resistor analisado e resistência comercial da série E24.

## Componentes Utilizados

1. **Resistores da serie E24 com faixa de 510 a 100k ohms**
2. **Matriz de LED 5x5 WS2812** 
3. **Microcontrolador Raspberry Pi Pico W**
4. **Dois botões Pushbutton**
5. **Protoboard**
6 . **Joystick**
7. **Display OLED 1306**
8. **Jumpers de conexão M-F**

## Funcionalidade

Ao iniciar o programa, com todas as conexões realizadas o display OLED apresentará a resistencia real do resistor desconhecido e sua faixa de cores. Simutaneamente será exibido essas cores na Matrid de led 5X5.

Funcionalidades dos Botões

Botão A: Alterna as informações presentes no display OLED, exibindo as faixa de cores e resistência real, ou exibe a resistencia comercial e o desvio em relação a resistência relativa

Botão B: Ativa o modo BOOTSEL da bitDogLab.

Botão C: Alterna a resolução do ADC para caso esteja conectado na bateria conseguir calcular uma resistência mais precisa.

### Como Usar

#### Usando a BitDogLab

- Clone este repositório: git clone https://github.com/rober1o/ohmimetro.git;
- Usando a extensão Raspberry Pi Pico importar o projeto;
- Compilar o projeto;
- Plugar a BitDogLab usando um cabo apropriado e gravar o código.
- Realizar a conexão na protoboad conforme interface do Arquivo Diagram.json
- Conectar o resistor desconhecido que deseja saber a resitência conforme o arquivo Diagram.json

## Atenção
O brilho dos LEDs é muito intenso, para evitar danos aos olhos é recomendado que o brilho_padrao seja ajustado para 30%.
## Demonstração

<!-- TODO: adicionar link do vídeo -->
Vídeo demonstrando as funcionalidades da solução implementada: [Demonstração](https://youtu.be/NLIjqA_kH5Q)
