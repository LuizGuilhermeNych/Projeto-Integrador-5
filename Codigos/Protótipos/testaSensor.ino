
#define temporizador 10

//Definição dos pinos que irão operar o LED e sensor
const int led = 26;
const int sensor = 27;

// Variáveis para tratamento de intervalos
unsigned long agora = millis();
unsigned long ultimoSinal = 0;
boolean iniciaContador = false;

// Verifica se um movimento foi detectado, então acende o LED e inicia uma contagem
void IRAM_ATTR detectaMovimento() {
  Serial.println("Movimento detectado!");
  digitalWrite(led, HIGH);
  iniciaContador = true;
  ultimoSinal = millis();
}

void setup() {

  //Inicializando a porta serial
  Serial.begin(115200);
  
  // Inicializando o sensor
  pinMode(sensor, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensor), detectaMovimento, RISING);

  // Inicializa o LED em LOW
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {

  // Momento presente
  agora = millis();
  
  //Desliga o LED assim que o tempo definido no contador termina
  if(iniciaContador && (agora - ultimoSinal > (temporizador*1000))) {
    Serial.println("Sem movimento...");
    digitalWrite(led, LOW);
    iniciaContador = false;
  }
}
