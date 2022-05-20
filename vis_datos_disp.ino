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

////////////////////////////////////

void setup() 
{

    // Config. del puerto serie
    Serial.begin(115200);

    // Config. del LCD
    lcd.begin(16, 2);
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Vel    :   0 m/s");
    lcd.setCursor(0, 1);
    lcd.print("Disparos : 0    ");
 
}

void loop() 
{

    bool error_com;
    bool actualizar_display;
    
    error_com = false;
    actualizar_display = false;


    // Lectura del puerto serie
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
            actualizar_display = true;
            verif = velocidad.D[0] + velocidad.D[1] + cantidad.D[0] + cantidad.D[1];
            if (verif == 0xFF)
                verif = 0xFE;

            if (verif != dato)
                error_com = true;
            estado = SYNC1;
            break;

        default:
            estado = SYNC1;
            break;

    }

    if (actualizar_display)
    {

        if (error_com)
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Error comunicion");
        }

        else
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Vel    : ");
            lcd.print(velocidad.val);
            lcd.print(" m/s");
            lcd.setCursor(0, 1);
            lcd.print("Disparos : ");
            lcd.print(cantidad.val);
        }
    }

}


/* vim: set ts=4 sw=4 tw=79 et :*/
