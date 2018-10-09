//INCLUSÃO DAS BIBLIOTECAS
#include <Ethernet.h>;
#include <MySQL_Connection.h>;
#include <MySQL_Cursor.h>;
#include <SPI.h>;
#include <dht.h>;

//DECLARAÇÃO DA VARIAVEIS
float temperatura;
float umidade;
char vlrtemp[10];
char vlrumid[10];
dht DHT;

//CONFIGURAÇÃO DA PLACA DE REDE
byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress server_addr("IP DO SERVIDOR DE BANCO DE DADOS");

//CONFIGURAÇÃO DA BANCO DE DADOS
char user[] = "USUARIO DO BANCO DE DADOS";              
char password[] = "123456";
char INSERIR_TEMP[] = "INSERT INTO DHT22 (temp,umid) VALUES (%s,%s)";
char BANCODEDADOS[] = "USE "BANCO DE DADOS" ";

//MONTA A COMANDO QUE VAI FAZER E INSERÇÃO NO BANCO DE DADOS
char sentenca[180];

EthernetClient client;
MySQL_Connection conn((Client *)&client);


void setup() {
  Serial.begin(9600);
   while (!Serial); 
   Ethernet.begin(mac_addr);
   Serial.println("Conectando...");
   if (conn.connect(server_addr, 3306, user, password)) 
   {
      delay(1000);
      
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
   DHT.read22(A1);
  temperatura = (DHT.temperature); //recebe a temperatura do sensor
  umidade = (DHT.humidity); //recebe a umidade do sensor
  dtostrf(temperatura, 4, 2, vlrtemp); //converter float para string
  dtostrf(umidade, 4, 2, vlrumid); //converter float para string
  Serial.print("Temperatura: ");
  Serial.println(vlrtemp);
  Serial.print("Umidade: ");
  Serial.println(vlrumid);
  sprintf(sentenca, INSERIR_TEMP, vlrtemp,vlrumid); //recebe o comando sql e os valores de temperatura e umidade.

  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
   cur_mem->execute(sentenca); //executa o comando de inserção no banco.
   delete cur_mem;
 
   delay(300000); //TEMPO DE INSERÇÃO NO BD.
}
