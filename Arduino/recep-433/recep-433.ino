
/* ========== RECEPTOR ===============
   Autor: Marlon Nardi Walendorff
   Data: 28/11/2020
   Projeto: Comunicação entre dois Arduinos sem fio utilizando módulos RF 433Mhz
*/
 
//==== Inclusão de bibliotecas ====//
#include <VirtualWire.h>             
 
//==== Mapemamento de Hardware e constantes =====//
#define pinLEDPot 3
#define pinLEDButton 4
 
//===== Variáveis globais ========//
byte message[VW_MAX_MESSAGE_LEN]; // Um buffer para armazenar as mensagens
byte messageLength = VW_MAX_MESSAGE_LEN; // Tamanho máximo das mensagens recebidas
 
 
void setup()
{
  //Inicia comunicação serialcom velocidade de 9600 BPS
  Serial.begin(9600);
  
  //Entradas/Saídas digitais
  pinMode(pinLEDPot, OUTPUT);
  pinMode(pinLEDButton, OUTPUT);
 
  vw_set_rx_pin(2); //Seleciona o pino para recepção dos dados
  vw_setup(4000);   //Velocidade de comunicação em BPS
  vw_rx_start();    //Começa a receber os dados
  
}//endSetup
 
void loop()
{
  if (vw_get_message(message, &messageLength))// Se houver dados para receber
  {
 
    analogWrite(pinLEDPot, message[0]);// Controle PWM no pino pinLEDPot
 
    if (message[1] == 1)// Se o segundo byte do vetor message for igual a um...
    {
      digitalWrite(pinLEDButton, LOW);// Desliga o LED no pino pinLEDButton
    }
    else 
      {
      digitalWrite(pinLEDButton, HIGH);// Liga o LED no pino pinLEDButton
      }
     
    Serial.print("PWM: ");
    Serial.print(message[0]);
    Serial.print("   Button: ");
    Serial.println(message[1]);
  }
 
}//endLoop
