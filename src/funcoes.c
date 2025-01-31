/**
 * @brief Implementação das funções de controle da matriz de LEDs
 */
#include "main.h"

//Criação de Pio
PIO pio = pio0;    
int offset;
int sm;
volatile bool status_led_R = 1, status_leds = 1;

/**
 * @brief inicia os pinos de GPIO
 */
void init_pins_gpio()
{
    //Configuração do botao A
    gpio_init(bot_A);
    gpio_pull_up(bot_A);
    gpio_set_dir(bot_A, GPIO_IN);

    //Configuração do botao B
    gpio_init(bot_B);
    gpio_pull_up(bot_B);
    gpio_set_dir(bot_B, GPIO_IN);

    //Configuração do buzzer B
    gpio_init(buz_B);
    gpio_set_dir(buz_B, GPIO_OUT);

    //Configuração do LED vermelho
    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);

    //Configuração do LED verde
    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);

    //Configuração do LED azul
    gpio_init(LED_B);
    gpio_set_dir(LED_B, GPIO_OUT);
}

/**
 * @brief Desenha figura (aceita um padrão hexa, vindo direto do https://www.piskelapp.com/)
 * @param _matriz aceita uma matriz 1x25 com o padrão dos leds
 * @param _intensidade aceita um inteiro de 0 a 100 refente a intensidade do led
 * 
    //Mapa leds

    25, 24, 23, 22, 21,

    16, 17, 18, 19, 20,  

    15, 14, 13, 12, 11,

    06, 07, 08, 09, 10,    

    05, 04, 03, 02, 01  
 */
void desenhar_fig(uint32_t *_matriz, uint8_t _intensidade)
{
    uint32_t pixel = 0; uint8_t r, g, b;

    for(int i = 24; i>19; i--) //Linha 1
    {
        pixel = _matriz[i];
        b = ((pixel >> 16) & 0xFF)*(_intensidade/100.00); // Isola os 8 bits mais significativos (azul)
        g = ((pixel >> 8) & 0xFF)*(_intensidade/100.00);  // Isola os 8 bits intermediários (verde)
        r = (pixel & 0xFF)*(_intensidade/100.00);         // Isola os 8 bits menos significativos (vermelho)
        pixel = 0;
        pixel = (g << 16) | (r << 8) | b;
        pio_sm_put_blocking(pio, sm, pixel<<8u);
    }

    for(int i = 15; i<20; i++) //Linha 2
    {
        pixel = _matriz[i];
        b = ((pixel >> 16) & 0xFF)*(_intensidade/100.00); // Isola os 8 bits mais significativos (azul)
        g = ((pixel >> 8) & 0xFF)*(_intensidade/100.00);  // Isola os 8 bits intermediários (verde)
        r = (pixel & 0xFF)*(_intensidade/100.00);         // Isola os 8 bits menos significativos (vermelho)
        pixel = 0;
        pixel = (b << 16) | (r << 8) | g;
        pixel = (g << 16) | (r << 8) | b;
        pio_sm_put_blocking(pio, sm, pixel<<8u);

    }

    for(int i = 14; i>9; i--) //Linha 3
    {
        pixel = _matriz[i];
        b = ((pixel >> 16) & 0xFF)*(_intensidade/100.00); // Isola os 8 bits mais significativos (azul)
        g = ((pixel >> 8) & 0xFF)*(_intensidade/100.00);  // Isola os 8 bits intermediários (verde)
        r = (pixel & 0xFF)*(_intensidade/100.00);         // Isola os 8 bits menos significativos (vermelho)
        pixel = 0;
        pixel = (g << 16) | (r << 8) | b;
        pio_sm_put_blocking(pio, sm, pixel<<8u);
    }

    for(int i = 5; i<10; i++) //Linha 4
    {
        pixel = _matriz[i];
        b = ((pixel >> 16) & 0xFF)*(_intensidade/100.00); // Isola os 8 bits mais significativos (azul)
        g = ((pixel >> 8) & 0xFF)*(_intensidade/100.00);  // Isola os 8 bits intermediários (verde)
        r = (pixel & 0xFF)*(_intensidade/100.00);         // Isola os 8 bits menos significativos (vermelho)
        pixel = 0;
        pixel = (g << 16) | (r << 8) | b;
        pio_sm_put_blocking(pio, sm, pixel<<8u);
    }

    for(int i = 4; i > -1 ; i--) //Linha 5
    {
        pixel = _matriz[i];
        b = ((pixel >> 16) & 0xFF)*(_intensidade/100.00); // Isola os 8 bits mais significativos (azul)
        g = ((pixel >> 8) & 0xFF)*(_intensidade/100.00);  // Isola os 8 bits intermediários (verde)
        r = (pixel & 0xFF)*(_intensidade/100.00);         // Isola os 8 bits menos significativos (vermelho)
        pixel = 0;
        pixel = (g << 16) | (r << 8) | b;
        pio_sm_put_blocking(pio, sm, pixel<<8u);
    }
}

