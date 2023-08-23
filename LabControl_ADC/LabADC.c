/* Ejemplo ADC
 * Laboratorio de Sistemas de Control II
 * Prof. Omar Pinzón-Ardila
 */

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include <stdint.h>

void setupADC()
{
    InitSysCtrl();  // Inicializa los registros del control del sistema - habilita el reloj de perifericos
    InitAdc();

    EALLOW;
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 1; // Configurar el canal del ADC0 a leer
  //  AdcRegs.ADCSOC0CTL.bit.ACQPS = 6;   // Configurar el número de ciclos de adquisición
  //  AdcRegs.ADCSOC0CTL.bit.TRIGSEL = 0; // Configurar el disparo por software
   //AdcRegs.ADCTRL1.bit.
    EDIS;
}


void startADC()
{
    EALLOW;
    AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1; // Iniciar la conversión ADC
    while(AdcRegs.ADCST.bit.SEQ1_BSY == 1); // Esperar a que la conversión se complete
    EDIS;
}

int main(void)
{
    setupADC();  // Configurar el ADC

    while(1)
    {
        startADC();  // Iniciar la conversión ADC

        // Leer el resultado de la conversión ADC
        uint16_t adcResult = AdcRegs.ADCRESULT0;

        // Realizar operaciones con el valor del ADC

        // Realizar otras tareas si es necesario
    }
}
