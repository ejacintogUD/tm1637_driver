// DisplayController.cpp
#include "DisplayController.h"

#define escritura       0x40
#define poner_brillo    0x88
#define dir_display     0xC0
#define brillo          5     // brillo por defecto

DisplayController::DisplayController(PinName pin_sclk, PinName pin_dio)
    : sclk(pin_sclk), dio(pin_dio) {
    // Inicializar variables
    for (int i = 0; i < 4; i++) {
        digit[i] = 0;
 }
}


void DisplayController::iniciarContador() {
    printf("Arranque del programa\n\r");
    send_data(0);
    send_bright(brillo);
    
}

void DisplayController::condicion_start() {
    sclk = 1;
    dio.output();
    dio = 1;
    wait_us(1);
    dio = 0;
    sclk = 0;
}

void DisplayController::condicion_stop() {
    sclk = 0;
    dio.output();
    dio = 0;
    wait_us(1);
    sclk = 1;
    dio = 1;
}

void DisplayController::send_byte(char data) {
    dio.output();
    for (int i = 0; i < 8; i++) {
        sclk = 0;
        dio = (data & 0x01) ? 1 : 0;
        data >>= 1;
        sclk = 1;
    }
    // Esperar el ack
    dio.input();
    sclk = 0;
    wait_us(1);
    // Espera la señal de ACK
    if (dio == 0) {
        sclk = 1;
        sclk = 0;
    }
}

void DisplayController::send_data(int number) {
    condicion_start();
    send_byte(escritura);
    condicion_stop();
    condicion_start();
    send_byte(dir_display);

    // Descomponer el número en dígitos y enviar al display Big Endian
    for (int i = 0; i < 4; i++) {
        digit[i] = number % 10;
        number /= 10;
    }
    // Enviar los dígitos desde el más significativo al menos  Little Endian
    for (int j = 3; j > -1; j--) {
       
        send_byte(digitToSegment[digit[j]]);
    }

    condicion_stop();
  
}

void DisplayController::send_bright(int bright){
    condicion_start();
    send_byte(poner_brillo + bright);
    condicion_stop();
}

void DisplayController::send_digit(char digit, int position){

    condicion_start();
    send_byte(escritura);
    condicion_stop();
    condicion_start();
    send_byte(dir_display + (3-position)); // Esta al contrario 
    send_byte(digitToSegment[digit]);
    condicion_stop();

}