/**
 * @brief coloca o PICO no modo de gravação
 */
void entrar_modo_gravacao() 
{
    printf("Entrando no modo de gravação...\n");
    reset_usb_boot(0, 0); 
}

/**
 * @brief trata a interrupção gerada pelos botões A e B da BitDog
 * @param gpio recebe o pino que gerou a interrupção
 * @param events recebe o evento que causou a interrupção
 */
void botoes_callback(uint gpio, uint32_t events)
{
    // Obtém o tempo atual em microssegundos
    uint32_t agora = to_us_since_boot(get_absolute_time());

    // Verifica se passou tempo suficiente desde o último evento
    if (agora - passado > 200000) // 200 ms de debouncing
    {
        botao_flag = 1;
        passado  = agora;
        if(gpio == bot_A) //Verifica se o botão A causou a interrupção
        {
            if(contador<9) //Verifica para incrementar
                contador++;
            else
                contador = 0;
        }
        else if (gpio == bot_B) //Verifica se o botão B causou a interrupção
        {
            if(contador>0) //Verifica para decrementar
                contador--;
            else
                contador = 9;
        }
        printf("Contador: %d\n", contador);
    }

    printf("Tempo na interrupcao: %llu us\n", (to_us_since_boot(get_absolute_time()) - agora));
}

/**
 * @brief Pisca o LED a intervalos regulares definidos na função add_repeating_timer_ms
 * @param t recebe ponteiro para a estrutura de dados do temporizador que chamou a função
 * @return retorna true para continuar com o timer ou false para parar
 */
bool pisca_led(struct repeating_timer *t)
{ 
    gpio_put(LED_G, 0); //Apaga LED verde
    gpio_put(LED_B, 0); //Apaga LED azul
    gpio_put(LED_R, status_led_R); //Acende LED vermelho a cada 200 ms
    if(!status_led_R) //Verifica se o LED vermelho está apagado
    {
        gpio_put(LED_G, status_leds); //Muda o estado do LED verde
        gpio_put(LED_B, !status_leds); //Muda o estado do LED azul = !verde
        status_leds = !status_leds; //Atualiza o valor para piscar os LEDs
    }
    status_led_R = !status_led_R; //Muda o estado do LED vermelho (pisca) 5 vezes por segundo
    return true;
}

/**
 * @brief reproduz um tom puro
 * @param freq é a frequência do sinal
 * @param duration_ms é a duração do sinal em milisegundos
 */
void som_buz(uint16_t freq, uint16_t duration_ms)
{
    uint period = 1000000 / freq;  // Período do sinal em microssegundos
    uint cycles = (duration_ms * 1000) / period;  // Número de ciclos a gerar

    for (uint i = 0; i < cycles; i++) 
    {
        gpio_put(buz_B, 1);  // Liga o buzzer
        sleep_us(period / 2);  // Espera metade do período
        gpio_put(buz_B, 0);  // Desliga o buzzer
        sleep_us(period / 2);  // Espera metade do período
    }

}