#include "mbed.h"
#include "stm32746g_discovery_lcd.h"

DigitalIn button(BUTTON1);
DigitalOut led(LED1);
volatile bool running = true;
Thread thread_LED;
Thread thread_LCD;
Thread thread_TLAC;


void inicializace_display(){
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
}

void led_thread()
{
    while (true) {
        led = !led;
        ThisThread::sleep_for(500);
    }
}

void button_kontrola()
{
    while(true){
        if(button){  
            running = false;    
            BSP_LCD_Clear(LCD_COLOR_RED);
            BSP_LCD_SetBackColor(LCD_COLOR_RED);
            BSP_LCD_SetTextColor(LCD_COLOR_ORANGE);
            BSP_LCD_DisplayStringAt(0, 100, (uint8_t *)"Stiskli jste tlacitko! >:|", CENTER_MODE);
            HAL_Delay(1000);
            running = true;
        }   
    }
}

void display_thread()
{
    while(true){
        while(running){
            BSP_LCD_Clear(LCD_COLOR_BLACK);
            BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
            BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
            BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
            BSP_LCD_DisplayStringAt(0, 100, (uint8_t *)"Ahoj!", CENTER_MODE);
            BSP_LCD_DisplayStringAt(0, 140, (uint8_t *)"Ja jsem tvuj superpomocnik!", CENTER_MODE);
            BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
            BSP_LCD_SetTextColor(LCD_COLOR_RED);
            BSP_LCD_DisplayStringAt(0, 200, (uint8_t *)"Neklikejte na tlacitko!", CENTER_MODE);
            HAL_Delay(1000);
        }
    }
}



int main()
{
    inicializace_display();
    thread_LED.start(led_thread);
    thread_TLAC.start(button_kontrola);
    thread_LCD.start(display_thread);
    while(true);
}
