#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureAxTLS.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureAxTLS.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>
#include <dht.h>

/* Dati per la connessione */
char* ssid = "your_ssid";
char* pass = "your_pass";
char* server = "your_server";

// Sensore DHT22
#define DHT22_PIN D2
dht DHT;
float t = 0, h = 0; //, p = 0; <- TODO: Gestire la pressione

// Gestione connessione al server da parte del client
WiFiClient client;

/* Funzione iniziale */
void setup() {
  Serial.begin(115200);

  // Connessione al router
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connessione alla rete ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);
    delay(10000);
  }

  Serial.println("Connesso");
}

/* Funzione iterativa */
void loop() {
  sendToDatabase();

  // Invio ogni 10 minuti (600000 millisecondi)
  delay(600000);
}

/* Funzione che fa uso dello script PHP, che salva le informazioni nel database del server */
void sendToDatabase() {
  /* Tentativo di Connessione al server */
  Serial.print("Connessione al server ");
  Serial.println(server);
  
  if (client.connect(server, 80)) {
    Serial.println("Connesso");
    
    // Salvataggio di temperatura ed umidità rilevati dal DHT22
    int check = DHT.read22(DHT22_PIN);
    t = DHT.temperature;
    h = DHT.humidity;
    // p = ... <- Registrazione della pressione in quell'istante, prossima implementazione

    // Stampa di t ed h nell'output seriale per verificare la registrazione
    Serial.println("Temperatura: "); Serial.println(String(t));
    Serial.println("Umidità: "); Serial.println(String(h));
    
    /* URL da inviare */
    String url = "GET /weather.php?t=" + String(t);
    url += "&h="; url += String(h);
    //url += "&p="; url += String(p); <- Futuro invio della pressione
    url += " HTTP/1.1";

    /* Invio al server dell'url creato, con successiva interruzione della connessione */
    client.println(url);
    client.println("Host: your_server");
    client.println("Connection: close");
    client.println();
    Serial.println("Connessione terminata con successo");
    Serial.println(url);
    client.stop(); 
  } else { // Se il tentativo di connessione non va a buon fine
    Serial.println("Connessione fallita");
    client.stop();
  }
}
