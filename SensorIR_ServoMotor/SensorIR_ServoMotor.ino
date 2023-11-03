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
int incrementoAngulo = 5;   
int ultimaTeclaPresionada = 0;

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
  
  // Control del servoHorizontal con el receptor IR
  if (IrReceiver.decode()) {
    int valor = IrReceiver.decodedIRData.command;

    if (valor == 67) {
      // Derecha
      anguloHorizontalInicial += incrementoAngulo;
      if (anguloHorizontalInicial > 180) {
        anguloHorizontalInicial = 180;
      }
      ultimaTeclaPresionada = 67; // Actualiza la última tecla
    } else if (valor == 68) {
      // Izquierda
      anguloHorizontalInicial -= incrementoAngulo;
      if (anguloHorizontalInicial < 0) {
        anguloHorizontalInicial = 0;
      }
      ultimaTeclaPresionada = 68; // Actualiza la última tecla
    } else if (valor == 0) {
      // Si el valor es 0, mueve en la dirección de la última tecla presionada
      if (ultimaTeclaPresionada == 67) {
        anguloHorizontalInicial += incrementoAngulo;
        if (anguloHorizontalInicial > 180) {
          anguloHorizontalInicial = 180;
        }
      } else if (ultimaTeclaPresionada == 68) {
        anguloHorizontalInicial -= incrementoAngulo;
        if (anguloHorizontalInicial < 0) {
          anguloHorizontalInicial = 0;
        }
      }
    }

    servoHorizontal.write(anguloHorizontalInicial);

    Serial.print("Dirección: ");
    Serial.print((ultimaTeclaPresionada == 67) ? "Derecha" : "Izquierda");
    Serial.print(", Ángulo: ");
    Serial.println(anguloHorizontalInicial);

    Serial.print("Valor IR recibido: ");
    Serial.println(valor);

    IrReceiver.resume(); // Continuar escuchando
  }
}
