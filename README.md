# Atividade - Interrupções Pico W - U4C4O12T

Atividade realizada utilizando o kit de desenvolvimento BitDogLab, no contexto do Embarcatech, da formação em Sistemas embarcados. 
Além de um contador que é incrementado ao pressionar a tecla A da BitDog, e decrementado ao pressionar a tecla B, o sistema conta com um timer que faz piscar os LEDs
conectados as GPIOs 11, 12 e 13. O contador exibe números de 0 a 9 em uma matriz 5x5 que tem como base LEDs WS2812 e a cada incremento/decremento deve ser ouvido um bip
gerado com o buzzer B (GPIO 10) da BitDog.

O sistema tem as seguintes funções implementadas:

1) O LED vermelho do RGB (GPIO 13) pisca 5 vezes por segundo;
2) Os LEDs verde e azul (GPIO 11 e 12) alternam enquanto o LED vermelho está apagado;
3) O botão A gera interrupção e incrementa o contador;
4) O botão B gera interrupção e decrementa o contador;
5) A matriz de LEDs (WS2812) exibe o valor do contador (de 0 a 9);
6) Ativação do modo de gravação enviando "#" via monitor serial.

## Instrução de Uso

Para utilizar o programa com o kit de desenvolvimento BitDogLab, o usuário deve:

- Clonar este repositório: git clone https://github.com/saturnino028/U4C2O1234A---Matriz-de-LEDs.git;
- Usando a extensão Raspberry Pi Pico importar o projeto;
- Compilar o projeto;
- Plugar a BitDogLab usando um cabo apropriado e gravar o código.

## Demonstração

Vídeo demonstrando as funcionalidades da solução implementada: [Vídeo](https://youtu.be/Ep0sseX6uZc).

## Atenção

O brilho dos LEDs é muito intenso, para evitar danos aos olhos recomendamos que o brilho_padrao seja ajustado para 10% quando estiver usando o kit BitDogLab.
