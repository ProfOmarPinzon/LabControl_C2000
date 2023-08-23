/* Ejemplo PWM
 * Laboratorio de Sistemas de Control II
 * Prof. Omar Pinzón-Ardila
 */

//  External Connections
//  - EPWM1A is on GPIO0
//  - EPWM1B is on GPIO1
//  - EPWM2A is on GPIO2
//  - EPWM2B is on GPIO3
//  - EPWM3A is on GPIO4
//  - EPWM3B is on GPIO5

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

// Defines that configure the period for each timer
//
#define EPWM1_TIMER_TBPRD  3000  // Registro del perido
#define EPWM1_CMPA         1500

void setupPWM()
{
    InitSysCtrl();  // Inicializa los registros del control del sistema - habilita el reloj de perifericos

    InitEPwm1Gpio(); // Inicializa los pines del GPIO - Ver external Connection

    EALLOW;
    // Configura Módulo EPWM 1
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Modo asimétrico contador en modo up
    EPwm1Regs.TBPRD = EPWM1_TIMER_TBPRD; // Establecer el periodo del PWM

    // Set actions
    EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET;      // Set PWM1A on Zero
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;    // Clear PWM1A on event A, up count
    EDIS;
}

int main(void)
{
    setupPWM();  // Configurar el PWM

    EPwm1Regs.CMPA.half.CMPA = EPWM1_CMPA; // Asignar valor de comparación

    while (1)
    {
    // Realizar otras tareas si es necesario
    }
}
