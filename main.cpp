/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


#include "DisplayController.h"

// Define los pines según tu placa
#define SCLK_PIN D2
#define DIO_PIN D3



int main() {
    DisplayController display(SCLK_PIN, DIO_PIN);
    display.iniciarContador();
    char c;
    while (true) {
        c++;
        if (c==9) c=0;
        display.send_digit(c, 2);
        printf("%04u\n\r",c);
        ThisThread::sleep_for(50ms);
    }
}