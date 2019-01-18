//#include <ThingSpeak.h>

/*
 * *************************
 * Capteur : DHT11
 *
 * Les broches sont numérotées de la gauche vers la droite lorsque l'on regarde le capteur de face
 *
 * Broche n°1 connectée au +3.3V
 * Broche n°2 (data) connectée à la broche 'D4' du NodeMcu (Pin 2 pour l'arduino) avec une résistance de 10 K reliée au +3.3v
 * Broche n°3 non connectée
 * Broche n°4 connectée à la masse (GND)
 *
 * Installer la bibliothèque 'DHT sensor library by Adarftuit'
 * Cette librairie necessite une librairie supplémentaire qui est disponible à l'adresse : https://github.com/adafruit/Adafruit_Sensor
 * et qui doit être installée selon ce tutoriel : https://learn.adafruit.com/adafruit-all-about-arduino-libraries-install-use/installing-a-library-on-linux
 *
 *  Installer également la bibliothèque ThingSpeak
 */

// Déclaration des librairies
#include <DHT.h>
#include <ESP8266HTTPClient.h>                     // pour communiquer avec le capteur DHT
#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
    char ssid[] = "Al";    //  your network SSID (name)
    char pass[] = "balde111";   // your network password
    int status = WL_IDLE_STATUS;
    WiFiClient  client;
unsigned long myChannelNumber = 659398;
const char * myWriteAPIKey = "AK8KKW5DEY931HGK";

// Préparation du capteur DHT
#define DHTPIN 2                      // broche sur laquelle est raccordée la data du capteur (la broche 'D4' du NodeMcu correspond à la broche 2 de l'arduino)
#define DHTTYPE DHT11                 // précise la référence du capteur DHT (DHT11 ou DHT21 ou DHT22)
DHT dht(DHTPIN, DHTTYPE);             // Initialisation du capteur DHT


// fonction de démarrage
void setup() {
  // Démarrage du bus série
  Serial.begin(115200);               // vitesse
  Serial.println("Bonjour");          // écriture d'un petit message...
  Serial.println("DHT11 et ThingSpeak");

  // Démarrage du capteur DHT11
  dht.begin();


  WiFi.begin(ssid, pass);
  
    while (WiFi.status() != WL_CONNECTED) {
      
    delay(1000);
    
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);
}

// boucle infinie
void loop() {


    HTTPClient http;
    http.begin("http://51.75.126.67/DHT11/store_temp.php"); 
    http.addHeader("Content-Type", "application/json");
    String data = "{\"temperature\":\"22\",\"humidite\":\"45\"}";
    int httpCode = http.POST(data);
    http.end();                  // attendre 1 heure

  float t = dht.readTemperature();    // mesurer la température (en ° Celsius)
  float h = dht.readHumidity();       // mesurer l'humidité (en %)

  // test si des valeurs ont été récupérées
  if (isnan(h) || isnan(t)) {         // si non
    //Serial.println("Failed to read from DHT sensor!");    // affiche un message d'erreur
    return;                           // quitte pour retenter une lecture
  }

  // affichage des valeurs dans le bus série
  Serial.print("Temperature : ");
  Serial.print(t);
  Serial.print(" *C\t");
  Serial.print("Humidité : ");
  Serial.print(h);
  Serial.println(" %");

  ThingSpeak.setField(1,int(t));
  ThingSpeak.setField(2,int(h));
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  delay(20000);
}
