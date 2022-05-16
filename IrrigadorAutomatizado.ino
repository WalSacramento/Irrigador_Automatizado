#include <virtuabotixRTC.h> //Carrega a biblioteca virtuabotixRTC
virtuabotixRTC myRTC(5, 6, 7); //Determina os pinos ligados ao modulo: (myRTC(clock, data, rst))

// definição de pinos para os sensores
#define sensorU1 A0
#define sensorU2 A1
#define sensorU3 A2

// definição do escopo de variáveis globais

int leituraMediaSensorU;
int leituraSensorU1;
int leituraSensorU2;
int leituraSensorU3;


void setup() {
  Serial.begin(9600);

  // definição dos pinos como INPUT ou OUTPUT de dados 
  
  pinMode(sensorU1, INPUT);
  pinMode(sensorU2, INPUT);
  pinMode(sensorU3, INPUT);

}

void loop() {

  exibirNoMonitorSerial();

  delay(10000); //delay para todo o código em loop
  
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
  Serial.print("MEDIA DOS SENSORES:");
  Serial.print(sensorUmidadeSolo());
  Serial.println();
  
}

int sensorUmidadeSolo(){
  
  leituraSensorU1 = analogRead(sensorU1);
  leituraSensorU2 = analogRead(sensorU2);
  leituraSensorU3 = analogRead(sensorU3);
  leituraMediaSensorU = ((leituraSensorU1 + leituraSensorU2 + leituraSensorU3) / 3);


  return leituraMediaSensorU;

}
