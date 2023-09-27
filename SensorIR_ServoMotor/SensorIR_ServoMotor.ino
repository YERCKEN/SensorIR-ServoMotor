#include <IRremote.h>
#include <Servo.h>

//PIN DEL SENSOR IR
const byte PIN_RECEPTOR_INFRARROJO = 11;


Servo servoHorizontal;
Servo servoVertical;

// ANGULOS INICIALES
int anguloHorizontalInicial = 90; // Ángulo horizontal inicial
int anguloVerticalInicial = 90;   // Ángulo vertical inicial
// INCREMENTO
int incrementoAngulo = 10;   

void setup()
{
  //VELOCIDAD
   Serial.begin(9600);
   //HABILITACIÓN RECEPTOR Y LED DEL MÓDULOO
   IrReceiver.begin(PIN_RECEPTOR_INFRARROJO, ENABLE_LED_FEEDBACK);

   //PIN servo horizontal
   servoHorizontal.attach(2);  
   //PIN servo vertical
   servoVertical.attach(3);   

   //ANGULOS INICIALES
   servoHorizontal.write(anguloHorizontalInicial);
   servoVertical.write(anguloVerticalInicial);     
}

void loop(){
  
   if (IrReceiver.decode())
   {
      //VALOR DE ENTRADA
      int valor = IrReceiver.decodedIRData.command;
      // DATA DE DIRECCIÓN
      String direccion;

      //CONTROL ======================================================================================

      // Derecha ----------------------------------------------
      if (valor == 67)  
        {
          anguloHorizontalInicial += incrementoAngulo;
          if (anguloHorizontalInicial  > 180) {
            anguloHorizontalInicial = 180;
          }
            
          servoHorizontal.write(anguloHorizontalInicial);
          direccion = "Derecha  (ángulo: " + String(anguloHorizontalInicial) + ")";
        }

      // Izquierda ----------------------------------------------
      else if (valor == 68)  
        {
          anguloHorizontalInicial -= incrementoAngulo;
          if (anguloHorizontalInicial < 0) {
            anguloHorizontalInicial = 0;
          }
          servoHorizontal.write(anguloHorizontalInicial);
          direccion = "Izquierda (ángulo: " + String(anguloHorizontalInicial) + ")";
        }

      // Arriba ----------------------------------------------
      else if (valor == 70)  
        {
          anguloVerticalInicial += incrementoAngulo;
          if (anguloVerticalInicial > 180) {
            anguloVerticalInicial = 180;
          }
          servoVertical.write(anguloVerticalInicial);
          direccion = "Arriba (ángulo: " + String(anguloVerticalInicial) + ")";
        }

      // Abajo ----------------------------------------------
      else if (valor == 21)  
        {
          anguloVerticalInicial -= incrementoAngulo;
          if (anguloVerticalInicial < 0) {
            anguloVerticalInicial = 0;
          }
          servoVertical.write(anguloVerticalInicial);
          direccion = "Abajo (ángulo: " + String(anguloVerticalInicial) + ")";
        }
      else
        {
          direccion = "Desconocida";
        }
      
      Serial.println("Dirección: " + direccion);

      IrReceiver.resume();
   }
}
