/* Ejemplo ADC
 * Laboratorio de Sistemas de Control II
 * Prof. Omar Pinzón-Ardila
 */

// Incluir el archivo de cabecera del MCU
#include "DSP28x_Project.h"

void InitADC(void)
{
    // Configurar el ADC
    EALLOW;
    // Reset del ADC
    AdcRegs.ADCTRL1.bit.RESET = 1;
    // Must wait for ADC reset to take effect
    asm(" RPT #22 || NOP");
    AdcRegs.ADCREFSEL.bit.REF_SEL = 0;  // 0=internal, 1=external

    //--- Power-up the ADC
    AdcRegs.ADCTRL3.all = 0x00EC; // Power-up reference and main ADC
    // bit 15-8      0's:    reserved
    // bit 7-6       11:     ADCBGRFDN, reference power, 00=off, 11=on
    // bit 5         1:      ADCPWDN, main ADC power, 0=off, 1=on
    // bit 4-1       0110:   ADCCLKPS, clock prescaler, FCLK=HSPCLK/(2*ADCCLKPS)
    // bit 0         0:      SMODE_SEL, 0=sequential sampling, 1=simultaneous sampling

    DELAY_US(5000); // Retardo 5ms antes de utilizar el ADC

    AdcRegs.ADCMAXCONV.all = 0x0000;  // Númerod e conversiones
    // bit 15-7      0's:    reserved
    // bit 6-4       000:    MAX_CONV2 value
    // bit 3-0       0000:   MAX_CONV1 value (0 means 1 conversion)
    // For CPU servicing of ADC, we are only doing 1 conversion in the
    // sequence.  So, we only need to configure the first channel
    // selection in the sequence.  All other channel selection fields
    // are don't cares in this example.

    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0;    // Convert Channel 0
//    AdcRegs.ADCSOC0CTL.bit.TRIGSEL = 0; // Seleccionar fuente de trigger para conversión (software)
//    AdcRegs.ADCSOC0CTL.bit.CHSEL = ADC_CHANNEL; // Seleccionar canal ADC
//    AdcRegs.ADCSOC0CTL.bit.ACQPS = 6; // Configurar el número de ciclos de conversión

    AdcRegs.ADCASEQSR.bit.SEQ_CNTR =1;
AdcRegs.ADCTRL1.bit.ACQ_PS =1;
    EDIS;
}

Uint16 ReadADC(void)
{
    Uint16 result;

    // Iniciar conversión ADC
    AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;
    // Esperar a que finalice la conversión
    while (AdcRegs.ADCST.bit.EOS_BUF1 == 1)
        ;
    // Leer el resultado del ADC
    result = AdcRegs.ADCRESULT0;

    return result;
}

int main(void)
{
    // Configurar el control del sistema
    InitSysCtrl();
    InitADC(); // Inicializar el ADC

    while (1)
    {
        // Leer el valor del ADC
        Uint16 adcValue = ReadADC();

        //...
        // Hacer algo con el valor leído
        // ...

        DELAY_US(100000); // Retardo de 100 ms
    }
}

