#include <Keypad.h> // Libreria para el teclado
#include <LiquidCrystal.h> // Libreria para el LCD
#include <Stepper.h>  // Libreria para el manejo de motores paso a paso 
#include <Wire.h>

// LCD
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;   // Pines donde esta conectado el LCD
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const byte Filas = 4;
const byte Columnas = 4;
char Teclas [Filas][Columnas] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'c', '0', '=', '+'}
};
// Teclado
byte FilasPin[Filas] = {23, 25, 27, 29}; // Pines a los que estan conectadas las filas
byte ColumnasPin[Columnas] = {30, 31, 32, 32}; // Pines a los que estan conectadas las columnas
Keypad keypad = Keypad(makeKeymap (Teclas), FilasPin, ColumnasPin, Filas, Columnas);
int i = 0;
char puls = 0;    // Para guardar cuando se oprime una tecla
char arr[10];
int vial = 0;          // Variable para guardar el vial que se ingreso
int Pos_vial = 0;     // Variable para guardar la posición del vial
int Jeringa = 0;     // Variable para guardar la jeringa que se selecciono
float Volumen = 0;  // Variable para guardar el volumen que se seleccione
// Motor DC
const int Switch1 = 19;
const int Switch2 = 20;
const int GiroA = 14;
const int GiroB = 15;
int estado1;    // Lectura del switch1
int estado2;   // Lectura del switch2
int re = 0;   // Sobra
int direction_ = 1;
int speed_ = 0;
// 1er motor paso a paso
#define STEPS 100   // Número de pasoa del motor
Stepper stepper(STEPS, 3, 2, 1, 0);   // Pines en los cuales se conecta usando L293D
const int button1 =  21; // Control de direccion motor paso a paso
int estado3;  // Lectura del botón
// 2do motor paso a paso
#define STEPS1 100   // Número de pasoa del motor
Stepper stepper1(STEPS1, 7, 6, 5, 4);   // Pines en los cuales se conecta usando L293D
float Pasos = 0;    // Variable para guardar los pasos para llegar al vial seleccionado

void setup() {
  lcd.begin(20, 4); // Tamaño de la LCD
  // Motor DC
  pinMode(GiroA, OUTPUT);
  pinMode(GiroB, OUTPUT);
  pinMode(Switch1, INPUT);
  pinMode(Switch2, INPUT);
  //  digitalWrite(GiroA, LOW);
  //  digitalWrite(GiroB, LOW);
  // Motor paso a paso
  pinMode(button1, INPUT_PULLUP);
  stepper.setSpeed(5);
  stepper1.setSpeed(5);

}

