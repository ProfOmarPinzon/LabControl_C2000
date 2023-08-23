/*
 * LabACDv2.c
 *
 *  Created on: 8 jun. 2023
 *      Author: omar
 */

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

void configureADC(void);
void configureGPIO(void);

void main(void)
{
    // Configurar ADC y GPIO
    configureADC();
    configureGPIO();

    // Bucle principal
    while (1)
    {
        // Leer el valor del ADC
        Uint16 adcValue = AdcaResultRegs.ADCRESULT0;

        // Realizar acciones con el valor del ADC (por ejemplo, mostrarlo por UART o realizar cálculos)

        // Retardo
        DELAY_US(100000); // Ajusta el valor del retardo según tus necesidades
    }
}

void configureADC(void)
{
    // Habilitar ADC Clock
    EALLOW;
    CpuSysRegs.PCLKCR13.bit.ADC_A = 1;
    EDIS;

    // Configurar el ADC
    EALLOW;
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6; // Configurar el divisor del reloj del ADC (fADCCLK = fSYSCLKOUT / (2 * (ADCCTL2.PRESCALE + 1)))
    AdcRegs.

    AdcaRegs.ADCCTL1.bit.ADCPWDN = 1; // Encender el ADC
    DELAY_US(1000); // Esperar por lo menos 1ms para que el ADC se encienda

    // Configurar los modos de disparo y muestreo
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 0; // Configurar el canal de entrada del SOC0 (por ejemplo, canal 0)
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 5; // Configurar el disparador del SOC0 (por ejemplo, EPWM1SOCA)
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = 39; // Configurar el periodo de adquisición (muestreo)

    // Configurar el resultado del ADC
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1; // Configurar la posición del pulso de interrupción
    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0; // Configurar el SOC0 como fuente de interrupción
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1; // Habilitar la interrupción del ADC
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1; // Habilitar la interrupción del ADC en el PIE
    IER |= M_INT1; // Habilitar la interrupción del ADC en el CPU
    EINT; // Habilitar las interrupciones globales

    EDIS;
}

void configureGPIO(void)
{
    EALLOW;

    // Configurar el pin del canal de entrada del ADC (por ejemplo, pin 0)
    GpioCtrlRegs.AIOMUX1.bit.AIO2 = 2; // Seleccionar el modo de pin para el ADC (por ejemplo, modo 2)
    GpioCtrlRegs.AIODIR.bit.AIO2 = 0; // Configurar el pin como entrada

    EDIS;
}

// Rutina de interrupción del ADC
interrupt void adcInterrupt(void)
{
    // Realizar acciones necesarias en la interrupción del ADC

    // Limpiar la bandera de interrupción del ADC
    AdcaRegs.ADCINTFLG
