#include <SPI.h>//Carrega biblioteca SD para o módulo de cartão SD
#include <SD.h>

#include <DHT.h> //Carrega a biblioteca DHT para o sensor de temperatura e umidade do ar
#include <DHT_U.h>

#include <virtuabotixRTC.h> //Carrega a biblioteca virtuabotixRTC
virtuabotixRTC myRTC(5, 6, 7); //Determina os pinos ligados ao modulo: (myRTC(clock, data, rst))

// definição de pinos para os sensores
#define sensorU1 A0 //Sensor de umidade do solo 1
#define sensorU2 A1 //Sensor de umidade do solo 2
#define sensorU3 A2 //Sensor de umidade do solo 3
#define sensorDHT A3 //Sensor DHT
#define tipoDHT DHT11 // Informa o tipo de DHT que estamos utilizando
DHT dht(sensorDHT, tipoDHT); // Parametros da biblioteca DHT

File myFile;// Parametro para a biblioteca SD

// definição do escopo de variáveis globais

int leituraMediaSensorU;
int leituraSensorU1;
int leituraSensorU2;
int leituraSensorU3;
float umidade;
float temperatura;


void setup() {
  Serial.begin(9600);

  // definição dos pinos como INPUT ou OUTPUT de dados 
  
  pinMode(sensorU1, INPUT);
  pinMode(sensorU2, INPUT);
  pinMode(sensorU3, INPUT);
  dht.begin(); // Inicia o sensor DHT

  myRTC.setDS1302Time(00, 5, 22, 2, 16, 5, 2022);// APENAS PARA CONFIGURAÇÃO DO RTC, COMENTAR ESSA LINHA APÓS A CONFIGURAÇÃO!!

  Serial.print("Inicializando SD card...");

  if (!SD.begin(4)) { // Checagem sobre a inicialização do SD Card!
    Serial.println("Inicialização do SD falhou!");
    while (1);
  }
  Serial.println("Inicialização do SD completa.");

  
}


void exibirNoMonitorSerial(){
  //Exibir no monitor serial as informações de data e hora.
  
  //Le as informacoes do CI
  myRTC.updateTime(); 

  //Imprime as informacoes no serial monitor
  Serial.print("Data : ");
  Serial.print(myRTC.dayofmonth);
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print("  ");
  Serial.print("Hora : ");
  //Adiciona um 0 caso o valor da hora seja <10
  if (myRTC.hours < 10){
    Serial.print("0");
  }
  Serial.print(myRTC.hours);
  Serial.print(":");
  //Adiciona um 0 caso o valor dos minutos seja <10
  if (myRTC.minutes < 10){
    Serial.print("0");
  }
  Serial.print(myRTC.minutes);
  Serial.print(":");
  //Adiciona um 0 caso o valor dos segundos seja <10
  if (myRTC.seconds < 10){
    Serial.print("0");
  }
  Serial.println(myRTC.seconds);

  
  // Exibir o valor da média dos sensores no monitor serial
  Serial.print("Umidade média do solo:");
  Serial.println(sensorUmidadeSolo());

  // Exibir as informações de temperatura e umidade no monitor serial
  Serial.print("Temperatura:");
  Serial.print(sensorTemperatura());
  Serial.println("ºc");

  Serial.print("Umidade do ar:");
  Serial.print(sensorUmidade());
  Serial.println("%t");

}

int sensorUmidadeSolo(){
  //Função responsável por calcular e retornar o valor médio da umidade do solo
  leituraSensorU1 = analogRead(sensorU1);
  leituraSensorU2 = analogRead(sensorU2);
  leituraSensorU3 = analogRead(sensorU3);
  leituraMediaSensorU = ((leituraSensorU1 + leituraSensorU2 + leituraSensorU3) / 3);


  return leituraMediaSensorU;

}

int sensorTemperatura(){
  // Função que checa o funcionamento do sensor DHT e retorna os valores de temperatura
  temperatura = dht.readTemperature();
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(temperatura)){
    Serial.println("ERRO NA LEITURA DO SENSOR DHT");
  } 
  
  return temperatura;
}

int sensorUmidade(){
  // Função que checa o funcionamento do sensor DHT e retorna os valores de umidade
  umidade = dht.readHumidity();
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(umidade)){
    Serial.println("ERRO NA LEITURA DO SENSOR DHT");
  } 
  
  return umidade;
}

void salvarDados(){

  myFile = SD.open("dados.csv", FILE_WRITE); //Abre o arquivo dados_irrigador.csv para guardar os dados
    
  if (myFile) { //Escrita no arquivo
    Serial.println("Salvando dados em **dados_irrigador.csv**");
    //Escreve informações de data e hora no arquivo
    myFile.print(myRTC.dayofmonth);
    myFile.print("/");
    myFile.print(myRTC.month);
    myFile.print("/");
    myFile.print(myRTC.year);
    myFile.print(",");
  
    if (myRTC.hours < 10){
        myFile.print("0");
      }
      myFile.print(myRTC.hours);
      myFile.print(":");
    //Adiciona um 0 caso o valor dos minutos seja <10
    if (myRTC.minutes < 10){
        myFile.print("0");
      }
    myFile.print(myRTC.minutes);
    myFile.print(":");
    //Adiciona um 0 caso o valor dos segundos seja <10
    if (myRTC.seconds < 10){
        myFile.print("0");
      }
    myFile.print(myRTC.seconds);
    myFile.print(",");

    //Escreve informações dos sensores no arquivo
    myFile.print(sensorUmidadeSolo());
    myFile.print(",");
  
    myFile.print(sensorTemperatura());
    myFile.print(",");
  
    myFile.print(sensorUmidade());
    myFile.println();


    // Terminou de escrever, fecha-se o arquivo:
    myFile.close();

    Serial.println("Dados escritos com sucesso!.");

  }
  else {
    // Se nao deu certo, comeca a dar merda desse ponto
    Serial.println("Nao foi possivel abrir o arquivo");
  }
  
    
}


void loop() {
  myRTC.updateTime(); 
  exibirNoMonitorSerial();
  salvarDados();

  Serial.println("-------------------------------------");

  delay(10000); //delay de 10s para todo o funcionamento do código
  
}
