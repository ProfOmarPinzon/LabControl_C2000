/* Plantilla Algoritmo de control
 * Laboratorio de Sistemas de Control II
 * Prof. Omar Pinzón-Ardila
 */
//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "FuncionesLab.h"
//
// Prototipos de Function
//
//
//
void main(void)
{
    IniciaTemporizadorLab(); // Ejecuta el Algoritmo de Control cada 500ms
    IniciaGPIO31Lab();

    while (1)
    {
        // Lazo infinito
    }
}

//
// Algoritmo de control
//
__interrupt void
AlgoritmoControlLab(void)
{
    CpuTimer0.InterruptCount++; // Varaible que se utiliza para verificar si entra a la interrupción
    //
    // Toggle GPIO31 cada 200 ms
    //
    GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
    //
    // Reconococe la interrupción y queda a la espera de la siguiente
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
//
// End of File
//

/*  Algoritmo de control

////////////////////////////////////////////////////////
 Input = leerADC(); //Leer la entrada
Setpoint = leerSP(); //Leer el Setpoint

// Cálculo del mando
 ek = Setpoint - Input; // error actual
 pk = Kp * (ek - ek_1); // acción proporcional
 ik = (Ts/1000) * Ki * ek_1; // acción integral
 uk = uk_1 + pk + ik; // mando del controlador

 // limita la salida
 if (uk < -255) uk = -255; // Satura la salida
 if (uk > 255) uk = 255;
 uk = constrain(uk, 0, 255);  // opción con función abajo
 ik = constrain(ik, 0, 255);

 Output = uk;
 escribePWM(); // Escribe el mando

 // memoriza valores previos
 ek_1 = ek;
 uk_1 = uk;

////////////////////////////////////////////////////////

int constrain(int value, int minValue, int maxValue) {
    if (value < minValue) {
        return minValue;
    } else if (value > maxValue) {
        return maxValue;
    } else {
        return value;
    }
}




 */


