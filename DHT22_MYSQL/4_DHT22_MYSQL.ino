//INCLUSÃO DAS BIBLIOTECAS
#include "DHT.h"
#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <SPI.h>
#define DHTPIN_S1 7
#define DHTPIN_S2 6
#define DHTPIN_S3 5
#define DHTPIN_S4 3
#define DHTTYPE DHT22 



//DECLARAÇÃO DA VARIAVEIS
float temp1;
float temp2;
float temp3;
float temp4;
float umid1;
float umid2;
float umid3;
float umid4;
char vlrtemp1[10];
char vlrtemp2[10];
char vlrtemp3[10];
char vlrtemp4[10];
char vlrumid1[10];
char vlrumid2[10];
char vlrumid3[10];
char vlrumid4[10];

DHT dht_S1(DHTPIN_S1, DHTTYPE);
DHT dht_S2(DHTPIN_S2, DHTTYPE);
DHT dht_S3(DHTPIN_S3, DHTTYPE);
DHT dht_S4(DHTPIN_S4, DHTTYPE);

//CONFIGURAÇÃO DA PLACA DE REDE
byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress server_addr(IP_DO_SERVIDOR_BANCO_DE_DADOS);

//CONFIGURAÇÃO DA BANCO DE DADOS
char user[] = "USUARIO_BD";              
char password[] = "SENHA_USUARIO_BD";
char INSERIR_TEMP[] = "INSERT INTO temp_dht22 (temp_prod,temp_inter,temp_link,temp_saida,umid_prod,umid_inter,umid_link,umid_saida) VALUES (%s,%s,%s,%s,%s,%s,%s,%s)";
char BANCODEDADOS[] = "USE arduino";

//MONTA A COMANDO QUE VAI FAZER E INSERÇÃO NO BANCO DE DADOS
char sentenca[180];

EthernetClient client;
MySQL_Connection conn((Client *)&client);

// função para resetar o arduino em caso de falha de conexão com o banco de dados.
void (*funcReset)() = 0;

void setup() {
  Serial.begin(9600);
  dht_S1.begin();
  dht_S2.begin();
  dht_S3.begin();
  dht_S4.begin();
   while (!Serial); 
   Ethernet.begin(mac_addr);
   Serial.println("Conectando...");
   if (conn.connect(server_addr, 3306, user, password)) 
   {
      //delay(1000);
      
      MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
      cur_mem->execute(BANCODEDADOS);
      delete cur_mem;
   }
   else
   {
      Serial.println("A conexão falhou");
      conn.close();
      
   }

}

void loop() {
  Serial.println("Executando sentença");
  temp1 = dht_S1.readTemperature();
  umid1 = dht_S1.readHumidity();

  temp2 = dht_S2.readTemperature();
  umid2 = dht_S2.readHumidity();

  temp3 = dht_S3.readTemperature();
  umid3 = dht_S3.readHumidity();

  temp4 = dht_S4.readTemperature();
  umid4 = dht_S4.readHumidity();
  
  dtostrf(temp1, 4, 2, vlrtemp1); //converter float para string
  dtostrf(umid1, 4, 2, vlrumid1); //converter float para string
  
  dtostrf(temp2, 4, 2, vlrtemp2); //converter float para string
  dtostrf(umid2, 4, 2, vlrumid2); //converter float para string
  
  dtostrf(temp3, 4, 2, vlrtemp3); //converter float para string
  dtostrf(umid3, 4, 2, vlrumid3); //converter float para string

  dtostrf(temp4, 4, 2, vlrtemp4); //converter float para string
  dtostrf(umid4, 4, 2, vlrumid4); //converter float para string
  
  
  Serial.print("Temperatura: ");
  Serial.println(vlrtemp1);
  Serial.print("Umidade: ");
  Serial.println(vlrumid1);

  Serial.print("Temperatura: ");
  Serial.println(vlrtemp2);
  Serial.print("Umidade: ");
  Serial.println(vlrumid2);

  Serial.print("Temperatura: ");
  Serial.println(vlrtemp3);
  Serial.print("Umidade: ");
  Serial.println(vlrumid3);

  Serial.print("Temperatura: ");
  Serial.println(vlrtemp4);
  Serial.print("Umidade: ");
  Serial.println(vlrumid4);
  
  sprintf(sentenca, INSERIR_TEMP,vlrtemp1,vlrtemp2,vlrtemp3,vlrtemp4,vlrumid1,vlrumid2,vlrumid3,vlrumid4); //recebe o comando sql e os valores de temperatura e umidade.

  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
   cur_mem->execute(sentenca); //executa o comando de inserção no banco.
   delete cur_mem;
  
	//Caso não consiga fazer a inserçaõ no banco de dados irá reiniciar o arduino.
   if(!cur_mem)
   {
    funcReset();
   }
    
 
   delay(300000); //TEMPO DE INSERÇÃO NO BD.
}
