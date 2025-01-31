#include "main.h"
#include "figuras.h"

#define brilho_mat 10 //Percentual de brilho matriz de led

volatile uint8_t contador = 0; //Contador para a matriz de LEDs
volatile bool botao_flag = 1;
volatile uint32_t passado = 0; //Usada para implementar o debouncing

struct repeating_timer timer; //Crie estrutura do tipo timer

int main()
{
    bool clock_setado = set_sys_clock_khz(133000, false); //Seta o clock do sitema
    stdio_init_all(); //Inicia a library stdio (UART)
    init_pins_gpio(); //Inicia os pinos GPIO
    
    if(clock_setado) 
        printf("Clock  setado %ld\n", clock_get_hz(clk_sys)); //Printa a velocidade do CLOCK
        
    offset = pio_add_program(pio, &Matriz_5x5_program); //Carrega o programa no PIO e armazena a posição
    sm = pio_claim_unused_sm(pio, true); //Busca uma máquina vazia
 
    Matriz_5x5_program_init(pio, sm, offset, Mat_pin); //Inica o programa

    desenhar_fig(open, brilho_mat); //Desenha um sorriso

    add_repeating_timer_ms(200, pisca_led, NULL, &timer); //Cria um temporizador (SDK)

    gpio_set_irq_enabled_with_callback(bot_A, GPIO_IRQ_EDGE_FALL, true, botoes_callback); //Interrupção SDK

    gpio_set_irq_enabled_with_callback(bot_B, GPIO_IRQ_EDGE_FALL, true, botoes_callback); //Interrupção SDK

    while(1)
    {    
        int c = getchar_timeout_us(1000); //Fazer leitura da serial
        if(c == '*')
            entrar_modo_gravacao();
        if(botao_flag)
        {
            switch (contador)
            {
            case 0:
                desenhar_fig(fig_0, brilho_mat);
                som_buz(freq_buz, dur_buz);
                botao_flag = 0;
                break;
            case 1:
                desenhar_fig(fig_1, brilho_mat);
                som_buz(freq_buz, dur_buz);
                botao_flag = 0;
                break;
            case 2:
                desenhar_fig(fig_2, brilho_mat);
                som_buz(freq_buz, dur_buz);
                botao_flag = 0;
                break;
            case 3:
                desenhar_fig(fig_3, brilho_mat);
                som_buz(freq_buz, dur_buz);
                botao_flag = 0;
                break;
            case 4:
                desenhar_fig(fig_4, brilho_mat);
                som_buz(freq_buz, dur_buz);
                botao_flag = 0;
                break;
            case 5:
                desenhar_fig(fig_5, brilho_mat);
                som_buz(freq_buz, dur_buz);
                botao_flag = 0;
                break;
            case 6:
                desenhar_fig(fig_6, brilho_mat);
                som_buz(freq_buz, dur_buz);
                botao_flag = 0;
                break;
            case 7:
                desenhar_fig(fig_7, brilho_mat);
                som_buz(freq_buz, dur_buz);
                botao_flag = 0;
                break;
            case 8:
                desenhar_fig(fig_8, brilho_mat);
                som_buz(freq_buz, dur_buz);
                botao_flag = 0;
                break;
            case 9:
                desenhar_fig(fig_9, brilho_mat);
                som_buz(freq_buz, dur_buz);
                botao_flag = 0;
                break;
            default:
                break;
            }
        }

    }
}