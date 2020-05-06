#include <SPI.h>
#include <Ethernet.h>
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
byte servidor[] = {10,0,0,X};
EthernetClient clienteArduino;
const int sensorcpfl = A0;
const int sensorgerador = A2;
const int sensorstatus = A4;

int statusnoticacao = 0;
int valorcpfl = 0;
int valorgerador = 0;
int valorstatus = 0;
int notifica = 0;
int status1 = 1;
int statusgerador = 0;

void setup() {
 pinMode (sensorcpfl, INPUT);
 pinMode (sensorgerador, INPUT);
 pinMode (sensorstatus, INPUT);
Serial.begin(9600);
 Ethernet.begin(mac);
 if(Ethernet.begin(mac) == 0){
    Serial.println("Falha ao conectar na rede");
    Ethernet.begin(mac);
  }
  Serial.print("Conectado a Rede, no IP: ");
  Serial.println(Ethernet.localIP());
  Serial.print("Arduino Ligou ");
  notificar(6);
}

//FUNÇÃO QUE NOTIFICA
void notificar(int statusnotficacao){
 if(clienteArduino.connect(servidor,80)){
    clienteArduino.print("GET /arduino/energia/salvar.php");
    clienteArduino.print("?status=");
    clienteArduino.print(statusnotficacao);
    clienteArduino.println(" HTTP/1.0");
    clienteArduino.println("Host: IP DO SEU SERVIDOR");
    clienteArduino.println("Connection: close");
    clienteArduino.println();
    }  
}

//FUNÇÃO NOTIFICA SE ESTA OPERANDO PELA CPFL OU GERADOR
void notificarstatus(int status2){
 if(clienteArduino.connect(servidor,80)){
    clienteArduino.print("GET /arduino/energia/salvar_status.php");
    clienteArduino.print("?status=");
    clienteArduino.print(status2);
    clienteArduino.println(" HTTP/1.0");
    clienteArduino.println("Host: IP DO SEU SERVIDOR");
    clienteArduino.println("Connection: close");
    clienteArduino.println();
    }  
}

void loop() {
    if(!clienteArduino.connected()){
    clienteArduino.stop();
}
valorcpfl = analogRead (sensorcpfl);
valorcpfl = (valorcpfl * 2) / 512; 

valorgerador = analogRead (sensorgerador);
valorgerador = (valorgerador * 2) / 512;

valorstatus = analogRead (sensorstatus);
valorstatus = (valorstatus * 2) / 512;


 if (valorcpfl == 1 ){
    Serial.println("Operando Normal CPFL");
    notificarstatus(1);
    if(statusnoticacao == 2){
       Serial.println ("Notificando...");
       notificar(1);
        statusnoticacao = 1;
      }
    statusnoticacao = 1; 
  }

   if (valorcpfl == 0 ){
    Serial.println("Queda de energia!!");
     if(statusnoticacao == 1){
       Serial.println ("Notificando...");
       notificar(0);      
       statusnoticacao = 2;
      }
   }

      if ((valorcpfl == 1 ) && (valorgerador == 1)){
        Serial.println("Voltou cpfl e gerador ainda ligado!");
        if(statusnoticacao == 2){
          Serial.println ("Notificando...");
          notificar(1);      
          statusnoticacao = 0;
      }
   }

  if (valorgerador == 1 ){
      Serial.println("Gerador Ligou!");
       notificarstatus(2);
     
      if(statusgerador == 1){
        Serial.println ("Notificando...");
        notificar(4);
        statusgerador = 2;
      } 
  }
   
    if (valorgerador == 0 ){
      Serial.println("Gerador Desligado!");
  
      if(statusgerador == 2){
        Serial.println ("Notificando...");
        notificar(5);
      }
      statusgerador = 1;
   }


    if (valorstatus == 1 ){
      Serial.println("Erro no Gerador!");
        if(status1 == 1){
        Serial.println ("Notificando...");
        notificar(2);      
        status1 = 2;
        }
    }

     if (valorstatus == 0 ){
      Serial.println("Gerador sem erro!");
     if(status1 == 2){
       Serial.println ("Notificando...");
       notificar(3);      
       status1 = 1;
     }
    }

Serial.println("**************************************");
       //AGUARDA 2 SEGUNDOS PARA PROXIMA LEITURA.
delay(2000);

 }
