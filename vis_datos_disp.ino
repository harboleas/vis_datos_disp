// Display de los datos (velocidad y cantidad)
// del disparo del canon

#include <LiquidCrystal.h>

// Definicion de variables y objetos
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

enum Estados {
    SYNC1, 
    SYNC2, 
    VEL0, 
    VEL1, 
    DISP0, 
    DISP1, 
    VERIF_ERROR};

Estados estado = SYNC1;
byte dato, verif;

union {
    unsigned int val;
    byte D[2];
    } velocidad, cantidad;

bool error_com;
bool actualizar_display;
 
// Para evitar el filckering en el display
unsigned int vel_anterior, cant_anterior;
bool error_anterior;
//////////////////////////////////////////

////////////////////////////////////

void setup() 
{

    // Config. del puerto serie
    Serial.begin(115200);

     // Config. del LCD
    delay(1000);
    lcd.begin(16, 2);
 
    // Info inicial
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Vel: 0 m/s      ");
    lcd.setCursor(0, 1);
    lcd.print("Disparos: 0     ");
 
    error_com = false;
    actualizar_display = false;
    error_anterior = false;
}

void loop() 
{

    // Lectura del puerto serie
    while(!Serial.available());   // Espera hasta q haya datos
    dato = Serial.read();

    // FSM para la decodificacion de la trama
    switch(estado)
    {
        case SYNC1:
            if (dato == 0xFF)
                estado = SYNC2;
            break;

        case SYNC2:
            if (dato == 0xFF)
                estado = VEL0;
            else
                estado = SYNC1;
            break;

        case VEL0:
            velocidad.D[0] = dato;
            estado = VEL1;
            break;

        case VEL1:
            velocidad.D[1] = dato;
            estado = DISP0;
            break;

        case DISP0:
            cantidad.D[0] = dato;
            estado = DISP1;
            break;

        case DISP1:
            cantidad.D[1] = dato;
            estado = VERIF_ERROR;
            break;

        case VERIF_ERROR: 
            verif = velocidad.D[0] + velocidad.D[1] + cantidad.D[0] + cantidad.D[1];
            if (verif == 0xFF)
                verif = 0xFE;

            if (verif != dato)
                error_com = true;
            else
                error_com = false;

            estado = SYNC1;
            actualizar_display = true;
            break;

        default:
            estado = SYNC1;
            break;

    }

    if (actualizar_display)
    {

        // Actualizo solo en los cambios de info.. para evitar
        // el flickering q se produce en el display

        if (error_com && !error_anterior)
        {
            lcd.clear();
            lcd.setCursor(4, 0);
            lcd.print("Error de");
            lcd.setCursor(2, 1);
            lcd.print("comunicacion");

            error_anterior = true;
        }

        else if (!error_com && error_anterior)
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Vel: ");
            lcd.print(velocidad.val);
            lcd.print(" m/s");
            lcd.setCursor(0, 1);
            lcd.print("Disparos: ");
            lcd.print(cantidad.val);

            vel_anterior = velocidad.val;
            cant_anterior = cantidad.val;
            error_anterior = false;
        }
        else if (!error_com)
        {
            if (velocidad.val != vel_anterior || cantidad.val != cant_anterior)
            {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Vel: ");
                lcd.print(velocidad.val);
                lcd.print(" m/s");
                lcd.setCursor(0, 1);
                lcd.print("Disparos: ");
                lcd.print(cantidad.val);

                vel_anterior = velocidad.val;
                cant_anterior = cantidad.val;
            }
 
        }

        actualizar_display = false;
    }

}


/* vim: set ts=4 sw=4 tw=79 et :*/
