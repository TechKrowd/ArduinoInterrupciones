#include "IRLremote.h"
//INTERRUPCIONES EN ARDUINO LEONARDO
const int INTPULSADOR4 = 0;    //interrupcion 0: pin 3
const int INTPULSADOR3 = 1;    //interrupcion 1: pin 2
const int INTPULSADOR1 = 2;    //interrupcion 2: pin 0
const int INTPULSADOR2 = 3;    //interrupcion 3: pin 1

const int interruptIR = 4;                 // Arduino LEONARDO interrupcion 4: Pin 7


const int LED1=8;
const int LED2=9;
const int LED3=10;
const int LED4=11;

uint8_t IRProtocol = 0;  // Variables para recibir los datos
uint16_t IRAddress = 0;
uint32_t IRCommand = 0;

int led=0;
int i;

void setup()
   {     //Serial.begin(115200);  // Fijate en la velocidad
         Serial.println("Startup");

          //PULSADORES
         for(i=0; i<=3; i++){
            pinMode(i, INPUT);
         }

         //LEDS
         for(i=8; i<=11; i++){
            pinMode(i, OUTPUT);
         }
         
         attachInterrupt( INTPULSADOR1, manejadorBoton1, RISING);
         attachInterrupt( INTPULSADOR2, manejadorBoton2, RISING);
         attachInterrupt( INTPULSADOR3, manejadorBoton3, RISING);
         attachInterrupt( INTPULSADOR4, manejadorBoton4, RISING);
         
         IRLbegin<IR_ALL>(interruptIR);
   }

void manejadorBoton1(){
    digitalWrite(LED1, !digitalRead(LED1));
}

void manejadorBoton2(){
    digitalWrite(LED2, !digitalRead(LED2));
}

void manejadorBoton3(){
    digitalWrite(LED3, !digitalRead(LED3));
}

void manejadorBoton4(){
    digitalWrite(LED4, !digitalRead(LED4));
}

void loop()
   { 
         uint8_t oldSREG = SREG;  // Parar las interrupciones
         cli();
         if (IRProtocol)          // Si reconoce el protocolo
            {
                 switch(IRCommand){
                  /* MANDO OPTOMA
                  case 0xe11e: led = LED1; break; //1
                  case 0x11ee: led = LED2; break; //2
                  case 0x6c93: led = LED3; break; //3
                  case 0x619e: led = LED4; break; //4
                  */

                  /* MANDO ENGEL */
                  case 0x4ab5: led = LED1; break; //1
                  case 0x0af5: led = LED2; break; //2
                  case 0x08f7: led = LED3; break; //3
                  case 0x6a95: led = LED4; break; //4
                 }

                 digitalWrite(led, !digitalRead(led));
                 
                 IRProtocol = 0;
            }
         SREG = oldSREG;
         
    }

void IREvent(uint8_t protocol, uint16_t address, uint32_t command)
    {
        IRProtocol = protocol;  // Recogemos los valores y nos volvemos
        IRAddress = address;
        IRCommand = command;
    }
