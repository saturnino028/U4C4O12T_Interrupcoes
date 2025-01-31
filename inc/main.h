/**
 * @brief Arquivo cabeçalho principal
 * @author Marco Antonio de Jesus Saturnino
 */
#ifndef MAIN_H
#define MAIN_H

/********************* Includes *********************/
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "hardware/pio.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"
#include "InterfacePio.pio.h"

/********************* Defines *********************/
#define bot_A   5
#define bot_B   6

#define Mat_pin 7

#define buz_B   10

#define LED_G   11
#define LED_B   12
#define LED_R   13

#define NUM_PIXELS 25 //Número de pixels/leds matriz
#define freq_buz   1000 //Frequencia do tom gerado
#define dur_buz    100 //Duração do sinal sonoro

/********************* Variaveis Globais *********************/
extern PIO pio;
extern int sm;
extern int offset;
extern volatile bool botao_flag;
extern volatile uint8_t contador;
extern volatile uint32_t passado;

/********************* Prototipo de Funções *********************/

void init_pins_gpio();
void desenhar_fig(uint32_t *_matriz, uint8_t _intensidade);
void entrar_modo_gravacao();
void botoes_callback(uint gpio, uint32_t events);
bool pisca_led(struct repeating_timer *t);
void som_buz(uint16_t freq, uint16_t duration_ms);

#endif //MAIN_H