float factor = 0.75;    // coeficiente para filtro pasa bajos
float maximo = 0.0;   // para almacenar valor maximo 
int minimoEntreLatidos = 300; // 300 mseg. de tiempo minimo entre latidos
float valorAnterior = 500;  // para almacenar valor previo
int latidos = 0;    // contador de cantidad de latidos

void setup() {
  pinMode(13, OUTPUT);    // LED incorporado en pin 13 como salida
  Serial.begin(9600);   // inicializacion de monitor serie a 9600 bps
  Serial.println("Iniciando mediciones"); // texto a mostrar
}

void loop() {
  static unsigned long tiempoLPM = millis();  // tiempo Latidos Por Minuto con
            // valor actual devuelto por millis()
  static unsigned long entreLatidos = millis(); // tiempo entre Latidos con
            // valor actual devuelto por millis()

  int valorLeido = analogRead(A0);    // lectura de entrada analogica A0

  float valorFiltrado = factor * valorAnterior + (1 - factor) * valorLeido; // filtro pasa bajos
  float cambio = valorFiltrado - valorAnterior;   // diferencia entre valor filtrado y
              // valor anterior
  valorAnterior = valorFiltrado;    // actualiza valor anterior con valor filtrado

  if ((cambio >= maximo) && (millis() > entreLatidos + minimoEntreLatidos)) { // si cambio es
          // es mayor o igual a maximo y pasaron al menos 300 mseg.
    maximo = cambio;      // actualiza maximo con valor de cambo
    digitalWrite(13, HIGH);   // enciende LED incorporado
    entreLatidos = millis();    // actualiza variable entreLatidos con millis()
    latidos++;        // incrementa latidos en uno
  }
  else {        // condicion falsa del condicional
    digitalWrite(13, LOW);    // apaga LED incorporado
  }
  
  maximo = maximo * 0.97;   // carga maximo como el 97 por ciento de su propio
          // valor para dejar decaer y no perder pulsos

  if (millis() >= tiempoLPM + 15000) {    // si transcurrieron al menos 15 segundos
    Serial.print("Latidos por minuto: "); // muestra texto
    Serial.println(latidos * 4);    // muestra variable latidos multiplicado por 4
    latidos = 0;        // coloca contador de latidos en cero
    tiempoLPM = millis();     // actualiza variable con valor de millis()
  }

  delay(50);        // demora entre lecturas de entrada analogica
}
