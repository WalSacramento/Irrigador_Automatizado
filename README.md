# Irrigador Automatizado
Este projeto é um irrigador automatizado desenvolvido como TCC no IFAL e contém código desenvolvido em Arduino.

## Recursos
### Comunicação com o usuário através de LEDS:
* LED que indica se o nível de umidade do solo está acima ou abaixo do limite configurado.
* LED que indica se a bomba d'água está em funcionamento.

### Envio de logs de dados ao computador conectado via comunicação serial, incluindo:
* Indicação se o SD card foi inicializado ou não.
* Data e hora atual.
* Valor de umidade média do solo.
* Temperatura em graus Celsius.
* Umidade do ar.
* Indicação se a bomba d'água está ligada ou não.
* Identificação de erros em sensores via monitor serial.
* Armazenamento de dados coletados pelos sensores em um arquivo .csv no SD card.
* Possibilidade de análise e criação de gráficos e apresentações a partir dos dados coletados.

## Instruções de Uso
1. Conecte o Arduino ao computador.
2. Abra o monitor serial para verificar os dados enviados pelo irrigador.
3. Configure os parâmetros de acordo com suas necessidades (umidade do solo, tempo de atualização, etc.).
4. Inicie o sistema e verifique o funcionamento através dos LEDS e do monitor serial.
5. Os dados coletados serão armazenados no SD card para análise posterior.
