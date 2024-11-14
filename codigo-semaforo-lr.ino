// Classe para representar o semáforo
class Semaforo {
  int vermelho;
  int amarelo;
  int verde;
  int currentCycle = 1;

public:
  // Construtor para inicializar as portas
  Semaforo(int p_vermelho, int p_amarelo, int p_verde) {
    vermelho = p_vermelho;
    amarelo = p_amarelo;
    verde = p_verde;
  }

  // Método para configurar as portas
  void configurar() {
    pinMode(vermelho, OUTPUT);
    pinMode(amarelo, OUTPUT);
    pinMode(verde, OUTPUT);
  }

  // Método para definir o sinal no vermelho
  void sinalVermelho() {
    digitalWrite(vermelho, HIGH);
    digitalWrite(amarelo, LOW);
    digitalWrite(verde, LOW);
  }

  // Método para definir o sinal no amarelo
  void sinalAmarelo() {
    digitalWrite(vermelho, LOW);
    digitalWrite(amarelo, HIGH);
    digitalWrite(verde, LOW);
  }

  // Método para definir o sinal no verde
  void sinalVerde() {
    digitalWrite(vermelho, LOW);
    digitalWrite(amarelo, LOW);
    digitalWrite(verde, HIGH);
  }

  void desligado() {
    digitalWrite(vermelho, LOW);
    digitalWrite(amarelo, LOW);
    digitalWrite(verde, LOW);
  }

  void verifyCycle() {
    int analogValue = analogRead(4);
    
    Serial.print("Analog Value = ");
    Serial.println(analogValue);

    if (analogValue < 200) {
      cicloNoturno();
      return;
    }

    if (currentCycle == 1) {
      cicloAberto();
      currentCycle = 0;
      return;
    }

    cicloFechado();
  }

  void cicloAberto() {
    sinalVerde();
    delay(4000);

    sinalAmarelo();
    delay(2000);
  }

  void cicloFechado() {
    sinalVermelho();
  }

  void cicloNoturno() {
    sinalAmarelo();
    delay(1000);
    desligado();
  }

};

// Instanciando o semáforo
Semaforo semaforo(2, 32, 33);

void setup() {
  semaforo.configurar();  // Aciona a função de configuração das portas do semáforo

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600); 
}

void loop() {
  semaforo.verifyCycle();
}
