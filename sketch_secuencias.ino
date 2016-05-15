//Suponiendo que tengas estos leds: rojo, verde, azul, amarillo
//conectados de la siguiente forma:
int ROJO = 3;
int VERDE = 4;
int AZUL = 5;
int AMARILLO = 6;
//si quieres más led con otros colores puedes añadirlos siempre que tengas pines libres

//y un pulsador conectado a un pin digital que soporte interrupciones
//el arduino UNO, por ejemplo, soporta en el 2 y en el 3
int PULSADOR = 2;

//en un array bidimensional defines las secuencias:
int secuencias [4][6]={ //en este ejemplo defino 4 secuencias con 6 colores cada una
  {ROJO, VERDE, AMARILLO, AZUL, ROJO, AZUL}, //esto es una secuencia
  {VERDE, AMARILLO, ROJO, VERDE, AZUL, AMARILLO},
  {AZUL, VERDE, AMARILLO, ROJO, AMARILLO, VERDE},
  {AZUL, VERDE, AZUL, AMARILLO, AZUL, ROJO}
  //puedes añadir más separandolas por comas
};

int i;
volatile int sec_seleccionada=0; //numero de secuencia que se va a usar (de 0 a n-1)
//en este ejemplo son 4 secuencias por lo que se numerarian de 0 a 3 para que coincida 
//con el indice del array (filas)
void setup() {
  pinMode(ROJO, OUTPUT);
  pinMode(VERDE, OUTPUT);
  pinMode(AZUL, OUTPUT);
  pinMode(AMARILLO, OUTPUT);

  pinMode(PULSADOR, INPUT);

//esta instrucción asocia la función manejadora a la iterrupción que se producirá
//cada vez que se presione el pulsador, es decir, cada vez que pase de LOW a HIGH el pin 2
  attachInterrupt(digitalPinToInterrupt(PULSADOR), manejadora, RISING);
}

void manejadora(){
  //cada vez que se presiona el pulsador se incrementa esta variable de forma que
  //se cambia a la siguiente secuencia
  sec_seleccionada++;
  if(sec_seleccionada==4){ //si llega a 4 (que son las que yo he definido) ya se han hecho todas y se empieza de nuevo
    sec_seleccionada=0;
  }
}

void loop() {
  //he puesto 6 colores a cada secuencia, la condición del bucle for dependerá de eso
  for(i=0; i< 6; i++){
    //la variable sec_seleccionada varia cada vez que se presiona el pulsador
    digitalWrite (secuencias [sec_seleccionada][i], HIGH);
    delay(400); //el tiempo que quieras que esté el led iluminado
    digitalWrite (secuencias [sec_seleccionada][i], HIGH);
    //el tiempo que quieras que estón los leds apagados, 
    delay(300); //si no quieres que pase un tiempo entre led y led quita esta linea
    
  }

}
