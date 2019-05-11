#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <dht.h>

#define DHT22_PIN D2
#define COL 16
#define ROW 2

dht DHT;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // nuova libreria

/* Funzione iniziale di configurazione */
void setup() {
  // Inizializzazione del display
  lcd.begin(COL, ROW);
  
  // Attivazione della retroilluminazione
  lcd.setBacklight(HIGH);
}

/* Funzione iterata */
void loop() {
  delay(3000);
  lcd.clear(); // Pulizia del buffer di output del display
  
  // Attivazione della registrazione di temperatura ed umidità
  int chk = DHT.read22(DHT22_PIN);
  
  // Stampa della temperatura
  lcd.print("Temp: " + String(DHT.temperature) + (char)223 + "C");
  
  // Cursore riposizionato sulla seconda riga
  lcd.setCursor(0,1);
  
  // Stampa dell'umidità
  lcd.print("Humidity: " + String(DHT.humidity) + "%");
}
