// DisplayController.h
#ifndef DISPLAYCONTROLLER_H
#define DISPLAYCONTROLLER_H

#include "mbed.h"

class DisplayController {
public:
    // Constructor
    DisplayController(PinName pin_sclk, PinName pin_dio);

    // Método para iniciar el contador
    void iniciarContador();
    void send_data(int number);
    void send_bright(int number); // numero entre 0 - 7
    void send_digit(char digit, int position); // enviar posicion especifica del display  0-3

private:
    // Métodos privados
    void condicion_start();
    void condicion_stop();
    void send_byte(char data);
    // Variables privadas
    DigitalOut sclk;
    DigitalInOut dio;
  
    char digit[4];
    const char digitToSegment[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
};

#endif // DISPLAYCONTROLLER_H