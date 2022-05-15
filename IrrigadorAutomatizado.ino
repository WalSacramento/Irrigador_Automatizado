#include <virtuabotixRTC.h> //Carrega a biblioteca virtuabotixRTC
virtuabotixRTC myRTC(5, 6, 7); //Determina os pinos ligados ao modulo: (myRTC(clock, data, rst))




void setup() {
  Serial.begin(9600);

}

void loop() {
 horario();

}

int horario(){
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
  if (myRTC.hours < 10)
  {
    Serial.print("0");
  }
  Serial.print(myRTC.hours);
  Serial.print(":");
  //Adiciona um 0 caso o valor dos minutos seja <10
  if (myRTC.minutes < 10)
  {
    Serial.print("0");
  }
  Serial.print(myRTC.minutes);
  Serial.print(":");
  //Adiciona um 0 caso o valor dos segundos seja <10
  if (myRTC.seconds < 10)
  {
    Serial.print("0");
  }
  Serial.println(myRTC.seconds);

  delay( 1000);
}
