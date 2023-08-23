/* Ejemplo GPIO
 * Laboratorio de Sistemas de Control II
 * Prof. Omar Pinzón-Ardila
 */

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

#define DELAY_CYCLES 10000000  // Definir el número de ciclos de retardo

void setupGPIO()
{
    EALLOW;
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0; // Configurar GPIOA como I/O digital
    GpioCtrlRegs.GPADIR.bit.GPIO31=1; // Configurar el pin como salida
    EDIS;
}

void activatePort()
{
    GpioDataRegs.GPASET.bit.GPIO31=1; // Activar el pin
}

void deactivatePort()
{
    GpioDataRegs.GPACLEAR.bit.GPIO31=1; // Desactivar el pin
}

void delay()
{
    volatile float i;
    for(i = 0; i < DELAY_CYCLES; i++) {}
}

int main(void)
{
    setupGPIO();  // Configurar el puerto GPIO

    while(1)
    {
        activatePort();    // Activar el pin en GPIO
        delay();           // Retardo entre encendido y apagado

        deactivatePort();  // Desactivar el pin en GPIO
        delay();           // Retardo entre apagado y siguiente encendido
    }
}


