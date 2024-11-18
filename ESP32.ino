#include <WiFi.h>
const char* WIFI_SSID = "SATC IOT";
const char* WIFI_PASSWORD = "IOT2024@#";
const int pinoSensorCorrente = 34;
const int pinoSensorTensao = 32;

#include <Firebase_ESP_Client.h>
#define FIREBASE_HOST "https://monitoramente-de-energia---iot-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "AIzaSyD36ECWmYCzAT0gut4v0o3XLmykE7oZTj0"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#define LARGURA_TELA 128  
#define ALTURA_TELA 64 
#define OLED_RESET     -1
Adafruit_SSD1306 display(LARGURA_TELA, ALTURA_TELA, &Wire, OLED_RESET);
#define SSD1306_I2C_ADDRESS 0x3C
#define ENDERECO_TELA 0x3C

#define EMAIL_USUARIO "azanettev2@gmail.com"
#define SENHA_USUARIO "galinha"
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Variáveis para controle de tempo
unsigned long ultimaVerificacaoWiFi = 0;
unsigned long ultimaLeituraSensores = 0;
unsigned long ultimaAtualizacaoTela = 0;
const long intervaloReconexaoWiFi = 1000;  // Intervalo para tentar reconectar o Wi-Fi (1 segundo)
const long intervaloLeituraSensores = 2000;    // Intervalo para ler os sensores (2 segundos)
const long intervaloAtualizacaoTela = 2500; // Intervalo para atualizar o display (2.5 segundos)

// Variáveis globais para armazenar os dados
float tensao = 0;
float corrente = 0;
float potencia = 0;

void setup() {
  Serial.begin(115200);
  pinMode(pinoSensorCorrente, INPUT);
  pinMode(pinoSensorTensao, INPUT);

  // Conexão Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  

  // Aguardar conexão Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(3000);
    Serial.print("."); 
  }
  Serial.println("Conectado ao WiFi!");

  // Configuração do Firebase
  auth.user.email = EMAIL_USUARIO;
  auth.user.password = SENHA_USUARIO;
  config.api_key = FIREBASE_AUTH;
  config.database_url = FIREBASE_HOST;
  Firebase.begin(&config, &auth);

  if (Firebase.ready()) {
    Serial.println("Firebase inicializado com sucesso!");
  } else {
    Serial.println("Falha na inicialização do Firebase.");
  }

  // Inicialização do display
  display.begin(SSD1306_I2C_ADDRESS, ENDERECO_TELA);
  display.display();
  display.clearDisplay();
  display.display();
}

void loop() {
  // Leitura dos sensores a cada 'intervaloLeituraSensores' milissegundos
  if (millis() - ultimaLeituraSensores >= intervaloLeituraSensores) {
    ultimaLeituraSensores = millis();

    int valorSensorCorrente = analogRead(pinoSensorCorrente);
    int valorSensorTensao = analogRead(pinoSensorTensao);
    
    // Cálculo da tensão
    tensao = valorSensorTensao * (3.3 / 4095);
    tensao = tensao - 1.65;
    tensao = tensao * 220.0;
    tensao = abs(tensao);
    if (tensao > 220.0) {
      tensao = 220.0;
    } else if (tensao < 0) {
      tensao = 0; 
    }
    
    // Cálculo da corrente
    corrente = valorSensorCorrente * (3.3 / 4095);
    corrente = corrente - 1.65;
    corrente = corrente * 5.0;
    corrente = abs(corrente);
    
    // Cálculo da potência
    potencia = (tensao * corrente)/1000;

    // Exibição no Serial Monitor
    Serial.print("Tensão: ");
    Serial.print(tensao);
    Serial.println("V");
    Serial.print("Corrente: ");
    Serial.print(corrente);
    Serial.println("A");
    Serial.print("Potência: ");
    Serial.print(potencia);
    Serial.println("kW");

    // Envio de dados para o Firebase
    FirebaseJson json;
    json.set("/Tensao", tensao);
    json.set("/Corrente", corrente);
    json.set("/Potencia", potencia);
    if (Firebase.RTDB.setJSON(&fbdo, "/Sensor", &json)) {
      Serial.println("Dados enviados com sucesso");
    } else {
      Serial.println("Falha no envio:");
      Serial.println(fbdo.errorReason());
    }
  }

  // Atualização do display a cada 'intervaloAtualizacaoTela' milissegundos
  if (millis() - ultimaAtualizacaoTela >= intervaloAtualizacaoTela) {
    ultimaAtualizacaoTela = millis(); 
    display.clearDisplay();
    display.setTextSize(1.9);      
    display.setTextColor(SSD1306_WHITE); 
    display.setCursor(0,0); 
    display.print("Tensao: ");
    display.print(tensao);
    display.println(" V");
    display.print("Corrente: ");
    display.print(corrente);
    display.println(" A");
    display.print("Potencia: ");
    display.print(potencia);
    display.println(" kW");
    display.display(); 
  }
}