void loop() {

  switch (i) {

    case 0:

      lcd.setCursor(4, 1);
      lcd.print(" Oreofusor ");
      delay(1000);
      lcd.clear();

      while (puls != 'c') {

        lcd.setCursor(3, 1);
        lcd.print(" Presiona c ");
        lcd.setCursor(2, 2);
        lcd.print(" para comenzar ");
        puls = keypad.getKey();

      }
      lcd.clear();
      i = 1;
      break;

    case 1: // Selecciona jeringa
      puls = 0;
      while (puls == 0) {

        lcd.setCursor(2, 0);
        lcd.print("Selecciona una ");
        lcd.setCursor(5, 1);
        lcd.print("jeringa ");

        lcd.setCursor(1, 2);
        lcd.print("Opcion 1");
        lcd.setCursor(10, 2);
        lcd.print("presiona 1");

        lcd.setCursor(1, 3);
        lcd.print("Opcion 2");
        lcd.setCursor(10, 3);
        lcd.print("presiona 2");
        puls = keypad.getKey();

      }
      if (puls) {

        if (puls == '1') {    // Jeringa de insulina (1ml)
          Jeringa = 1;
          lcd.clear();
          lcd.setCursor(2, 0);
          lcd.print("Selecciono 1");
          puls = keypad.getKey();
          delay(1000);

        }
        else if (puls == '2') {     // Jeringa de 4ml
          Jeringa = 2;
          lcd.clear();
          lcd.setCursor(2, 0);
          lcd.print("Selecciono 2");
          puls = keypad.getKey();
          delay(1000);

        }
      }
      lcd.clear();
      i = 2;
      break;

    case 2:     // Selecciona volumen

      puls = 0;
      while (puls == 0) {

        puls = keypad.getKey();
        lcd.setCursor(4, 0);
        lcd.print("Selecciona un ");
        lcd.setCursor(10, 1);
        lcd.print(" volumen ");

        if (Jeringa == 1) {     // Jeringa de 1 ml

          lcd.setCursor(4, 0);
          lcd.print("Selecciona un ");
          lcd.setCursor(10, 1);
          lcd.print(" volumen ");
          lcd.setCursor(0, 1);

          lcd.print("Oprime:");
          lcd.setCursor(0, 2);
          lcd.print("1 = 0.2");
          lcd.setCursor(10, 2);
          lcd.print("2 = 0.5");
          lcd.setCursor(0, 3);
          lcd.print("3 = 0.7");
          lcd.setCursor(10, 3);
          lcd.print("4 = 0.9");
          puls = keypad.getKey();

          if (puls) {

            if (puls == '1') {

              Volumen = 0.2;
              lcd.clear();
              lcd.setCursor(2, 0);
              lcd.print("Selecciono 0.2 ml");
              delay(1000);

            }

            else if (puls == '2') {

              Volumen = 0.5;
              lcd.clear();
              lcd.setCursor(2, 0);
              lcd.print("Selecciono 0.5 ml");
              delay(1000);

            }

            else if (puls == '3') {

              Volumen = 0.7;
              lcd.clear();
              lcd.setCursor(2, 0);
              lcd.print("Selecciono 0.7 ml");
              delay(1000);

            }

            else if (puls == '4') {

              Volumen = 0.9;
              lcd.clear();
              lcd.setCursor(2, 0);
              lcd.print("Selecciono 0.9 ml");
              delay(1000);

            }
          }

        }

        if (Jeringa == 2) {     // Jeringa de 4 ml

          lcd.setCursor(4, 0);
          lcd.print("Selecciona un ");
          lcd.setCursor(10, 1);
          lcd.print(" volumen ");

          lcd.setCursor(0, 1);
          lcd.print("Oprime:");
          lcd.setCursor(0, 2);
          lcd.print("5 = 0.5");
          lcd.setCursor(10, 2);
          lcd.print("6 = 1.0");
          lcd.setCursor(0, 3);
          lcd.print("7 = 1.5");
          lcd.setCursor(10, 3);
          lcd.print("8 = 2.0");
          puls = keypad.getKey();

          if (puls) {

            if (puls == '5') {

              Volumen = 0.5;
              lcd.clear();
              lcd.setCursor(2, 0);
              lcd.print("Selecciono 0.5 ml");
              delay(1000);

            }

            else if (puls == '6') {

              Volumen = 1.0;
              lcd.clear();
              lcd.setCursor(2, 0);
              lcd.print("Selecciono 1.0 ml");
              delay(1000);

            }

            else if (puls == '7') {

              Volumen = 1.5;
              lcd.clear();
              lcd.setCursor(2, 0);
              lcd.print("Selecciono 1.5 ml");
              delay(1000);

            }

            else if (puls == '8') {

              Volumen = 2.0;
              lcd.clear();
              lcd.setCursor(2, 0);
              lcd.print("Selecciono 2.0 ml");
              delay(1000);

            }
          }

        }

      }

      i = 3;
      break;

    case 3:   // Selecciona vial

      lcd.setCursor(0, 0);
      lcd.print("Selecciona el vial ");
      lcd.setCursor(4, 1);
      lcd.print("entre 1 y 12 ");
      puls = keypad.getKey();

      if (puls ) {

        if (puls == '=') {

          if (vial > 0 && vial < 13) {  // Para que no acepte numeros mayores a 12, ni menores a 1

            lcd.clear();
            i = 4;

          }
          else {    // Si presiona un numero fuera del rango pide ingresar otro numero

            vial = 0;
            Pos_vial = 0;
            lcd.clear();
          }

        }
        else {

          if (Pos_vial == 1) {

            vial = (vial * 10) + (puls - 48);   // Para volver los caracteres en numeros
            lcd.setCursor(Pos_vial, 3);
            lcd.print(puls);

          }
          else {

            vial = puls - 48;     // Para pasar de HEX a DEC
            lcd.setCursor(0, 2);
            lcd.print("Vial:");
            lcd.setCursor(Pos_vial, 3);
            lcd.print(puls);
            Pos_vial ++;      // Cada que presiona un numero corre un espacio a la derecha

          }

        }

      }

      break;

    case 4:     // Motores, empieza en el purgado

      lcd.setCursor(5, 2);
      lcd.print("Motor DC ");

      // 1era vez
      digitalWrite(GiroA, HIGH);
      digitalWrite(GiroB, LOW);
      delay(3000);
      digitalWrite(GiroA, HIGH);
      digitalWrite(GiroB, HIGH);
      delay(100);
      digitalWrite(GiroA, LOW);
      digitalWrite(GiroB, HIGH);
      delay(3000);
      digitalWrite(GiroA, HIGH);
      digitalWrite(GiroB, HIGH);
      delay(100);
      // 2da vez
      digitalWrite(GiroA, HIGH);
      digitalWrite(GiroB, LOW);
      delay(3000);
      digitalWrite(GiroA, HIGH);
      digitalWrite(GiroB, HIGH);
      delay(100);
      digitalWrite(GiroA, LOW);
      digitalWrite(GiroB, HIGH);
      delay(3000);
      digitalWrite(GiroA, HIGH);
      digitalWrite(GiroB, HIGH);
      delay(100);
      // 3ra vez
      digitalWrite(GiroA, HIGH);
      digitalWrite(GiroB, LOW);
      delay(3000);
      digitalWrite(GiroA, HIGH);
      digitalWrite(GiroB, HIGH);
      delay(100);
      digitalWrite(GiroA, LOW);
      digitalWrite(GiroB, HIGH);
      delay(3000);
      digitalWrite(GiroA, HIGH);
      digitalWrite(GiroB, HIGH);

      i = 5;
      break;

    case 5:   // Motor paso a paso baja la jeringa

      lcd.setCursor(0, 2);
      lcd.print("Motor tornillo");

      stepper.step(-100); // Derecha
      delay(25);

      lcd.clear();
      i = 6;
      break;

    case 6:  // Motor DC recoge el líquido
      estado1 = digitalRead(Switch1);

      lcd.setCursor(4, 2);
      lcd.print("Recogiendo...");

      digitalWrite(GiroA, HIGH);
      digitalWrite(GiroB, LOW);
      delay(6000);

      digitalWrite(GiroA, HIGH);
      digitalWrite(GiroB, HIGH);

      lcd.clear();
      i = 7;
      break;

    case 7:   // Motor tornillo sube la jeringa

      lcd.setCursor(0, 2);
      lcd.print("Motor tornillo");

      stepper.step(100);  // Izquierda
      delay(25);

      lcd.clear();
      i = 8;
      break;

    case 8:   // Motor platillo empieza a girar buscando el vial

      lcd.setCursor(0, 2);
      lcd.print("Motor platillo");

      Pasos = 14.4 * vial;     // Pasos para llegar a cada vial (1.8 grados por paso)
      stepper1.step(Pasos);
      
      lcd.clear();
      i = 9;
      break;

    case 9:   // Motor DC inyecta

      estado2 = digitalRead(Switch2);

      lcd.setCursor(2, 2);
      lcd.print("Inyectando...");

      digitalWrite(GiroA, LOW);
      digitalWrite(GiroB, HIGH);
      delay(4000);

      digitalWrite(GiroA, HIGH);
      digitalWrite(GiroB, HIGH);

      lcd.clear();
      i = 10;
      break;

    case 10:    // Finaliza

      lcd.setCursor(2, 2);
      lcd.print("Fin del ciclo");

      if (Pasos < 200 ) {

        float Total;  // Total de pasos a dar
        int P_Total = 200;    // Total de pasos que hay en una vuelta
        Total = P_Total - Pasos;
        stepper1.step(Total);

      }


      i = 0;
      break;

  }
}

//////////////////////////////Para evitar el rebote del botón /////////////////////////////////

bool debounce()
{
  byte count = 0;
  for (byte j = 0; j < 5; j++) {
    if (digitalRead(button1) == 0)
      count++;
    delay(100);
  }
  if (count > 3)  return 4; //aqui cotamos las veces que es oprimido el boton teiendo en cuenta que haya finalizado el purgado para poder seguir con el proceso
  else           return 0;

}
