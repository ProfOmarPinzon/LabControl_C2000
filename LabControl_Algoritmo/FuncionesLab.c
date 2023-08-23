/*
 * FuncionesLab.c
 *
 *  Created on: 9 jun. 2023
 *      Author: omar
 */
//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

#define PERIODO_MUESTREO 200000 // Periodo de muestreo 200ms


__interrupt void AlgoritmoControlLab(void);

// Función inicialización función control
void IniciaTemporizadorLab()
{
//
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2833x_SysCtrl.c file.
//
    InitSysCtrl();

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
//
    DINT;

//
// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the DSP2833x_PieCtrl.c file.
//
    InitPieCtrl();

//
// Disable CPU interrupts and clear all CPU interrupt flags:
//
    IER = 0x0000;
    IFR = 0x0000;

//
// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in DSP2833x_DefaultIsr.c.
// This function is found in DSP2833x_PieVect.c.
//
    InitPieVectTable();

//
// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
//
    EALLOW;
    // This is needed to write to EALLOW protected registers
    PieVectTable.TINT0 = &AlgoritmoControlLab;
    EDIS;
    // This is needed to disable write to EALLOW protected registers

//
// Step 4. Initialize the Device Peripheral. This function can be
//         found in DSP2833x_CpuTimers.c
//
    InitCpuTimers();   // For this example, only initialize the Cpu Timers
#if (CPU_FRQ_150MHZ)
//
// Configure CPU-Timer 0 to interrupt every 500 milliseconds:
// 150MHz CPU Freq, 50 millisecond Period (in uSeconds)
//
    ConfigCpuTimer(&CpuTimer0, 150, PERIODO_MUESTREO);
#endif
#if (CPU_FRQ_100MHZ)
//
// Configure CPU-Timer 0 to interrupt every 500 milliseconds:
// 100MHz CPU Freq, 50 millisecond Period (in uSeconds)
//
ConfigCpuTimer(&CpuTimer0, 100, PERIODO_MUESTREO);
#endif

//
// To ensure precise timing, use write-only instructions to write to the
// entire register. Therefore, if any of the configuration bits are changed
// in ConfigCpuTimer and InitCpuTimers (in DSP2833x_CpuTimers.h), the
// below settings must also be updated.
//

//
// Use write-only instruction to set TSS bit = 0
//
    CpuTimer0Regs.TCR.all = 0x4000;

//
// Step 5. User specific code, enable interrupts
//

//
// Enable CPU INT1 which is connected to CPU-Timer 0:
//
    IER |= M_INT1;

//
// Enable TINT0 in the PIE: Group 1 interrupt 7
//
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

//
// Enable global Interrupts and higher priority real-time debug events
//
    EINT;
    // Enable Global interrupt INTM
    ERTM;
    // Enable Global realtime interrupt DBGM
}

void IniciaGPIO31Lab()
{
    //
    // Step 2. Initialize GPIO:
    // This example function is found in the DSP2833x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    //InitGpio();  // Skipped for this example

//
// Configure GPIO31 as a GPIO output pin
//
    EALLOW;
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;
    EDIS;
}

